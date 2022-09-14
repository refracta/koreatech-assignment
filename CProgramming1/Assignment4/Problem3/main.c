#include <stdio.h>
#include <math.h>

/**
 * 3. 세 자리 십진수를 입력받고 각 자리의 숫자들이 각각 짝수인지, 홀수인지, 0인지 출력하는 프로그램을 작성하세요.
 */
void runAssignment3() {
    printf("세 자리 십진수를 입력하시오: ");
    int number;
    scanf("%d", &number);
    for (int i = floor(log10(number)); i >= 0; i--) {
        int powI = pow(10, i);
        int digit = number / powI;
        printf("%d: ", digit);
        printf(digit == 0 ? "0" : (digit % 2 == 0 ? "짝수" : "홀수"));
        if (i != 0) {
            printf(", ");
        }
        number -= digit * powI;
    }
}

int main() {
    runAssignment3();
}
