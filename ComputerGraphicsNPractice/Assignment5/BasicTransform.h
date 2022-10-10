#ifndef MAIN_H
#define MAIN_H

#define MENU_CALLBACK_VALUE -1
#define SCREEN_SIZE 500

#ifndef POINT2DI_H
#define POINT2DI_H
/**
 * 2차원 정수 좌표를 다루는 구조체
 */
struct Point2DI {
    int x;
    int y;
} typedef Point2DI;
#endif

enum Menu {
    MENU_INIT = 'i',
    MENU_TRANSFORM = 't',
    MENU_SCALE = 's',
    MENU_ROTATE_X = 'x',
    MENU_ROTATE_Y = 'y',
    MENU_ROTATE_Z = 'z',
    MENU_COMPLEX_ROTATE = 'Z',
    MENU_COMPLEX_SCALE = 'c',
    MENU_COMPLEX_SHEERING = 'h',
    MENU_ROTATE_ARBITRARY_AXIS = 'r',
    MENU_SET_RANDOM_AXIS = 'a',
    MENU_EXIT = 'q'
} typedef Menu;

Point2DI prevLocation;
#endif