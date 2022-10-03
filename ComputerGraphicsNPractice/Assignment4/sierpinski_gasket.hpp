#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdbool>

#define SQRT3 1.73205080757f
// √3
#define SQRT3_1O3 (1.73205080757f / 3)
// √3 * (1/3)
#define SQRT3_2O3 (SQRT3_1O3 * 2)
// √3 * (2/3)

#define EDGE_SIZE 2
// 그릴 시에르핀스키 삼각형의 크기
#define SCREEN_SIZE 900
// 창 크기
#define glVertexP2D(p2d) glVertex3f((p2d).x, (p2d).y, 0)
// Point2D 구조체를 이용해 GL 정점을 그리는 매크로

#ifndef POINT2D_H
#define POINT2D_H
/**
 * 2차원 좌표를 다루는 구조체
 */
struct Point2D {
    float x;
    float y;
} typedef Point2D;
#endif
/**
 * 주어진 중심 좌표에 주어진 변 크기를 가지는 정삼각형을 그리는 함수
 * @param center 중심 좌표
 * @param edgeSize 변 크기
 * @param inverted 뒤집힌 정삼각형을 그릴지 결정하는 플래그
 */
void drawEquilateralTriangle(Point2D center, float edgeSize, bool inverted = false) {
    int invertedFactor = !inverted ? 1 : -1;
    float height = SQRT3 / 2 * edgeSize;
    Point2D v1 = {center.x, center.y + invertedFactor * height * 2 / 3};
    Point2D v2 = {center.x - edgeSize / 2, center.y + -invertedFactor * height / 3};
    Point2D v3 = {center.x + edgeSize / 2, center.y + -invertedFactor * height / 3};

    glBegin(GL_TRIANGLES);
    glVertexP2D(v1);
    glVertexP2D(v2);
    glVertexP2D(v3);
    glEnd();
}

/**
 * 주어진 중심 좌표에 주어진 변 크기를 가지는 시에르핀스키 삼각형을 그리는 함수
 * @param center 중심 좌표
 * @param edgeSize 변 크기
 * @param limit 재귀 연산 한계
 * @param depth 재귀 연산의 깊이
 */
void drawSierpinski(Point2D center, float edgeSize, int limit = 7, int depth = 0) {
    if (limit < depth)
        return;

    if (depth == 0) {
        glColor3f(1, 1, 1);
        drawEquilateralTriangle(center, edgeSize);
    }

    edgeSize /= 2;
    glColor3f(depth * 0.1f, depth * 0.1f, depth * 0.1f);
    drawEquilateralTriangle(center, edgeSize, true);
    drawSierpinski({center.x, center.y + (1 / SQRT3) * edgeSize}, edgeSize, limit, depth + 1);
    drawSierpinski({center.x - edgeSize / 2, center.y - (1 / (2 * SQRT3)) * edgeSize}, edgeSize, limit, depth + 1);
    drawSierpinski({center.x + edgeSize / 2, center.y - (1 / (2 * SQRT3)) * edgeSize}, edgeSize, limit, depth + 1);
}