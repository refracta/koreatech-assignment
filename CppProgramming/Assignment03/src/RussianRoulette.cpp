#include <stdio.h>
#include <stdlib.h>

void playRussianRoulette(int nTurns, int nBullets, int nMax) {
    int start = rand() % nTurns;
    printf("\n총을 돌렸습니다. %d번부터 시작합니다.\n", start + 1);
    while (true) {
        int pos = rand() % nMax;
        printf("[%d번]\t탄창을 무작위로 돌렸습니다.\n", start + 1);
        printf("\t엔터를 누르면 격발됩니다...");
        getchar();
        if (pos < nBullets) {
            printf("\t빵~~~~~~~~~%d번이 총에 맞았습니다!!!\n", start + 1);
            printf("이제 남은 사람은 %d명이고 총알은 %d발입니다.\n", --nTurns, --nBullets);
            start++;
            if (!nTurns || !nBullets) {
                break;
            }
        }
        else {
            printf("\t휴~~~ 살았습니다!!!\n");
        }
        start = (start + 1) % nTurns;
    }
}