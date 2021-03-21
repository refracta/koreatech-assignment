#include "SpeedGugu.h"

int main() {
    srand((unsigned)time(NULL));

    int nPlay = 3, game;
    printf("������ �����ϼ���: \n");
    printf("    1: ���ǵ� ������\n");
    printf("    2: ���ڸ��� ����\n");
    printf("    3~9 : n�ڸ��� ����\n");
    printf("     ���� ---> ");
    scanf("%d", &game);

    if (game == 1) printf("[���ǵ� ������ ����]\n\n");
    else if (game == 2) printf("[���ڸ��� ���� ����]\n\n");
    else if (3 <= game && game <= 9) printf("[%d�ڸ��� ���� ����]\n\n", game);
    else return 0;

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
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar(); getchar();
    return 0;
}