#include <gl/glut.h>
#include "Mesh.hpp"
#include "Robot.hpp"

#define MIN_MODEL_SCALE 150
#define MAX_MODEL_SCALE 50
float modelScale = 70;

bool bCoord = true;
bool renderModel = false;
Mesh loadedModel;
Robot robot(modelScale, true);

/**
 * 디스플레이 콜백 함수
 */
void display() {
    glClearColor(0.85, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (renderModel) {
        glkSetColor(0.8, 0.8, 0.8, 1);
        loadedModel.draw(modelScale, bCoord);
    } else {
        robot.bCoord = bCoord;
        robot.scale = modelScale;
        robot.draw();
    }
    glutSwapBuffers();
}

/**
 * 키보드 사용시 호출되는 콜백
 * @param key 누른 키
 * @param x 마우스 가로 좌표
 * @param y 마우스 세로 좌표
 */
void keyboard(unsigned char key, int x, int y) {
    char *fileName;
    switch (key) {
        case 'l':
            fileName = glkFileDlg(FILTER_ASE);
            loadedModel.clearAse();
            loadedModel.readAse(fileName);
            renderModel = true;
            break;
        case 't':
            renderModel = !renderModel;
            break;
        case 'c':
            bCoord = !bCoord;
            break;
        case 'i':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            break;
        case 'w':
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonMode(GL_BACK, GL_POINT);
            break;
        case 's':
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_LINE);
            break;
        case 'z':
            modelScale += MIN_MODEL_SCALE >= modelScale ? 5 : 0;
            break;
        case 'Z':
            modelScale += MAX_MODEL_SCALE <= modelScale ? -5 : 0;
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

GLint PrevX;
GLint PrevY;

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
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - PrevX, 0, -1, 0);
    glRotated(y - PrevY, -1, 0, 0);
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
    glutAddMenuEntry("Load model (l)", 'l');
    glutAddMenuEntry("Toggle view [Robot <-> Model] (t)", 't');
    glutAddMenuEntry("Toggle axis (c)", 'c');
    glutAddMenuEntry("Init view (i)", 'i');
    glutAddMenuEntry("Wire mode (w)", 'w');
    glutAddMenuEntry("Solid mode (s)", 's');
    glutAddMenuEntry("Resize: Smaller (z)", 'z');
    glutAddMenuEntry("Resize: Bigger (Z)", 'Z');
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
    // glEnable(GL_NORMALIZE); // 정규화
    glEnable(GL_DEPTH_TEST); // depth 검사 (Z-버퍼 사용)
    glShadeModel(GL_SMOOTH);
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

    initRendering(); // 조명값 설정
    // keyboard('l', 0, 0);

    glutMainLoop();
    return 0;
}
