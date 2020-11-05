/**
  @file Problem2.c
  @brief Lab6-2. 베팅판 게임 (팀1)
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  @brief 베팅판 배열입니다.
*/
int bet_grid[5][5] = {0,};
/**
  @brief 기본 토큰(돈)입니다.
*/
int token = 10;

/**
  @brief bet_grid를 초기화합니다.
*/
void init_bet_grid() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int is_odd = (x + y) % 2 == 1;
            bet_grid[x][y] = (rand() % 5 + 1) - is_odd * (5 + 1);
        }
    }
}

/**
  @brief bet_grid를 출력합니다.
*/
void print_bet_grid() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            printf("%d", bet_grid[x][y]);
            x < 5 - 1 ? printf("\t") : 0;
        }
        printf("\n");
    }
}

/**
  @brief 사용자의 선택 행을 질의하고 가져옵니다.
  @return 선택 행
*/
int get_select_row() {
    printf("던지고 싶은 행을 선택해주세요 : ");
    int selected_row;
    scanf("%d", &selected_row);
    int is_valid_range = 0 <= selected_row && selected_row <= 4;
    if (!is_valid_range) {
        printf("잘못된 수를 입력하셨습니다.\n");
        return get_select_row();
    }
    int is_disabled_row =
            !bet_grid[0][selected_row] && !bet_grid[1][selected_row] && !bet_grid[2][selected_row] &&
            !bet_grid[3][selected_row] &&
            !bet_grid[4][selected_row];
    if (is_disabled_row) {
        printf("그 행은 모든 숫자가 소모되었습니다. ");
        return get_select_row();
    }
    return selected_row;
}

/**
  @brief 사용자의 베팅 금액을 질의하고 가져옵니다.
  @return 베팅 금액
*/
int get_bet_token() {
    printf("베팅하고 싶은 돈을 걸어주세요 : ");
    int bet_token;
    scanf("%d", &bet_token);
    int is_valid_range = 0 < bet_token && bet_token <= token;
    if (!is_valid_range) {
        printf("최소 1 이상, 현재 소지금 이하의 금액을 걸어야합니다. ");
        return get_bet_token();
    }
    return bet_token;
}

/**
  @brief 주어진 행에서의 유효한 무작위 열 색인을 반환합니다.
  @return 유효한 무작위 열 색인
*/
int get_random_column(int row) {
    int current_index = 0;
    int index_array[5] = {0,};
    for (int i = 0; i < 5; i++) {
        if (bet_grid[i][row] != 0) {
            index_array[current_index++] = i;
        }
    }
    return index_array[rand() % current_index];
}

/**
  @brief 시작 함수입니다.
*/
int main() {
    srand(time(NULL));
    init_bet_grid();
    while (true) {
        print_bet_grid();
        printf("가지고 있는 토큰 : %d개\n", token);
        int selected_row = get_select_row();
        int bet_money = get_bet_token();
        int column = get_random_column(selected_row);

        printf("[행 : %d 열 : %d]에 위치한 칸이 선택되었습니다.\n");
        int rate = bet_grid[column][selected_row];
        bet_grid[column][selected_row] = 0;
        int delta_money = rate * bet_money;
        printf("당신은 %d을(를) %s\n", delta_money * (delta_money < 0 ? -1 : 1), delta_money < 0 ? "잃었습니다." : "얻었습니다.");
        token += delta_money;
        if (token >= 50) {
            printf("\n미션 성공!\n");
            break;
        } else if (token <= 0) {
            printf("\n미션 실패...\n");
            break;
        }
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
