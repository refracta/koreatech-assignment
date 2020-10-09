/**
  @file Problem1.c
  @brief Lab3-1. 블랙잭（팀5)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_LIMIT BUFSIZ
/**
  @brief 내 카드가 담길 배열
*/
int myCards[DECK_LIMIT] = { 0, };
/**
  @brief 내 카드 배열의 element push를 위한 신규 할당값 인덱스
*/
int myCardsIndex = 0;
/**
  @brief 딜러 카드가 담길 배열
*/
int dealerCards[DECK_LIMIT] = { 0, };
/**
  @brief 딜러 카드 배열의 element push를 위한 신규 할당값 인덱스
*/
int dealerCardsIndex = 0;

/**
 * @brief 1~10까지의 무작위 수를 생성합니다.
 * @return 1~10까지의 무작위 수
 */
int generateRandomValue() {
    return rand() % 10 + 1;
}

/**
 * @brief 새로운 카드를 받습니다. (나)
 */
void drawMyCard() {
    myCards[myCardsIndex++] = generateRandomValue();
}

/**
 * @brief 새로운 카드를 받습니다. (딜러)
 */
void drawDealerCard() {
    dealerCards[dealerCardsIndex++] = generateRandomValue();
}

/**
 * @brief 카드 목록을 출력합니다.
 * @param cards 카드 배열
 * @param startIndex 출력 시작 색인
 * @param limit 출력할 카드의 개수
 */
void printCard(int cards[], int startIndex, int limit) {
    for (int i = startIndex; i < startIndex + limit; i++) {
        if (cards[i] > 0) {
            printf(i == startIndex ? "%d" : " %d", cards[i]);
        } else {
            break;
        }
    }
}

/**
 * @brief 카드 값의 합산을 반환합니다.
 * @param cards 카드 배열
 * @param startIndex 합산 시작 색인
 * @param limit 합산할 카드의 개수
 * @return 카드 값 합산
 */
int getCardsSum(int cards[], int startIndex, int limit) {
    int sum = 0;
    for (int i = startIndex; i < startIndex + limit; i++) {
        if (cards[i] > 0) {
            sum += cards[i];
        } else {
            break;
        }
    }
    return sum;
}

/**
 * @brief 사용자에게 카드를 받을지 확인합니다.
 * @return 카드 받음 여부 boolean (1=받음, 0=받지 않음)
 */
int drawCardConfirm() {
    printf("카드를 받으시겠습니까 (1:받음, 0:받지 않음):");
    int yn;
    scanf("%d", &yn);
    if (!(yn == 0 || yn == 1)) {
        printf("숫자를 잘 못 입력했습니다.\n");
        return drawCardConfirm();
    } else {
        return yn;
    }
}

/**
 * @brief 유사난수 생성 시드를 초기화합니다.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief 게임 시작 전 초기화를 담당하는 함수입니다.
 */
void initGame() {
    for (int i = 0; i < 2; i++) {
        drawMyCard();
        drawDealerCard();
    }

    printf("내 카드: ");
    printCard(myCards, 0, 2);
    printf("\n");

    printf("딜러 카드: * ");
    printCard(dealerCards, 1, 1);
    printf("\n");
}

/**
 * @brief 게임 결과를 나타내는 열거형입니다.
 */
typedef enum GameResult {
    LOSE_PLAYER_BUST, WIN_DEALER_BUST, LOSE_SMALL_NUMBER, WIN_LARGE_NUMBER, DRAW
};

/**
 * @brief 나와 딜러의 카드 합산 값을 받아 게임 결과를 반환합니다.
 * @param myCardsSum 내 카드 합산
 * @param dealerCardsSum 딜러 카드 합산
 * @return 게임 결과
 */
int getGameStatus(int myCardsSum, int dealerCardsSum) {
    if (myCardsSum > 21) {
        return LOSE_PLAYER_BUST;
    } else if (dealerCardsSum > 21) {
        return WIN_DEALER_BUST;
    } else if (dealerCardsSum > myCardsSum) {
        return LOSE_SMALL_NUMBER;
    } else if (dealerCardsSum < myCardsSum) {
        return WIN_LARGE_NUMBER;
    } else {
        return DRAW;
    }
}

/**
 * @brief 게임 결과를 결과 알림 문자열로 변환합니다.
 * @param gameResult 게임 결과
 @ @return 결과 알림 문자열
 */
char *toResultString(int gameResult) {
    switch (gameResult) {
        case LOSE_PLAYER_BUST:
            return "졌습니다. (나의 버스트)";
        case WIN_DEALER_BUST:
            return "이겼습니다. (딜러의 버스트)";
        case LOSE_SMALL_NUMBER:
            return "졌습니다. (딜러보다 작은 카드 합산)";
        case WIN_LARGE_NUMBER:
            return "이겼습니다. (딜러보다 큰 카드 합산)";
        case DRAW:
            return "비겼습니다.";
    }
}

/**
 * @brief 메인 게임 로직입니다.
 */
void game() {
    while (drawCardConfirm()) {
        drawMyCard();
        drawDealerCard();
        printf("내 카드: ");
        printCard(myCards, 0, DECK_LIMIT);
        printf("\n");
        printf("딜러 카드: * ");
        printCard(dealerCards, 1, DECK_LIMIT - 1);
        printf("\n");
    }

    while (getCardsSum(dealerCards, 0, DECK_LIMIT) < 17) {
        drawDealerCard();
    }

    int myCardsSum = getCardsSum(myCards, 0, DECK_LIMIT);
    int dealerCardsSum = getCardsSum(dealerCards, 0, DECK_LIMIT);
    int gameStatus = getGameStatus(myCardsSum, dealerCardsSum);
    printf("나의 카드: %d, 딜러 카드: %d(으)로 %s", myCardsSum, dealerCardsSum, toResultString(gameStatus));
}


/**
 * @brief 시작 함수입니다.
 */
int main() {
    initRand();
    initGame();
    game();
    printf("\nPress ENTER to exit...");
    fflush(stdin);
    getchar();
}
