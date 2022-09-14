/**
  @file Problem2.c
  @brief Lab1-2. 로또 당첨 여부 (팀4)
  */
#include <stdio.h>

#define LOTTO_NUM 6

/**
 * @brief 로또 당첨번호 6개의 배열
 */
int targetNumbers[LOTTO_NUM] = {0};
/**
 * @brief 보너스 번호
 */
int targetBonusNumber = 0;
/**
 * @brief 사용자 선택 번호의 배열
 */
int selectNumbers[LOTTO_NUM] = {0};

/**
 * @brief 시작 함수입니다.
 */
int main() {
    printf("로또 당첨번호 6개와 보너스 번호 1개를 입력하세요.\n");
    scanf("%d %d %d %d %d %d %d", &targetNumbers[0], &targetNumbers[1], &targetNumbers[2], &targetNumbers[3],
          &targetNumbers[4], &targetNumbers[5], &targetBonusNumber);

    printf("구매한 로또 번호 6개를 입력하세요.\n");
    scanf("%d %d %d %d %d %d", &selectNumbers[0], &selectNumbers[1], &selectNumbers[2], &selectNumbers[3],
          &selectNumbers[4], &selectNumbers[5], &selectNumbers[6]);

    int matchCount = 0;
    for (int t = 0; t < LOTTO_NUM; t++) {
        for (int s = 0; s < LOTTO_NUM; s++) {
            if (targetNumbers[t] == selectNumbers[s]) {
                // 순회하는 로또 당첨번호가 사용자 선택 번호중에 있는 경우
                matchCount++;
                break;
            }
        }
    }

    int isBonus = selectNumbers[0] == targetBonusNumber || selectNumbers[1] == targetBonusNumber ||
                  selectNumbers[2] == targetBonusNumber || selectNumbers[3] == targetBonusNumber ||
                  selectNumbers[4] == targetBonusNumber || selectNumbers[5] == targetBonusNumber;
    // 보너스 번호가 맞았는지 검사

    if (matchCount == 6) {
        printf("1등입니다.");
    } else if (matchCount == 5 && isBonus) {
        printf("2등입니다.");
    } else if (matchCount == 5 ) {
        printf("3등입니다.");
    } else if (matchCount == 4) {
        printf("4등입니다.");
    } else if (matchCount == 3) {
        printf("5등입니다.");
    } else if (matchCount <= 2) {
        printf("꽝입니다.");
    }

    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}