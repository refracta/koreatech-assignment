#include "SpeedGugu.h"

int main() {
    srand((unsigned)time(NULL));

    int nPlay = 3, game;
    printf("게임을 선택하세요: \n");
    printf("    1: 스피드 구구단\n");
    printf("    2: 두자리수 곱셈\n");
    printf("    3~9 : n자리수 덧셈\n");
    printf("     선택 ---> ");
    scanf("%d", &game);

    if (game == 1) printf("[스피드 구구단 게임]\n\n");
    else if (game == 2) printf("[두자리수 곱셈 게임]\n\n");
    else if (3 <= game && game <= 9) printf("[%d자리수 덧셈 게임]\n\n", game);
    else return 0;

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
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar(); getchar();
    return 0;
}