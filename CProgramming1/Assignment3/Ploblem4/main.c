#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined(_WIN32) || defined(_WIN64)
# define strtok_r strtok_s
#endif

typedef enum Boolean {
    false, true
};

/**
 * 4. 하나의 정수를 입력받아 아래의 수식에 대입해 결과를 출력하는 프로그램을 작성하라.
 * (x^3+30)/(x-5)
 */
long double calculatePolynomial(char *expressionStr, char targetCharacter, long double x);

void runAssignment4() {
    long double x;
    printf("수를 입력하시오: ");
    scanf("%Lf", &x);
    printf("%Lf", calculatePolynomial("x^3+30", 'x', x) / calculatePolynomial("x-5", 'x', x));
}

/**
 * 어떤 문자에 대한 다항식 표현 문자열과 다항식 문자에 대입될 미지수(∈R)를 받아 해당 다항식의 결과값을 계산한다.
 * ※ 계수 생략, 음수 부호 항(덧셈 부호 생략) 지원 추가
 * @param expressionStr 파싱할 문자에 대한 다항식 표현 문자열
 * @param targetCharacter 다항식의 문자
 * @param value 다항식 문자에 대입될 값(∈R)
 * @return 계산된 다항식값
 */
long double calculatePolynomial(char *expressionStr, char targetCharacter, long double value) {
    char targetCStr[2];
    targetCStr[0] = targetCharacter;
    targetCStr[1] = '\0';

    long double result = 0;
    int eStrLength = strlen(expressionStr);
    int minusCount = 0;
    for (int i = 0; i < eStrLength; i++) {
        if (expressionStr[i] == '-') {
            minusCount++;
        }
    }

    char *copyExpressionStr = (char *) malloc((eStrLength + 1 + minusCount) * sizeof(char));
    for (int i = 0, j = 0; i < eStrLength; i++, j++) {
        if (expressionStr[i] == '-') {
            copyExpressionStr[j] = '+';
            copyExpressionStr[++j] = '-';
        } else {
            copyExpressionStr[j] = expressionStr[i];
        }
    }
    copyExpressionStr[eStrLength + minusCount] = '\0';

    char *termContext = NULL;
    char *termStr = strtok_r(copyExpressionStr, "+", &termContext);
    while (termStr != NULL) {
        int isConst = true;
        int length = strlen(termStr);
        for (int i = 0; i < length; i++) {
            if (termStr[i] == targetCharacter) {
                isConst = false;
                break;
            }
        }
        double coefficient = 1;
        int degree = isConst ? 0 : 1;
        char *copyTermStr = (char *) malloc((strlen(termStr) + 1) * sizeof(char));
        strcpy(copyTermStr, termStr);
        char *cSplitStrContext = NULL;
        char *cSplitStr = strtok_r(copyTermStr, targetCStr, &cSplitStrContext);
        int isCoefficient = true;
        while (cSplitStr != NULL) {
            if (isCoefficient) {
                coefficient = atof(cSplitStr);
                isCoefficient = false;
                if (coefficient == 0) {
                    int coeLength = strlen(cSplitStr);
                    if (coeLength == 1 && cSplitStr[0] == '-') {
                        coefficient = -1;
                    } else {
                        coefficient = 1;
                        continue;
                    }
                }
            } else {
                char *copyXSplitStr = (char *) malloc((strlen(cSplitStr) + 1) * sizeof(char));
                strcpy(copyXSplitStr, cSplitStr);
                char *caretSplitStrContext = NULL;
                char *caretSplitStr = strtok_r(copyXSplitStr, "^", &caretSplitStrContext);
                while (caretSplitStr != NULL) {
                    degree = atoi(caretSplitStr);
                    caretSplitStr = strtok_r(caretSplitStrContext, "^", &caretSplitStrContext);
                }
                free(copyXSplitStr);
            }
            cSplitStr = strtok_r(cSplitStrContext, targetCStr, &cSplitStrContext);
        }
        free(copyTermStr);
        termStr = strtok_r(termContext, "+", &termContext);
        result += coefficient * pow(value, degree);
    }
    free(copyExpressionStr);
    return result;
}

int main() {
    runAssignment4();
}
