#include <stdio.h>
#include <math.h>

/**
 * 1. 다섯 자리로 이루어진 숫자를 입력받고 각각의 자릿수를 분리해 출력하는 프로그램을 작성하라.
 */
void runAssignment1() {
    printf("다섯 자리 수를 입력하시오: ");
    int number;
    scanf("%d", &number);
    for (int i = floor(log10(number)); i >= 0; i--) {
        int powI = pow(10, i);
        int digit = number / powI;
        printf("%d", digit);
        if (i != 0) {
            printf(", ");
        }
        number -= digit * powI;
    }
}

int main() {
    runAssignment1();
}
