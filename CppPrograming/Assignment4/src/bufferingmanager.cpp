#include "bufferingmanager.h"

BufferingManager *BufferingManager::instance_ = NULL;

BufferingManager::BufferingManager() {}

BufferingManager &BufferingManager::instance() {
    if (instance_ == NULL) {
        instance_ = new BufferingManager();
    }
    return *instance_;
}

int BufferingManager::get_width() {
    return this->width;
}

int BufferingManager::get_height() {
    return this->height;
}

void BufferingManager::set_print_color(short color) {
    this->print_color = color;
}

short BufferingManager::get_print_color() {
    return this->print_color;
}

bool BufferingManager::get_cursor_visibility() {
    return cursor_info.bVisible;
}

void BufferingManager::set_cursor_visibility(bool visibility) {
    cursor_info.bVisible = visibility;
}

void BufferingManager::set_cursor_position(int x, int y) {
    cursor_position.X = x;
    cursor_position.Y = y;
}

COORD BufferingManager::get_cursor_position()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(get_current_screen_buffer(), &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        COORD invalid = {0, 0};
        return invalid;
    }
}

void BufferingManager::init(int width, int height) {
    this->width = width;
    this->height = height;
    char_buffer = new CHAR_INFO[width * height];

    clear();

    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_buffer_size.X = this->width;
    coord_buffer_size.Y = this->height;

    coord_buffer_coord.X = 0;
    coord_buffer_coord.Y = 0;

    write_rect.Left = write_rect.Top = 0;
    write_rect.Right = this->width - 1;
    write_rect.Bottom = this->height - 1;

    screen_buffer1 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    screen_buffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleScreenBufferSize(screen_buffer1, coord_buffer_size);
    SetConsoleWindowInfo(screen_buffer1, TRUE, &write_rect);

    SetConsoleScreenBufferSize(screen_buffer2, coord_buffer_size);
    SetConsoleWindowInfo(screen_buffer2, TRUE, &write_rect);

    current_screen_buffer = 1;
    GetConsoleCursorInfo(screen_buffer1, &cursor_info);
}

HANDLE BufferingManager::get_current_screen_buffer(bool next) {
    next ? current_screen_buffer = !(current_screen_buffer - 1) + 1 : 0;
    if (current_screen_buffer == 1) {
        return screen_buffer1;
    } else if (current_screen_buffer == 2) {
        return screen_buffer2;
    } else {
        return NULL;
    }
}

void BufferingManager::draw() {
    HANDLE screen_buffer = get_current_screen_buffer(true);
    WriteConsoleOutputW(screen_buffer, char_buffer, coord_buffer_size, coord_buffer_coord, &write_rect);
    SetConsoleActiveScreenBuffer(screen_buffer);
    SetConsoleCursorPosition(screen_buffer, cursor_position);
    SetConsoleCursorInfo(screen_buffer, &cursor_info);
}

void BufferingManager::wprintf(wchar_t *format, ...) {
    va_list arg_ptr;

            va_start(arg_ptr, format);
    int buffer_size = _vscwprintf(format, arg_ptr) + 1;
            va_end(arg_ptr);

    wchar_t *buffer_ptr = (wchar_t *) malloc(sizeof(wchar_t) * buffer_size);
    if (buffer_ptr == NULL) {
        return;
    }
            va_start(arg_ptr, format);
    _vsnwprintf(buffer_ptr, buffer_size, format, arg_ptr);
            va_end(arg_ptr);

    xywprintf(-1, -1, L"%s", buffer_ptr);
    free(buffer_ptr);
}

void BufferingManager::clear(){
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char_buffer[x + width * y].Char.UnicodeChar = ' ';
            char_buffer[x + width * y].Attributes = print_color;
        }
    }
}

/**
 * @brief 콘솔의 x, y 위치에 wprintf 함수와 같은 기능을 수행한다.
 * @param x 가로줄 출력 위치
 * @param y 세로줄 출력 위치
 * @param format 포맷 문자열
 */
void BufferingManager::xywprintf(int x, int y, wchar_t *format, ...) {
    va_list arg_ptr;

            va_start(arg_ptr, format);
    int buffer_size = _vscwprintf(format, arg_ptr) + 1;
            va_end(arg_ptr);

    wchar_t *buffer_ptr = (wchar_t *) malloc(sizeof(wchar_t) * buffer_size);
    if (buffer_ptr == NULL) {
        return;
    }
            va_start(arg_ptr, format);
    _vsnwprintf(buffer_ptr, buffer_size, format, arg_ptr);
            va_end(arg_ptr);

    int position = x + width * y;
    if (!(-1 < position && position < width * height)) {
        position = cursor_position.X + width * cursor_position.Y;
    }

    for (int i = 0; i < buffer_size; i++) {
        if (buffer_ptr[i] == '\0') {
            break;
        } else if (buffer_ptr[i] == '\n') {
            position = ((position / width) + 1) * width + x;
        } else if (buffer_ptr[i] == '\b') {
            position--;
        } else {
            bool is_full_width = WCharUtils::is_full_width(buffer_ptr[i]);
            if (is_full_width && position % width == width - 1) {
                char_buffer[position].Char.UnicodeChar = L' ';
                char_buffer[position].Attributes = print_color;
                position++;
                position %= width * height;
            }
            char_buffer[position].Char.UnicodeChar = buffer_ptr[i];
            char_buffer[position].Attributes = print_color;
            position++;
            position %= width * height;
            if (is_full_width) {
                char_buffer[position].Char.UnicodeChar = L' ';
                char_buffer[position].Attributes = print_color;
                position++;
            }
        }
        position %= width * height;
    }

    cursor_position.X = position % width;
    cursor_position.Y = position / width;
    free(buffer_ptr);
}