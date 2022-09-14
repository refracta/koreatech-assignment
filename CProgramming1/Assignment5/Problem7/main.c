#include <stdio.h>

/*
 * 7. 사용자에게 정수를 입력받고, 1에서부터 입력받은 정수까지의 수 중 3의 배수인 수의 합을 출력하는 프로그램을 while문을 이용해 작성하시오.
 */
int main() {
    int integer;
    printf("정수를 입력하시오: ");
    scanf("%d", &integer);
    int i = 1;
    int sum = 0;
    while (i < integer) {
        sum += i % 3 == 0 ? i : 0;
        i++;
    }
    printf("%d", sum);
}
