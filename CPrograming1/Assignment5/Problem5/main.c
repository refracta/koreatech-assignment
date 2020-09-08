#include <stdio.h>
#include <math.h>

/*
 * 5. 사용자로부터 7자리 정수를 입력받고, 각각 자리의 수를 반대로 출력하는 프로그램을 while문을 이용해 작성하시오.
 */
int main() {
    int N;
    printf("7자리 정수를 입력하시오: ");
    scanf("%d", &N);

    int lastPow = floor(log10(N));
    int i = 0;
    while (i <= lastPow) {
        int digit = N % 10;
        printf("%d", digit);
        N -= digit;
        N /= 10;
        i++;
    }
}
