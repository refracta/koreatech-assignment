#include "tictactoe.h"

int eval_grid(char grid[GRID_SIZE][GRID_SIZE]) {
   int grid_status = get_grid_status(grid);
   switch (grid_status) {
       case AI_WIN:
           return 1;
           // 인공지능이 이긴 경우 1 반환
       case HUMAN_WIN:
           return -1;
           //  사람이 이긴 경우 -1 반환
       case DRAW:
       case NOT_FINISHED:
       case UNKNOWN:
           return 0;
           // 그 외의 경우 0 반환
   }
}

int generateGrid(char grid[GRID_SIZE][GRID_SIZE], char (*grid_array)[GRID_SIZE][GRID_SIZE], char target_symbol) {
   int array_index = 0;
   for (int x = 0; x < GRID_SIZE; x++) {
       for (int y = 0; y < GRID_SIZE; y++) {
           if (grid[x][y] == EMPTY_SYMBOL) {
               copy_grid(grid_array[array_index], grid);
               // grid_array에 기존 grid 복사
               gridArray[array_index][x][y] = target_symbol;
               // target_symbol로 해당 위치 문자 교체
               array_index++;
               // arrayIndex 증가
           }
       }
   }
   return array_index;
   // ArraySize 반환
}

char result_grid[GRID_SIZE][GRID_SIZE];
// 인공지능의 다음 수를 저장하는 grid
int minimax(char grid[GRID_SIZE][GRID_SIZE], int depth, int original_depth, int maximizing_player) {
   int grid_status = get_grid_status(grid);
   int node_is_terminal_node = grid_status != NOT_FINISHED && grid_status != UNKNOWN;
   if (depth == 0 || node_is_terminal_node) {
       return eval_grid(grid);
       // README.md의 Pseudocode의 부분과 동일
   }
   char grid_array[GRID_SIZE * GRID_SIZE][GRID_SIZE][GRID_SIZE];
   int array_size = generateGrid(grid, grid_array, maximizing_player ? AI_SYMBOL : HUMAN_SYMBOL);
   int best_value;
   int best_grid_index;
   int is_root_node = original_depth == depth;
   if (maximizing_player) {
       best_value = -INFINITY;
       for (int i = 0; i < array_size; i++) {
           int val = minimax(grid_array[i], depth - 1, original_depth, false);
           best_value = MAX(best_value, val);
           // README.md의 Pseudocode의 부분과 동일
           if(is_root_node && val == best_value){
               best_grid_index = i;
           }
       }
   } else {
       best_value = INFINITY;
       for (int i = 0; i < array_size; i++) {
           int val = minimax(grid_array[i], depth - 1, original_depth, true);
           best_value = MIN(best_value, val);
           // README.md의 Pseudocode의 부분과 동일
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
   minimax(grid, GRID_SIZE * GRID_SIZE, GRID_SIZE * GRID_SIZE, true);
   copy_grid(grid, result_grid);
}

int main() {
   init_ai(apply_ai_selection);
   run_tictactoe();
   // 간이-틱택토 구현체 실행
}
