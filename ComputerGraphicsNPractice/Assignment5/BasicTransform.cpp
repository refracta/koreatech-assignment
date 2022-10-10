#include "BasicTransform.h"
#include "glk.h"
#include <stdlib.h>

#define RANDOM() (rand() / (double) RAND_MAX)

// 동차 좌표계로 표시함
static double P[12] = {0.3, 0.2, 0.1, 1,
                       0.7, 0.2, 0.1, 1,
                       0.5, 0.7, 0.1, 1};
static double Q[12];
static double L[16] = {-0.1, -0.1, -0.1, 1,
                        // 직선 시작점 (A)
                       0.8, 0.8, 0.8, 1,
                        // 직선 종료점 (B)
                       NULL, NULL, NULL, 0,
                        // 직선 벡터 (AB, positionL)
                       NULL, NULL, NULL, 0};
                        // y축 회전된 직선 벡터 (yRotatedL)
double *positionL = L + 8;
// 직선 벡터의 포인터
double *yRotatedL = L + 12;
// y축 회전된 직선 벡터의 포인터

void transformTriangle(double *m, double *p, double *q) {
    glkTransform(m, p, q);
    glkTransform(m, p + 4, q + 4);
    glkTransform(m, p + 8, q + 8);
}

bool drawArbitraryAxis = false;

/**
 * 디스플레이 콜백
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glkTriangle4d(P);
    glColor3f(0.0, 0.0, 1.0);
    glkTriangle4d(Q);
    glkCoord();
    if (drawArbitraryAxis) {
        glColor3f(0.0, 1.0, 1.0);
        glkLine(L[0], L[1], L[2], L[4], L[5], L[6]);
    }
    glFlush();
}

/**
 * 키보드 사용시 호출되는 콜백
 * @param key 누른 키
 * @param x 마우스 가로 좌표
 * @param y 마우스 세로 좌표
 */
void keyboard(unsigned char key, int x, int y) {
    double m1[16], m2[16];
    bool isCalledByMenu = x == MENU_CALLBACK_VALUE && y == MENU_CALLBACK_VALUE;
    drawArbitraryAxis = key == MENU_ROTATE_ARBITRARY_AXIS || key == MENU_SET_RANDOM_AXIS;
    if (key == MENU_INIT) {
        // 뷰 초기화
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    } else if (key == MENU_TRANSFORM) {
        // 이동 변환
        glkMatTrans(m1, -1, -0.5, 0);
        printf("Move: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_SCALE) {
        // 신축 변환
        glkMatScale(m1, 1.5, 1.2, 1.4);
        printf("Scale: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_ROTATE_X) {
        // X축 회전 변환
        glkMatRotateX(m1, 60);
        printf("Rotate X: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_ROTATE_Y) {
        // Y축 회전 변환
        glkMatRotateY(m1, 60);
        printf("Rotate Y: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_ROTATE_Z) {
        // Z축 회전 변환
        glkMatRotateZ(m1, 60);
        printf("Rotate Z: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_COMPLEX_ROTATE) {
        // 복합 변환 - 회전
        glkMatIdentity(m1);
        // 단위 행렬로 m1 초기화

        glkMatTrans(m2, -P[0], -P[1], -P[2]);
        glkMatMult(m2, m1, m1);
        // 원점으로 이동 변환

        static double angle = 0.0;
        glkMatRotateZ(m2, angle += isCalledByMenu ? 50 : 10);
        glkMatMult(m2, m1, m1);
        // Z축 회전 변환

        glkMatTrans(m2, P[0], P[1], P[2]);
        glkMatMult(m2, m1, m1);
        // 원래 지점으로 이동 변환

        printf("Complex rotate: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_COMPLEX_SCALE) {
        // 복합 변환 - 신축
        glkMatIdentity(m1);
        // 단위 행렬로 m1 초기화
        glkMatTrans(m2, -P[0], -P[1], -P[2]);
        glkMatMult(m2, m1, m1);
        // 원점으로 이동 변환

        static double scale = 0.0;
        scale += isCalledByMenu ? 0.5 : 0.1;
        scale = scale < 1.5 ? scale : 0.1;
        glkMatScale(m2, scale * 1.2, scale, scale);
        glkMatMult(m2, m1, m1);
        // 신축 변환

        glkMatTrans(m2, P[0], P[1], P[2]);
        glkMatMult(m2, m1, m1);
        // 원래 지점으로 이동 변환

        printf("Complex scale: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_COMPLEX_SHEERING) {
        // 복합 변환 - 밀림
        glkMatIdentity(m1);
        // 단위 행렬로 m1 초기화
        glkMatTrans(m2, -P[0], -P[1], -P[2]);
        glkMatMult(m2, m1, m1);
        // 원점으로 이동 변환

        static double sheer = 0.0;
        sheer += isCalledByMenu ? 0.5 : 0.1;
        sheer = sheer < 1.5 ? sheer : 0.1;
        glkMatShearX(m2, sheer, 1);
        glkMatMult(m2, m1, m1);
        // 전단(밀림) 변환

        glkMatTrans(m2, P[0], P[1], P[2]);
        glkMatMult(m2, m1, m1);
        // 원래 지점으로 이동 변환

        printf("Complex sheering: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_ROTATE_ARBITRARY_AXIS) {
        for (int i = 0; i < 4; i++) {
            positionL[i] = L[i % 4 + 4] - L[i];
        }
        // 직선 벡터 계산

        double yAngle = -(atan2(positionL[2], positionL[0]) / M_PI * 180);
        // 직선을 x축으로 맞추기 위해 필요한 y축 방향 회전각
        glkMatRotateY(m2, yAngle);
        // yAngle 회전 행렬

        glkTransform(m2, positionL, yRotatedL);
        // 직선 벡터를 yAngle 만큼 회전하여 Y축 회전된 AB 벡터 계산

        double zAngle = -(atan2(yRotatedL[1], yRotatedL[0]) / M_PI * 180);
        // 직선을 x축으로 맞추기 위해 필요한 z축 방향 회전각

        glkMatIdentity(m1);
        // 단위 행렬로 m1 초기화

        glkMatTrans(m2, -L[0], -L[1], -L[2]);
        glkMatMult(m2, m1, m1);
        // 직선을 원점으로 이동

        glkMatRotateY(m2, yAngle);
        glkMatMult(m2, m1, m1);
        // y축 회전 변환

        glkMatRotateZ(m2, zAngle);
        glkMatMult(m2, m1, m1);
        // z축 회전 변환

        static double angle = 0.0;
        glkMatRotateX(m2, angle += isCalledByMenu ? 15 : 3);
        glkMatMult(m2, m1, m1);
        // x축 회전 변환 (사용자 입력 각도 회전)

        glkMatRotateZ(m2, -zAngle);
        glkMatMult(m2, m1, m1);
        // z축 회전 역변환

        glkMatRotateY(m2, -yAngle);
        glkMatMult(m2, m1, m1);
        // y축 회전 역변환

        glkMatTrans(m2, L[0], L[1], L[2]);
        glkMatMult(m2, m1, m1);
        // 직선을 원래 위치로 이동

        printf("Rotate arbitrary axis: \n");
        glkMatPrint(m1);
        transformTriangle(m1, P, Q);
    } else if (key == MENU_SET_RANDOM_AXIS) {
        double newL[16] = {-RANDOM(), -RANDOM(), -RANDOM(), 1,
                           RANDOM(), RANDOM(), RANDOM(), 1,
                           NULL, NULL, NULL, 0,
                           NULL, NULL, NULL, 0};
        memcpy(L, newL, sizeof(double) * 16);
        printf("Random axis: \n");
        glkMatPrint(newL);
    } else if (key == MENU_EXIT) exit(0);
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
    glutPostRedisplay();
}


/**
 * 메뉴 변경시 호출되는 콜백
 * @param id 메뉴 ID
 */
void handleMenu(int id) {
    keyboard(id, MENU_CALLBACK_VALUE, MENU_CALLBACK_VALUE);
}

/**
 * 메뉴 초기화 함수
 */
void initMenu() {
    GLint mainMenu = glutCreateMenu(handleMenu);
    glutAddMenuEntry("Init view (i)", MENU_INIT);
    glutAddMenuEntry("Transform (t)", MENU_TRANSFORM);
    glutAddMenuEntry("Scale (s)", MENU_SCALE);
    glutAddMenuEntry("Rotate X (x)", MENU_ROTATE_X);
    glutAddMenuEntry("Rotate Y (y)", MENU_ROTATE_Y);
    glutAddMenuEntry("Rotate Z (z)", MENU_ROTATE_Z);
    glutAddMenuEntry("[Complex transform] Rotate (Z)", MENU_COMPLEX_ROTATE);
    glutAddMenuEntry("[Complex transform] Scale (c)", MENU_COMPLEX_SCALE);
    glutAddMenuEntry("[Complex transform] Sheering (h)", MENU_COMPLEX_SHEERING);
    glutAddMenuEntry("[Own complex transform] Rotate arbitrary axis (r)", MENU_ROTATE_ARBITRARY_AXIS);
    glutAddMenuEntry("[Own complex transform] Set random axis (a)", MENU_SET_RANDOM_AXIS);
    glutAddMenuEntry("Exit", MENU_EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Geometric Transform");
    initMenu();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}