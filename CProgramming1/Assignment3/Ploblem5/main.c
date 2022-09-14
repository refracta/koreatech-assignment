#include <stdio.h>

/**
 * 5. 두 개의 10진수 정수를 입력받아 비트 연산자 AND, OR, XOR를 이용하여 연산을 수행하고 연산 결과를 아래의 식에 대입해 결과를 출력하는 프로그램을 작성하라.
 */

void runAssignment5() {
    int x, y;
    printf("두 수를 입력하시오: ");
    scanf("%d %d", &x, &y);
    printf("%lf", ((x & y) + (x | y)) / (double) (x ^ y));
}

int main() {
    runAssignment5();
}
