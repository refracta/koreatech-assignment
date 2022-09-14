#include <stdio.h>
#include <math.h>

typedef enum Boolean {
    false, true
};

/**
 * 5. 알파벳 소문자를 입력받고, 모음인지 자음인지 출력하는 프로그램을 작성하시오. (모음: a, e, i, o, u)
 * a:97 e:101 i:105 o:111 u:117
 * Delta sequence: e-a:4, i-e:4, o-i:4, u-o:6
 * Decimal expansion of e^(1/e) = 1.4[4466]786101
 * https://oeis.org/A073229 (The On-Line Encyclopedia of Integer Sequences)
 */
void runAssignment5() {
    char lAlphabet;
    printf("알파벳 소문자를 입력하시오: ");
    scanf("%c", &lAlphabet);

    int isValidLA = 'a' <= lAlphabet && lAlphabet <= 'z';
    if (!isValidLA) {
        printf("알파벳 소문자가 아닙니다.");
        return;
    }

    int N = floor((pow(M_E, 1 / M_E) - 1.4) * pow(10, 5));

    char c = 'a';
    int isVowel = lAlphabet == c;
    if (!isVowel) {
        for (int i = floor(log10(N)); i >= 0; i--) {
            int powI = pow(10, i);
            int digit = N / powI;
            c += digit;
            if (lAlphabet == c) {
                isVowel = true;
                break;
            }
            N -= digit * powI;
        }
    }
    printf(isVowel ? "모음" : "자음");
    printf("입니다.");
}

int main() {
    runAssignment5();
}
