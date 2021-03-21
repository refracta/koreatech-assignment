#include <cstdio>
#include <iostream>
#include <cstdlib>        // rand() 함수를 위함
#include <ctime>            // time() 함수를 위함
#include <cmath>

#if defined(_WIN32) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#define BIG_RAND() (((long) rand() << 15) | rand())
#define START_GAME(check)  {             \
    startClock();                        \
    for (int i = 0; i < nPlay; i++) {    \
    if (check == false)                  \
        printf("\t틀렸습니다.\n");       \
    }                                    \
    return getScoreWithEndClock();       \
}

extern double tElapsed;    // 게임 소요 시간
extern double playSpeedGugu(int nPlay);
extern double playSpeedGugu2(int nPlay);
extern double playSpeedSum(int nPlay, int game);