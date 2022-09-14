#include "colortextutils.h"
#include "bufferingmanager.h"

int ColorTextUtils::to_2d_y(int index) {
    return index / MATRIX_COL;
}

int ColorTextUtils::to_2d_x(int index) {
    return index % MATRIX_COL;
}

void ColorTextUtils::draw_color_text(int cursor_x, int cursor_y, int start_x, int start_y, int size_x, int size_y, const int array[], int width, int height) {
    BufferingManager &bm = BufferingManager::instance();
    bm.set_cursor_position(cursor_x, cursor_y);
    short color = bm.get_print_color();
    for (int y = start_y; y < start_y + size_y; y++) {
        for (int x = start_x; x < start_x + size_x; x++) {
            bm.set_print_color(to_2d_x(array[x + y * width]));
            wchar_t c = to_2d_y(array[x + y * width]);
            bm.wprintf(L"%c", c);
        }
        bm.set_cursor_position(cursor_x, ++cursor_y);
    }
    bm.set_print_color(color);
}