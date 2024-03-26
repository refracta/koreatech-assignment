#include <stdio.h>

/**
 * 2. 사용자로부터 두 개의 실수를 입력 받은 후, 두 수의 곱을 계산하여 화면에 출력하는 프로그램을 작성하라.
 */
void runAssignment2() {
    long double real1;
    long double real2;
    printf("실수를 입력하시오: ");
    scanf("%Lf", &real1);
    printf("실수를 입력하시오: ");
    scanf("%Lf", &real2);
    printf("두 수의 곱은 %Lf입니다.", real1 * real2);
}

int main() {
    runAssignment2();
}
