#define _USE_MATH_DEFINES

#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define ROUND(v) ((int) (v + 0.5))
//#define DEBUG

#include <gl/glut.h>
#include <iostream>

inline double dist(double dx, double dy) { return sqrt(dx * dx + dy * dy); }

static int winW = 500, winH = 500;
static int nGrid = 30;
static double pixelW, pixelH;
static int px, py, qx, qy;
static int mode = 0;

void draw2DGrid() {
    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = 0; i <= nGrid; i++) {
        glVertex2d(i * pixelW, 0);
        glVertex2d(i * pixelW, winH);
        glVertex2d(0, i * pixelH);
        glVertex2d(winW, i * pixelH);
    }
    glEnd();
}

void drawPixel(GLint x, GLint y) {
    int xi = x * pixelW;
    int yi = y * pixelH;
    glRectd(xi, yi, xi + pixelW, yi + pixelH);
}

void displayPixel(int x, int y) {
#ifdef DEBUG
    printf("displayPixel(%d, %d)\n", x, y);
#endif
    drawPixel(x, y);
}

/**
 * 기본적인 ROUND 계산 알고리즘 구현체
 */
void lineBasic(GLint x1, GLint y1, GLint x2, GLint y2) {
    double m = (double)(y2 - y1) / (x2 - x1);
    // "기울기 1"을 분기로 x와 y에 대한 계산을 사용
    if (abs(m) > 1) {
        m = 1 / m;
        for (int y = min(y1, y2); y <= max(y1, y2); y++) {
            double x = m * (y - y1) + x1;
            drawPixel(ROUND(x), y);
        }
    }
    else {
        for (int x = min(x1, x2); x <= max(x1, x2); x++) {
            double y = m * (x - x1) + y1;
            displayPixel(x, ROUND(y));
        }
    }
}

/**
 * DDA 알고리즘 구현체
 */
void lineDDA(GLint x1, GLint y1, GLint x2, GLint y2) {
    int dX = abs(x2 - x1);
    int dY = abs(y2 - y1);
    int steps = max(dX, dY);
    double incX = (double)(x2 - x1) / steps;
    double incY = (double)(y2 - y1) / steps;
    double x = x1;
    double y = y1;
    for (int i = 0; i <= steps; i++, x += incX, y += incY) {
        displayPixel(ROUND(x), ROUND(y));
    }
}

/**
 * y를 기준으로 x를 계산하는 Bresenham 구현체
 */
void lineBresenhamHigh(GLint x1, GLint y1, GLint x2, GLint y2) {
    int dX = x2 - x1;
    int dY = y2 - y1;
    int xi = 1;
    if (dX < 0) {
        xi = -1;
        dX = -dX;
    }
    int D = (2 * dX) - dY;
    int x = x1;

    for (int y = y1; y <= y2; y++) {
        drawPixel(x, y);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dX - dY));
        }
        else {
            D = D + 2 * dX;
        }
    }
}

/**
 * x를 기준으로 y를 계산하는 Bresenham 구현체
 */
void lineBresenhamLow(GLint x1, GLint y1, GLint x2, GLint y2) {
    int dX = x2 - x1;
    int dY = y2 - y1;
    int yi = 1;
    if (dY < 0) {
        yi = -1;
        dY = -dY;
    }
    int D = (2 * dY) - dX;
    int y = y1;

    for (int x = x1; x <= x2; x++) {
        drawPixel(x, y);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dY - dX));
        }
        else {
            D = D + 2 * dY;
        }
    }
}

/**
 * Bresenham 알고리즘 구현체
 */
void lineBresenham(GLint x1, GLint y1, GLint x2, GLint y2) {
    int yDelta = abs(y2 - y1);
    int xDelta = abs(x2 - x1);
    // xDelta, yDelta의 대소를 비교하여 계산의 기준이 되는 변수를 달리 설정
    if (yDelta < xDelta) {
        if (x1 > x2) {
            lineBresenhamLow(x2, y2, x1, y1);
        }
        else {
            lineBresenhamLow(x1, y1, x2, y2);
        }
        // 항상 작은 점이 함수의 첫번째 인자로 처리될 수 있게 하는 조건 분기
    }
    else {
        if (y1 > y2) {
            lineBresenhamHigh(x2, y2, x1, y1);
        }
        else {
            lineBresenhamHigh(x1, y1, x2, y2);
        }
        // 항상 작은 점이 함수의 첫번째 인자로 처리될 수 있게 하는 조건 분기
    }
}

/**
 * 점을 8방향 반사하여 그리는 함수
 */
void drawCirclePoint(GLint x, GLint y) {
    displayPixel(x, y);
    displayPixel(-x, y);
    displayPixel(x, -y);
    displayPixel(-x, -y);

    displayPixel(y, x);
    displayPixel(-y, x);
    displayPixel(y, -x);
    displayPixel(-y, -x);
}

/**
 * Midpoint Circle 알고리즘 구현체
 */
void circleMidPoint(GLint radius) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    for (; y > x; x++) {
        if (d < 0) {
            d = d + 2 * x + 3;
        }
        else {
            d = d + 2 * (x - y) + 5;
            y = y - 1;
        }
        drawCirclePoint(x, y);
    }
}

enum {
    LINE_BASIC, LINE_DDA, LINE_BRESENHAM, CIRCLE_MID_POINT
} typedef Mode;
/**
 * 창 타이틀 변경용 모드 타이틀 문자열
 */
const char* MODE_STRINGS[] = { "Basic Line Drawing", "DDA Line Drawing", "Bresenham Line Drawing",
                              "Midpoint Circle Drawing" };

/**
 * 디스플레이 콜백 함수
 */
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    draw2DGrid(); // 화소 그리드

    glColor3f(0, 0, 0); // Bresenham 선분
    switch (mode) {
    case LINE_BASIC:
        lineBasic(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
        break;
    case LINE_DDA:
        lineDDA(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
        break;
    case LINE_BRESENHAM:
        lineBresenham(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
        break;
    case CIRCLE_MID_POINT:
        int radius = ROUND(dist(px / pixelW - qx / pixelW, py / pixelH - qy / pixelH));

        glPushMatrix();
        glTranslated((int)(px / pixelW) * pixelW, (int)(py / pixelH) * pixelH, 0);
        circleMidPoint(radius);
        glPopMatrix();

        break;
    }

    glColor3f(1.0, 0.0, 1.0); // 원래의 선분
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(px, py);
    glVertex2f(qx, qy);
    glEnd();
    glFlush();
}

/**
 * 마우스 클릭시 호출되는 콜백
 * @param button 클릭한 버튼
 * @param state 상태
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseClick(GLint button, GLint state, GLint x, GLint y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        px = x;
        py = winH - y;
    }
}

/**
 * 마우스 모션시 호출되는 콜백
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseMotion(GLint x, GLint y) {
    qx = x;
    qy = (winH - y);
    glutPostRedisplay();
}

/**
 * 키보드 사용시 호출되는 콜백
 * @param key 누른 키
 * @param x 마우스 가로 좌표
 * @param y 마우스 세로 좌표
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'b':
        mode = LINE_BASIC;
        glutSetWindowTitle(MODE_STRINGS[mode]);
        break;
    case 'd':
        mode = LINE_DDA;
        glutSetWindowTitle(MODE_STRINGS[mode]);
        break;
    case 'r':
        mode = LINE_BRESENHAM;
        glutSetWindowTitle(MODE_STRINGS[mode]);
        break;
    case 'c':
        mode = CIRCLE_MID_POINT;
        glutSetWindowTitle(MODE_STRINGS[mode]);
        break;
    case 'q':
        exit(0);
    }

    glutPostRedisplay();
}

/**
 * 메뉴 변경시 호출되는 콜백
 * @param id 메뉴 ID
 */
void handleMenu(int id) {
    keyboard(id, 0, 0);
}

/**
 * 메뉴 초기화 함수
 */
void initMenu() {
    GLint mainMenu = glutCreateMenu(handleMenu);
    glutAddMenuEntry("Basic Line Drawing (b)", 'b');
    glutAddMenuEntry("DDA Line Drawing (d)", 'd');
    glutAddMenuEntry("Bresenham Line Drawing (r)", 'r');
    glutAddMenuEntry("Midpoint Circle Drawing (c)", 'c');
    glutAddMenuEntry("Exit (q)", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(winW, winH);
    glutCreateWindow(MODE_STRINGS[mode]);

    initMenu();

    pixelW = winW / nGrid;
    pixelH = winH / nGrid;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winW, 0, winH, -1, 1);

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}