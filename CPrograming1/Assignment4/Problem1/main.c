#include <stdio.h>

/**
 * 1. 사용자에게 두 수를 입력받고, 두 수의 곱이 100 이상인지 아닌지 출력하는 프로그램을 작성하라.
 */
void runAssignment1() {
    int x, y;
    printf("두 수를 입력하시오:");
    scanf("%d %d", &x, &y);
    printf("100 이상");
    printf(x * y > 100 ? "입니다." : "이 아닙니다.");

}

int main() {
    runAssignment1();
}
