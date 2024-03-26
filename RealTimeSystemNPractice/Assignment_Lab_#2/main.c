#include <stdio.h>
#include <malloc.h>
#include "edf.h"

// 마이크로컨트롤러의 타이머와 유사한 타이머
// 스케줄링 로직에서 지금 참조하고 있는 시간을 나타낸다.
int timer = 0;

int main() {
    task *t;
    int n, hyper_period, active_task_id;
    float cpu_utilization;
    // 프로그램에 필요한 변수 선언부
    // task 배열 (t), task 배열의 길이 (n), hyper_peroid, 활성 task 번호 (active_task_id), CPU 이용률(cpu_utilization)을 선언한다

    printf("Enter number of tasks\n");
    scanf("%d", &n);
    // task 개수 입력
    t = malloc(n * sizeof(task));
    get_tasks(t, n);
    // task 배열 초기화
    cpu_utilization = cpu_util(t, n);
    printf("CPU Utilization %f\n", cpu_utilization);
    // CPU 이용률 계산 및 출력

    if (cpu_utilization < 1) {
        // CPU 이용률이 1 미만인지 확인하여, 스케줄이 가능하면 계속 진행
        printf("Tasks can be scheduled\n");
    } else {
        // 스케줄이 불가능한 경우 종료 코드 -1과 함께 프로그램 종료
        printf("Schedule is not feasible\n");
        return -1;
    }
    hyper_period = hyperperiod_calc(t, n);
    // 주기 값들의 최소 공배수 계산
    copy_execution_time(t, n, ALL);
    // 각 task의 실행 시간을 실행 시간 사본 변수(잔여 실행 시간 변수)로 복사
    update_abs_arrival(t, n, 0, ALL);
    // 절대 도착 시간 계산
    update_abs_deadline(t, n, ALL);
    // 절대 마감 시간 계산

    while (timer <= hyper_period) {
        // task 배열에 포함된 task들의 가장 큰 주기(hyper_peroid)보다 timer가 작을 때 계속한다.

        if (sp_interrupt(t, timer, n)) {
            // 해당 timer 시간에 스케줄링(활성화) 될 task가 있는지 확인
            active_task_id = min(t, n, abs_deadline);
            // 현재 시간에 활성화될 task의 id를 구한다.
            // 현재 시간에 활성화될 task는 task 배열의 모든 task 중 절대 마감 시간이 가장 작은 task이다. (EDF 스케줄링은 마감 시간까지 남은 시간이 가장 짧은 task의 작업이 먼저 스케줄 됨)
        }

        if (active_task_id == IDLE_TASK_ID) {
            // 현재 시간에 활성화 될 task가 없는 경우
            printf("%d  Idle\n", timer);
            // 현재 시간에 대해 유후 상태임을 출력
        }

        if (active_task_id != IDLE_TASK_ID) {
            // 현재 시간에 활성화 될 task가 있는 경우
            if (t[active_task_id].T[execution_copy] != 0) {
                // 현재 활성화된 task의 남은 실행 시간(execution_copy)이 존재하면
                t[active_task_id].T[execution_copy]--;
                // 남은 실행 시간을 1만큼 감소
                printf("%d  Task %d\n", timer, active_task_id + 1);
                // 현재 시간에 해당 Task를 실행함을 출력
            }

            if (t[active_task_id].T[execution_copy] == 0) {
                // 현재 활성화된 task의 남은 실행 시간(execution_copy)이 존재하지 않으면
                t[active_task_id].instance++;
                // instance (task의 실행 횟수)를 1 증가
                t[active_task_id].alive = 0;
                // 죽은 task로 상태 변경

                copy_execution_time(t, active_task_id, CURRENT);
                // 현재 활성화된 task의 남은 실행 시간 갱신
                update_abs_arrival(t, active_task_id, t[active_task_id].instance, CURRENT);
                // 현재 활성화된 task의 절대 도착 시간 계수를 task의 실행 횟수(instance)로 하여 갱신
                update_abs_deadline(t, active_task_id, CURRENT);
                // 현재 활성화된 task의 절대 마감 시간 갱신
                active_task_id = min(t, n, abs_deadline);
                // active_task_id를 갱신
            }
        }
        ++timer;
        // 타이머를 1 증가
    }
    free(t);
    // task 배열 메모리 해제
    return 0;
}
