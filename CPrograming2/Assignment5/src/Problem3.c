/**
  @file Problem3.c
  @brief Lab5-3. 일차원 배열로 이차원 배열 표현하기 (김영우 조교)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief 배열의 길이입니다.
 */
#define SCALE 10
// #define USE_2D_INDEX_LOOP
// 배열을 읽을 때 2차원 색인을 사용할 지의 여부를 설정합니다.

/**
 * @brief 2차원 색인 x, y를 받아 1차원 색인으로 반환합니다.
 * @param x 2차원 색인
 * @param y 2차원 색인
 * @return 1차원 색인화된 2차원 색인
 */
int to_index(int x, int y) {
    return x * SCALE + y;
}

/**
 * @brief 1차원 색인 index를 받아 2차원 색인 x로 반환합니다.
 * @param index 1차원 색인
 * @return 2차원 색인 x
 */
int to_2dx(int index) {
    return index / SCALE;
}

/**
 * @brief 1차원 색인 index를 받아 2차원 색인 y로 반환합니다.
 * @param index 1차원 색인
 * @return 2차원 색인 y
 */
int to_2dy(int index) {
    return index - to_2dx(index) * SCALE;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    int flat_array[SCALE * SCALE] = {0,};
    // 색인을 이용하는 유사 2차원 배열의 정의입니다.
    int *flat_pointer_array[SCALE];
    // 포인터 이용한 유사 2차원 배열의 정의입니다.
    for (int i = 0; i < SCALE; i++) {
        flat_pointer_array[i] = malloc(sizeof(int) * 10);
    }

    // CSR or CRS
    // https://ko.wikipedia.org/wiki/희소행렬
    for (int x = 0; x < SCALE; x++) {
        for (int y = 0; y < SCALE; y++) {
            int i = to_index(x, y);
            flat_array[to_index(x, y)] = i * 2;
            flat_pointer_array[x][y] = i * 2;
        }
    }

#ifndef USE_2D_INDEX_LOOP
    int lastX;
#endif
    printf("Use Index Calculation\n");
#ifdef USE_2D_INDEX_LOOP
    for (int x = 0; x < SCALE; x++) {
        for (int y = 0; y < SCALE; y++) {
            printf("%d\t", flat_array[to_index(x, y)]);
        }
        printf("\n");
    }
#else
    lastX = false;
    for (int i = 0; i < SCALE * SCALE; i++) {
        int x = to_2dx(i);
        lastX != x ? (lastX = x, printf("\n")) : false;
        printf("%d\t", flat_array[i], lastX);
    }
    printf("\n");
#endif

    printf("Use Pointer Array\n");
#ifdef USE_2D_INDEX_LOOP
    for (int x = 0; x < SCALE; x++) {
        for (int y = 0; y < SCALE; y++) {
            printf("%d\t", flat_pointer_array[x][y]);
        }
        printf("\n");
    }
#else
    lastX = false;
    for (int i = 0; i < SCALE * SCALE; i++) {
        int x = to_2dx(i);
        int y = to_2dy(i);
        lastX != x ? (lastX = x, printf("\n")) : false;
        printf("%d\t", flat_pointer_array[x][y], lastX);
    }
    printf("\n");
#endif
    // 다양한 방식으로 배열의 요소를 출력합니다.

    for (int i = 0; i < SCALE; i++) {
        free(flat_pointer_array[i]);
    }
    // 메모리를 회수합니다.
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
