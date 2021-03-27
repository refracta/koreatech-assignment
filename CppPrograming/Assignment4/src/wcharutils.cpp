/**
  @file wcharutils.c
  @brief wchar 문자열 처리 유틸 함수들이 구현된 소스 파일
*/
#include "wcharutils.h"

/**
* @brief 문자열이 전각인지 검사한다.
* @param s wchar_t 문자열
* @return 전각 여부 bool
*/
bool WCharUtils::is_full_width(wchar_t c)
{
    if (c < 256 || (c >= 0xff61 && c <= 0xff9f))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
* @brief 전각은 2글자로, 반각은 1글자로 계산한 문자의 길이를 계산한다.
* @param s wchar_t 문자열
* @return 문자열의 길이
*/
int WCharUtils::strrlen(wchar_t *s)
{
    int len = wcslen(s);
    int rlen = len;
    for (int i = 0; i < len; i++)
    {
        rlen += is_full_width(s[i]);
    }
    return rlen;
}