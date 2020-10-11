#include "tictactoe.h"

void init_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            grid[x][y] = EMPTY_SYMBOL;
        }
    }
}

void copy_grid(char destination[GRID_SIZE][GRID_SIZE], char source[GRID_SIZE][GRID_SIZE]) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            destination[x][y] = source[x][y];
        }
    }
}

void print_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int y = GRID_SIZE - 1; y >= 0; y--) {
        for (int x = 0; x < GRID_SIZE; x++) {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
}


int check_horizon(char grid[GRID_SIZE][GRID_SIZE], char target_symbol) {
    for (int y = 0; y < GRID_SIZE; y++) {
        int line = true;
        for (int x = 0; x < GRID_SIZE; x++) {
            line = line && grid[x][y] == target_symbol;
            if (!line) {
                break;
            }
        }
        if (line) {
            return true;
        }
    }
    return false;
}

int check_vertical(char grid[GRID_SIZE][GRID_SIZE], char target_symbol) {
    for (int x = 0; x < GRID_SIZE; x++) {
        int line = true;
        for (int y = 0; y < GRID_SIZE; y++) {
            line = line && grid[x][y] == target_symbol;
            if (!line) {
                break;
            }
        }
        if (line) {
            return true;
        }
    }
    return false;
}

int check_diagonal(char grid[GRID_SIZE][GRID_SIZE], char target_symbol) {
    int line1 = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        line1 = line1 && grid[i][i] == target_symbol;
        if (!line1) {
            break;
        }
    }
    int line2 = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        line2 = line2 && grid[GRID_SIZE - i - 1][i] == target_symbol;
        if (!line2) {
            break;
        }
    }
    return line1 || line2;
}

int check_total(char grid[GRID_SIZE][GRID_SIZE], char target_symbol) {
    return check_horizon(grid, target_symbol) || check_vertical(grid, target_symbol) ||
           check_diagonal(grid, target_symbol);
}

int check_finished(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (grid[x][y] == EMPTY_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

int get_grid_status(char grid[GRID_SIZE][GRID_SIZE]) {
    int is_finished = check_finished(grid);
    int ai = check_total(grid, AI_SYMBOL);
    int human = check_total(grid, HUMAN_SYMBOL);
    if ((is_finished && ai && human) || (is_finished && !ai && !human)) {
        return DRAW;
    } else if (!is_finished && ai && !human) {
        return AI_WIN;
    } else if (!is_finished && !ai && human) {
        return HUMAN_WIN;
    } else if (!is_finished && !ai && !human) {
        return NOT_FINISHED;
    } else {
        return UNKNOWN;
    }
}


int human_selection() {
    printf("Next? (1~%d):", GRID_SIZE * GRID_SIZE);
    int selection;
    scanf("%d", &selection);
    if (1 <= selection && selection <= 9) {
        return selection;
    } else {
        printf("Invalid Number!\n");
        return human_selection();
    }
}

void apply_human_selection(char grid[GRID_SIZE][GRID_SIZE]) {
    int selection = human_selection();
    selection--;
    int y = selection / GRID_SIZE;
    int x = selection - y * GRID_SIZE;
    y = GRID_SIZE - y - 1;
    if(grid[x][y] == EMPTY_SYMBOL){
        grid[x][y] = HUMAN_SYMBOL;
    }else{
        printf("Invalid Position!\n");
        apply_human_selection(grid);
    }
}

void (*user_apply_ai_selection)(char [GRID_SIZE][GRID_SIZE]);

void init_ai(void (*callback)(char [GRID_SIZE][GRID_SIZE])) {
    user_apply_ai_selection = callback;
}

void print_explain() {
    printf("<Tic-Tac-Toe>\n\nInput ↔ Grid\n");
    for (int i = 1; i <= GRID_SIZE * GRID_SIZE; i++) {
        printf("%d", i);
        if (i % GRID_SIZE != 0) {
            printf("/");
        } else {
            printf("\n");
        }
    }
    printf("====================\n");
}

void process_grid_status(char grid[GRID_SIZE][GRID_SIZE]) {
    int grid_status = get_grid_status(grid);
    switch (grid_status) {
        case AI_WIN:
            print_grid(grid);
            printf("\n");
            printf("AI WIN!");
            exit(0);
            break;
        case HUMAN_WIN:
            print_grid(grid);
            printf("\n");
            printf("HUMAN WIN!");
            exit(0);
            break;
        case DRAW:
            print_grid(grid);
            printf("\n");
            printf("DRAW!");
            exit(0);
            break;
        default:
            return;
    }
}

void run_tictactoe() {
    print_explain();
    char grid[GRID_SIZE][GRID_SIZE] = {0,};
    init_grid(grid);
    while (true) {
        print_grid(grid);
        apply_human_selection(grid);
        printf("====================\n");
        process_grid_status(grid);
        user_apply_ai_selection(grid);
        process_grid_status(grid);
    }
}