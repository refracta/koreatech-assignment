#include <stdio.h>

const int GRID_WIDTH = 40;
const int GRID_HEIGHT = 40;

char grid[40][40];
char copyGrid[40][40];

int main() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[x][y] = '.';
        }
    }
    // grid 배열 초기화

    grid[20][20] = '#';
    grid[20 + 1][20] = '#';
    grid[20 + 2][20] = '#';
    grid[20][20 + 1] = '#';
    grid[20][20 + 2] = '#';
    grid[20 + 4][20 + 4] = '#';
    grid[20 + 3][20 + 4] = '#';
    grid[20 + 2][20 + 4] = '#';
    grid[20 + 4][20 + 3] = '#';
    grid[20 + 4][20 + 2] = '#';
    grid[20 + 1][20 + 3] = '#';
    grid[20 + 3][20 + 1] = '#';
    // 복제기 그리기

    for (int g = 0; g <= 96; g++) {
        // 세대 루프
        for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                printf("%c", grid[x][y]);
            }
            printf("\n");
        }
        printf("%d세대\n\n", g);
        // 격자판 출력

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                copyGrid[x][y] = grid[x][y];
            }
        }
        // grid 배열의 내용을 copyGrid 배열로 복사

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                int liveCell = 0;
                int dx, dy;
                int cx, cy;

                /* dx = 1 Case */
                dx = 1, dy = 1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                dx = 1, dy = 0;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                dx = 1, dy = -1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                /* dx = 0 Case */
                dx = 0, dy = 1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                dx = 0, dy = -1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                /* dx = -1 Case */
                dx = -1, dy = 1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                dx = -1, dy = 0;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';

                dx = -1, dy = -1;
                cx = (x + dx) % GRID_WIDTH, cx = cx < 0 ? cx + GRID_WIDTH : cx;
                cy = (y + dy) % GRID_HEIGHT, cy = cy < 0 ? cy + GRID_HEIGHT : cy;
                liveCell += copyGrid[cx][cy] == '#';


                if (copyGrid[x][y] == '.') {
                    // 죽음 상태의 세포
                    // B36
                    if (liveCell == 3 || liveCell == 6) {
                        grid[x][y] = '#';
                    } else {
                        grid[x][y] = '.';
                    }
                } else {
                    // 생존 상태의 세포
                    // S23
                    if (liveCell == 2 || liveCell == 3) {
                        grid[x][y] = '#';
                    } else {
                        grid[x][y] = '.';
                    }
                }
            }
        }
    }
}
