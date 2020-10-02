#include <stdio.h>

char chessboard[8][8] =
        {{'.', '.', '.', '.', '.', '.', '.', '.'},
         {'.', '.', 'K', '.', 'P', 'p', '.', 'P'},
         {'.', '.', '.', '.', '.', 'P', 'p', '.'},
         {'.', '.', 'p', 'k', '.', '.', 'p', '.'},
         {'.', '.', '.', 'P', '.', '.', '.', '.'},
         {'.', 'b', 'P', '.', '.', '.', '.', 'p'},
         {'.', '.', '.', '.', '.', '.', '.', '.'},
         {'.', 'q', 'n', '.', '.', '.', '.', 'r'}};

int getValue(char piece) {
    switch (piece) {
        case 'Q':
        case 'q':
            return 9;
        case 'R':
        case 'r':
            return 5;
        case 'N':
        case 'n':
        case 'B':
        case 'b':
            return 3;
        case 'P':
        case 'p':
            return 1;
        default:
            return 0;
    }
}

int evalWhite() {
    // 흰색 체스 기물의 평가값을 가져오는 함수입니다.
    int value = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int piece = chessboard[x][y];
            if (piece == 'Q' || piece == 'N' || piece == 'R' || piece == 'B' || piece == 'P') {
                value += getValue(piece);
            }
        }
    }
    return value;
}

int evalBlack() {
    // 검은색 체스 기물의 평가값을 가져오는 함수입니다.
    int value = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int piece = chessboard[x][y];
            if (piece == 'q' || piece == 'n' || piece == 'r' || piece == 'b' || piece == 'p') {
                value += getValue(piece);
            }
        }
    }
    return value;
}

void printChessboard() {
    // chessboard를 출력하는 함수입니다.
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            printf("%c", chessboard[x][y]);
        }
        printf("\n");
    }
}

int main() {
    printf("체스 보드\n");
    printChessboard();
    int black = evalBlack();
    int white = evalWhite();
    printf("흑:%d %c 백:%d, %s", black, (black > white ? '>' : black < white ? '<' : '='), white,
           (black > white ? "흑이 우세합니다." : black < white ? "백이 우세합니다." : "동률입니다."));
}
