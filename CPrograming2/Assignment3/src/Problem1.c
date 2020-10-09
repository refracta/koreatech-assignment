/**
  @file Problem1.c
  @brief Lab3-1. ���裨��5)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_LIMIT BUFSIZ
/**
  @brief �� ī�尡 ��� �迭
*/
int myCards[DECK_LIMIT] = { 0, };
/**
  @brief �� ī�� �迭�� element push�� ���� �ű� �Ҵ簪 �ε���
*/
int myCardsIndex = 0;
/**
  @brief ���� ī�尡 ��� �迭
*/
int dealerCards[DECK_LIMIT] = { 0, };
/**
  @brief ���� ī�� �迭�� element push�� ���� �ű� �Ҵ簪 �ε���
*/
int dealerCardsIndex = 0;

/**
 * @brief 1~10������ ������ ���� �����մϴ�.
 * @return 1~10������ ������ ��
 */
int generateRandomValue() {
    return rand() % 10 + 1;
}

/**
 * @brief ���ο� ī�带 �޽��ϴ�. (��)
 */
void drawMyCard() {
    myCards[myCardsIndex++] = generateRandomValue();
}

/**
 * @brief ���ο� ī�带 �޽��ϴ�. (����)
 */
void drawDealerCard() {
    dealerCards[dealerCardsIndex++] = generateRandomValue();
}

/**
 * @brief ī�� ����� ����մϴ�.
 * @param cards ī�� �迭
 * @param startIndex ��� ���� ����
 * @param limit ����� ī���� ����
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
 * @brief ī�� ���� �ջ��� ��ȯ�մϴ�.
 * @param cards ī�� �迭
 * @param startIndex �ջ� ���� ����
 * @param limit �ջ��� ī���� ����
 * @return ī�� �� �ջ�
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
 * @brief ����ڿ��� ī�带 ������ Ȯ���մϴ�.
 * @return ī�� ���� ���� boolean (1=����, 0=���� ����)
 */
int drawCardConfirm() {
    printf("ī�带 �����ðڽ��ϱ� (1:����, 0:���� ����):");
    int yn;
    scanf("%d", &yn);
    if (!(yn == 0 || yn == 1)) {
        printf("���ڸ� �� �� �Է��߽��ϴ�.\n");
        return drawCardConfirm();
    } else {
        return yn;
    }
}

/**
 * @brief ���糭�� ���� �õ带 �ʱ�ȭ�մϴ�.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief ���� ���� �� �ʱ�ȭ�� ����ϴ� �Լ��Դϴ�.
 */
void initGame() {
    for (int i = 0; i < 2; i++) {
        drawMyCard();
        drawDealerCard();
    }

    printf("�� ī��: ");
    printCard(myCards, 0, 2);
    printf("\n");

    printf("���� ī��: * ");
    printCard(dealerCards, 1, 1);
    printf("\n");
}

/**
 * @brief ���� ����� ��Ÿ���� �������Դϴ�.
 */
typedef enum GameResult {
    LOSE_PLAYER_BUST, WIN_DEALER_BUST, LOSE_SMALL_NUMBER, WIN_LARGE_NUMBER, DRAW
};

/**
 * @brief ���� ������ ī�� �ջ� ���� �޾� ���� ����� ��ȯ�մϴ�.
 * @param myCardsSum �� ī�� �ջ�
 * @param dealerCardsSum ���� ī�� �ջ�
 * @return ���� ���
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
 * @brief ���� ����� ��� �˸� ���ڿ��� ��ȯ�մϴ�.
 * @param gameResult ���� ���
 @ @return ��� �˸� ���ڿ�
 */
char *toResultString(int gameResult) {
    switch (gameResult) {
        case LOSE_PLAYER_BUST:
            return "�����ϴ�. (���� ����Ʈ)";
        case WIN_DEALER_BUST:
            return "�̰���ϴ�. (������ ����Ʈ)";
        case LOSE_SMALL_NUMBER:
            return "�����ϴ�. (�������� ���� ī�� �ջ�)";
        case WIN_LARGE_NUMBER:
            return "�̰���ϴ�. (�������� ū ī�� �ջ�)";
        case DRAW:
            return "�����ϴ�.";
    }
}

/**
 * @brief ���� ���� �����Դϴ�.
 */
void game() {
    while (drawCardConfirm()) {
        drawMyCard();
        drawDealerCard();
        printf("�� ī��: ");
        printCard(myCards, 0, DECK_LIMIT);
        printf("\n");
        printf("���� ī��: * ");
        printCard(dealerCards, 1, DECK_LIMIT - 1);
        printf("\n");
    }

    while (getCardsSum(dealerCards, 0, DECK_LIMIT) < 17) {
        drawDealerCard();
    }

    int myCardsSum = getCardsSum(myCards, 0, DECK_LIMIT);
    int dealerCardsSum = getCardsSum(dealerCards, 0, DECK_LIMIT);
    int gameStatus = getGameStatus(myCardsSum, dealerCardsSum);
    printf("���� ī��: %d, ���� ī��: %d(��)�� %s", myCardsSum, dealerCardsSum, toResultString(gameStatus));
}


/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    initRand();
    initGame();
    game();
    printf("\nPress ENTER to exit...");
    fflush(stdin);
    getchar();
}
