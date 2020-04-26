#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * 1. 중심각과 반지름을 입력받아 부채꼴의 넓이를 계산하고 출력하는 프로그램을 작성하여 보자. 원주율은 3.14라고 가정한다. 모든 변수는 float형으로 입력한다.
 */
const float ASSIGNMENT_FORM_PI = (int) (M_PI * 100) / 100.0;

void runAssignment1() {
    float centralAngle, radius;
    printf("중심각(°)과 지름을 입력하시오:");
    scanf("%f %f", &centralAngle, &radius);
    printf("부채꼴의 넓이는 %f입니다.", 1.0 / 2 * (radius * radius) * (centralAngle / 180 * ASSIGNMENT_FORM_PI));
}

int main() {
    runAssignment1();
}
