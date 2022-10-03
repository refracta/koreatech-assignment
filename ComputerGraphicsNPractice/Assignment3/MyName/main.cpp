#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "name.h"
// 이름 이미지가 배열로 선언된 헤더 파일

#define TIMER_TICK 30
// timer 함수 호출 주기
#define RECT_SIZE 0.0035f
// 브러시로 사용할 기준 사각형 크기
#define SCREEN_SIZE 900
// 창 크기
#define glVertexP2D(p2d) glVertex3f((p2d).x, (p2d).y, 0)
// Point2D 구조체를 이용해 GL 정점을 그리는 매크로

/**
 * 2차원 좌표를 다루는 구조체
 */
struct Point2D {
    float x;
    float y;
} typedef Point2D;

/**
 * 주어진 중심 좌표에 주어진 변 크기를 가지는 정사각형을 그려주는 함수
 * @param center 중심 좌표
 * @param edgeSize 변 크기
 */
void drawRect(Point2D center, float edgeSize) {
    edgeSize /= 2;
    Point2D v1 = {center.x - edgeSize, center.y - edgeSize};
    Point2D v2 = {center.x + edgeSize, center.y - edgeSize};
    Point2D v3 = {center.x + edgeSize, center.y + edgeSize};
    Point2D v4 = {center.x - edgeSize, center.y + edgeSize};

    glBegin(GL_QUADS);
    glVertexP2D(v1);
    glVertexP2D(v2);
    glVertexP2D(v3);
    glVertexP2D(v4);
    glEnd();
}

/**
 * 내 이름을 화면에 그리는 함수
 */
void drawMyName() {
    const float startX = -RECT_SIZE * NAME_WIDTH / 2;
    const float startY = RECT_SIZE * NAME_HEIGHT / 2;
    for (int i = 0; i < NAME_SIZE; i++) {
        drawRect({startX + RECT_SIZE * NAME[i][0], startY + -RECT_SIZE * NAME[i][1]}, RECT_SIZE);
    }
}

void MyDisplay() {
    drawMyName();
    glFlush();
}

float color[3] = {0.1f, 0.3f, 0.1f};
bool increaseGreen = true;

/**
 * 색깔 그라데이션을 계산하여 적용하는 함수
 */
void applyGradation() {
    if (color[1] <= 0.3f) {
        increaseGreen = true;
    } else if (color[1] >= 1) {
        increaseGreen = false;
    }
    color[1] += (increaseGreen ? 1 : -1) * 0.01f;
    glColor3f(color[0], color[1], color[2]);
}

/**
 * TIMER_TICK 주기로 호출되며, 그라데이션 적용과, 화면 갱신을 처리하는 함수
 * @param value 타이머 값
 */
void drawTimer(int value) {
    applyGradation();
    glutPostRedisplay();
    glutTimerFunc(TIMER_TICK, timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("3_4 Draw My Name");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);
    glutTimerFunc(TIMER_TICK, timer, 0);
    glutMainLoop();
    return 0;
}
