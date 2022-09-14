/**
  @file Problem2.c
  @brief Lab3-2. 무기강화（팀1)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief 남은 강화 횟수
 */
int leftChance = 10;
/**
 * @brief 현재 강화 횟수
 */
int reinforcement = 0;

/**
 * @brief 유사난수 생성 시드를 초기화합니다.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief 백분율 확률을 모의실험합니다.
 * @details 백분율 확률을 매개변수로 받아 해당 백분률 확률을 모의실험합니다. percent=20이면 20% 확률로 true(=1)를 80% 확률로 false(=0)을 반환합니다.
 * @return 성공 여부 boolean
 */
int simulateProbability(int percent) {
    return rand() % 100 < percent;
}

/**
 * @brief 강화를 시도합니다.
 */
void tryReinforcement() {
    int result = simulateProbability(10 * leftChance--);
    reinforcement += result;
    result ? printf("성공") : printf("실패");
    printf("\n");
    printf("+%d 입니다. 기회는 %d번 남았습니다.\n", reinforcement, leftChance);
}

/**
 * @brief 사용자에게 강화를 계속할지 확인합니다.
 * @return 강화 진행 여부 boolean (1=계속, 0=중지)
 */
int reinforcementConfirm() {
    printf("계속 강화하시겠습니까? (예: 1, 아니오: 0):");
    int yn;
    scanf("%d", &yn);
    if (!(yn == 0 || yn == 1)) {
        printf("숫자를 잘 못 입력했습니다.\n");
        return reinforcementConfirm();
    } else {
        return yn;
    }
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    initRand();
    printf("강화 성공 할 수록 확률은 10%씩 낮아집니다. 강화 기회는 총 10번입니다.\n");
    tryReinforcement();
    while (leftChance > 0 && reinforcementConfirm()) {
        tryReinforcement(leftChance * 10);
    }
    printf("무기의 강화 레벨은 +%d 입니다.", reinforcement);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}