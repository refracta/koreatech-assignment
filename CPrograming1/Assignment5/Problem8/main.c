#include <stdio.h>


/*
 * 8. 1부터 x까지의 합이 10000을 넘지 않는 가장 큰 합을 구해 출력하고, 그 때의 x를 출력하는 프로그램을 while문을 이용해 작성하시오.
 */
int main() {
    int maxValue = 0;
    int k = 1;
    while (k++) {
        int newMax = k * (k + 1) / 2;
        if (newMax <= 10000) {
            maxValue = newMax;
        } else {
            k--;
            break;
        }
    }
    printf("%d, %d", maxValue, k);
}
