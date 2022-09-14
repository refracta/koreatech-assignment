#include "puzzle.h"

void Puzzle::init_puzzle() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i % DIM][i / DIM] = i;
    map[DIM - 1][DIM - 1] = 15;
}

bool Puzzle::move(PuzzleDirection dir) {
    int x, y;
    for (int i = 0; i < DIM * DIM; i++) {
        if (map[i % DIM][i / DIM] == 15) {
            x = i % DIM;
            y = i / DIM;
            break;
        }
    }
    if (dir == RIGHT && x > 0) {
        map[x][y] = map[x - 1][y];
        map[--x][y] = 15;
    } else if (dir == LEFT && x < DIM - 1) {
        map[x][y] = map[x + 1][y];
        map[++x][y] = 15;
    } else if (dir == UP && y < DIM - 1) {
        map[x][y] = map[x][y + 1];
        map[x][++y] = 15;
    } else if (dir == DOWN && y > 0) {
        map[x][y] = map[x][y - 1];
        map[x][--y] = 15;
    } else return false;

    return true;
}

void Puzzle::shuffle_once() {
    while (true) {
        PuzzleDirection key = (PuzzleDirection) (rand() % 4);
        if (!move(key)) {
            continue;
        } else {
            break;
        }
    }
}

bool Puzzle::is_done() {
    for (int yy = 0; yy < DIM; yy++) {
        for (int xx = 0; xx < DIM; xx++) {
            if (map[xx][yy] != xx + yy * DIM)
                return (xx == DIM - 1) && (yy == DIM - 1);
        }
    }
    return true;
}
