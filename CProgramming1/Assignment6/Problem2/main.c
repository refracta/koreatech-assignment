#include <stdio.h>

const char TRIANGLE_CHARACTER = '*';
const char SPACE_CHARACTER = ' ';
const int ASSIGNMENT_LENGTH = 7;

/**
 * 문자 한개와 개수를 받아 해당 문자로 이루어진 줄을 출력한다.
 * @param lLength 줄의 길이
 */
void render_char_line(char tChar, int lLength) {
    for (int i = 0; i < lLength; i++) {
        printf("%c", tChar);
    }
}

/**
 * 마룸모의 가로 대각선 길이를 받아 마름모의 윗 부분에 해당하는 삼각형을 출력한다.
 * @param hdLength 마름모의 가로 대각선 길이
 */
void triangle_by_length(int hdLength) {
    for (int i = 1 + !(hdLength % 2); i < hdLength; i += 2) {
        int spaceSize = (hdLength - i) / 2;
        render_char_line(SPACE_CHARACTER, spaceSize);
        render_char_line(TRIANGLE_CHARACTER, i);
        render_char_line(SPACE_CHARACTER, spaceSize);
        printf("\n");
    }
}

/**
 * 마룸모의 가로 대각선 길이를 받아 마름모의 아랫 부분에 해당하는 역삼각형을 출력한다.
 * @param hdLength 마름모의 가로 대각선 길이
 */
void rev_triangle_by_length(int hdLength) {
    for (int i = hdLength - 2; i >= 1; i -= 2) {
        int spaceSize = (hdLength - i) / 2;
        render_char_line(SPACE_CHARACTER, spaceSize);
        render_char_line(TRIANGLE_CHARACTER, i);
        render_char_line(SPACE_CHARACTER, spaceSize);
        printf("\n");
    }
}

/**
 * 마룸모의 가로 대각선 길이를 받아 마름모를 화면에 출력힌디.
 * @param hdLength
 */
void render_rhombus_by_length(int hdLength) {
    triangle_by_length(hdLength);
    render_char_line(TRIANGLE_CHARACTER, hdLength);
    printf("\n");
    rev_triangle_by_length(hdLength);
}

/**
 * triangle_by_length 함수를 과제 문제 명세에 맞게 구현한 버전
 */
void triangle() {
    triangle_by_length(ASSIGNMENT_LENGTH);
}

/**
 * rev_triangle_by_length 함수를 과제 문제 명세에 맞게 구현한 버전
 */
void rev_triangle() {
    rev_triangle_by_length(ASSIGNMENT_LENGTH);
}

/**
 * render_rhombus_by_length 함수를 과제 문제 명세에 맞게 구현한 버전
 */
void render_rhombus() {
    triangle();
    render_char_line(TRIANGLE_CHARACTER, ASSIGNMENT_LENGTH);
    printf("\n");
    rev_triangle();
}

/**
 * 아래와 같이 결과를 출력하는 프로그램을 작성하기 위해 2개의 함수를 구현하시오. triangle() 함수는 세번째 줄까지 삼각형 모양을 출력한다. rev_triangle() 함수는 네번째 줄부터 끝까지 역삼각형 모양을 출력한다. 두 함수 모두 입력과 반환값은 없다. 구현된 함수를 이용하여 아래와 같이 출력하는 프로그램을 작성하시오.
 *    *
 *   ***
 *  *****
 * *******
 *  *****
 *   ***
 *    *
 */
int main() {
    render_rhombus();
}
