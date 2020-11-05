/**
  @file Problem1.c
  @brief Lab5-1. 아스키코드를 통한 암호 해독（팀1)
*/

#include <stdio.h>

/**
 * @brief 문제에 정의된 함수의 동일 명세 구현체입니다.
 */
int sub(int a, int b) {
    return a - b;
}

/**
 * @brief 문제에 정의된 함수의 동일 명세 구현체입니다.
 */
int sum(int a, int b) {
    return a + b;
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    int (*fpArray[2])(int, int) = {sum, sub};
    // 함수 포인터 배열을 초기화합니다.
    int input[6] = {0,};
    scanf("%d %d %d %d %d %d", &input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
    // 사용자의 입력을 받습니다.
    for (int i = 0; i < 6 - 1; i++) {
        int c = fpArray[i % 2 == 0](input[i], input[i + 1]);
        // 상황에 알맞는 함수를 사용합니다.
        c = c >= 0 ? c : -c;
        // 음수값이 나올 수 있으므로 절댓값 처리를 합니다.
        printf("%c", c);
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
