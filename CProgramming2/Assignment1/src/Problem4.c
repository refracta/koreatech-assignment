/**
  @file Problem4.c
  @brief Lab1-4. ���б����� (����ȫ ����)
  */
#include <stdio.h>

/**
 * @brief �����Լ� f(x) = ax^2 + bx + c
 * @param a x^2 ���� ���
 * @param b x ���� ���
 * @param c �����
 * @param x ������ x��
 */
double f(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

/**
 * @brief f(x) = ax^2 + bx + c�� A���� B���� ��ġ�����Ͽ� �� ���� ��ȯ�Ѵ�.
 * @param a x^2 ���� ���
 * @param b x ���� ���
 * @param c �����
 * @param n ������ ����
 */
double integrateFx(double a, double b, double c, double A, double B, int n) {
    double sum = 0;
    for (int x = 1; x <= n; x++) {
        sum += f(a, b, c, A + (B - A) * x / n) * (B - A) / n;
    }
    return sum;
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    double a, b, c, A, B;
    printf("Integrate[ax^2 + bx + c, {x, A, B}]:\n");
    printf(" a b c A B: ");
    scanf("%lf %lf %lf %lf %lf", &a, &b, &c, &A, &B);
    printf("  =%lf", integrateFx(a, b, c, A, B, 10000));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
