#include <stdio.h>

/**
 * 5. 피타고라스 정리를 이용해 두 직각변의 길이를 사용자로부터 입력 받아 빗변의 길이를 계산해 출력하는 프로그램을 작성하라.
 */
long double sqrt(long double a);

double powByInteger(long double p, int n);

void runAssignment5() {
    long double a, b;
    printf("직각변의 길이를 입력하시오(cm): ");
    scanf("%Lf", &a);
    printf("직각변의 길이를 입력하시오(cm): ");
    scanf("%Lf", &b);
    printf("빗변의 길이는 %Lfcm입니다.", sqrt(powByInteger(a, 2) + powByInteger(b, 2)));
}


/**
 * Babylonian 법을 이용하여 제곱근을 계산한다.
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
 * @param x0 임의의 양의 실수 x0
 * @param a 제곱근을 구할 양의 실수
 * @return 근사된 제곱근 값
 */

long double babylonianSqrt(long double x0, long double a, int repeat) {
    long double xn = x0;

    for (int i = 0; i < repeat; i++) {
        xn = 1.0 / 2 * (xn + a / xn);
    }
    return xn;
}

/**
 * 한가지 매개변수만을 이용하여 Babylonian 법으로 제곱근을 계산한다.
 * @param a 제곱근을 구할 양의 실수
 * @return 근사된 제곱근 값
 */
const int SQRT_PRECISION = 10;

long double sqrt(long double a) {
    long double x0 = 0;
    while (x0 * x0 <= a) {
        x0 += 0.1;
    }
    return babylonianSqrt(x0, a, SQRT_PRECISION);
}

/**
 * p^n을 계산한다
 * @param p 밑(∈R)
 * @param n 지수(∈Z)
 * @return 계산된 p^n값
 */
double powByInteger(long double p, int n) {
    long double result = 1;
    while (n--) {
        result *= p;
    }
    return result;
}


int main() {
    runAssignment5();
}
