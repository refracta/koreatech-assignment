#include <stdio.h>
#include "APSimulator.h"

#define DISTANCE 16
// 2^(4K^3)
const int devilY = DISTANCE + 1;
// 악마의 고정 Y 색인
const int separationDistance = 4;
// 악마가 건너뛸 칸의 거리

int removedXIndexArray[GRID_HEIGHT];
// 삭제된 블럭의 x 좌표를 저장하는 배열
int rxiaIndex;
// removedXIndexArray의 배열 커서

// rxia를 초기화하는 함수
void initRXIA() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        removedXIndexArray[i] = -1;
    }
    rxiaIndex = 0;
}

// rxia에 값을 추가하는 함수
void addToRXIA(int index) {
    removedXIndexArray[rxiaIndex++] = index;
}

int xIndex;
// 삭제할 x 색인값의 저장 변수

int controlDevil(char grid[GRID_WIDTH][GRID_HEIGHT], int angelIndex, int turn) {
    int x = to2DX(angelIndex);
    int y = to2DY(angelIndex);
    int range = devilY - y;
    if (turn == 0) {
        // 초기화 코드
        initRXIA();
        xIndex = x - range;
    } else if (turn == 9 || turn == 13 || turn == 15) {
        // 각 천사가 남은 거리의 절반이 되는 차례마다
        // 천사 원뿔 내부 내부에 위치한 가장 왼쪽의 삭제 블럭의 x 색인을 구하고
        // xIndex를 구한 x 색인의 한칸 이전 칸으로 설정
        for (int i = 0; i < rxiaIndex; i++) {
            int ix = removedXIndexArray[i];
            if (x - range < ix) {
                xIndex = ix - 1;
                initRXIA();
                break;
            }
        }
    } else if (turn == 16) {
        // 마지막 차례에 천사와 같은 x 색인의 블럭 삭제 (미관상 삽입)
        return toIndex(x, y + 2);
    }

    int removeIndex = toIndex(xIndex, devilY);
    // xIndex와 devilY에 위치한 칸의 2차원 색인을 1차원 색인으로 압축함
    addToRXIA(xIndex);
    xIndex += separationDistance;
    // xIndex를 separationDistance만큼 증가시킴
    return removeIndex;
}

// 시작 함수
int main() {
    initSimulator(controlDevil);
    runSimulator();
}
