/**
  @file Problem5.c
  @brief Lab3-5. 데이터 필터 만들기（김덕수 교수)
*/

#include <stdio.h>
#include "FilterFunction.h"
#define DATA_LENGTH 100

/**
 * @brief 필터의 길이입니다.
 */
#define FILTER_SIZE 5

/**
 * @brief 시작 함수입니다.
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
    // inputData에 필터를 적용한 값으로 outputData를 초기화합니다.

    printf("\n\n**** Output Data ****\n");
    printData(outputData, DATA_LENGTH, DATA_MAX);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
    return 0;
}