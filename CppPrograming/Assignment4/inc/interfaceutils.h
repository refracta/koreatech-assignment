/**
 @file interfaceutils.h
 @brief interfaceutils의 헤더 파일
*/
#ifndef INTERFACEUTILS_H
#define INTERFACEUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

#include "environment.h"
#include "consoleutils.h"
#include "wcharutils.h"
#include "beeputils.h"
#include "bufferingmanager.h"
#include "keycode.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define _set_print_color bm.set_print_color
#define _xywprintf bm.xywprintf
#define _set_cursor_position bm.set_cursor_position
#define _set_cursor_visibility bm.set_cursor_visibility
#define _get_cursor_visibility bm.get_cursor_visibility
#define _wprintf bm.wprintf
#define _draw() bm.draw()

/**
 * @brief 메뉴 렌더링 데이터들을 포함하는 구조체
 */
typedef struct
{
    int x;
    int y;
    wchar_t *name;
    wchar_t **list;
    int length;
    int current_index;
    short outline_tbcolor;
    short name_tbcolor;
    short element_tbcolor;
    short selected_tbcolor;
    short non_selected_tbcolor;
} MenuData;

/**
 * @brief 프롬프트 렌더링 데이터들을 포함하는 구조체
 */
typedef struct
{
    int x;
    int y;
    wchar_t *message;
    int rlen;
    short outline_tbcolor;
    short message_tbcolor;
    short text_tbcolor;
} PromptData;

namespace InterfaceUtils {
    static BufferingManager& bm = BufferingManager::instance();
    void draw_menu(MenuData *data);
    int run_menu(MenuData *, bool);
    void draw_prompt(PromptData *data);
    wchar_t *run_prompt(PromptData *);
}
#endif


