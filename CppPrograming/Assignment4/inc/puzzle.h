#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdlib.h>

#define DIM 4
#define END_PUZZLE_INDEX (DIM*DIM-1)

#define TO_PUZZLE_DIRECTION(c) \
    (   (PuzzleDirection)      \
    (                          \
        c == 'U' ? (UP) :      \
        c == 'D' ? (DOWN) :    \
        c == 'L' ? (LEFT) :    \
        c == 'R' ? (RIGHT) :   \
        NULL                   \
    )                          \
    )
#define TO_REVERSE_PUZZLE_DIRECTION(c) \
    (   (PuzzleDirection)      \
    (                          \
        c == 'D' ? (UP) :      \
        c == 'U' ? (DOWN) :    \
        c == 'R' ? (LEFT) :    \
        c == 'L' ? (RIGHT) :   \
        NULL                   \
    )                          \
    )

typedef enum
{
    LEFT, RIGHT, UP, DOWN
} PuzzleDirection;

class Puzzle {
public:
    int map[DIM][DIM];

    void init_puzzle();
    bool move(PuzzleDirection dir);
    void shuffle_once();
    bool is_done();
};

#endif