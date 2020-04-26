#include <stdio.h>


typedef enum Boolean {
    false, true
};

/**
 * 3. 사용자가 두 개의 알파벳 대문자를 입력하면, 두 문자의 아스키 코드값의 곱을 출력하는 프로그램을 작성하라.
 */
void runAssignment3() {
    for (int i = 0; true; i++) {
        printf("알파벳 대문자를 입력하시오:");
        char uAlphabet1, uAlphabet2;
        scanf(i==0 ? "%c %c" : "%*c%c %c", &uAlphabet1, &uAlphabet2);
        int isValidUA1 = 'A' <= uAlphabet1 && uAlphabet1 <= 'Z';
        int isValidUA2 = 'A' <= uAlphabet2 && uAlphabet2 <= 'Z';
        if (!isValidUA1) {
            printf("'%c'는 대문자 알파벳이 아닙니다. 다시 입력해주세요.\n", uAlphabet1);
        }
        if (!isValidUA2) {
            printf("'%c'는 대문자 알파벳이 아닙니다. 다시 입력해주세요.\n", uAlphabet2);
        }
        if (!(isValidUA1 && isValidUA2)) {
            continue;
        }
        printf("%f 입니다.\n", (float) (uAlphabet1 * uAlphabet2));
        // printf("%d 입니다.\n", uAlphabet1 * uAlphabet2);
        break;
    }
}

int main() {
    runAssignment3();
}
