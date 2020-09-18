/**
  @file Problem2.c
  @brief Lab1-2. �ζ� ��÷ ���� (��4)
  */
#include <stdio.h>

#define LOTTO_NUM 6

/**
 * @brief �ζ� ��÷��ȣ 6���� �迭
 */
int targetNumbers[LOTTO_NUM] = {0};
/**
 * @brief ���ʽ� ��ȣ
 */
int targetBonusNumber = 0;
/**
 * @brief ����� ���� ��ȣ�� �迭
 */
int selectNumbers[LOTTO_NUM] = {0};

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    printf("�ζ� ��÷��ȣ 6���� ���ʽ� ��ȣ 1���� �Է��ϼ���.\n");
    scanf("%d %d %d %d %d %d %d", &targetNumbers[0], &targetNumbers[1], &targetNumbers[2], &targetNumbers[3],
          &targetNumbers[4], &targetNumbers[5], &targetBonusNumber);

    printf("������ �ζ� ��ȣ 6���� �Է��ϼ���.\n");
    scanf("%d %d %d %d %d %d", &selectNumbers[0], &selectNumbers[1], &selectNumbers[2], &selectNumbers[3],
          &selectNumbers[4], &selectNumbers[5], &selectNumbers[6]);

    int matchCount = 0;
    for (int t = 0; t < LOTTO_NUM; t++) {
        for (int s = 0; s < LOTTO_NUM; s++) {
            if (targetNumbers[t] == selectNumbers[s]) {
                // ��ȸ�ϴ� �ζ� ��÷��ȣ�� ����� ���� ��ȣ�߿� �ִ� ���
                matchCount++;
                break;
            }
        }
    }

    int isBonus = selectNumbers[0] == targetBonusNumber || selectNumbers[1] == targetBonusNumber ||
                  selectNumbers[2] == targetBonusNumber || selectNumbers[3] == targetBonusNumber ||
                  selectNumbers[4] == targetBonusNumber || selectNumbers[5] == targetBonusNumber;
    // ���ʽ� ��ȣ�� �¾Ҵ��� �˻�

    if (matchCount == 6) {
        printf("1���Դϴ�.");
    } else if (matchCount == 5 && isBonus) {
        printf("2���Դϴ�.");
    } else if (matchCount == 5 ) {
        printf("3���Դϴ�.");
    } else if (matchCount == 4) {
        printf("4���Դϴ�.");
    } else if (matchCount == 3) {
        printf("5���Դϴ�.");
    } else if (matchCount <= 2) {
        printf("���Դϴ�.");
    }

    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}