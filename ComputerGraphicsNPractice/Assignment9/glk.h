#pragma once

#include <stdio.h>
#include <memory.h>
#include <gl/glut.h>

#define _USE_MATH_DEFINES

#include <math.h>

#include <string.h>

#define SIN(x) sin(x*M_PI / 180.)
#define COS(x) cos(x*M_PI / 180.)

#define TO_COLOR_F(hexColor) ((hexColor & 0xFF0000) >> 16) / ((float) 0xFF), ((hexColor & 0x00FF00) >> 8) / ((float) 0xFF), (hexColor & 0x0000FF) / ((float) 0xFF)

inline void glkMatSet(
        double *m,
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33
);

inline void glkMatMult(double *m1, double *m2, double *dst = nullptr);

inline void glkMatPrint(double *m);

inline void glkMatIdentity(double *m);

inline void glkMatTrans(double *m, double tx, double ty, double tz);

inline void glkMatScale(double *m, double sx, double sy, double sz);

inline void glkMatRotateX(double *m, double a);

inline void glkMatRotateY(double *m, double a);

inline void glkMatRotateZ(double *m, double a);

inline void glkMatShearX(double *m, double dy, double dz);

inline void glkTransform(double *m, double *p, double *q);

inline void glkLine(double x1, double y1, double z1, double x2, double y2, double z2);

inline void glkTriangle4d(double *p);

inline void glkCoord();

void glkString(const char *s);

void glkSetColor(float r, float g, float b, float a);

void glkLine2D(double startX, double startY, double endX, double endY);

void glkRect2D(double startX, double startY, double endX, double endY);

void glkDrawCoord(double len);