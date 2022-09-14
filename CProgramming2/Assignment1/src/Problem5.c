/**
  @file Problem5.c
  @brief Lab1-5. 정수 하나에 캐릭터 정보 담기 (김덕수 교수)
  @details WARNING: 본 예제 풀이는 int형 변수의 크기가 32비트임을 상정하고 제작되었습니다.
  */
#include <stdio.h>

/**
 * @brief 종족 문자열 배열
 */
const char RACES[4][BUFSIZ] = {
        "휴먼",
        "오크",
        "언데드",
        "엘프"
};

/**
 * @brief 캐릭터 정보를 받아 unsigned int형 변수로 반환합니다.
 * @details 종족(0:휴먼, 1:오크, 2:언데드, 3:엘프), 레벨(0~63), 체력(0~4095), 마나(0~4095)를 받아 캐릭터 정보를 int형 변수 하나로 압축합니다. WARNING: 디버그용 함수입니다.
 * @param raceIndex 캐릭터 종족 색인 값
 * @param level 캐릭터 레벨
 * @param hp 캐릭터 체력
 * @param mana 캐릭터 마나
 * @return unsigned int형으로 압축된 캐릭터 정보
 */
unsigned int generateData(int raceIndex, int level, int hp, int mana) {
    return (raceIndex << 30) + (level << 24) + (hp << 12) + (mana << 0);
}

/**
 * @brief 마스킹 처리용 정수를 가져옵니다.
 * @details 마스크 연산을 통해 주어진 size 변수의 값에 따라 int 변수의 이진형 기준 우측부터 1을 채운 값을 반환합니다. size=1이면 [00000000 00000000 00000000 00000001], size=10이면 [00000000 00000000 00000011 11111111]를 반환합니다.
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
 * @brief unsigned int형 캐릭터 정보 데이터를 받아 종족 값을 반환합니다.
 * @param data unsigned int형 캐릭터 정보 데이터
 * @return 캐릭터 종족
 */
unsigned char *extractRace(unsigned int data) {
    return (unsigned char *) RACES[extractData(0, 2, data)];
    // https://stackoverflow.com/questions/24830335/c-compiler-warning-return-discards-qualifiers-from-pointer-target-type
}

/**
 * @brief unsigned int형 캐릭터 정보 데이터를 받아 레벨 값을 반환합니다.
 * @param data unsigned int형 캐릭터 정보 데이터
 * @return 캐릭터 레벨
 */
int extractLevel(unsigned int data) {
    return extractData(2, 6, data);
}

/**
 * @brief unsigned int형 캐릭터 정보 데이터를 받아 체력 값을 반환합니다.
 * @param data unsigned int형 캐릭터 정보 데이터
 * @return 캐릭터 체력
 */
int extractHP(unsigned int data) {
    return extractData(2 + 6, 12, data);
}

/**
 * @brief unsigned int형 캐릭터 정보 데이터를 받아 마나 값을 반환합니다.
 * @param data unsigned int형 캐릭터 정보 데이터
 * @return 캐릭터 마나
 */
int extractMana(unsigned int data) {
    return extractData(2 + 6 + 12, 12, data);
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    unsigned int data;
    printf("정수를 입력 하시오:");
    scanf("%d", &data);
    printf("종족:%s Lv.%d HP:%d MP:%d", extractRace(data), extractLevel(data), extractHP(data), extractMana(data));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}