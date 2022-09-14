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

class SpeedGugu {
private:
    int NumGames = 0;    // ��ü �õ� Ƚ��
    int NumWins = 0;    // ���� Ƚ��
    double Score = 0;    // ����
    double tElapsed = 0;        // ���� �ҿ�ð�
    clock_t t0;
    clock_t t1;
    int nPlay = 10;

    bool playGuguOnce() {
        int a = rand() % 8 + 2;
        int b = rand() % 8 + 2;
        int result;

        NumGames++;
        printf("[����%2d]: %2d x %2d = ", NumGames, a, b);
        scanf("%d", &result);
        if (result == a * b) NumWins++;
        return (result == a * b);
    }

    bool playSpeedGugu2Once() {
        int a = rand() % 90 + 10;
        int b = rand() % 90 + 10;
        int result;

        NumGames++;
        printf("[����%2d]: %2d x %2d = ", NumGames, a, b);
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
        printf("[����%2d]: %d + %d = ", NumGames, a, b);
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
        printf("������ �����ϼ���: \n");
        printf("    1: ���ǵ� ������\n");
        printf("    2: ���ڸ��� ����\n");
        printf("    3~9 : n�ڸ��� ����\n");
        printf("     ���� ---> ");
        scanf("%d", &game);

        if (game == 1) printf("[���ǵ� ������ ����]\n\n");
        else if (game == 2) printf("[���ڸ��� ���� ����]\n\n");
        else if (3 <= game && game <= 9) printf("[%d�ڸ��� ���� ����]\n\n", game);
        else return;

        getchar();

        printf(" %d�� �׽�Ʈ �ϰڽ��ϴ�.\n", nPlay);
        printf(" ũ�� ��ȣ���� �Ͻð�...\n �غ�Ǹ� ���͸� ��������...");

        getchar();
        system("cls");

        double score = 0;
        if (game == 1) score = playSpeedGugu(nPlay);
        else if (game == 2) score = playSpeedGugu2(nPlay);
        else score = playSpeedSum(nPlay, game);
        printf("\n���� = %4.1f��(�� %4.1f��)\n", score, tElapsed);
    }
};