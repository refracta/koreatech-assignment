/**
  @file Problem3.c
  @brief Lab2-3. 카드 배틀 게임 (김영우 조교)
  @details WARNING: 본 예제 풀이는 int형 변수의 크기가 32비트임을 상정하고 제작되었습니다.
*/
#include <stdio.h>

/**
 * @brief 마스킹 처리용 정수를 가져옵니다.
 * @details 마스크 연산을 통해 주어진 size 변수의 값에 따라 int 변수의 Binary Form 기준 우측부터 1을 채운 값을 반환합니다. size=1이면 [00000000 00000000 00000000 00000001], size=10이면 [00000000 00000000 00000011 11111111]를 반환합니다.
 * @param size 양의 정수
 * @return 마스킹 처리용 정수
 */
int getMaskInt(int size) {
    int mask = 1;
    for (int i = 0; i < size - 1; i++) {
        mask = (mask << 1) + 1;
    }
    return mask;
}

/**
 * @brief Shift Operator를 이용하여 unsigned int형 변수에서 원하는 비트 구간의 정보를 추출합니다.
 * @details 주어진 매개변수 값에 맞는 비트 구간의 정보를 data 매개변수에서 추출하여 반환합니다. shiftMargin=2, maskSize=6, data=[11100111 11111111 11111111 11111111]인 경우 [11<100111> 11111111 11111111 11111111] <100111>을 추출하게 됩니다.
 * @param shiftMargin 좌측으로부터 건너 뛰고 읽을 비트의 개수
 * @param maskSize 읽을 비트의 개수
 * @param data 추출할 대상 데이터
 * @return 추출된 비트 구간의 정보
 */
int extractData(int shiftMargin, int maskSize, unsigned int data) {
    int maskInt = getMaskInt(maskSize);
    data = data & (maskInt << (32 - maskSize - shiftMargin));
    data = data >> (32 - maskSize - shiftMargin);
    return data;
}

/**
 * @brief Shift Operator를 이용하여 unsigned int형 변수의 원하는 부분에 데이터를 주입합니다.
 * @details 주어진 매개변수 값에 맞는 baseData의 비트 구간에 newData의 값을 주입합니다. shiftMargin=2, maskSize=4, baseData=[00000000 00000000 00000000 00000000], baseData=[00000000 00000000 00000000 0100<0010>]인 경우 [00<0010>00 00000000 00000000 00000000] <0010>을 주입하게 됩니다.
 * @param shiftMargin 좌측으로부터 건너 뛰고 주입할 비트의 개수
 * @param baseData 수정할 대상 데이터
 * @param maskSize 주입 범위
 * @param newData 주입할 대상 데이터
 * @return 수정된 데이터
 */
int injectData(int shiftMargin, int maskSize, unsigned int baseData, unsigned int newData) {
    int maskInt = getMaskInt(maskSize);
    newData = (maskInt & newData) << (32 - maskSize - shiftMargin);
    baseData = baseData & ~(maskInt << (32 - maskSize - shiftMargin));
    return baseData + newData;
}

/**
 * @brief 카드 정보 색인의 열거형입니다.
 */
typedef enum CardData {
    PRICE, DEFAULT_HP, CURRENT_HP, DEFAULT_ATK, CURRENT_ATK
};

/**
 * @brief 전투 결과의 열거형입니다. 상호 파괴, 카드 생존, 적 생존, 모두 생존의 경우가 있습니다.
 */
typedef enum BattleStatus {
    MUTUAL_DESTROYED, CARD_SURVIVED, ENEMY_SURVIVED, ALL_SURVIVED
};

const char *cardName[5] = {"이즈리얼", "유미", "아리", "피오라", "이블린"};
int cardData[5] = {0x33331, 0x11222, 0x22221, 0x55333, 0x44222};

/**
 * @brief 소스 템플릿에 정의된 함수의 동일 명세 구현체입니다.
 */
int getCardData(int number) {
    return cardData[number];
}
/**
 * @brief 소스 템플릿에 정의된 함수의 동일 명세 구현체입니다.
 */
int getData(unsigned int data, int index) {
    return extractData(12 + 20 - (index + 1) * 4, 4, data);
}
/**
 * @brief 소스 템플릿에 정의된 함수의 동일 명세 구현체입니다.
 */
int updateData(unsigned int data, int index, int value) {
    return injectData(12 + 20 - (index + 1) * 4, 4, data, value);
}

/**
 * @brief 소스 템플릿에 정의된 함수의 동일 명세 구현체입니다.
 */
void battleResult(int cardData, int enemyData) {
    int status = 0;
    status += getData(cardData, CURRENT_HP) > getData(enemyData, CURRENT_ATK);
    status += (getData(enemyData, CURRENT_HP) > getData(cardData, CURRENT_ATK)) * 2;
    switch (status) {
        case MUTUAL_DESTROYED:
            printf("두 카드 모두 파괴되어 무승부입니다.\n");
            break;
        case CARD_SURVIVED:
            printf("내 카드가 승리했습니다.\n");
            break;
        case ENEMY_SURVIVED:
            printf("상대 카드가 승리했습니다.\n");
            break;
        case ALL_SURVIVED:
            printf("내 카드가 모두 파괴되지 않았으며 무승부입니다.\n");
            break;
    }
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    printf("모든 카드 정보 \n");
    for (int i = 0; i < 5; i++) {
        printf("%s : 공격력 %d, 체력 %d, 가격 %d\n", cardName[i], getData(cardData[i], DEFAULT_ATK),
               getData(cardData[i], DEFAULT_HP), getData(cardData[i], PRICE));
    }
    printf("--------------------------------------------------\n");

    int mycardNumber = 3; //내 카드가 어떤 카드인지
    int mycardData = getCardData(mycardNumber); //내 카드의 기본 정보를 불러옵니다
    printf("내가 가지고 있는 카드는 [%s] 입니다. \n", cardName[mycardNumber]);

    int enemycardNumber = 1; //상대 카드가 어떤 카드인지
    int enemycardData = getCardData(enemycardNumber); //상대 카드의 기본 정보를 불러옵니다
    printf("상대가 가지고 있는 카드는 [%s] 입니다. \n", cardName[enemycardNumber]);

    printf("--------------------------------------------------\n");
    printf("전투 결과 [%s] vs [%s] \n", cardName[mycardNumber], cardName[enemycardNumber]);
    battleResult(mycardData, enemycardData); //전투 결과 출력

    mycardData = updateData(mycardData, CURRENT_HP,
                            getData(mycardData, CURRENT_HP) - getData(enemycardData, CURRENT_ATK)); // 내 카드의 상태를 업데이트 합니다. 마이너스 체력도 출력합니다
    printf("%s : 현재공격력 %d, 현재체력 %d, 가격 %d\n", cardName[mycardNumber], getData(mycardData, CURRENT_ATK), getData(mycardData, CURRENT_HP),
           getData(mycardData, PRICE));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}