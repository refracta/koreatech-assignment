#include <cstdio>
#include <iostream>
#include <cstdlib>        // rand() �Լ��� ����
#include <ctime>            // time() �Լ��� ����
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
        printf("\tƲ�Ƚ��ϴ�.\n");       \
    }                                    \
    return getScoreWithEndClock();       \
}

extern double tElapsed;    // ���� �ҿ� �ð�
extern double playSpeedGugu(int nPlay);
extern double playSpeedGugu2(int nPlay);
extern double playSpeedSum(int nPlay, int game);