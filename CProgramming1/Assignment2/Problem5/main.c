#include <stdio.h>

/**
 * Shift 연산을 통해 주어진 변수의 Binary Form을 출력한다.
 * @param decimal 출력할 정수
 */
void printBinaryForm(int decimal) {
    int mask;
    for (int i = 31; i >= 0; i--) {
        mask = 1 << i;
        printf("%d", decimal & mask ? 1 : 0);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
}

/**
 * 주어진 문자에 대한 다양한 형태의 정보를 출력한다.
 * @param target 정보를 출력할 대상 문자
 */
void printCharacterInfo(char target) {
    printf("Character: '%c'\n", target);
    printf("\tBinary Form: ");
    printBinaryForm(target);
    printf("\n");
    printf("\tOctal Form: %o\n", target);
    printf("\tDecimal Form (ASCII Code): %d\n", target);
    printf("\tHexadecimal Form: %x\n", target);
}

const char LOWERCASE_A = 'a';
const char LOWERCASE_B = 'b';
const char LOWERCASE_C = 'c';
const char LOWERCASE_D = 'd';

/**
 * 5. ‘a’, ‘b’, ‘c’, ‘d’, 이 4개의 문자의 아스키 코드 값을 알아내고, 이를 8진수, 10진수, 16진수로 출력하는 프로그램을 작성하라.
 * */
void runAssignment5() {
    printCharacterInfo(LOWERCASE_A);
    printf("============================================================\n");
    printCharacterInfo(LOWERCASE_B);
    printf("============================================================\n");
    printCharacterInfo(LOWERCASE_C);
    printf("============================================================\n");
    printCharacterInfo(LOWERCASE_D);
}

int main() {
    runAssignment5();
}
