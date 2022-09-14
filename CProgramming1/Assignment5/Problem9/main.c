#include <stdio.h>

/*
 * 출력할 별 줄의 길이를 받아 해당하는 만큼 별로 이루어진 줄을 그립니다.
 * @param starLength 별 줄의 길이
 */
int renderStarLine(int starLength) {
    int i = 0;
    while (i < starLength) {
        printf("*");
        i++;
    }
    printf("\n");
    return starLength;
}

/*
 * 9. while문을 사용해서 아래와 같이 출력되는 프로그램을 작성하시오.
 * *******
 * ******
 * *****
 * ****
 * ***
 * **
 * *
 */
int main() {
    int startSize = 7;
    while (renderStarLine(startSize--));
}
