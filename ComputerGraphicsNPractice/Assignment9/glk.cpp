#include "glk.h"

inline void glkMatSet(
        double *m,
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33
) {
    double mat[16] = {m00, m01, m02, m03,
                      m10, m11, m12, m13,
                      m20, m21, m22, m23,
                      m30, m31, m32, m33};
    memcpy(m, mat, sizeof(double) * 16);
}

inline void glkMatMult(double *m1, double *m2, double *dst) {
    double n[16];
    for (int k = 0; k < 16; k++) {
        n[k] = 0;
        double *p = m1 + (k / 4) * 4;
        double *q = m2 + (k % 4);
        for (int i = 0; i < 4; i++) {
            n[k] += p[i] * q[i * 4];
        }
    }
    memcpy(dst != nullptr ? dst : m1, n, sizeof(double) * 16);
}

inline void glkMatPrint(double *m) {
    for (int i = 0; i < 4; i++) {
        printf("\t[");
        for (int j = 0; j < 4; j++)
            printf("%6.2f", m[i * 4 + j]);
        printf("]\n");
    }
    printf("\n");
}

inline void glkMatIdentity(double *m) {
    glkMatSet(
            m,
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

inline void glkMatTrans(double *m, double tx, double ty, double tz) {
    glkMatSet(
            m,
            1, 0, 0, tx,
            0, 1, 0, ty,
            0, 0, 1, tz,
            0, 0, 0, 1
    );
}

inline void glkMatScale(double *m, double sx, double sy, double sz) {
    glkMatSet(
            m,
            sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1
    );
}

inline void glkMatRotateX(double *m, double a) {
    glkMatSet(
            m,
            1, 0, 0, 0,
            0, COS(a), -SIN(a), 0,
            0, SIN(a), COS(a), 0,
            0, 0, 0, 1
    );
}

inline void glkMatRotateY(double *m, double a) {
    glkMatSet(
            m,
            COS(a), 0, -SIN(a), 0,
            0, 1, 0, 0,
            SIN(a), 0, COS(a), 0,
            0, 0, 0, 1
    );
}

inline void glkMatRotateZ(double *m, double a) {
    glkMatSet(
            m,
            COS(a), -SIN(a), 0, 0,
            SIN(a), COS(a), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

inline void glkMatShearX(double *m, double dy, double dz) {
    glkMatSet(
            m,
            1, dy, dz, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

// 정점의 변환 함수 [q] = [M] [p]
inline void glkTransform(double *m, double *p, double *q) {
    q[0] = q[1] = q[2] = q[3] = 0;
    for (int i = 0; i < 4; i++) {
        q[0] += m[i] * p[i];
        q[1] += m[i + 4] * p[i];
        q[2] += m[i + 8] * p[i];
        q[3] += m[i + 12] * p[i];
    }
}

// 간단한 그리기 함수들: 선분, 삼각형, 좌표축
inline void glkLine(double x1, double y1, double z1, double x2, double y2, double z2) {
    glBegin(GL_LINES);
    glVertex3d(x1, y1, z1);
    glVertex3d(x2, y2, z2);
    glEnd();
}

inline void glkTriangle4d(double *p) {
    glBegin(GL_TRIANGLES);
    glVertex4dv(p);
    glVertex4dv(p + 4);
    glVertex4dv(p + 8);
    glEnd();
}

inline void glkCoord() {
    glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    glVertex3d(-0.1, 0, 0);
    glVertex3d(1, 0, 0);

    glColor3d(0, 1, 0);
    glVertex3d(0, -0.1, 0);
    glVertex3d(0, 1, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0, 0, -0.1);
    glVertex3d(0, 0, 1);
    glEnd();
}

// GLUT를 이용한 문자열 출력
void glkString(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

// 재질의 색상 설정
void glkSetColor(float r, float g, float b, float a) {
    float color[4] = {r, g, b, a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
}

void glkLine2D(double startX, double startY, double endX, double endY) {
    glBegin(GL_LINES);
    glVertex3d(startX, startY, 0);
    glVertex3d(endX, endY, 0);
    glEnd();
}

void glkRect2D(double startX, double startY, double endX, double endY) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(startX, startY, 0);
    glVertex3f(endX, startY, 0);
    glVertex3f(endX, endY, 0);
    glVertex3f(startX, endY, 0);
    glVertex3f(startX, startY, 0);
    glEnd();
}


// 좌표계 그리기. 원점에서 +x(red), +y(blue), +z(gray)로 길이 len인 선분.
void glkDrawCoord(double len) {
    glDisable(GL_LIGHTING); // 조명 사용 설정

    glColor3f(1.0f, 0, 0);
    glkLine(0, 0, 0, len, 0, 0); // RED ==> +x axis
    glRasterPos3f(len, 0, 0);
    glkString("x");

    glColor3f(0, 1.0f, 0);
    glkLine(0, 0, 0, 0, len, 0); // GREEN ==> +y axis
    glRasterPos3f(0, len, 0);
    glkString("y");

    glColor3f(0, 0, 1.0f);
    glkLine(0, 0, 0, 0, 0, -len); // BLUE ==> -z axis
    glRasterPos3f(0, 0, -len);
    glkString("z");

    glEnable(GL_LIGHTING); // 조명 사용 설정
}