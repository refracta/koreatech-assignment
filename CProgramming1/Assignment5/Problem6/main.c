#include <stdio.h>

/*
 * 6. 1에서 30까지의 정수 중 홀수 만을 출력하는 프로그램을 while문을 이용해 작성하시오.
 */
int main() {
    int i = 1;
    while (i <= 30) {
        i % 2 == 1 ? printf("%d ", i) : 0;
        i++;
    }
}
