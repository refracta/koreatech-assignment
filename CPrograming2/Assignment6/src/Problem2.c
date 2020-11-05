/**
  @file Problem2.c
  @brief Lab6-2. ������ ���� (��1)
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  @brief ������ �迭�Դϴ�.
*/
int bet_grid[5][5] = {0,};
/**
  @brief �⺻ ��ū(��)�Դϴ�.
*/
int token = 10;

/**
  @brief bet_grid�� �ʱ�ȭ�մϴ�.
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
  @brief bet_grid�� ����մϴ�.
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
  @brief ������� ���� ���� �����ϰ� �����ɴϴ�.
  @return ���� ��
*/
int get_select_row() {
    printf("������ ���� ���� �������ּ��� : ");
    int selected_row;
    scanf("%d", &selected_row);
    int is_valid_range = 0 <= selected_row && selected_row <= 4;
    if (!is_valid_range) {
        printf("�߸��� ���� �Է��ϼ̽��ϴ�.\n");
        return get_select_row();
    }
    int is_disabled_row =
            !bet_grid[0][selected_row] && !bet_grid[1][selected_row] && !bet_grid[2][selected_row] &&
            !bet_grid[3][selected_row] &&
            !bet_grid[4][selected_row];
    if (is_disabled_row) {
        printf("�� ���� ��� ���ڰ� �Ҹ�Ǿ����ϴ�. ");
        return get_select_row();
    }
    return selected_row;
}

/**
  @brief ������� ���� �ݾ��� �����ϰ� �����ɴϴ�.
  @return ���� �ݾ�
*/
int get_bet_token() {
    printf("�����ϰ� ���� ���� �ɾ��ּ��� : ");
    int bet_token;
    scanf("%d", &bet_token);
    int is_valid_range = 0 < bet_token && bet_token <= token;
    if (!is_valid_range) {
        printf("�ּ� 1 �̻�, ���� ������ ������ �ݾ��� �ɾ���մϴ�. ");
        return get_bet_token();
    }
    return bet_token;
}

/**
  @brief �־��� �࿡���� ��ȿ�� ������ �� ������ ��ȯ�մϴ�.
  @return ��ȿ�� ������ �� ����
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
  @brief ���� �Լ��Դϴ�.
*/
int main() {
    srand(time(NULL));
    init_bet_grid();
    while (true) {
        print_bet_grid();
        printf("������ �ִ� ��ū : %d��\n", token);
        int selected_row = get_select_row();
        int bet_money = get_bet_token();
        int column = get_random_column(selected_row);

        printf("[�� : %d �� : %d]�� ��ġ�� ĭ�� ���õǾ����ϴ�.\n");
        int rate = bet_grid[column][selected_row];
        bet_grid[column][selected_row] = 0;
        int delta_money = rate * bet_money;
        printf("����� %d��(��) %s\n", delta_money * (delta_money < 0 ? -1 : 1), delta_money < 0 ? "�Ҿ����ϴ�." : "������ϴ�.");
        token += delta_money;
        if (token >= 50) {
            printf("\n�̼� ����!\n");
            break;
        } else if (token <= 0) {
            printf("\n�̼� ����...\n");
            break;
        }
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
