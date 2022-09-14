/**
  @file Problem4.c
  @brief Lab4-4. �޸� ���󿡼� ���� ã�� (����� ����)
*/

#include <stdio.h>
#include "../inc/treasureMap.h"

/**
 * @brief Baseline Code�� ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
void *FindingTreasure(void *_map, int _depth) {
    return _depth == 0 ? _map : FindingTreasure(*(void **) _map, _depth - 1);
}

/**
 * @brief ���� �Լ��Դϴ�.
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