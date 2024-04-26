#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <getopt.h>
#include <time.h>

#define MIN(a, b) (((a)<(b))?(a):(b))

// 상수 정의
#define MAX_PROCESSORS 10  // 최대 프로세서 수
#define MAX_PROCESSES 1000  // 최대 프로세스 수
#define DEFAULT_N 2  // 기본 프로세서 수
#define DEFAULT_SAP 'M'  // 기본 스케줄링 접근 방식 (멀티큐)
#define DEFAULT_QS "RM"  // 기본 큐 선택 방식 (라운드 로빈)
#define DEFAULT_ALG "RR"  // 기본 스케줄링 알고리즘 (라운드 로빈)
#define DEFAULT_Q 20  // 기본 타임 퀀텀
#define DEFAULT_INFILE "in.txt"  // 기본 입력 파일
#define DEFAULT_OUTMODE 1  // 기본 출력 모드
#define DEFAULT_OUTFILE "out.txt"  // 기본 출력 파일
#define DEFAULT_T 200  // 기본 T 값
#define DEFAULT_T1 10  // 기본 T1 값
#define DEFAULT_T2 1000  // 기본 T2 값
#define DEFAULT_L 100  // 기본 L 값
#define DEFAULT_L1 10  // 기본 L1 값
#define DEFAULT_L2 500  // 기본 L2 값
#define DEFAULT_PC 10  // 기본 프로세스 수
#define MAX_SIMULATION_TIME 30.0  // 최대 시뮬레이션 시간

// 데이터 구조체
typedef struct burst {
    int pid;  // 프로세스 ID
    int burst_length;  // burst 길이
    double arrival_time;  // 도착 시간
    double start_time;  // 시작 시간
    double real_start_time;  // 실제 시작 시간
    double remaining_time;  // 남은 시간
    double finish_time;  // 완료 시간
    double turnaround_time;  // 반환 시간
    double waiting_time;  // 대기 시간
    double response_time;  // 응답 시간
    int cpu_id;  // 실행된 CPU ID
    char finished;  // 완료 여부
    struct burst *next;  // 다음 burst를 가리키는 포인터
} Burst;

typedef struct {
    Burst *head;  // 큐의 헤드
    Burst *tail;  // 큐의 테일
} Queue;

typedef struct {
    pthread_mutex_t lock;  // 뮤텍스 락
    Queue queue;  // 큐
} MutexQueue;

// 전역 변수
int n_processors = DEFAULT_N;  // 프로세서 수
char sap = DEFAULT_SAP;  // 스케줄링 접근 방식
char qs[3] = DEFAULT_QS;  // 큐 선택 방식
char alg[5] = DEFAULT_ALG;  // 스케줄링 알고리즘
char infile[256] = DEFAULT_INFILE;  // 입력 파일 이름
int outmode = DEFAULT_OUTMODE;  // 출력 모드
char outfile[256] = DEFAULT_OUTFILE;  // 출력 파일 이름
int T = DEFAULT_T, T1 = DEFAULT_T1, T2 = DEFAULT_T2;  // T, T1, T2 값
int L = DEFAULT_L, L1 = DEFAULT_L1, L2 = DEFAULT_L2;  // L, L1, L2 값
int PC = DEFAULT_PC;  // 프로세스 수
int Q = DEFAULT_Q;  // 타임 퀀텀
bool random_flag = false;  // 랜덤 플래그
MutexQueue mutex_queues[MAX_PROCESSORS];  // 프로세서별 뮤텍스 큐
pthread_t processor_threads[MAX_PROCESSORS];  // 프로세서 스레드
Queue finished_bursts;  // 완료된 burst의 큐
pthread_mutex_t finished_bursts_lock;  // 완료된 burst 큐에 대한 뮤텍스 락
int completed_processes = 0;  // 완료된 프로세스 수
pthread_mutex_t completed_processes_lock;  // 완료된 프로세스 수에 대한 뮤텍스 락
double max_simulation_time = MAX_SIMULATION_TIME;  // 최대 시뮬레이션 시간

// 함수 원형
void parse_arguments(int argc, char *argv[]);

void initialize_simulation();

void read_input_file();

void create_random_bursts();

void *processor_thread(void *arg);

void enqueue(Queue *queue, Burst *burst);

Burst *dequeue(Queue *queue);

Burst *dequeue_valid_burst(Queue *queue, double current_time);

Burst *peek(Queue *queue);

Burst *find_shortest_job(Queue *queue, double current_time);

int queue_length(Queue *queue);

bool is_queue_empty(Queue *queue);

void output_simulation_results();

double get_wall_clock_time();

double simulation_start_time;

int main(int argc, char *argv[]) {
    parse_arguments(argc, argv);
    // 명령줄 인자 파싱
    initialize_simulation();
    // 시뮬레이션 초기화

    // 랜덤 플래그가 설정되어 있으면 랜덤 burst 생성, 아니면 입력 파일 읽기
    if (random_flag) {
        create_random_bursts();
    } else {
        read_input_file();
    }

    simulation_start_time = get_wall_clock_time();
    // 시뮬레이션 시작 시간 기록

    // 각 프로세서에 대한 스레드 생성
    for (int i = 0; i < n_processors; i++) {
        pthread_create(&processor_threads[i], NULL, processor_thread, (void *) (long) i);
    }

    // 모든 프로세서 스레드가 완료될 때까지 대기
    for (int i = 0; i < n_processors; i++) {
        pthread_join(processor_threads[i], NULL);
    }

    output_simulation_results();
    // 시뮬레이션 결과 출력

    return 0;
    // 프로그램 종료
}

void *processor_thread(void *arg) {
    int cpu_id = (int) (long) arg;  // 스레드에 할당된 CPU ID를 가져옴
    MutexQueue *mutex_queue = &mutex_queues[cpu_id];  // 해당 CPU ID에 해당하는 큐를 가져옴

    while (true) {
        Burst *burst = NULL;
        double current_time = (get_wall_clock_time() - simulation_start_time) * 1000;  // 현재 시뮬레이션 시간 계산

        // 해당 큐가 비어있지 않은 경우
        if (!is_queue_empty(&mutex_queue->queue)) {
            // 스케줄링 알고리즘에 따라 다음 실행할 burst를 가져옴
            if (strcmp(alg, "RR") == 0) {  // 라운드 로빈 알고리즘
                burst = dequeue_valid_burst(&mutex_queue->queue, current_time);
            } else if (strcmp(alg, "SJF") == 0) {  // 최단 작업 우선 알고리즘
                burst = find_shortest_job(&mutex_queue->queue, current_time);
            } else if (strcmp(alg, "FCFS") == 0) {  // 선입 선출 알고리즘
                burst = dequeue_valid_burst(&mutex_queue->queue, current_time);
            }
        }

        // 실행할 burst가 존재하는 경우
        if (burst != NULL) {
            if (strcmp(alg, "RR") == 0) {  // 라운드 로빈 스케줄링
                burst->cpu_id = cpu_id;  // CPU ID 설정
                Burst *copy_burst = (Burst *) malloc(sizeof(Burst));  // burst 사본 생성
                *copy_burst = *burst;
                copy_burst->start_time = (get_wall_clock_time() - simulation_start_time) * 1000;  // 시작 시간 설정
                burst->real_start_time = copy_burst->real_start_time =  // 실제 시작 시간 설정
                        copy_burst->real_start_time == 0 ? copy_burst->start_time : MIN(copy_burst->real_start_time,
                                                                                        copy_burst->start_time);

                // 타임 퀀텀보다 남은 시간이 긴 경우
                if (copy_burst->remaining_time > Q) {
                    usleep(Q * 1000);  // 타임 퀀텀만큼 대기
                    copy_burst->remaining_time = burst->remaining_time -= Q;  // 남은 시간 감소
                    copy_burst->finish_time = (get_wall_clock_time() - simulation_start_time) * 1000;  // 완료 시간 갱신
                    enqueue(&mutex_queue->queue, burst);  // burst를 다시 큐에 추가
                } else {
                    // 타임 퀀텀 이내에 완료될 경우
                    usleep((int) burst->remaining_time * 1000);  // 남은 시간만큼 대기
                    copy_burst->remaining_time = burst->remaining_time = 0;  // 남은 시간을 0으로 설정
                    copy_burst->finish_time = (get_wall_clock_time() - simulation_start_time) * 1000;  // 완료 시간 설정
                    copy_burst->turnaround_time = copy_burst->finish_time - burst->arrival_time;  // 반환 시간 계산
                    copy_burst->waiting_time = copy_burst->turnaround_time - copy_burst->burst_length;  // 대기 시간 계산
                    copy_burst->response_time = copy_burst->real_start_time - copy_burst->arrival_time;  // 응답 시간 계산
                    copy_burst->finished = 'Y';  // 완료 플래그 설정
                    completed_processes++;  // 완료된 프로세스 수 증가
                }
                enqueue(&finished_bursts, copy_burst);  // 결과 큐에 burst 복사본 추가
            } else {
                // SJF 또는 FCFS 스케줄링의 경우
                burst->cpu_id = cpu_id;
                burst->start_time = burst->real_start_time = (get_wall_clock_time() - simulation_start_time) * 1000;
                usleep(burst->remaining_time * 1000);  // burst의 남은 시간만큼 대기
                burst->finish_time = (get_wall_clock_time() - simulation_start_time) * 1000;  // 완료 시간 설정
                burst->turnaround_time = burst->finish_time - burst->arrival_time;  // 반환 시간 계산
                burst->waiting_time = burst->turnaround_time - burst->burst_length;  // 대기 시간 계산
                burst->response_time = burst->real_start_time - burst->arrival_time;  // 응답 시간 계산
                burst->finished = 'Y';  // 완료 플래그 설정
                enqueue(&finished_bursts, burst);  // 결과 큐에 burst 추가
                completed_processes++;  // 완료된 프로세스 수 증가
            }
        }

        // 최대 시뮬레이션 시간을 초과한 경우 반복문 종료
        if (get_wall_clock_time() - simulation_start_time > max_simulation_time) {
            break;
        }
    }

    return NULL;
}

void parse_arguments(int argc, char *argv[]) {
    int opt;  // 옵션을 저장할 변수

    // 명령줄 옵션을 정의한 구조체 배열
    static struct option long_options[] = {
            {"n_processors",         required_argument, 0, 'n'},
            {"assignment_policy",    required_argument, 0, 'a'},
            {"scheduling_algorithm", required_argument, 0, 's'},
            {"infile",               required_argument, 0, 'i'},
            {"outmode",              required_argument, 0, 'm'},
            {"outfile",              required_argument, 0, 'o'},
            {"random",               required_argument, 0, 'r'},
            {"time",                 required_argument, 0, 't'},
            {0, 0,                                      0, 0}
    };

    // getopt_long 함수를 이용하여 명령줄 인자를 순차적으로 파싱
    while ((opt = getopt_long(argc, argv, "n:a:s:i:m:o:r:t:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'n':  // 프로세서 수 설정
                n_processors = atoi(optarg);
                break;
            case 'a':  // 할당 정책 설정
                sscanf(optarg, "%c %2s", &sap, qs);
                qs[sizeof(qs) - 1] = '\0';
                break;
            case 's':  // 스케줄링 알고리즘 설정
                sscanf(optarg, "%4s %d", alg, &Q);
                alg[sizeof(alg) - 1] = '\0';
                break;
            case 'i':  // 입력 파일 이름 설정
                strncpy(infile, optarg, sizeof(infile) - 1);
                infile[sizeof(infile) - 1] = '\0';
                break;
            case 'm':  // 출력 모드 설정
                outmode = atoi(optarg);
                break;
            case 'o':  // 출력 파일 이름 설정
                strncpy(outfile, optarg, sizeof(outfile) - 1);
                outfile[sizeof(outfile) - 1] = '\0';
                break;
            case 'r':  // 랜덤 모드 설정
                sscanf(optarg, "%d %d %d %d %d %d %d", &T, &T1, &T2, &L, &L1, &L2, &PC);
                random_flag = true;
                break;
            case 't':  // 최대 시뮬레이션 시간 설정
                max_simulation_time = atoi(optarg);
                break;
            default:  // 알 수 없는 옵션에 대한 처리
                printf("Usage: %s [-n N] [-a \"SAP QS\"] [-s \"ALG Q\"] [-i INFILE] [-m OUTMODE] [-o OUTFILE] [-r \"T T1 T2 L L1 L2 PC\"]\n",
                       argv[0]);
                exit(1);
        }
    }
}

// 시뮬레이션 초기화 함수
void initialize_simulation() {
    // 각 프로세서에 대한 뮤텍스 큐 초기화
    for (int i = 0; i < MAX_PROCESSORS; i++) {
        pthread_mutex_init(&mutex_queues[i].lock, NULL);  // 뮤텍스 초기화
        mutex_queues[i].queue.head = NULL;  // 큐의 head 초기화
        mutex_queues[i].queue.tail = NULL;  // 큐의 tail 초기화
    }
    // 완료된 프로세스와 burst를 위한 뮤텍스 초기화
    pthread_mutex_init(&completed_processes_lock, NULL);
    pthread_mutex_init(&finished_bursts_lock, NULL);
    finished_bursts.head = NULL;  // 완료된 burst 큐의 head 초기화
    finished_bursts.tail = NULL;  // 완료된 burst 큐의 tail 초기화
}

// 입력 파일 읽기 함수
void read_input_file() {
    FILE *file = fopen(infile, "r");  // 입력 파일 열기
    if (file == NULL) {
        perror("Error opening input file");  // 파일 열기 오류 처리
        exit(1);
    }

    // 파일에서 프로세스 정보 읽기
    int pid, burst_length, arrival_time;
    while (fscanf(file, "%d %d %d", &pid, &burst_length, &arrival_time) == 3) {
        Burst *burst = (Burst *) malloc(sizeof(Burst));  // 새 burst 메모리 할당
        // burst 정보 설정
        burst->pid = pid;
        burst->burst_length = burst_length;
        burst->arrival_time = arrival_time;
        burst->remaining_time = burst_length;
        burst->start_time = 0;
        burst->real_start_time = 0;
        burst->finish_time = 0;
        burst->turnaround_time = 0;
        burst->waiting_time = 0;
        burst->response_time = 0;
        burst->cpu_id = -1;
        burst->finished = 'N';
        burst->next = NULL;

        // 할당 정책에 따라 burst를 큐에 추가
        if (sap == 'S') {  // 싱글 큐
            enqueue(&mutex_queues[0].queue, burst);
        } else if (sap == 'M') {  // 멀티 큐
            int target_queue;
            if (strcmp(qs, "RM") == 0) {  // 라운드 로빈 방식
                target_queue = pid % n_processors;
            } else if (strcmp(qs, "LM") == 0) {  // 부하 균형 방식
                target_queue = 0;
                int min_queue_length = queue_length(&mutex_queues[0].queue);
                for (int i = 1; i < n_processors; i++) {
                    int current_queue_length = queue_length(&mutex_queues[i].queue);
                    if (current_queue_length < min_queue_length) {
                        min_queue_length = current_queue_length;
                        target_queue = i;
                    }
                }
            }
            enqueue(&mutex_queues[target_queue].queue, burst);
        }
    }
    fclose(file);  // 파일 닫기
}

// 랜덤 burst 생성 함수
void create_random_bursts() {
    srand(time(NULL));  // 랜덤 시드 설정

    // 지정된 수의 burst를 랜덤하게 생성
    for (int i = 0; i < T; i++) {
        int pid = i;
        int burst_length = rand() % (T2 - T1 + 1) + T1;
        int arrival_time = rand() % (L2 - L1 + 1) + L1;
        Burst *burst = (Burst *) malloc(sizeof(Burst));  // 새 burst 메모리 할당
        // burst 정보 설정
        burst->pid = pid;
        burst->burst_length = burst_length;
        burst->arrival_time = arrival_time;
        burst->remaining_time = burst_length;
        burst->start_time = 0;
        burst->real_start_time = 0;
        burst->finish_time = 0;
        burst->turnaround_time = 0;
        burst->waiting_time = 0;
        burst->response_time = 0;
        burst->cpu_id = -1;
        burst->finished = 'N';
        burst->next = NULL;

        // 할당 정책에 따라 burst를 큐에 추가
        if (sap == 'S') {  // 싱글 큐
            enqueue(&mutex_queues[0].queue, burst);
        } else if (sap == 'M') {  // 멀티 큐
            int target_queue;
            if (strcmp(qs, "RM") == 0) {  // 라운드 로빈 방식
                target_queue = pid % n_processors;
            } else if (strcmp(qs, "LM") == 0) {  // 부하 균형 방식
                target_queue = 0;
                int min_queue_length = queue_length(&mutex_queues[0].queue);
                for (int i = 1; i < n_processors; i++) {
                    int current_queue_length = queue_length(&mutex_queues[i].queue);
                    if (current_queue_length < min_queue_length) {
                        min_queue_length = current_queue_length;
                        target_queue = i;
                    }
                }
            }
            enqueue(&mutex_queues[target_queue].queue, burst);
        }
    }
}

// 큐에 burst 추가 함수
void enqueue(Queue *queue, Burst *burst) {
    // 큐가 비어있으면 burst를 head와 tail로 설정
    if (queue->tail == NULL) {
        queue->head = burst;
        queue->tail = burst;
    } else {
        // 그렇지 않으면 tail 다음에 burst 추가
        queue->tail->next = burst;
        queue->tail = burst;
    }
    burst->next = NULL;  // 다음 burst 없음으로 설정
}

// 큐에서 burst 제거 함수
Burst *dequeue(Queue *queue) {
    Burst *burst = queue->head;  // 큐의 head를 가져옴
    if (burst != NULL) {
        queue->head = burst->next;  // head를 다음 burst로 설정
        if (queue->head == NULL) {
            queue->tail = NULL;  // 큐가 비어있으면 tail도 NULL로 설정
        }
    }
    return burst;  // 제거된 burst 반환
}

// (도착 시간이) 유효한 burst를 꺼내는 함수
Burst *dequeue_valid_burst(Queue *queue, double current_time) {
    int count = 0;
    // 큐를 순회하며 현재 시간 이전에 도착한 burst 탐색
    for (Burst *burst = queue->head; burst != NULL; burst = burst->next, count++) {
        if (burst->arrival_time <= current_time) {
            // 도착 시간이 현재 시간보다 이전인 경우, 해당 burst를 제거
            for (int i = 0; i < count; i++) {
                enqueue(queue, dequeue(queue));
            }
            return dequeue(queue);
        }
    }
    return NULL;  // 해당하는 burst가 없는 경우 NULL 반환
}

// 큐의 head 확인 함수
Burst *peek(Queue *queue) {
    return queue->head;  // 큐의 head 반환
}

// 최단 작업 찾기 함수
Burst *find_shortest_job(Queue *queue, double current_time) {
    Burst *prev = NULL;
    Burst *shortest_prev = NULL;
    Burst *shortest = NULL;
    double min_remaining_time = DBL_MAX;

    // 큐의 각 burst를 순회하며 최단 작업을 찾음
    for (Burst *burst = queue->head; burst != NULL; prev = burst, burst = burst->next) {
        // 현재 시간 이전에 도착한 burst 중 남은 시간이 가장 짧은 burst를 찾음
        if (burst->arrival_time <= current_time && burst->remaining_time < min_remaining_time) {
            min_remaining_time = burst->remaining_time;
            shortest = burst;
            shortest_prev = prev;
        }
    }

    // 찾은 최단 burst를 큐에서 제거
    if (shortest_prev != NULL) {
        shortest_prev->next = shortest->next;
    } else if (shortest != NULL) {
        queue->head = shortest->next;
    }

    if (shortest == queue->tail) {
        queue->tail = shortest_prev;
    }

    return shortest;
}

// 현재 벽시계 시간을 가져오는 함수
double get_wall_clock_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);  // 현재 시간을 가져옴
    return tp.tv_sec + tp.tv_usec * 1e-6;  // 초 및 마이크로초를 합하여 반환
}

// 시뮬레이션 결과를 출력하는 함수
void output_simulation_results() {
    FILE *output_file = NULL;
    // 출력 모드에 따라 파일을 열거나 표준 출력을 사용
    if (outmode != 1) {
        output_file = fopen(outfile, "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            exit(1);
        }
    }

    // 평균 대기 시간, 평균 응답 시간, 평균 반환 시간 계산
    double average_turnaround_time = 0.0;
    double average_waiting_time = 0.0;
    double average_response_time = 0.0;
    int burst_count = 0;
    for (Burst *burst = finished_bursts.head; burst != NULL; burst = burst->next) {
        if (burst->finished == 'Y') {
            average_turnaround_time += burst->turnaround_time;
            average_waiting_time += burst->waiting_time;
            average_response_time += burst->response_time;
            burst_count++;
        }
    }
    average_turnaround_time /= burst_count;
    average_waiting_time /= burst_count;
    average_response_time /= burst_count;

    // 계산된 평균값을 출력
    if (outmode == 1 || outmode == 3) {
        printf("Average_Turnaround_Time: %lf, Average_Waiting_Time: %lf, Average_Response_Time: %lf\n",
               average_turnaround_time, average_waiting_time, average_response_time);
        // 테이블 헤더 출력
        printf("%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\t%-15s\t%-20s\t%-20s\t%-20s\t%-10s\n",
               "Burst_ID", "CPU_ID", "Burst_Length", "Arrival_Time", "Real_Start_Time",
               "Start_Time", "Finish_Time", "Turnaround_Time", "Waiting_Time", "Response_Time", "Finished");
    }
    if (outmode == 2 || outmode == 3) {
        // 파일에 결과를 출력
        fprintf(output_file, "Average_Turnaround_Time: %lf, Average_Waiting_Time: %lf, Average_Response_Time: %lf\n",
                average_turnaround_time, average_waiting_time, average_response_time);
        fprintf(output_file, "%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\t%-15s\t%-20s\t%-20s\t%-20s\t%-10s\n",
                "Burst_ID", "CPU_ID", "Burst_Length", "Arrival_Time", "Real_Start_Time",
                "Start_Time", "Finish_Time", "Turnaround_Time", "Waiting_Time", "Response_Time", "Finished");
    }

    // 각 burst에 대한 상세 정보를 출력
    for (Burst *burst = finished_bursts.head; burst != NULL; burst = burst->next) {
        if (outmode == 1 || outmode == 3) {
            printf("%-10d\t%-10d\t%-15d\t%-15.2lf\t%-20.2lf\t%-15.2lf\t%-15.2lf\t%-20.2lf\t%-20.2lf\t%-20.2lf\t%-10c\n",
                   burst->pid,
                   burst->cpu_id,
                   burst->burst_length,
                   burst->arrival_time,
                   burst->real_start_time,
                   burst->start_time,
                   burst->finish_time,
                   burst->turnaround_time,
                   burst->waiting_time,
                   burst->response_time,
                   burst->finished);
        }
        if (outmode == 2 || outmode == 3) {
            fprintf(output_file,
                    "%-10d\t%-10d\t%-15d\t%-15.2lf\t%-20.2lf\t%-15.2lf\t%-15.2lf\t%-20.2lf\t%-20.2lf\t%-20.2lf\t%-10c\n",
                    burst->pid,
                    burst->cpu_id,
                    burst->burst_length,
                    burst->arrival_time,
                    burst->real_start_time,
                    burst->start_time,
                    burst->finish_time,
                    burst->turnaround_time,
                    burst->waiting_time,
                    burst->response_time,
                    burst->finished);
        }
    }

    // 파일이 열려있으면 닫음
    if (output_file != NULL) {
        fclose(output_file);
    }
}

// 큐의 길이를 반환하는 함수
int queue_length(Queue *queue) {
    int length = 0;
    Burst *current = queue->head;

    // 큐를 순회하며 길이 계산
    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

// 큐가 비어있는지 확인하는 함수
bool is_queue_empty(Queue *queue) {
    return queue->head == NULL;
}