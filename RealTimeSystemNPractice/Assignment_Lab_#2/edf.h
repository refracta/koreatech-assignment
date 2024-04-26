// T 배열의 접근 색인 상수들

#define arrival			0
// 도착 시간의 색인
#define execution 		1
// 실행 시간의 색인
#define deadline		2
// 마감 시간의 색인
#define period			3
// 주기의 색인
#define abs_arrival		4
// 절대 도착 시간의 색인
#define execution_copy  5
// 실행 시간 사본(잔여 실행 시간)의 색인
#define abs_deadline	6
// 절대 마감 시간의 색인


// task 구조체
typedef struct
{
	int T[7],instance,alive;
/*
		사용자에게 주어지는 task 매개변수들
		T[0] == T[arrival]  			(도착 시간, Arrival time)
		T[1] == T[execution]			(실행 시간, Execution time)
		T[2] == T[deadline] 			(마감 시간, Deadline time)
		T[3] == T[period]  			    (주기, Period)
	
		These task parameters are internal to the program
		T[4] == T[abs_arrival]  		(절대 도착 시간, Absolute Arrival time)
		T[5] == T[execution_copy]	(실행 시간 사본 = 잔여 실행 시간, Execution time copy)
		T[6] == T[abs_deadline]  	(절대 마감 시간, Absolute Deadline time)

		instance (실행 횟수, 시간=0 부터 task가 도착한 횟수)
		alive (task가 준비되었는지의 여부, 0은 준비되지 않음, 1은 준비됨)
*/
}task;

#define IDLE_TASK_ID 1023
// 해당 시간에 할당된 task가 없음을 표현하기 위해 사용하는 유후 task 번호 (1023으로 임의 배정됨)
#define ALL 1
// 전체 지정을 위한 플래그 상수
#define CURRENT 0
// 단일 요소 지정을 위한 플래그 상수

void get_tasks(task *t1,int n);
// task 매개변수들을 가져온다 - 도착 시간, 실행 시간, 마감 시간, 주기
int hyperperiod_calc(task *t1,int n);
// task 배열의 hyperperoid를 계산한다.
float cpu_util(task *t1,int n);
// CPU 사용률을 계산한다.
int gcd(int a, int b);
// 최대 공약수를 계산한다.
int lcm(int *a, int n);
// 최소 공배수를 계산한다.
int sp_interrupt(task *t1,int tmr,int n);
// 스케줄링 포인트 인터럽트
int min(task *t1,int n,int p);
// 주어진 task 매개변수 중 최솟값을 찾는다.
void update_abs_arrival(task *t1,int n,int k,int all);
// 절대 도착 시간을 갱신한다. (절대 도착 시간 = 도착 시간 + instance * 주기)
void update_abs_deadline(task *t1,int n,int all);
// 절대 마감 시간을 갱신한다 (절대 마감 시간 = 절대 도착 시간 + 마감 시간)
void copy_execution_time(task *t1,int n,int all);
// 실행 시간의 백업 복사본을 유지한다.

