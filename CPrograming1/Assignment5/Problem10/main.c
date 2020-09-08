#include <stdio.h>

#define SAFE_CASE 1

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
 * 10. 사용자로부터 1부터 5까지의 수를 입력받고, 입력받은 숫자대로 아래와 같이 층이 쌓여 *이 출력되는 프로그램을 switch문과 while문을 이용해 작성하시오.
 */
int main() {
    int endSize;
    printf("숫자를 입력하시오: ");
    scanf("%d", &endSize);
    int i = 1;
    switch (endSize > 0) {
        case SAFE_CASE:
            while (renderStarLine(i++) < endSize);
            break;
        default:
            printf("1 이상의 정수를 입력하시오.");
            break;
    }
}
