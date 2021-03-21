#include <stdio.h>
#include <stdlib.h>

void playRussianRoulette(int nTurns, int nBullets, int nMax) {
    int start = rand() % nTurns;
    printf("\n���� ���Ƚ��ϴ�. %d������ �����մϴ�.\n", start + 1);
    while (true) {
        int pos = rand() % nMax;
        printf("[%d��]\tźâ�� �������� ���Ƚ��ϴ�.\n", start + 1);
        printf("\t���͸� ������ �ݹߵ˴ϴ�...");
        getchar();
        if (pos < nBullets) {
            printf("\t��~~~~~~~~~%d���� �ѿ� �¾ҽ��ϴ�!!!\n", start + 1);
            printf("���� ���� ����� %d���̰� �Ѿ��� %d���Դϴ�.\n", --nTurns, --nBullets);
            start++;
            if (!nTurns || !nBullets) {
                break;
            }
        }
        else {
            printf("\t��~~~ ��ҽ��ϴ�!!!\n");
        }
        start = (start + 1) % nTurns;
    }
}