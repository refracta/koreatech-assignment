#include <stdio.h>

/**
 * p^n을 계산한다
 * @param p 밑(∈R)
 * @param n 지수(∈Z)
 * @return 계산된 p^n값
 */
int expo(int p, int n) {
    int result = 1;
    while (n--) {
        result *= p;
    }
    return result;
}

/**
 * 사용자로부터 2개의 수를 입력받고, 첫번째 수를 두번째 수만큼 곱한 결과를 계산하는 expo() 함수를 작성하고, 결과를 출력하는 프로그램을 작성하시오. expo() 함수의 입력은 2개의 정수, 반환값은 2개 입력 정수의 곱을 나타내는 정수로 한다.
 */
int main() {
    int number1, number2;
    printf("두 수를 입력하시오: ");
    scanf("%d %d", &number1, &number2);
    printf("%d", expo(number1, number2));
}

