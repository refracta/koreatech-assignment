#include <stdio.h>
#include "APSimulator.h"

int controlDevil(char grid[GRID_WIDTH][GRID_HEIGHT], int angelIndex, int turn) {
    // @param grid - 좌측 하단이 [0][0]인 현재 상태 격자판입니다. 아래는 글자별 좌표 배정의 예시입니다.
    // AB A(0, 1), B(1, 1)
    // CD C(0, 0), D(0, 1)
    // 실제로는 grid에서 천사는 'A', 제거된 블록은 '#', 빈 공간은 '.'으로 표기됩니다.

    // @param angelIndex - 1차원화된 천사의 2차원 색인입니다.
    // https://ko.wikipedia.org/wiki/희소행렬 - Compressed sparse row 참조

    // @param turn - 현재 차례 수입니다.

    int x = to2DX(angelIndex);
    int y = to2DY(angelIndex);
    // 압축된 색인을 2차원 배열 색인으로 분리합니다.
    // x, y는 grid 내부에 위치한 천사의 색인입니다. 

    if(turn == 0){
        // turn은 0부터 시작합니다.
    }

    // 이 함수가 반환하는 좌표 값이 다음 차례에 악마가 제거할 블록의 위치가 됩니다.
    // toIndex(x, y) 함수로 2차원 배열 색인를 1차원 색인으로 압축하여 반환해야 합니다.
    return toIndex(turn, 16 + 1);
}

int main() {
    initSimulator(controlDevil);
    // 악마를 제어하는 함수를 매개변수로 넘기면
    runSimulator();
    // 이제 모든 것은 시뮬레이터가 알아서 합니다.
}
