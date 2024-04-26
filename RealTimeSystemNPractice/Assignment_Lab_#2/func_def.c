#include <stdio.h>
#include "edf.h"

/**
 * 주어진 task 배열을 초기화한다. 사용자의 입력에 따라 도착 시간(Arrival time), 실행 시간(Execution time), 마감 시간(Deadline time), 주기(Peroid)의 값이 할당되며, task 구조체의 기타 변수들은 기본값(0)을 할당한다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 */
void get_tasks(task *t1, int n) {
    int i = 0;
    while (i < n) {
        printf("Enter Task %d parameters\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &t1->T[arrival]);
        printf("Execution time: ");
        scanf("%d", &t1->T[execution]);
        printf("Deadline time: ");
        scanf("%d", &t1->T[deadline]);
        printf("Period: ");
        scanf("%d", &t1->T[period]);
        t1->T[abs_arrival] = 0;
        t1->T[execution_copy] = 0;
        t1->T[abs_deadline] = 0;
        t1->instance = 0;
        t1->alive = 0;
        t1++;
        i++;
    }
}

/**
 * 주어진 task 배열의 주기 값들의 최소 공배수를 계산하여 반환한다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 * @return 주기 값들의 최소 공배수 (hyperperoid)
 */
int hyperperiod_calc(task *t1, int n) {
    int i = 0, ht, a[10];
    while (i < n) {
        a[i] = t1->T[period];
        t1++;
        i++;
    }
    ht = lcm(a, n);

    return ht;
}

/**
 * 유클리드 호제법을 이용하여 재귀적으로 최대 공약수를 구하여 반환한다.
 * @param a 최대 공약수를 구할 대상 첫 번째 수
 * @param b 최대 공약수를 구할 대상 두 번째 수
 * @return a와 b의 최대 공약수
 */
int gcd(int a, int b) {
    if (b == 0)
        return a;
        // b가 0이면 a가 최대 공약수임
    else
        return gcd(b, a % b);
        // a를 b로 나눈 나머지와 함께 재귀 호출
}

/**
 * 배열에 있는 모든 정수의 최소 공배수를 구한다.
 * @param a 최소 공배수를 구할 정수 배열
 * @param n 배열의 길이
 * @return 배열에 있는 모든 정수의 최소 공배수
 */
int lcm(int *a, int n) {
    int res = 1, i;
    for (i = 0; i < n; i++) {
        res = res * a[i] / gcd(res, a[i]);
        // 현재 값(res)과 배열의 각 원소의 최소 공배수를 구하기 위해
        // 두 수를 곱한 다음 최대 공약수로 나눈다
    }
    return res;
}

/**
 * 주어진 task 배열과 주어진 특정 시간에 스케줄링 될 task가 있는지 여부를 반환한다.
 * @param t1 task 배열
 * @param tmr 현재 스케줄링이 진행되는 시간
 * @param n task 배열의 길이
 * @return 스케줄링 될 task가 있는지에 대한 여부
 */
int sp_interrupt(task *t1, int tmr, int n) {
    int i = 0, n1 = 0, a = 0;
    task *t1_copy;
    t1_copy = t1;
    // 초기 t1의 위치를 저장하는 변수

    while (i < n) {
        if (tmr == t1->T[abs_arrival]) {
            // 절대 도착 시간이 현재 스케줄링 시간과 같으면
            t1->alive = 1;
            // task를 살아있는 상태로 변경
            a++;
            // 살아있는 task의 수를 a에 집계
        }
        t1++;
        i++;
    }

    t1 = t1_copy;
    i = 0;

    while (i < n) {
        // 전체 task에 대해서 살아있지 않은(죽어있는) task의 수를 n1에 집계
        if (t1->alive == 0) {
            n1++;
        }
        t1++;
        i++;
    }

    // 전체 task가 죽어있거나, 살아있는 task가 하나도 없는 경우
    if (n1 == n || a != 0) {
        return 1;
        // 참 값을 반환
    }

    return 0;
    // 거짓 값을 반환
}

/**
 * 주어진 task 배열의 각 task의 절대 마감 시간(T[abs_deadline])을 설정한다.
 * `절대 마감 시간 = 마감 시간 + 절대 도착 시간`으로 계산된다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 * @param all 전체 지정을 위한 플래그, 0이면 현재 task의 값만, 0이 아니면 task 배열 전체의 값에 로직을 적용한다.
 */
void update_abs_deadline(task *t1, int n, int all) {
    int i = 0;
    if (all) {
        while (i < n) {
            t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
            t1++;
            i++;
        }
    } else {
        t1 += n;
        t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
    }
}

/**
 * 주어진 task 배열의 각 task의 절대 도착 시간(T[abs_arrival])을 설정한다.
 * `절대 도착 시간 = 도착 시간 + 절대 도착 시간 계수 * 주기`로 계산된다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 * @param k 절대 도착 시간 계수
 * @param all 전체 지정을 위한 플래그, 0이면 현재 task의 값만, 0이 아니면 task 배열 전체의 값에 로직을 적용한다.
 */
void update_abs_arrival(task *t1, int n, int k, int all) {
    int i = 0;
    if (all) {
        while (i < n) {
            t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);
            t1++;
            i++;
        }
    } else {
        t1 += n;
        t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);
    }
}

/**
 * 주어진 task 배열의 각 task에 대해 실행 시간(T[execution]) 값을, 실행 시간 값 사본(T[execution_copy])으로 복사한다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 * @param all 전체 지정을 위한 플래그, 0이면 현재 task의 값만, 0이 아니면 task 배열 전체의 값에 로직을 적용한다.
 */
void copy_execution_time(task *t1, int n, int all) {
    int i = 0;
    if (all) {
        while (i < n) {
            t1->T[execution_copy] = t1->T[execution];
            t1++;
            i++;
        }
    } else {
        t1 += n;
        t1->T[execution_copy] = t1->T[execution];
    }
}

/**
 * 주어진 task 배열에서 살아있는(alive == 1) task의 T 배열의 p 색인에 할당된 값 대해 가장 작은 값을 가지는 task의 색인을 반환한다.
 * @param t1 task 배열
 * @param n task 배열의 길이
 * @param p T 배열의 색인
 * @return task 배열의 살아있는 task 중, T 배열의 p 색인의 값이 가장 작은 task 색인
 */
int min(task *t1, int n, int p) {
    int i = 0, min = 0x7FFF, task_id = IDLE_TASK_ID;
    while (i < n) {
        if (min > t1->T[p] && t1->alive == 1) {
            min = t1->T[p];
            task_id = i;
        }
        t1++;
        i++;
    }
    return task_id;
}

/**
 * 주어진 task 배열에서 CPU 이용률의 정의 U=sum(C_i/P_i, 1, n)에 따라 CPU 이용률을 계산하여 반환한다.
 * @param t1 task 구조체 배열
 * @param n task 배열의 길이
 * @return CPU 이용률
 */
float cpu_util(task *t1, int n) {
    int i = 0;
    float cu = 0;
    while (i < n) {
        cu = cu + (float) t1->T[execution] / (float) t1->T[period];
        t1++;
        i++;
    }
    return cu;
}
