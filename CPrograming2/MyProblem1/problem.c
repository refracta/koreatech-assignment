#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x;
int y;

int outX;
int outY;

int turn = 0;

int NEXT_FUNC = 0;
int SEEK_SUCCESS = 0;
int MOVE_SUCCESS = 0;

const int MOVE_UP = 1;
const int MOVE_DOWN = 2;
const int MOVE_LEFT = 3;
const int MOVE_RIGHT = 4;
const int SEEK_UP = 5;
const int SEEK_DOWN = 6;
const int SEEK_LEFT = 7;
const int SEEK_RIGHT = 8;

int main() {
	// srand 초기화
    srand(time(NULL));
	/*
		x = rand() % 10;
		y = rand() % 10;
		outX = rand() % 10;
		outY = rand() % 10;
		// 초기화 예시입니다.
	*/
    while (!(x == outX && y == outY)) {
        // <용산 지하상가 그리기>
		
        if (turn > 1000) {
            printf("당신은 용산 지하상가 안에서 굶어죽었습니다.");
            exit(0);
        }
		
        SEEK_SUCCESS = 0;
        MOVE_SUCCESS = 0;
        switch (NEXT_FUNC) {
            case 1:
                // MOVE_UP
                break;
            case 2:
                // MOVE_DOWN
                break;
            case 3:
                // MOVE_LEFT
                break;
            case 4:
                // MOVE_RIGHT
                break;
            case 5:
                // SEEK_UP
                break;
            case 6:
                // SEEK_DOWN
                break;
            case 7:
                // SEEK_LEFT
                break;
            case 8:
                // SEEK_RIGHT
                break;
        }
        
        // <움직임 전략>
        printf("Current Turn: %d\n", turn++);
    }
    
	// <용산 지하상가 그리기>
    printf("End Turn: %d\n", turn++);
    printf("용산 지하상가에서 탈출했습니다.");
}