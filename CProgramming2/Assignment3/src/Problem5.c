/**
  @file Problem5.c
  @brief Lab3-5. ������ ���� ����⣨����� ����)
*/

#include <stdio.h>
#include "FilterFunction.h"
#define DATA_LENGTH 100

/**
 * @brief ������ �����Դϴ�.
 */
#define FILTER_SIZE 5

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main(void)
{
    int inputData[DATA_LENGTH] = { 0, };
    genData(inputData, DATA_LENGTH, DATA_MAX);
    int outputData[DATA_LENGTH] = { 0, };
    printf("**** Input Data ****\n");
    printData(inputData, DATA_LENGTH, DATA_MAX);
    // Apply filter here
    // Caution: You should not make another array for this problem
    for(int i = 0 ; i < DATA_LENGTH; i++){
        outputData[i] = inversionFilter(smoothingFilter(inputData, DATA_LENGTH, i, FILTER_SIZE));
    }
    // inputData�� ���͸� ������ ������ outputData�� �ʱ�ȭ�մϴ�.

    printf("\n\n**** Output Data ****\n");
    printData(outputData, DATA_LENGTH, DATA_MAX);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
    return 0;
}