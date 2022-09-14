#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define USERNAME_LENGTH 10+1

const char *RPS_KOREAN[] = {"바위", "보", "가위"};
typedef enum RPS_RESULT {
    TIE, USER1_WIN, USER2_WIN
};

/**
 * 1. 사용자의 2명의 이름을 입력받고, rand() 함수를 활용해 가위, 바위, 보 중 무엇을 내게 할지 정하고 결과를 출력하는 프로그램을 작성하시오. (사용자 정의 함수를 작성하지 않아도 됨)
 */
int main() {
    srand((unsigned) time(NULL));

    char user1Name[USERNAME_LENGTH], user2Name[USERNAME_LENGTH];
    printf("사용자 1의 이름: ");
    scanf("%s", user1Name);
    printf("사용자 2의 이름: ");
    scanf("%s", user2Name);

    int user1RPS = rand() % 3, user2RPS = rand() % 3;
    int resultOfRPS = (3 + user1RPS - user2RPS) % 3;
    int isTie = resultOfRPS == TIE;
    int isUser1Win = resultOfRPS == USER1_WIN;
    printf("%s은(는) ‘%s’를 내고, %s은(는) ‘%s’를 내어 %s%s%s.", user1Name, RPS_KOREAN[user1RPS], user2Name, RPS_KOREAN[user2RPS],
           (isTie ? "" : (isUser1Win ? user1Name : user2Name)), (isTie ? "" : "이(가) "), (isTie ? "비겼습니다" : "이겼습니다"));
}
