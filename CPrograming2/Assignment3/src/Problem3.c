/**
  @file Problem3.c
  @brief Lab3-3. 카드 셔플 & 카드 찾기（김영우 조교)
*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/**
 * @brief 1~100까지의 무작위 수를 생성합니다.
 * @return 1~100까지의 무작위 수
 */
int generateRandomValue() {
    return rand() % 100 + 1;
}

/**
 * @brief 유사난수 생성 시드를 초기화합니다.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief 예제에 정의된 함수의 동일 명세 구현체입니다.
 */
int find(int a[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (a[i] == value) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief 예제에 정의된 함수의 동일 명세 구현체입니다.
 */
void randomGenerate(int a[], int size) {
    int index = 0;
    while (index < size) {
        int randomValue = generateRandomValue();
        if (find(a, size, randomValue) >= 0) {
            continue;
        }
        a[index++] = randomValue;
    }
}
/**
 * @brief 예제에 정의된 함수의 동일 명세 구현체입니다.
 */
void printArray(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf(i == 0 ? "%d" : " %d", a[i]);
    }
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    initRand();
    int a[100] = { 0, };
    int randomLimit = 30;
    randomGenerate(a, randomLimit);
    printArray(a, randomLimit);
    printf("\n");
    int findTarget = 30;
    int findIndex = find(a, randomLimit, findTarget);
    printf("%d(이)가 배열에 존재하는지 확인\n", findTarget);
    findIndex == -1 ? printf("해당 값이 존재하지 않습니다.") : printf("배열의 %d번째 인덱스에 존재 a[%d] = %d", findIndex, findIndex, findTarget);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
