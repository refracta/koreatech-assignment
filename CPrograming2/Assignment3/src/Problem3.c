/**
  @file Problem3.c
  @brief Lab3-3. ī�� ���� & ī�� ã�⣨�迵�� ����)
*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/**
 * @brief 1~100������ ������ ���� �����մϴ�.
 * @return 1~100������ ������ ��
 */
int generateRandomValue() {
    return rand() % 100 + 1;
}

/**
 * @brief ���糭�� ���� �õ带 �ʱ�ȭ�մϴ�.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief ������ ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
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
 * @brief ������ ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
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
 * @brief ������ ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
void printArray(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf(i == 0 ? "%d" : " %d", a[i]);
    }
}

/**
 * @brief ���� �Լ��Դϴ�.
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
    printf("%d(��)�� �迭�� �����ϴ��� Ȯ��\n", findTarget);
    findIndex == -1 ? printf("�ش� ���� �������� �ʽ��ϴ�.") : printf("�迭�� %d��° �ε����� ���� a[%d] = %d", findIndex, findIndex, findTarget);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
