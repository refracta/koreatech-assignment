#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char yongsanDungeon[12][12] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
                               {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};


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


char direction = '.';
int seekStatus = 0;
int leftComplete = 0;

int main() {
    srand(time(NULL));
    x = rand() % 10 + 1;
    y = rand() % 10 + 1;
    yongsanDungeon[x][y] = '@';
    outX = rand() % 10 + 1;
    outY = rand() % 10 + 1;
    yongsanDungeon[outX][outY] = '<';

    while (!(x == outX && y == outY)) {
        // <용산 지하상가 그리기 - 시작>
        for (int y = 11; y >= 0; y--) {
            for (int x = 0; x < 12; x++) {
                printf("%c", yongsanDungeon[x][y]);
            }
            printf("\n");
        }
        // <용산 지하상가 그리기 - 끝>

        if (turn > 1000) {
            printf("당신은 용산 지하상가를 안에서 굶어죽었습니다.");
            exit(0);
        }

        SEEK_SUCCESS = 0;
        MOVE_SUCCESS = 0;
        switch (NEXT_FUNC) {
            case 1:
                // MOVE_UP
                if (y < 12 - 2) {
                    yongsanDungeon[x][y] = '.';
                    y++;
                    yongsanDungeon[x][y] = '@';
                    MOVE_SUCCESS = 1;
                }
                break;
            case 2:
                // MOVE_DOWN
                if (y > 0 + 1) {
                    yongsanDungeon[x][y] = '.';
                    y--;
                    yongsanDungeon[x][y] = '@';
                    MOVE_SUCCESS = 1;
                }
                break;
            case 3:
                // MOVE_LEFT
                if (x > 0 + 1) {
                    yongsanDungeon[x][y] = '.';
                    x--;
                    yongsanDungeon[x][y] = '@';
                    MOVE_SUCCESS = 1;
                }
                break;
            case 4:
                // MOVE_RIGHT
                if (x < 12 - 2) {
                    yongsanDungeon[x][y] = '.';
                    x++;
                    yongsanDungeon[x][y] = '@';
                    MOVE_SUCCESS = 1;
                }
                break;
            case 5:
                // SEEK_UP
                for (int yPos = y + 1; yPos < 12 - 1; yPos++) {
                    if (yongsanDungeon[x][yPos] == '<') {
                        SEEK_SUCCESS = 1;
                        break;
                    }
                }
                break;
            case 6:
                // SEEK_DOWN
                for (int yPos = y - 1; yPos > 0; yPos--) {
                    if (yongsanDungeon[x][yPos] == '<') {
                        SEEK_SUCCESS = 1;
                        break;
                    }
                }
                break;
            case 7:
                // SEEK_LEFT
                for (int xPos = x - 1; xPos > 0; xPos--) {
                    if (yongsanDungeon[xPos][y] == '<') {
                        SEEK_SUCCESS = 1;
                        break;
                    }
                }
                break;
            case 8:
                // SEEK_RIGHT
                for (int xPos = x + 1; xPos < 12 - 1; xPos++) {
                    if (yongsanDungeon[xPos][y] == '<') {
                        SEEK_SUCCESS = 1;
                        break;
                    }
                }
                break;
        }

        /*
         * char direction = '.';
         * int seekStatus = 0;
         * int leftComplete = 0;
         */

        // <움직임 전략 - 시작>
        if (direction == '.') {
            direction = NEXT_FUNC == SEEK_UP && SEEK_SUCCESS ? 'u' : (NEXT_FUNC == SEEK_DOWN && SEEK_SUCCESS ? 'd' : '.');
            // 이전 동작이 SEEK_UP이고 성공한 경우 'u'
            // 그렇지 않은 경우 이전 동작이 SEEK_DOWN이고 성공한 경우 'd'
            // 위의 두 경우 모두 아닌 경우면 '.'
        }
        if (!leftComplete) {
            leftComplete = NEXT_FUNC == MOVE_LEFT && !MOVE_SUCCESS ? 1 : 0;
            // 이전 동작이 MOVE_LEFT이고 움직이는데 실패했으면 1 아니면 0
        }
        if (!leftComplete) {
            NEXT_FUNC = MOVE_LEFT;
            // 왼쪽 벽에 붙을 때 까지 왼쪽으로 이동
        } else {
            if (direction == 'u') {
                NEXT_FUNC = MOVE_UP;
                // 현재 위치 위에 출구가 있다는 것을 발견한 경우 위쪽으로 계속 이동
            } else if (direction == 'd') {
                NEXT_FUNC = MOVE_DOWN;
                // 현재 위치 위에 출구가 있다는 것을 발견한 경우 아래쪽으로 계속 이동
            } else {
                if (seekStatus == 0) {
                    NEXT_FUNC = SEEK_UP;
                    seekStatus++;
                    // *왼쪽 끝으로 이동했을 때부터 이 부분이 시작됨
                    // 다음 동작을 SEEK_UP으로 변경하여 위쪽에 출구가 있는지 살핌
                    // 위쪽에 출구가 있는 경우 direction 변수가 'u'가 되므로 올라가게 됨
                    // 위쪽에 출구가 없는 경우 seekStatus 2인 경우가 실행됨
                } else if (seekStatus == 1) {
                    NEXT_FUNC = SEEK_DOWN;
                    seekStatus++;
                    // 다음 동작을 SEEK_DOWN으로 변경하여 아래쪽에 출구가 있는지 살핌
                    // 아래쪽에 출구가 있는 경우 direction 변수가 'd'가 되므로 내려가게 됨
                    // 아래쪽에 출구가 없는 경우 seekStatus 3인 경우가 실행됨
                } else if (seekStatus == 2) {
                    NEXT_FUNC = MOVE_RIGHT;
                    seekStatus = 0;
                    // 위쪽과 아래쪽에서 모두 출구를 발견하지 못했으므로 우측으로 이동함
                }
            }
        }
        // <움직임 전략 - 끝>
        printf("Current Turn: %d\n", turn++);
    }

    // <용산 지하상가 그리기 - 시작>
    for (int y = 11; y >= 0; y--) {
        for (int x = 0; x < 12; x++) {
            printf("%c", yongsanDungeon[x][y]);
        }
        printf("\n");
    }
    // <용산 지하상가 그리기 - 끝>
    printf("End Turn: %d\n", turn);
    printf("용산 지하상가에서 탈출했습니다.");
}
