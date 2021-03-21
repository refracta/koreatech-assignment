#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

extern void playRussianRoulette(int nTurn, int nBullets, int nMax);

int main() {
    int nTurn, nMax, nBullets;
    srand((unsigned)time(NULL));
    printf("게임 인원 (예:2) ==> ");
    scanf("%d", &nTurn);
    printf("탄창 구멍 개수 ==> ");
    scanf("%d", &nMax);
    printf("총알 개수 (%d이하) ==> ", nMax);
    scanf("%d", &nBullets);
    getchar();

    playRussianRoulette(nTurn, nBullets, nMax);
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
    return 0;
}
