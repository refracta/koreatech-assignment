#ifndef COLORTEXTUTILS_H
#define COLORTEXTUTILS_H
#define MATRIX_COL 256

namespace ColorTextUtils {
    int to_2d_y(int index);
    int to_2d_x(int index);
    void draw_color_text(int cursor_x, int cursor_y, int start_x, int start_y, int size_x, int size_y, const int array[], int width, int height);
}

#endif
