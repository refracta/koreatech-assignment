#include "tictactoe.h"

int eval_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    int grid_status = get_grid_status(grid);
    /*
    switch (grid_status) {
        case AI_WIN:
            // return <?>;
        case HUMAN_WIN:
            // return <?>;
        case DRAW:
            // return <?>;
        case NOT_FINISHED:
            // return <?>;
        case UNKNOWN:
            // return <?>;
    }
    */
}

int generateGrid(char grid[GRID_SIZE][GRID_SIZE], char (*gridArray)[GRID_SIZE][GRID_SIZE], char target_symbol) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (grid[x][y] == EMPTY_SYMBOL) {
                // copy_grid(gridArray[?], grid);
                // Your code
            }
        }
    }
    // return <real size of gridArray>;
}

char result_grid[GRID_SIZE][GRID_SIZE];
int minimax(char grid[GRID_SIZE][GRID_SIZE], int depth, int original_depth, int maximizing_player) {
    //if (depth == 0 || node_is_terminal_node) {
    //    return eval_grid(grid);
    //}
    char grid_array[GRID_SIZE * GRID_SIZE][GRID_SIZE][GRID_SIZE];
    int array_size = generateGrid(grid, grid_array, maximizing_player ? AI_SYMBOL : HUMAN_SYMBOL);
    int best_value;
    int best_grid_index;
    int is_root_node = original_depth == depth;
    if (maximizing_player) {
        best_value = -INFINITY;
        for (int i = 0; i < array_size; i++) {
            int val;
            // Your code
            if(is_root_node && val == best_value){
                best_grid_index = i;
            }
        }
    } else {
        best_value = INFINITY;
        for (int i = 0; i < array_size; i++) {
            int val;
            // Your code
            if(is_root_node && val == best_value){
                best_grid_index = i;
            }
        }
    }
    if (is_root_node) {
        copy_grid(result_grid, grid_array[best_grid_index]);
    }
    return best_value;
}

void apply_ai_selection(char grid[GRID_SIZE][GRID_SIZE]) {
    // 인공지능의 행동 함수입니다. 현재 틱택토 판을 매개변수로 받습니다.
    minimax(grid, GRID_SIZE * GRID_SIZE, GRID_SIZE * GRID_SIZE, true);
    copy_grid(grid, result_grid);
}

int main() {
    init_ai(apply_ai_selection);
    // 인공지능의 행동 함수를 매개변수로 넘기면

    run_tictactoe();
    // 이제 모든 것은 간이-틱택토 구현체가 알아서 합니다.
    // 항상 사람이 먼저 차례를 가지게 구현되었습니다.
}