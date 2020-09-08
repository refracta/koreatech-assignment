#include <stdio.h>

/**
 * 2. 사용자에게 알파벳 하나를 입력받아, 그 문자의 아스키 코드값이 홀수인지 짝수인지 출력하는 프로그램을 작성하라.
 */
void runAssignment2() {
    char c;
    printf("알파벳을 입력하시오: ");
    scanf("%c", &c);
    printf(c % 2 == 0 ? "짝수" : "홀수");
    printf("입니다.");

}

int main() {
    runAssignment2();
}
