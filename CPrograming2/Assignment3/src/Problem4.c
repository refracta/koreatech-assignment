/**
  @file Problem4.c
  @brief Lab3-4. 이 프로젝트는 몇 달이 걸리나요? (이재홍 조교)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief 업무의 개수입니다.
 */
#define NUMBER_OF_JOBS 10
/**
 * @brief 업무당 포함된 일의 개수입니다.
 */
#define NUMBER_OF_WORKS 10
/**
 * @brief 직원 수입니다.
 */
#define NUMBER_OF_EMPLOYEES 5

/**
 * @brief 직원의 Man Month가 저장되는 배열입니다.
 */
int employees[NUMBER_OF_EMPLOYEES];
/**
 * @brief 업무당 할당된 일이 저장되는 2차원 배열입니다.
 */
int jobsArray[NUMBER_OF_JOBS][NUMBER_OF_WORKS] = { 0, };

/**
 * @brief 예제에 정의된 함수의 동일 명세 구현체입니다.
 */
int work(const int jobs[], const int manMonth, const int numJobs) {
    int totalTime = 0;
    for (int i = 0; i < numJobs; i++) {
        totalTime += jobs[i] / manMonth;
    }
    return totalTime;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_JOBS; i++) {
        for (int j = 0; j < NUMBER_OF_WORKS; j++) {
            jobsArray[i][j] = rand() % 100 + 1;
        }
    }
    printf("Man Month를 입력하시오: ");
    scanf("%d %d %d %d %d", &employees[0], &employees[1], &employees[2], &employees[3], &employees[4]);

    int totalTime[NUMBER_OF_EMPLOYEES] = { 0, };
    // 프로젝트 시간 계산용 합계 저장 배열

    for (int i = 0; i < NUMBER_OF_JOBS; i++) {
        int employeeIndex = i % NUMBER_OF_EMPLOYEES;
        int workTime = work(jobsArray[i], employees[employeeIndex], NUMBER_OF_JOBS);
        totalTime[employeeIndex] += workTime;
        printf("%d번째 직원이 %d번째 업무를 하는 데에 %d개월 걸렸다.\n", employeeIndex + 1, i + 1, workTime);
    }

    int projectTime = 0;
    for(int i = 0; i < NUMBER_OF_EMPLOYEES; i++){
        projectTime < totalTime[i] ? projectTime += totalTime[i] : 0;
    }
    printf("이 프로젝트는 %d개월 걸렸다.\n", projectTime);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}