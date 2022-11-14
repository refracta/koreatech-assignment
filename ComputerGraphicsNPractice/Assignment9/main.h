#ifndef MAIN_H
#define MAIN_H

#include <cstdio>
#include <iostream>
#include <stdbool.h>
#include <gl/glut.h>
#include "glk.h"
#include <list>

#define GRADIENT(line) ((line.end.y - line.start.y) / (line.end.x - line.start.x))
#define SWAP(line) line = {{line.end.x, line.end.y}, {line.start.x, line.start.y}}
#define POINT_EQUALS(p1, p2) (p1.x == p2.x && p1.y == p2.y)
#define LINE_EQUALS(l1, l2) (POINT_EQUALS(l1.start, l2.start) && POINT_EQUALS(l1.end, l2.end))
#define x1 line.start.x
#define x2 line.end.x
#define y1 line.start.y
#define y2 line.end.y
#define xMin boundary.start.x
#define xMax boundary.end.x
#define yMin boundary.start.y
#define yMax boundary.end.y
#define BOUNDARY (1 / 3.0)
#define WINDOW_SIZE 600
#define SCALE(value) ((value - (WINDOW_SIZE / 2)) / (WINDOW_SIZE / 2.0))
#define DRAW_LINE(line) glkLine2D(line.start.x, line.start.y, line.end.x, line.end.y)

struct Point2D {
    double x;
    double y;
} typedef Point2D;

struct PointPair {
    Point2D start;
    Point2D end;
} typedef PointPair;

enum Region {
    INSIDE = 0b0000,
    LEFT = 0b0001,
    RIGHT = 0b0010,
    BOTTOM = 0b0100,
    TOP = 0b1000,
    LEFT_TOP = LEFT | TOP,
    RIGHT_TOP = RIGHT | TOP,
    LEFT_BOTTOM = LEFT | BOTTOM,
    RIGHT_BOTTOM = RIGHT | BOTTOM,
} typedef Region;

using namespace std;

bool isDragging = false;
Point2D lineStart;
Point2D lineEnd;
list<PointPair> lineList;
PointPair boundary = {{-BOUNDARY, -BOUNDARY},
                      {BOUNDARY, BOUNDARY}};

bool clipCohenSutherland(PointPair boundary, PointPair line, void (*acceptCallback)(PointPair line));
bool clipLiangBarsky(PointPair boundary, PointPair line, void (*acceptCallback)(PointPair line));
bool (*clipAlgorithm)(PointPair boundary, PointPair line, void (*acceptCallback)(PointPair line)) = clipCohenSutherland;

#endif