#include <stdio.h>
#include "APSimulator.h"

int controlDevil(char grid[GRID_WIDTH][GRID_HEIGHT], int angelIndex, int turn) {
    // @param grid - ���� �ϴ��� [0][0]�� ���� ���� �������Դϴ�. �Ʒ��� ���ں� ��ǥ ������ �����Դϴ�.
    // AB A(0, 1), B(1, 1)
    // CD C(0, 0), D(0, 1)
    // �����δ� grid���� õ��� 'A', ���ŵ� ����� '#', �� ������ '.'���� ǥ��˴ϴ�.

    // @param angelIndex - 1����ȭ�� õ���� 2���� �����Դϴ�.
    // https://ko.wikipedia.org/wiki/������ - Compressed sparse row ����

    // @param turn - ���� ���� ���Դϴ�.

    int x = to2DX(angelIndex);
    int y = to2DY(angelIndex);
    // ����� ������ 2���� �迭 �������� �и��մϴ�.
    // x, y�� grid ���ο� ��ġ�� õ���� �����Դϴ�. 

    if(turn == 0){
        // turn�� 0���� �����մϴ�.
    }

    // �� �Լ��� ��ȯ�ϴ� ��ǥ ���� ���� ���ʿ� �Ǹ��� ������ ����� ��ġ�� �˴ϴ�.
    // toIndex(x, y) �Լ��� 2���� �迭 ���θ� 1���� �������� �����Ͽ� ��ȯ�ؾ� �մϴ�.
    return toIndex(turn, 16 + 1);
}

int main() {
    initSimulator(controlDevil);
    // �Ǹ��� �����ϴ� �Լ��� �Ű������� �ѱ��
    runSimulator();
    // ���� ��� ���� �ùķ����Ͱ� �˾Ƽ� �մϴ�.
}
