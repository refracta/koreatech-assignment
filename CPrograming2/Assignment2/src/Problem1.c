/**
  @file Problem1.c
  @brief Lab2-1. 엘리베이터가 멈추는 층 (팀2)
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief 층을 저장할 Set의 크기
 */
#define FLOOR_SET_SIZE 4

/**
 * @brief 층을 저장할 Set
 */
int floorSet[FLOOR_SET_SIZE] = {0};
/**
 * @brief Set의 현재 색인
 */
int floorSetIndex = 0;

/**
 * @brief 층을 받아서 Set에 넣는 함수
 * @details 중복 제거/수동 정렬 기능이 있는 유사 Set을 구현합니다.
 * @param floor 넣을 층
 */
void addToSet(int floor) {
    for (int i = 0; i < floorSetIndex; i++) {
        if (floorSet[i] == floor) {
            return;
        }
    }
    floorSet[floorSetIndex++] = floor;
}

/**
 * @brief Set 내부를 정렬하는 함수
 * @details Set 내부를 수동 호출을 통해 내림차순 정렬합니다. 거품 정렬을 이용하며 XOR 변수 스왑을 사용했습니다.
 */
void sortSet() {
    for (int i = FLOOR_SET_SIZE - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (floorSet[j] < floorSet[j + 1]) {
                floorSet[j] ^= floorSet[j+1];
                floorSet[j+1] ^= floorSet[j];
                floorSet[j] ^= floorSet[j+1];
            }
        }
    }
}

/**
 * @brief 주민 1의 현재층
 */
int inhabitant1;
/**
 * @brief 주민 2의 현재층
 */
int inhabitant2;
/**
 * @brief 주민 1의 목표 층
 */
int targetFloor1;
/**
 * @brief 주민 2의 목표 층
 */
int targetFloor2;

/**
 * @brief 초기 설정 함수
 * @details srand를 호출하여 난수 시드를 현재 시간값을 기반으로 초기화하고 사용할 변수들을 초기화합니다.
 */
void init() {
    srand(time(NULL));
    inhabitant1 = rand() % 30 + 1;
    inhabitant2 = rand() % 30 + 1;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    init();
    printf("주민1은 현재 %d층에 있습니다. 몇 층으로 가시겠습니까? ", inhabitant1);
    scanf("%d", &targetFloor1);
    printf("주민2은 현재 %d층에 있습니다. 몇 층으로 가시겠습니까? ", inhabitant2);
    scanf("%d", &targetFloor2);

    addToSet(targetFloor1);
    addToSet(targetFloor2);
    addToSet(inhabitant1);
    addToSet(inhabitant2);
    sortSet();

    for(int i = 0; i < floorSetIndex; i++){
        printf("%d층\n", floorSet[i]);
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
