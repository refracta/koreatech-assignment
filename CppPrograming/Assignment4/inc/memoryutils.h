/**
 @file memoryutils.h
 @brief memoryutils의 헤더 파일
*/
#ifndef MEMORYUTILS_H
#define MEMORYUTILS_H

#include <stdio.h>
#include <stdlib.h>

namespace MemoryUtils {
    void **malloc_double_pointer(int type_size, int width, int height);
    void free_double_pointer(void **grid, int width);
}
#endif
