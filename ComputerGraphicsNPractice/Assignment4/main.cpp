#include <GL/glut.h>
#include "name.hpp"
#include "sierpinski_gasket.hpp"
#include "main.h"

/**
 * 메뉴 변경시 호출되는 콜백
 * @param id 메뉴 ID
 */
void handleMenu(int id) {
    currentMenu = (Menu) id;
    if (currentMenu == MENU_EXIT) {
        exit(0);
    } else {
        isAutoUpdateMode = false;
    }

    glutPostRedisplay();
}

/**
 * 메뉴 초기화 함수
 */
void initMenu() {
    GLint MyMainMenuID = glutCreateMenu(handleMenu);
    glutAddMenuEntry("Draw WireCube", MENU_WIRE_CUBE);
    glutAddMenuEntry("Draw WireSphere", MENU_WIRE_SPHERE);
    glutAddMenuEntry("Draw WireCone", MENU_WIRE_CONE);
    glutAddMenuEntry("Draw WireTorus", MENU_WIRE_TORUS);
    glutAddMenuEntry("Draw WireTetrahedron", MENU_WIRE_TETRAHEDRON);
    glutAddMenuEntry("Draw WireTeapot", MENU_WIRE_TEAPOT);
    glutAddMenuEntry("Draw MyName", MENU_MY_NAME);
    glutAddMenuEntry("Draw SierpinskiGasket", MENU_SIERPINSKI_GASKET);
    glutAddMenuEntry("Exit", MENU_EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * 주어진 메뉴에 맞는 도형을 그리는 함수
 */
void draw() {
    switch (currentMenu) {
        case MENU_WIRE_CUBE:
            glutWireCube(1.0);
            break;
        case MENU_WIRE_SPHERE:
            glutWireSphere(0.9, 20, 20);
            break;
        case MENU_WIRE_CONE:
            glutWireCone(1.0, 1.0, 20, 20);
            break;
        case MENU_WIRE_TORUS:
            glutWireTorus(0.1, 0.75, 20, 20);
            break;
        case MENU_WIRE_TETRAHEDRON:
            glutWireTetrahedron();
            break;
        case MENU_WIRE_ICOSAHEDRON:
            glutWireIcosahedron();
            break;
        case MENU_WIRE_TEAPOT:
            glutWireTeapot(0.5);
            break;
        case MENU_MY_NAME:
            drawMyName();
            break;
        case MENU_SIERPINSKI_GASKET:
            drawSierpinski({0, -0.2}, 1.75);
            break;
    }
}

/**
 * 디스플레이 콜백
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    glFlush();
}

/**
 * 창 크기 변경시 호출되는 콜백
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-width / (double) SCREEN_SIZE,
            width / (double) SCREEN_SIZE,
            -height / (double) SCREEN_SIZE,
            height / (double) SCREEN_SIZE, -1, 1);

    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

/**
 * 마우스 클릭시 호출되는 콜백
 * @param button 클릭한 버튼
 * @param state 상태
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        prevLocation = {x, y};
    }
}

/**
 * 마우스 모션시 호출되는 콜백
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseMotion(GLint x, GLint y) {
    glRotated(x - prevLocation.x, 0, 1, 0);
    glRotated(y - prevLocation.y, 1, 0, 0);
    prevLocation = {x, y};
}

/**
 * 키보드 사용시 호출되는 콜백
 * @param key 누른 키
 * @param x 마우스 가로 좌표
 * @param y 마우스 세로 좌표
 */
void keyboard(unsigned char key, int x, int y) {
    if ('0' <= key && key < '0' + MENU_EXIT) {
        isAutoUpdateMode = false;
        currentMenu = (Menu) (key - '0');
    } else if (key == 'a') {
        isAutoUpdateMode = !isAutoUpdateMode;
    } else if (key == 'i') {
        glLoadIdentity();
    } else if (key == 'q') {
        exit(0);
    }
}

/**
 * 자동 모드인 경우, 0.5초마다 메뉴 상태를 변경하는 타이머 콜백
 * @param value 타이머 값
 */
void updateTimer(int value) {
    if (isAutoUpdateMode) {
        currentMenu = (Menu) ((currentMenu + 1) % MENU_EXIT);
    }
    glutTimerFunc(AUTO_UPDATE_TICK, updateTimer, 0);
}

/**
 * 화면 갱신 및 그라데이션 효과를 적용하는 타이머 콜백
 * @param value 타이머 값
 */
void drawTimer(int value) {
    if (currentMenu == MENU_MY_NAME) {
        applyGradation();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    glutPostRedisplay();
    glutTimerFunc(DRAW_TICK, drawTimer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GLUT"
                     " Gallery");
    initMenu();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(DRAW_TICK, drawTimer, 0);
    glutTimerFunc(AUTO_UPDATE_TICK, updateTimer, 0);
    glutMainLoop();
    return 0;
}
