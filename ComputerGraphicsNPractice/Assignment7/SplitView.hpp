#pragma once

#define LEFT_UP_VIEW(width, height) 0, height/2.0 , width/2.0, height/2.0
#define LEFT_DOWN_VIEW(width, height) 0, 0, width/2.0, height/2.0
#define RIGHT_UP_VIEW(width, height) width/2.0, height/2.0, width/2.0, height/2.0
#define RIGHT_DOWN_VIEW(width, height) width/2.0, 0, width/2.0, height/2.0

#define X_AXIS_EYE 1, 0, 0
#define Y_AXIS_EYE 0, 1, 0
#define Z_AXIS_EYE 0, 0, -1
#define QUARTER_VIEW_EYE 0.2, -0.2, 0.2, false
#define X_AXIS_VECTOR 1, 0, 0

#define Y_AXIS_VECTOR 0, 1, 0
#define Z_AXIS_VECTOR 0, 0, 1

enum Quadrant {
    RIGHT_UP_QUADRANT = 0,
    LEFT_UP_QUADRANT = 1,
    LEFT_DOWN_QUADRANT = 2,
    RIGHT_DOWN_QUADRANT = 3
} typedef Quadrant;

/**
 * x와 y값을 받아 해당 사분면 열거형을 반환
 * @param x 좌표평면상의 x값
 * @param y 좌표평면상의 y값
 * @return 사분면 열거형
 */
Quadrant getQuadrant(double x, double y) {
    double location = atan2(y, x);
    location = (location < 0 ? location + 2 * M_PI : location) / M_PI_2;
    int quadrant = (int) location;
    return (Quadrant) quadrant;
}

/**
 * Mouse delta x와 y값을 받아 해당 사분면 열거형을 반환
 * @param x 좌표평면상의 x값
 * @param y 좌표평면상의 y값
 * @return 사분면 열거형
 */
Quadrant getMouseQuadrant(double x, double y) {
    return (Quadrant) (3 - getQuadrant(x, y));
}