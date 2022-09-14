#include <stdio.h>
#include <math.h>

/**
 * 3. 2차원 공간에서 두 점 사이의 거리를 계산하는 프로그램을 작성하라. 제곱근의 계산은 <math.h>에 정의된 sqrt() 함수를 사용한다.
 */
void runAssignment3() {
    int x1, x2, y1, y2;
    printf("첫 번째 점의 위치(x, y): ");
    scanf("%d %d", &x1, &y1);
    printf("두 번째 점의 위치(x, y): ");
    scanf("%d %d", &x2, &y2);
    printf("두 점 사이의 거리는 %lf입니다.", sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

int main() {
    runAssignment3();
}
