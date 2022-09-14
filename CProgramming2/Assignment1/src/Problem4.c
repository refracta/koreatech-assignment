/**
  @file Problem4.c
  @brief Lab1-4. 구분구적법 (이재홍 조교)
  */
#include <stdio.h>

/**
 * @brief 이차함수 f(x) = ax^2 + bx + c
 * @param a x^2 항의 계수
 * @param b x 항의 계수
 * @param c 상수항
 * @param x 대입할 x값
 */
double f(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

/**
 * @brief f(x) = ax^2 + bx + c를 A부터 B까지 수치적분하여 그 값을 반환한다.
 * @param a x^2 항의 계수
 * @param b x 항의 계수
 * @param c 상수항
 * @param n 구간의 갯수
 */
double integrateFx(double a, double b, double c, double A, double B, int n) {
    double sum = 0;
    for (int x = 1; x <= n; x++) {
        sum += f(a, b, c, A + (B - A) * x / n) * (B - A) / n;
    }
    return sum;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    double a, b, c, A, B;
    printf("Integrate[ax^2 + bx + c, {x, A, B}]:\n");
    printf(" a b c A B: ");
    scanf("%lf %lf %lf %lf %lf", &a, &b, &c, &A, &B);
    printf("  =%lf", integrateFx(a, b, c, A, B, 10000));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
