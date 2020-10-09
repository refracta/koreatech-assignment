/**
  @file Problem2.c
  @brief Lab3-2. ���Ⱝȭ����1)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief ���� ��ȭ Ƚ��
 */
int leftChance = 10;
/**
 * @brief ���� ��ȭ Ƚ��
 */
int reinforcement = 0;

/**
 * @brief ���糭�� ���� �õ带 �ʱ�ȭ�մϴ�.
 */
void initRand() {
    srand(time(NULL));
}

/**
 * @brief ����� Ȯ���� ���ǽ����մϴ�.
 * @details ����� Ȯ���� �Ű������� �޾� �ش� ��з� Ȯ���� ���ǽ����մϴ�. percent=20�̸� 20% Ȯ���� true(=1)�� 80% Ȯ���� false(=0)�� ��ȯ�մϴ�.
 * @return ���� ���� boolean
 */
int simulateProbability(int percent) {
    return rand() % 100 < percent;
}

/**
 * @brief ��ȭ�� �õ��մϴ�.
 */
void tryReinforcement() {
    int result = simulateProbability(10 * leftChance--);
    reinforcement += result;
    result ? printf("����") : printf("����");
    printf("\n");
    printf("+%d �Դϴ�. ��ȸ�� %d�� ���ҽ��ϴ�.\n", reinforcement, leftChance);
}

/**
 * @brief ����ڿ��� ��ȭ�� ������� Ȯ���մϴ�.
 * @return ��ȭ ���� ���� boolean (1=���, 0=����)
 */
int reinforcementConfirm() {
    printf("��� ��ȭ�Ͻðڽ��ϱ�? (��: 1, �ƴϿ�: 0):");
    int yn;
    scanf("%d", &yn);
    if (!(yn == 0 || yn == 1)) {
        printf("���ڸ� �� �� �Է��߽��ϴ�.\n");
        return reinforcementConfirm();
    } else {
        return yn;
    }
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    initRand();
    printf("��ȭ ���� �� ���� Ȯ���� 10%�� �������ϴ�. ��ȭ ��ȸ�� �� 10���Դϴ�.\n");
    tryReinforcement();
    while (leftChance > 0 && reinforcementConfirm()) {
        tryReinforcement(leftChance * 10);
    }
    printf("������ ��ȭ ������ +%d �Դϴ�.", reinforcement);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}