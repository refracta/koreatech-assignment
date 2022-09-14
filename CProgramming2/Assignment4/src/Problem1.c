/**
  @file Problem1.c
  @brief Lab4-1. 탱크 포탄（팀2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief 시도 횟수를 증가시키고 반환합니다.
 * @return 시도 횟수
 */
int increase_number_of_try() {
    static int numOfTry = 0;
    return ++numOfTry;
}

/**
 * @brief 탄을 발사하고 적의 피격 여부를 반환합니다.
 * @return 적의 피격 여부
 */
int fire(int enemy_location, int v0) {
    double hit_location = (v0 * v0 * 0.7) / 10;
    return hit_location - 30 <= enemy_location && enemy_location <= hit_location + 30;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    srand(time(NULL));
    int enemy_location = 175 + rand() % (343 - 175) + 1;
    // 적의 무작위 위치 생성 (175 ~ 343)
    int try;
    while (true) {
        printf("초속 몇 m탄으로 할지 정하시오:");
        int v0;
        scanf("%d", &v0);
        if (!(50 <= v0 && v0 <= 70)) {
            printf("그런 탄은 없습니다.\n");
            continue;
        }
        try = increase_number_of_try();
        if (fire(enemy_location, v0)) {
            printf("적을 맞추었습니다.\n");
            break;
        } else {
            printf("적을 맞추지 못했습니다.\n");
        }
    }
    printf("시도횟수:%d", try);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
