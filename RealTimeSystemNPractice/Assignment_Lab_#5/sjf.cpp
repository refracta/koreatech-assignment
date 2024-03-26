#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>

using namespace std;

// 프로세스 정보를 담는 구조체
struct process {
    int pid; // 프로세스 ID
    int arrival_time; // 도착 시간
    int burst_time; // 실행 시간
    int start_time; // 시작 시간
    int completion_time; // 완료 시간
    int turnaround_time; // 반환 시간
    int waiting_time; // 대기 시간
    int response_time; // 응답 시간
};

int main() {

    int n; // 프로세스의 수
    struct process p[100]; // 프로세스 배열
    float avg_turnaround_time; // 평균 반환 시간
    float avg_waiting_time; // 평균 대기 시간
    float avg_response_time; // 평균 응답 시간
    float cpu_utilisation; // CPU 사용률
    int total_turnaround_time = 0; // 총 반환 시간
    int total_waiting_time = 0; // 총 대기 시간
    int total_response_time = 0; // 총 응답 시간
    int total_idle_time = 0; // 총 유휴 시간
    float throughput; // 처리량
    int is_completed[100]; // 완료 상태 배열
    memset(is_completed, 0, sizeof(is_completed)); // 완료 상태 초기화

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n; // 프로세스 수 입력

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time; // 도착 시간 입력
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time; // 실행 시간 입력
        p[i].pid = i + 1; // 프로세스 ID 할당
        cout << endl;
    }

    int current_time = 0; // 현재 시간
    int completed = 0; // 완료된 프로세스 수
    int prev = 0; // 이전 프로세스의 완료 시간

    // 모든 프로세스가 완료될 때까지
    while (completed != n) {
        int idx = -1;
        int mn = 10000000;
        // 현재 시간 이전에 도착한, 아직 완료되지 않은 프로세스 중에서
        // 가장 짧은 실행 시간을 가진 프로세스를 찾기
        for (int i = 0; i < n; i++) {
            // 현재 시간 이전에 도착했고, 아직 완료되지 않은 프로세스인지 확인
            if (p[i].arrival_time <= current_time && is_completed[i] == 0) {
                // 해당 프로세스의 실행 시간이 현재까지 찾은 가장 짧은 실행 시간보다 짧은 경우
                if (p[i].burst_time < mn) {
                    mn = p[i].burst_time; // 가장 짧은 실행 시간 업데이트
                    idx = i; // 선택된 프로세스의 인덱스 업데이트
                }
                // 만약 실행 시간이 같다면, 더 빨리 도착한 프로세스를 선택
                if (p[i].burst_time == mn) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time; // 가장 짧은 실행 시간 업데이트
                        idx = i; // 선택된 프로세스의 인덱스 업데이트
                    }
                }
            }
        }
        if (idx != -1) {
            // 선택된 프로세스의 시작 시간, 완료 시간 등 계산
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            // 총 시간들을 계산
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            // 프로세스 완료 표시
            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        } else {
            current_time++; // 아직 실행할 프로세스가 없는 경우 시간을 증가
        }

    }

    // 전체 프로세스 중 가장 빠른 도착 시간과 가장 늦은 완료 시간을 찾는 부분
    int min_arrival_time = 10000000; // 가장 빠른 도착 시간을 찾기 위한 초기 값 설정
    int max_completion_time = -1; // 가장 늦은 완료 시간을 찾기 위한 초기 값 설정

    for (int i = 0; i < n; i++) {
        // 모든 프로세스를 순회하며
        // 현재까지의 최소 도착 시간과 비교하여 더 작은 값을 min_arrival_time에 저장
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);

        // 현재까지의 최대 완료 시간과 비교하여 더 큰 값을 max_completion_time에 저장
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    // 프로세스 상세 정보 및 평균 시간, CPU 사용률, 처리량 출력
    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);

    cout << endl << endl;

    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t"
             << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t"
             << p[i].response_time << "\t" << "\n" << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl;
}

/*
AT - 프로세스의 도착 시간
BT - 프로세스의 실행 시간
ST - 프로세스의 시작 시간
CT - 프로세스의 완료 시간
TAT - 프로세스의 반환 시간
WT - 프로세스의 대기 시간
RT - 프로세스의 응답 시간

사용된 공식들:

TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/
