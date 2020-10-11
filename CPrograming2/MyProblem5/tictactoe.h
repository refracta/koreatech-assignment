#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define HUMAN_SYMBOL 'O'
#define AI_SYMBOL 'X'
#define EMPTY_SYMBOL '.'
#define GRID_SIZE 3
#define INFINITY INT_MAX
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

#define DRAW 0
#define AI_WIN 1
#define HUMAN_WIN 2
#define NOT_FINISHED 3
#define UNKNOWN 4

void copy_grid(char [GRID_SIZE][GRID_SIZE], char [GRID_SIZE][GRID_SIZE]);
void print_grid(char [GRID_SIZE][GRID_SIZE]);
int get_grid_status(char [GRID_SIZE][GRID_SIZE]);
void init_ai(void (*)(char [GRID_SIZE][GRID_SIZE]));
void run_tictactoe();