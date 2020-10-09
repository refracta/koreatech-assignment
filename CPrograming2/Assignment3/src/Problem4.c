/**
  @file Problem4.c
  @brief Lab3-4. �� ������Ʈ�� �� ���� �ɸ�����? (����ȫ ����)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief ������ �����Դϴ�.
 */
#define NUMBER_OF_JOBS 10
/**
 * @brief ������ ���Ե� ���� �����Դϴ�.
 */
#define NUMBER_OF_WORKS 10
/**
 * @brief ���� ���Դϴ�.
 */
#define NUMBER_OF_EMPLOYEES 5

/**
 * @brief ������ Man Month�� ����Ǵ� �迭�Դϴ�.
 */
int employees[NUMBER_OF_EMPLOYEES];
/**
 * @brief ������ �Ҵ�� ���� ����Ǵ� 2���� �迭�Դϴ�.
 */
int jobsArray[NUMBER_OF_JOBS][NUMBER_OF_WORKS] = { 0, };

/**
 * @brief ������ ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
int work(const int jobs[], const int manMonth, const int numJobs) {
    int totalTime = 0;
    for (int i = 0; i < numJobs; i++) {
        totalTime += jobs[i] / manMonth;
    }
    return totalTime;
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_JOBS; i++) {
        for (int j = 0; j < NUMBER_OF_WORKS; j++) {
            jobsArray[i][j] = rand() % 100 + 1;
        }
    }
    printf("Man Month�� �Է��Ͻÿ�: ");
    scanf("%d %d %d %d %d", &employees[0], &employees[1], &employees[2], &employees[3], &employees[4]);

    int totalTime[NUMBER_OF_EMPLOYEES] = { 0, };
    // ������Ʈ �ð� ���� �հ� ���� �迭

    for (int i = 0; i < NUMBER_OF_JOBS; i++) {
        int employeeIndex = i % NUMBER_OF_EMPLOYEES;
        int workTime = work(jobsArray[i], employees[employeeIndex], NUMBER_OF_JOBS);
        totalTime[employeeIndex] += workTime;
        printf("%d��° ������ %d��° ������ �ϴ� ���� %d���� �ɷȴ�.\n", employeeIndex + 1, i + 1, workTime);
    }

    int projectTime = 0;
    for(int i = 0; i < NUMBER_OF_EMPLOYEES; i++){
        projectTime < totalTime[i] ? projectTime += totalTime[i] : 0;
    }
    printf("�� ������Ʈ�� %d���� �ɷȴ�.\n", projectTime);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}