#include <stdio.h>
#include <math.h>

/*
 * 2. 사용자로부터 3자리 정수를 입력받고, 각 자리수가 홀수인지 짝수인지 출력하는 프로그램을 switch문을 이용해 작성하시오.
 */
int main() {
    int N;
    printf("3자리 정수를 입력하시오: ");
    scanf("%d", &N);
    for (int i = floor(log10(N)); i >= 0; i--) {
        int powI = pow(10, i);
        int digit = N / powI;

        printf(digit % 2 == 0 ? "%d의 자리: 짝수" : "%d의 자리: 홀수", powI);
        if (i != 0) {
            printf(", ");
        }
        N -= digit * powI;
    }
}
