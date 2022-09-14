/**
 @file consoleutils.h
 @brief consoleutils의 헤더 파일
*/
#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include "systemutils.h"

#if defined(_WIN32) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#define CURSOR_SIZE_SMALL 25
#define CURSOR_SIZE_LARGE 100

#define NUMBER_OF_COLOR 16
#define TO_TEXT_COLOR(tbcolor) (tbcolor % NUMBER_OF_COLOR)
#define TO_BACKGROUND_COLOR(tbcolor) (tbcolor / NUMBER_OF_COLOR)
#define TO_TBCOLOR(text_color, background_color) (NUMBER_OF_COLOR * (background_color) + (text_color))

/**
 * @brief 콘솔에서 사용하는 색깔 열거형
 */
typedef enum
{
    BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
    LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
} ConsoleColor;

namespace ConsoleUtils {
    void set_locale_korean();
    void set_locale_default();
    void set_encoding_cp949();
    void set_encoding_utf8();
    void set_boost_mode();
    void set_default_mode();
    short get_print_color();
    void set_print_color(int tbcolor);
    COORD get_cursor_position();
    void set_cursor_position(int x, int y);
    bool get_cursor_visibility();
    void set_cursor_visibility(bool visibility);
    void set_console_size(int cols, int lines);
    void set_cursor_size(int cursor_size);
    void set_console_title(const wchar_t*title);
    void clear_console();
    void xyprintf(int x, int y, char *format, ...);
    void xywprintf(int x, int y, wchar_t *format, ...);
    int get_key_input();
    int wait_with_handler(unsigned long ms, int (*handler)(int, void *), void *data);
}
#endif
