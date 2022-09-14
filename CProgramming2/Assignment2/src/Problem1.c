/**
  @file Problem1.c
  @brief Lab2-1. ���������Ͱ� ���ߴ� �� (��2)
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief ���� ������ Set�� ũ��
 */
#define FLOOR_SET_SIZE 4

/**
 * @brief ���� ������ Set
 */
int floorSet[FLOOR_SET_SIZE] = {0};
/**
 * @brief Set�� ���� ����
 */
int floorSetIndex = 0;

/**
 * @brief ���� �޾Ƽ� Set�� �ִ� �Լ�
 * @details �ߺ� ����/���� ���� ����� �ִ� ���� Set�� �����մϴ�.
 * @param floor ���� ��
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
 * @brief Set ���θ� �����ϴ� �Լ�
 * @details Set ���θ� ���� ȣ���� ���� �������� �����մϴ�. ��ǰ ������ �̿��ϸ� XOR ���� ������ ����߽��ϴ�.
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
 * @brief �ֹ� 1�� ������
 */
int inhabitant1;
/**
 * @brief �ֹ� 2�� ������
 */
int inhabitant2;
/**
 * @brief �ֹ� 1�� ��ǥ ��
 */
int targetFloor1;
/**
 * @brief �ֹ� 2�� ��ǥ ��
 */
int targetFloor2;

/**
 * @brief �ʱ� ���� �Լ�
 * @details srand�� ȣ���Ͽ� ���� �õ带 ���� �ð����� ������� �ʱ�ȭ�ϰ� ����� �������� �ʱ�ȭ�մϴ�.
 */
void init() {
    srand(time(NULL));
    inhabitant1 = rand() % 30 + 1;
    inhabitant2 = rand() % 30 + 1;
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    init();
    printf("�ֹ�1�� ���� %d���� �ֽ��ϴ�. �� ������ ���ðڽ��ϱ�? ", inhabitant1);
    scanf("%d", &targetFloor1);
    printf("�ֹ�2�� ���� %d���� �ֽ��ϴ�. �� ������ ���ðڽ��ϱ�? ", inhabitant2);
    scanf("%d", &targetFloor2);

    addToSet(targetFloor1);
    addToSet(targetFloor2);
    addToSet(inhabitant1);
    addToSet(inhabitant2);
    sortSet();

    for(int i = 0; i < floorSetIndex; i++){
        printf("%d��\n", floorSet[i]);
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
