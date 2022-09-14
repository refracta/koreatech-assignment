#define WORLD_CUP 1
#define OLYMPIC 2
#include <stdio.h>

/*
 * 1. 사용자로부터 년도를 숫자로 입력받고, 월드컵 혹은 하계 올림픽이 개최되는 해인지 판단해 출력하는 프로그램을 switch문을 이용해 작성하시오. 월드컵은 1950년부터 4년마다, 하계 올림픽은 1952년부터 4년마다 개최된다. (사용자로부터 년도는 1950년 이후로만 받는 것으로 가정하고, 2020년 하계 올림픽은 열린 것으로 가정한다.)
 */
int main() {
    int year;
    printf("년도를 입력하시오: ");
    scanf("%d", &year);
    int isWorldCup = (year - 1950) % 4 == 0;
    int isOlympic = (year - 1952) % 4 == 0;

    switch (isWorldCup * WORLD_CUP + isOlympic * OLYMPIC) {
        case WORLD_CUP:
            printf("월드컵");
            break;
        case OLYMPIC:
            printf("하계 올림픽");
            break;
        default:
            printf("개최되지 않음");
            break;
    }
}
