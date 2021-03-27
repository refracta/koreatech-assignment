#ifndef BUFFERINGMANAGER_H
#define BUFFERINGMANAGER_H

#include <windows.h>
#include <stdbool.h>
#include <stdarg.h>
#include <wchar.h>
#include <conio.h>
#include <Windows.h>
#include "wcharutils.h"
#include "consoleutils.h"

class BufferingManager {
public:
    static BufferingManager &instance();
    CHAR_INFO *char_buffer;
    void init(int width, int height);
    HANDLE get_current_screen_buffer(bool next = false);
    void draw();
    int get_width();
    int get_height();
    void BufferingManager::clear();
    void BufferingManager::xywprintf(int x, int y, wchar_t *format, ...);
    void BufferingManager::wprintf(wchar_t *format, ...);
    void BufferingManager::set_print_color(short color);
    short BufferingManager::get_print_color();
    bool BufferingManager::get_cursor_visibility();
    void BufferingManager::set_cursor_visibility(bool visibility);
    COORD get_cursor_position();
    void BufferingManager::set_cursor_position(int x, int y);

private:
    BufferingManager();
    static BufferingManager *instance_;
    int width;
    int height;
    int current_screen_buffer;
    HANDLE stdout_handle;
    HANDLE screen_buffer1;
    HANDLE screen_buffer2;
    COORD coord_buffer_size;
    COORD coord_buffer_coord;
    COORD cursor_position = {0, 0};
    CONSOLE_CURSOR_INFO cursor_info;
    short print_color = ConsoleUtils::get_print_color();
    SMALL_RECT write_rect;
};


#endif BUFFERINGMANAGER_H
