#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
# define strtok_r strtok_s
#endif

typedef enum Boolean {
    false, true
};

/**
 * p^n을 계산한다
 * @param p 밑(∈R)
 * @param n 지수(∈Z)
 * @return 계산된 p^n값
 */
long double powByInteger(long double p, int n) {
    long double result = 1;
    while (n--) {
        result *= p;
    }
    return result;
}

/**
 * 3. 다항식 10x^3+4x^2+7x+6의 값을 계산하는 프로그램을 작성하라. x의 값은 실수로 사용자에게 입력 받는다.
 */
long double calculatePolynomialForX(char *expressionStr, long double x);

void runAssignment3() {
    long double x;
    printf("실수를 입력하시오: ");
    scanf("%Lf", &x);
    printf("다항식의 값은 %Lf", calculatePolynomialForX("10x^3+4x^2+7x+6", x));
}


/**
 * x에 대한 다항식 문자열과 대입될 x(∈R)를 받아 해당 다항식의 결과값을 계산한다.
 * @param expressionStr 파싱할 x에 대한 다항식 표현 문자열
 * @param x 다항식에 대입될 x(∈R)
 * @return 계산된 다항식값
 */
long double calculatePolynomialForX(char *expressionStr, long double x) {
    long double result = 0;
    char *copyExpressionStr = (char *) malloc((strlen(expressionStr) + 1) * sizeof(char));
    strcpy(copyExpressionStr, expressionStr);
    char *termContext = NULL;
    char *termStr = strtok_r(copyExpressionStr, "+", &termContext);
    while (termStr != NULL) {
        int isConst = true;
        for (int i = 0; i < strlen(termStr); i++) {
            if (termStr[i] == 'x') {
                isConst = false;
                break;
            }
        }
        double coefficient;
        int degree = isConst ? 0 : 1;
        char *copyTermStr = (char *) malloc((strlen(termStr) + 1) * sizeof(char));
        strcpy(copyTermStr, termStr);
        char *xSplitStrContext = NULL;
        char *xSplitStr = strtok_r(copyTermStr, "x", &xSplitStrContext);
        int isCoefficient = true;
        while (xSplitStr != NULL) {
            if (isCoefficient) {
                coefficient = atof(xSplitStr);
                isCoefficient = false;
            } else {
                char *copyXSplitStr = (char *) malloc((strlen(xSplitStr) + 1) * sizeof(char));
                strcpy(copyXSplitStr, xSplitStr);
                char *caretSplitStrContext = NULL;
                char *caretSplitStr = strtok_r(copyXSplitStr, "^", &caretSplitStrContext);
                while (caretSplitStr != NULL) {
                    degree = atoi(caretSplitStr);
                    caretSplitStr = strtok_r(caretSplitStrContext, "^", &caretSplitStrContext);
                }
                free(copyXSplitStr);
            }
            xSplitStr = strtok_r(xSplitStrContext, "x", &xSplitStrContext);
        }
        free(copyTermStr);
        termStr = strtok_r(termContext, "+", &termContext);
        result += coefficient * powByInteger(x, degree);
    }
    free(copyExpressionStr);
    return result;
}

int main() {
    runAssignment3();
}
