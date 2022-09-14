/**
  @file Problem4.c
  @brief Lab4-4. 메모리 세상에서 보물 찾기 (김덕수 교수)
*/

#include <stdio.h>
#include "../inc/treasureMap.h"

/**
 * @brief Baseline Code에 정의된 함수의 동일 명세 구현체입니다.
 */
void *FindingTreasure(void *_map, int _depth) {
    return _depth == 0 ? _map : FindingTreasure(*(void **) _map, _depth - 1);
}

/**
 * @brief 시작 함수입니다.
 */
void main(void) {
    void *map[MAX_SIZE] = {0};
    int hints[MAX_SIZE] = {0};
    int treasureSize = getMap(map, hints);
    for (int i = 0; i < treasureSize; i++) {
        printf("%c", *((char *) FindingTreasure(map[i], hints[i])));
    }
    printf("\n");
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}