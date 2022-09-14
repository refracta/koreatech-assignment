/**
  @file Problem1.c
  @brief Lab4-1. ��ũ ��ź����2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief �õ� Ƚ���� ������Ű�� ��ȯ�մϴ�.
 * @return �õ� Ƚ��
 */
int increase_number_of_try() {
    static int numOfTry = 0;
    return ++numOfTry;
}

/**
 * @brief ź�� �߻��ϰ� ���� �ǰ� ���θ� ��ȯ�մϴ�.
 * @return ���� �ǰ� ����
 */
int fire(int enemy_location, int v0) {
    double hit_location = (v0 * v0 * 0.7) / 10;
    return hit_location - 30 <= enemy_location && enemy_location <= hit_location + 30;
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    srand(time(NULL));
    int enemy_location = 175 + rand() % (343 - 175) + 1;
    // ���� ������ ��ġ ���� (175 ~ 343)
    int try;
    while (true) {
        printf("�ʼ� �� mź���� ���� ���Ͻÿ�:");
        int v0;
        scanf("%d", &v0);
        if (!(50 <= v0 && v0 <= 70)) {
            printf("�׷� ź�� �����ϴ�.\n");
            continue;
        }
        try = increase_number_of_try();
        if (fire(enemy_location, v0)) {
            printf("���� ���߾����ϴ�.\n");
            break;
        } else {
            printf("���� ������ ���߽��ϴ�.\n");
        }
    }
    printf("�õ�Ƚ��:%d", try);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
