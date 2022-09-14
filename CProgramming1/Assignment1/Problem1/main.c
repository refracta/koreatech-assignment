#include <stdio.h>

static long double PI;
typedef enum Boolean {
    false, true
};

/**
 * 1. 사용자로부터 반지름의 길이를 입력 받아 원의 넓이를 계산하여 출력하는 프로그램을 작성하라.
 * π로 수렴하는 무한급수인 Bailey-Borwein-Plouffe 공식을 이용하여 PI를 계산한다.
 * https://en.wikipedia.org/wiki/Bailey-Borwein-Plouffe_formula
 */
long double powByInteger(long double p, int n);

void runAssignment1() {
    printf("반지름을 입력하시오(cm): ");
    long double radius;
    scanf("%Lf", &radius);
    long double area = PI * powByInteger(radius, 2);
    printf("원의 넓이는 %Lfcm^2입니다.", area);
}

/**
 * p^n을 계산한다
 * @param p 밑(∈R)
 * @param n 지수(∈Z)
 * @return 계산된 p^n값
 */
long double powByInteger(long double p, int n) {
    long double result = 1;
    while (n--) {
        result *= p;
    }
    return result;
}

/**
 * k값에 따른 BBP 수열의 한 항을 계산한다.
 * @param k 대입하여 계산할 k의 값
 * @return 수열의 계산된 한 항
 */
long double getBBPResult(int k) {
    int _8k = 8 * k;
    long double result = 4.0 / (_8k + 1) - 2.0 / (_8k + 4) - 1.0 / (_8k + 5) - 1.0 / (_8k + 6);
    for (int i = 0; i < k; i++) {
        result /= 16;
    }
    return result;
}

/**
 * 위끝 k값까지의 BBP 급수를 계산한다
 * @param k 위끝 k값
 * @return 근사된 PI값
 */
long double calculatePI(int k) {
    long double result = 0;
    for (int i = 0; i < k + 1; i++) {
        result += getBBPResult(i);
    }
    return result;
}

/**
 * 과제에서 제시된 상수 PI 값을 구한다
 * @param k 위끝 k값
 * @return 과제에서 제시된 상수로 절삭된 근사된 PI값
 */
double calculateAssignmentFormPI(int k) {
    return (int) (calculatePI(k) * 100) / 100.0;
}

const USE_ASSIGNMENT_PI = true;
const int PI_PRECISION = 100;

void init() {
    PI = USE_ASSIGNMENT_PI ? calculateAssignmentFormPI(PI_PRECISION) : calculatePI(PI_PRECISION);
}

int main() {
    init();
    runAssignment1();
}
