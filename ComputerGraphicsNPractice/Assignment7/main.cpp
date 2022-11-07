#include <gl/glut.h>
#include "Mesh.hpp"
#include "Robot.hpp"
#include "SplitView.hpp"

#define MIN_MODEL_SCALE 250
#define MAX_MODEL_SCALE 25
#define MAX_MODEL_ZOOM 8
#define MIN_MODEL_ZOOM 0.25
#define MAX_TICK_UNIT 15
#define MIN_TICK_UNIT 1
#define DEFAULT_MODEL_SCALE 70
#define DEFAULT_MODEL_ZOOM 1
#define DEFAULT_TICK_TIME 10
#define DEFAULT_TICK_UNIT 3

#define LIMIT_XY_LOCATION 1

int tickUnit = DEFAULT_TICK_UNIT;
int tickTime = DEFAULT_TICK_TIME;
double modelZoom = DEFAULT_MODEL_ZOOM;
double ModelX = 0;
double ModelY = 0;
double RotX = 0;
double RotY = 0;

Mesh loadedModel;
Robot robot(DEFAULT_MODEL_SCALE, true);

GLint PrevX;
GLint PrevY;
GLint InstDeltaX;
GLint InstDeltaY;
GLint DeltaX;
GLint DeltaY;

Quadrant previousQuadrant;
RunAnimation runAnimation;
FlyKickAnimation flyKickAnimation;

/**
 * 각기 다른 뷰 로직 처리 함수
 */
void handleViewLogic() {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    Quadrant mouseQuadrant = getMouseQuadrant(PrevX - width / 2.0, PrevY - height / 2.0);
    if (previousQuadrant != mouseQuadrant) {
        DeltaX = DeltaY = 0;
        previousQuadrant = mouseQuadrant;
    }

    // 마우스의 사분면 뷰에 대한 기능 처리
    switch (mouseQuadrant) {
        case LEFT_UP_QUADRANT:
            ModelX = DeltaX / 100.0;
            ModelX = LIMIT_XY_LOCATION < ModelX ? LIMIT_XY_LOCATION : ModelX;
            ModelX = -LIMIT_XY_LOCATION > ModelX ? -LIMIT_XY_LOCATION : ModelX;
            ModelY = DeltaY / 100.0;
            ModelY = LIMIT_XY_LOCATION < ModelY ? LIMIT_XY_LOCATION : ModelY;
            ModelY = -LIMIT_XY_LOCATION > ModelY ? -LIMIT_XY_LOCATION : ModelY;
            break;
        case LEFT_DOWN_QUADRANT:
            RotX = DeltaX;
            RotY = DeltaY;
            break;
        case RIGHT_UP_QUADRANT:
            if (InstDeltaX < 0) {
                modelZoom += MAX_MODEL_ZOOM >= modelZoom ? 0.025 : 0;
            } else if (InstDeltaX > 0) {
                modelZoom += MIN_MODEL_ZOOM <= modelZoom ? -0.025 : 0;
            }
            break;
        case RIGHT_DOWN_QUADRANT:
            if (InstDeltaX > 0) {
                robot.scale += MIN_MODEL_SCALE >= robot.scale ? 0.75 : 0;
            } else if (InstDeltaX < 0) {
                robot.scale += MAX_MODEL_SCALE <= robot.scale ? -0.75 : 0;
            }
            break;
    }
}

/**
 * 4분할 뷰 렌더링 함수
 */
void renderView(int x, int y, int width, int height,
                double upx, double upy, double upz,
                double eyex, double eyey, double eyez, bool useOrtho = true) {
    glViewport(x, y, width, height);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (useOrtho) {
        glOrtho(
                -1, 1, -1, 1,
                0, 10
        );
    } else {
        glFrustum(
                -1, 1, -1, 1,
                0, 10
        );
    }

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
            eyex, eyey, eyez,
            0, 0, 0,
            upx, upy, upz
    );

    handleViewLogic();
    glTranslated(ModelX, 0, ModelY);
    glRotated(RotX, 0, -1, 0);
    glRotated(RotY, 1, 0, 0);
    glScalef(modelZoom, modelZoom, modelZoom);

    robot.draw();
    glPopMatrix();
}

/**
 * 디스플레이 콜백 함수
 */
void display() {
    glClearColor(0.85, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    renderView(LEFT_UP_VIEW(width, height), Z_AXIS_VECTOR, Y_AXIS_EYE);
    renderView(LEFT_DOWN_VIEW(width, height), Y_AXIS_VECTOR, Z_AXIS_EYE);
    renderView(RIGHT_UP_VIEW(width, height), Y_AXIS_VECTOR, QUARTER_VIEW_EYE);
    renderView(RIGHT_DOWN_VIEW(width, height), Y_AXIS_VECTOR, X_AXIS_EYE);
    // 4개의 뷰 그리기

    glutSwapBuffers();
    glFlush();
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
            robot.bCoord = !robot.bCoord;
            break;
        case 'i':
            RotX = RotY = ModelX = ModelY = DeltaX = DeltaY = 0;
            robot.scale = DEFAULT_MODEL_SCALE;
            modelZoom = DEFAULT_MODEL_ZOOM;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glutPostRedisplay();
            break;
        case 'f':
            robot.animation = &flyKickAnimation;
            break;
        case 'r':
            robot.animation = &runAnimation;
            break;
        case 's':
            robot.animation = &robot.defaultAnimation;
            break;
        case 'z':
            tickUnit += MIN_TICK_UNIT <= tickUnit ? -1 : 0;
            break;
        case 'x':
            tickUnit += MAX_TICK_UNIT > tickUnit ? 1 : 0;
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
        PrevX = x;
        PrevY = y;
    }
}

/**
 * 마우스 모션시 호출되는 콜백
 * @param x 가로 좌표
 * @param y 세로 좌표
 */
void mouseMotion(GLint x, GLint y) {
    DeltaX += InstDeltaX = PrevX - x;
    DeltaY += InstDeltaY = PrevY - y;
    PrevX = x;
    PrevY = y;
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
    glutAddMenuEntry("Toggle axis (c)", 'c');
    glutAddMenuEntry("Init view (i)", 'i');
    glutAddMenuEntry("Stop animation (s)", 's');
    glutAddMenuEntry("Running animation (r)", 'r');
    glutAddMenuEntry("Fly kick Animation (f)", 'f');
    glutAddMenuEntry("Animation speed down (z)", 'z');
    glutAddMenuEntry("Animation speed up (x)", 'x');
    glutAddMenuEntry("Exit (q)", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * 렌더링 설정 초기화
 */
void initRendering() {
    // 조명 처리
    GLfloat light_specular[] = {0.8, 0.5, 0.8, 1.0};
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_position[] = {0.35, 0.05f, 0.05f, 0.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Mesh의 재질
    GLfloat mat_specular[] = {0.5, 1.0, 0.5, 1.0};
    GLfloat mat_shininess[] = {70.0};
    GLfloat mat_color[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING); // 조명 사용 설정
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); // 정규화
    glEnable(GL_DEPTH_TEST); // depth 검사 (Z-버퍼 사용)
    glShadeModel(GL_SMOOTH);
}

/**
 * 틱 조절 및 렌더링 처리용 타이머 함수
 * @param value 타이머 값
 */
void timer(int value) {
    robot.animation->tick += tickUnit;
    glutPostRedisplay();
    glutTimerFunc(tickTime, timer, 0);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("RobotWorld");

    initMenu();
    glutDisplayFunc(display); // 디스플레이 콜백 등록
    glutKeyboardFunc(keyboard); // 키보드 콜백 등록
    glutMouseFunc(mouseClick); // 마우스 클릭 콜백 등록
    glutMotionFunc(mouseMotion); // 마우스 모션 콜백 등록

    glutTimerFunc(tickTime, timer, 1);
    initRendering(); // 조명값 설정

    glutMainLoop();
    return 0;
}
