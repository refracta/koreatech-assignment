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

class SpeedGugu {
private:
    int NumGames = 0;    // 전체 시도 횟수
    int NumWins = 0;    // 맞힌 횟수
    double Score = 0;    // 점수
    double tElapsed = 0;        // 게임 소요시간
    clock_t t0;
    clock_t t1;
    int nPlay = 10;

    bool playGuguOnce() {
        int a = rand() % 8 + 2;
        int b = rand() % 8 + 2;
        int result;

        NumGames++;
        printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
        scanf("%d", &result);
        if (result == a * b) NumWins++;
        return (result == a * b);
    }

    bool playSpeedGugu2Once() {
        int a = rand() % 90 + 10;
        int b = rand() % 90 + 10;
        int result;

        NumGames++;
        printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
        scanf("%d", &result);
        if (result == a * b) NumWins++;
        return (result == a * b);
    }

    bool playSpeedSumOnce(int game) {
        int unit = pow(10, game - 1);

        int a = BIG_RAND() % (unit * 9) + unit;
        int b = BIG_RAND() % (unit * 9) + unit;
        int result;

        NumGames++;
        printf("[문제%2d]: %d + %d = ", NumGames, a, b);
        scanf("%d", &result);
        if (result == a + b) NumWins++;
        return (result == a + b);
    }

    void startClock() {
        t0 = clock();
    }

    double getScoreWithEndClock() {
        t1 = clock();
        tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;
        Score = (NumGames > NumWins) ? 0.0 : 100 * (5.0 * NumGames - tElapsed) / (5.0 * NumGames);
        return Score;
    }

    double playSpeedGugu(int nPlay) {
        START_GAME(playGuguOnce());
    }

    double playSpeedGugu2(int nPlay) {
        START_GAME(playSpeedGugu2Once());
    }

    double playSpeedSum(int nPlay, int game) {
        START_GAME(playSpeedSumOnce(game));
    }

public:
    void play() {
        srand((unsigned)time(NULL));

        int game;
        printf("게임을 선택하세요: \n");
        printf("    1: 스피드 구구단\n");
        printf("    2: 두자리수 곱셈\n");
        printf("    3~9 : n자리수 덧셈\n");
        printf("     선택 ---> ");
        scanf("%d", &game);

        if (game == 1) printf("[스피드 구구단 게임]\n\n");
        else if (game == 2) printf("[두자리수 곱셈 게임]\n\n");
        else if (3 <= game && game <= 9) printf("[%d자리수 덧셈 게임]\n\n", game);
        else return;

        getchar();

        printf(" %d번 테스트 하겠습니다.\n", nPlay);
        printf(" 크게 심호흡을 하시고...\n 준비되면 앤터를 누르세요...");

        getchar();
        system("cls");

        double score = 0;
        if (game == 1) score = playSpeedGugu(nPlay);
        else if (game == 2) score = playSpeedGugu2(nPlay);
        else score = playSpeedSum(nPlay, game);
        printf("\n점수 = %4.1f점(총 %4.1f초)\n", score, tElapsed);
    }
};