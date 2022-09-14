/**
  @file Problem3.c
  @brief Lab4-3. 반복문없이 구구단 출력하기（이재홍 조교)
*/
#include <stdio.h>

/**
 * @brief 재귀적 방법을 통해 구구단을 출력합니다.
 */
void printTable(int m, int n) {
    !(n > 9) ? (printf("%d * %d = %d\n", m, n, m * n), 0) || (printTable(m, n + 1), 0) : 0;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    int m;
    printTable((scanf("%d", &m), m), 1);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
