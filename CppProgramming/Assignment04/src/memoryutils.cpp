/**
  @file memoryutils.c
  @brief 메모리 제어 관련 유틸 함수들이 구현된 소스 파일
*/
#include "memoryutils.h"

/**
* @brief 동적 할당을 통해 이차원 배열처럼 쓸 수 있는 이중 포인터를 반환한다.
* @param type_size 이중 포인터의 타입
* @param width 이중 포인터의 가로 길이
* @param height 이중 포인터의 세로 길이
* @return 이중 포인터
*/
void **MemoryUtils::malloc_double_pointer(int type_size, int width, int height) {
    void **grid = (void **) malloc(sizeof(void *) * width);
    if (grid == NULL) {
        return NULL;
    }
    for (int i = 0; i < width; i++) {
        grid[i] = malloc(type_size * height);
        if (grid[i] == NULL) {
            return NULL;
        }
    }
    return grid;
}

/**
* @brief 동적 할당을 통해 생성한 이중 포인터를 할당 해제한다.
* @param width 가로 길이
*/
void MemoryUtils::free_double_pointer(void **grid, int width) {
    for (int x = 0; x < width; x++) {
        free(grid[x]);
    }
    free(grid);
}