/**
 @file wcharutils.h
 @brief wcharutils의 헤더 파일
*/
#ifndef WCHARUTILS_H
#define WCHARUTILS_H

#include <stdbool.h>
#include <wchar.h>

namespace WCharUtils {
    bool is_full_width(wchar_t c);
    int strrlen(wchar_t *s);
}
#endif