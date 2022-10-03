#ifndef MAIN_H
#define MAIN_H

#define DRAW_TICK 10
#define AUTO_UPDATE_TICK 500
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
    MENU_WIRE_CUBE,
    MENU_WIRE_SPHERE,
    MENU_WIRE_CONE,
    MENU_WIRE_TORUS,
    MENU_WIRE_TETRAHEDRON,
    MENU_WIRE_ICOSAHEDRON,
    MENU_WIRE_TEAPOT,
    MENU_MY_NAME,
    MENU_SIERPINSKI_GASKET,
    MENU_EXIT
} typedef Menu;

bool isAutoUpdateMode = true;
Point2DI prevLocation;
Menu currentMenu = MENU_WIRE_CUBE;

#endif