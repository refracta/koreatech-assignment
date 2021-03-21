#include "SpeedGugu.h"

static int NumGames = 0;    // 전체 시도 횟수
static int NumWins = 0;    // 맞힌 횟수
static double Score = 0;    // 점수
double tElapsed = 0;        // 게임 소요시간
clock_t t0;
clock_t t1;

static bool playGuguOnce() {
    int a = rand() % 8 + 2;
    int b = rand() % 8 + 2;
    int result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

static bool playSpeedGugu2Once() {
    int a = rand() % 90 + 10;
    int b = rand() % 90 + 10;
    int result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

static bool playSpeedSumOnce(int game) {
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

static void startClock() {
    t0 = clock();
}

static double getScoreWithEndClock() {
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