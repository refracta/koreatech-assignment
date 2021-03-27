/**
  @file interfaceutils.h
  @brief 게임 인터페이스 함수들이 구현된 소스 파일
*/

#include "interfaceutils.h"

/**
* @brief 메뉴를 그린다.
* @param data 메뉴 정보 데이터
*/
void InterfaceUtils::draw_menu(MenuData *data) {
    short color = ConsoleUtils::get_print_color();
    int max_length = WCharUtils::strrlen(data->name);
    for (int i = 0; i < data->length; i++) {
        max_length = MAX(max_length, WCharUtils::strrlen(data->list[i]));
    }
    max_length += max_length % 2 == 1;
    _set_print_color(data->outline_tbcolor);
    _xywprintf(data->x, data->y, L"┌─");
    _set_print_color(data->name_tbcolor);
    _wprintf(L"[ %s%*s ]", data->name, max_length - WCharUtils::strrlen(data->name) , L"");
    _set_print_color(data->outline_tbcolor);
    _wprintf(L"─┐");
    for (int i = 0; i < data->length; i++) {
        _set_print_color(data->outline_tbcolor);
        _xywprintf(data->x, data->y + (i + 1), L"│ ");
        for (int i = 0; i < 8 + max_length - 2; i++) {
            _wprintf(L" ");
        }
        _set_cursor_position(data->x + 2, data->y + (i + 1));
        if (i != data->current_index) {
            _set_print_color(data->non_selected_tbcolor);
        } else {
            _set_print_color(data->selected_tbcolor);
        }
        _wprintf(L"   %s%*s   ", data->list[i], max_length - WCharUtils::strrlen(data->list[i]) + 2, L"");
        _set_print_color(data->outline_tbcolor);
        _wprintf(L"│ ");
    }

    _xywprintf(data->x, data->y + data->length + 1, L"└──");
    for (int i = 0; i < max_length / 2 + 1; i++) {
        _wprintf(L"─");
    }
    _wprintf(L"─┘");
    _set_print_color(color);
}

/**
* @brief 메뉴를 실행한다.
* @param data 메뉴 데이터
* @param disable_escape ESC 메뉴 종료 비활성화 여부
* @return 메뉴 항목 색인
*/
int InterfaceUtils::run_menu(MenuData *data, bool disable_escape) {
    int return_value = -1;
    draw_menu(data);
    _draw();
    while (true) {
        int c = ConsoleUtils::get_key_input();
        switch (c) {
            case ESCAPE_KEY:
                if (!disable_escape) {
                    return -1;
                }
                break;
            case DOWN_KEY:
                data->current_index = data->current_index + 1 < data->length ? data->current_index + 1 : 0;
                draw_menu(data);
                FA(OCTAVE_5, 100);
                break;
            case UP_KEY:
                data->current_index = data->current_index > 0 ? data->current_index - 1 : data->length - 1;
                draw_menu(data);
                FA(OCTAVE_5, 100);
                break;
            case SPACE_KEY:
            case ENTER_KEY:
                SI(OCTAVE_5, 100);
                SOL(OCTAVE_5, 100);
                return data->current_index;
                break;
        }
        _draw();
    }
}

/**
* @brief 프롬프트를 그린다.
* @param data 프롬프트 정보 데이터
*/
void InterfaceUtils::draw_prompt(PromptData *data) {
    short color = ConsoleUtils::get_print_color();
    int max_length = MAX(data->rlen, WCharUtils::strrlen(data->message));
    max_length += max_length % 2 == 1;

    _set_print_color(data->outline_tbcolor);
    _xywprintf(data->x, data->y, L"┌─");
    _set_print_color(data->message_tbcolor);
    _wprintf(L"[ %s%*s ]", data->message, (int) (max_length - WCharUtils::strrlen(data->message)) + 2, L"");
    _set_print_color(data->outline_tbcolor);
    _wprintf(L"─┐");
    _set_print_color(data->outline_tbcolor);
    _xywprintf(data->x, data->y + 1, L"│     %*s     │ ", max_length, L"");
    _xywprintf(data->x, data->y + 2, L"└──");
    for (int i = 0; i < max_length / 2 + 2; i++) {
        _wprintf(L"─");
    }
    _wprintf(L"─┘");
    _set_print_color(color);
}

/**
* @brief 프롬프트를 실행한다.
* @param data 프롬프트 데이터
* @return 프롬프트 입력 텍스트
*/
wchar_t *InterfaceUtils::run_prompt(PromptData *data) {
    bool visibility = _get_cursor_visibility();
    short color = ConsoleUtils::get_print_color();
    _set_cursor_visibility(true);


    draw_prompt(data);
    _set_print_color(data->text_tbcolor);
    _set_cursor_position(data->x + 4, data->y + 1);
    _draw();

    int index = 0;
    int crlen = 0;
    wchar_t *text = (wchar_t *) malloc(sizeof(wchar_t) * data->rlen + 2);
    if (text == NULL) {
        return NULL;
    }

    while (true) {
        int c = ConsoleUtils::get_key_input();
        int crl;
        switch (c) {
            default:
                crl = WCharUtils::is_full_width(c) ? 2 : 1;
                if (crlen + crl > data->rlen) {
                    continue;
                }
                if (crl == 1 && strchr("\\/:*?\"<>| ", (char) c)) {
                    continue;
                }
                text[index++] = c;
                crlen += crl;
                _wprintf(L"%c", c);
                break;
            case BACKSPACE_KEY:
                if (index <= 0) {
                    continue;
                }
                _set_print_color(data->outline_tbcolor);
                if (WCharUtils::is_full_width(text[index - 1])) {
                    crlen -= 2;
                    _wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
                    _wprintf(L"  ");
                    _wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
                } else {
                    crlen--;
                    _wprintf(L"%c", BACKSPACE_KEY);
                    _wprintf(L" ");
                    _wprintf(L"%c", BACKSPACE_KEY);
                }
                _set_print_color(data->text_tbcolor);
                index--;
                break;
            case ENTER_KEY:
                if (index <= 0) {
                    continue;
                }
                text[index] = '\0';
                _set_print_color(color);
                _set_cursor_visibility(visibility);
                return text;
        }
        _draw();
    }
}