/**
  @file Problem3.c
  @brief Lab4-3. �ݺ������� ������ ����ϱ⣨����ȫ ����)
*/
#include <stdio.h>

/**
 * @brief ����� ����� ���� �������� ����մϴ�.
 */
void printTable(int m, int n) {
    !(n > 9) ? (printf("%d * %d = %d\n", m, n, m * n), 0) || (printTable(m, n + 1), 0) : 0;
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    int m;
    printTable((scanf("%d", &m), m), 1);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
