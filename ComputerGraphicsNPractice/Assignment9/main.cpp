#include "main.h"

/**
 * 경계 박스와 점을 매개변수로 받아 점의 위치를 Region 열거형으로 반환한다
 * @param boundary 경계 박스
 * @param point 위치를 판별할 점
 * @return 점의 Region
 */
Region toRegion(PointPair boundary, Point2D point) {
    int region = INSIDE;
    if (point.x < boundary.start.x) {
        region |= LEFT;
    } else if (boundary.end.x < point.x) {
        region |= RIGHT;
    }
    if (point.y < boundary.start.y) {
        region |= BOTTOM;
    } else if (boundary.end.y < point.y) {
        region |= TOP;
    }
    return (Region) region;
}

/**
 * Cohen-Sutherland 알고리즘 구현체
 * @param boundary 경계 박스
 * @param line 자를 직선
 * @param acceptCallback aceept시 호출할 콜백 함수
 * @return aceept 여부 (bool)
 */
bool clipCohenSutherland(PointPair boundary, PointPair line, void (*acceptCallback)(PointPair line)) {
    while (true) {
        Region startRegion = toRegion(boundary, line.start);
        Region endRegion = toRegion(boundary, line.end);

        if (startRegion == INSIDE && endRegion == INSIDE) {
            acceptCallback(line);
            return true;
        } else if (startRegion & endRegion) {
            return false;
        } else {
            Region outerRegion = startRegion;
            if (outerRegion == INSIDE) {
                outerRegion = endRegion;
                // 항상 start, end 점 중 바깥에 있는 점의 Region을 사용하도록 처리
                SWAP(line);
                // 항상 x1, y1을 외부의 있는 점으로 설정함
            }
            double m = GRADIENT(line);
            if (outerRegion & LEFT) {
                y1 += (xMin - x1) * m;
                x1 = xMin;
            } else if (outerRegion & RIGHT) {
                y1 += (xMax - x1) * m;
                x1 = xMax;
            } else if (outerRegion & BOTTOM) {
                x1 += (yMin - y1) / m;
                y1 = yMin;
            } else if (outerRegion & TOP) {
                x1 += (yMax - y1) / m;
                y1 = yMax;
            }
        }
    }
}

/**
 * Liang-Barsky 알고리즘에서 사용하는 직선 테스트 함수
 * @param p Liang-Barsky 부등식에서의 p_k
 * @param q Liang-Barsky 부등식에서의 q_k
 * @param u1 P_outer의 매개변수 (외부->내부 직선의 좌측점)
 * @param u2 P_inner의 매개변수 (내부->외부 직선의 우측점)
 * @return 클립 테스트 결과 (참인 경우 이어서 다음 클립 테스트 진행)
 */
bool clipTest(double p, double q, double &u1, double &u2) {
    bool result = true;
    double r = q / p;
    if (p < 0) {
        // 외부 -> 내부
        if (r > u2) {
            result = false;
        } else if (r > u1) {
            u1 = r;
        }
    } else if (p > 0) {
        // 내부 -> 외부
        if (r < u1) {
            result = false;
        } else if (r < u2) {
            u2 = r;
        }
    } else {
        // 수직 또는 수평선
        if (q < 0) {
            result = false;
        }
    }

    return result;
}

/**
 * Liang-Barsky 알고리즘 구현체
 * @param boundary 경계 박스
 * @param line 자를 직선
 * @param acceptCallback aceept시 호출할 콜백 함수
 * @return
 */
bool clipLiangBarsky(PointPair boundary, PointPair line, void (*acceptCallback)(PointPair line)) {
    double u1 = 0;
    double u2 = 1;
    double dx = x2 - x1;
    double dy = y2 - y1;
    PointPair originalLine = line;
    if (clipTest(-dx, x1 - xMin, u1, u2)) {
        if (clipTest(dx, xMax - x1, u1, u2)) {
            if (clipTest(-dy, y1 - yMin, u1, u2)) {
                if (clipTest(dy, yMax - y1, u1, u2)) {
                    if (u2 < 1) {
                        x2 = x1 + u2 * dx;
                        y2 = y1 + u2 * dy;
                    }
                    if (u1 > 0) {
                        x1 = x1 + u1 * dx;
                        y1 = y1 + u1 * dy;
                    }
                }
            }
        }
    }

    if (!LINE_EQUALS(originalLine, line)) {
        acceptCallback(line);
        return true;
    } else {
        return false;
    }
}

/**
 * Accept시 직선 정보를 출력한다
 * @param line 잘라진 직선
 */
void printAcceptResult(PointPair line) {
    printf(" ---> Accept: (%lf, %lf) to (%lf, %lf)\n", x1, y1, x2, y2);
}

/**
 * Accept시 직선을 렌더링한다
 * @param line 잘라진 직선
 */
void accept(PointPair line) {
    DRAW_LINE(line);
}

void drawBoundaryLine() {
    glColor3f(0, 0, 0);
    glLineWidth(1);
    glkLine2D(-1, BOUNDARY, 1, BOUNDARY);
    glkLine2D(-1, -BOUNDARY, 1, -BOUNDARY);
    glkLine2D(BOUNDARY, -1, BOUNDARY, 1);
    glkLine2D(-BOUNDARY, -1, -BOUNDARY, 1);
    glColor3f(0, 1, 0);
    glkRect2D(-BOUNDARY, -BOUNDARY, BOUNDARY, BOUNDARY);
}

/**
 * 디스플레이 콜백 함수
 */
void display() {
    glClearColor(0.85, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBoundaryLine();
    for (PointPair &line: lineList) {
        glColor3f(1, 0, 0);
        glLineWidth(1);
        DRAW_LINE(line);
        glColor3f(1, 1, 0);
        glLineWidth(2);
        clipAlgorithm(boundary, line, accept);
    }
    // 이전에 그린 직선 그리기

    if (isDragging) {
        PointPair line = {lineStart, lineEnd};
        glColor3f(0, 0, 1);
        glLineWidth(1);
        DRAW_LINE(line);
        glColor3f(0, 1, 1);
        glLineWidth(2);
        clipAlgorithm(boundary, line, accept);
    }
    // 드래그 중인 직선 그리기

    glutSwapBuffers();
}

/**
 * 키보드 사용시 호출되는 콜백
 * @param key 누른 키
 * @param x 마우스 가로 좌표
 * @param y 마우스 세로 좌표
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
            clipAlgorithm = clipCohenSutherland;
            break;
        case 'l':
            clipAlgorithm = clipLiangBarsky;
            break;
        case 'r':
            lineList.clear();
            break;
        case 'q':
            exit(0);
    }
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
        // 마우스를 눌렀을 때 처리
        lineStart.x = SCALE(x);
        lineStart.y = -SCALE(y);
        isDragging = true;
    } else if (state == GLUT_UP) {
        // 마우스를 놓았을 때 처리
        lineEnd.x = SCALE(x);
        lineEnd.y = -SCALE(y);
        PointPair line = {lineStart, lineEnd};
        printf("Algorithm: %s\n", clipAlgorithm == clipLiangBarsky ? "Liang-Barsky" : "Cohen-Sutherland");
        printf("Line: (%lf, %lf) to (%lf, %lf)", x1, y1, x2, y2);
        if (!clipAlgorithm(boundary, line, printAcceptResult)) {
            printf(" ---> Reject\n");
        }
        lineList.push_back(line);
        // 직선 리스트에 직선 추가
        isDragging = false;
    }
}

/**
 * 마우스 모션시 호출되는 콜백
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseMotion(GLint x, GLint y) {
    lineEnd.x = SCALE(x);
    lineEnd.y = -SCALE(y);
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
    glutAddMenuEntry("Use Cohen-Sutherland Algorithm (c)", 'c');
    glutAddMenuEntry("Use Liang-Barsky Algorithm (l)", 'l');
    glutAddMenuEntry("Clear line (r)", 'r');
    glutAddMenuEntry("Exit (q)", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("ClipLine");

    initMenu();
    glutDisplayFunc(display); // 디스플레이 콜백 등록
    glutKeyboardFunc(keyboard); // 키보드 콜백 등록
    glutMouseFunc(mouseClick); // 마우스 클릭 콜백 등록
    glutMotionFunc(mouseMotion); // 마우스 모션 콜백 등록

    glutMainLoop();
    return 0;
}
