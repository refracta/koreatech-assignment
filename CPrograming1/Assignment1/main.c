#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
# define strtok_r strtok_s
#endif

static long double PI;
typedef enum Boolean {
    false, true
};

/**
 * 개인적인 도전 과제:
 * 1. math.h 없이
 * 2. 주어진 것보다 Hardcore 하게
 * */

/**
 * 1. 사용자로부터 반지름의 길이를 입력 받아 원의 넓이를 계산하여 출력하는 프로그램을 작성하라.
 * π로 수렴하는 무한급수인 Bailey-Borwein-Plouffe 공식을 이용하여 PI를 계산한다
 * https://en.wikipedia.org/wiki/Bailey-Borwein-Plouffe_formula
 */
long double powByInteger(long double p, int n);

void runAssignment1() {
    printf("반지름을 입력하시오(cm): ");
    long double radius;
    scanf("%Lf", &radius);
    long double area = PI * powByInteger(radius, 2);
    printf("원의 넓이는 %Lfcm^2입니다.", area);
}

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
 * k값에 따른 BBP 수열의 한 항을 계산한다.
 * @param k 대입하여 계산할 k의 값
 * @return 수열의 계산된 한 항
 */
long double getBBPResult(int k) {
    int _8k = 8 * k;
    long double result = 4.0 / (_8k + 1) - 2.0 / (_8k + 4) - 1.0 / (_8k + 5) - 1.0 / (_8k + 6);
    for (int i = 0; i < k; i++) {
        result /= 16;
    }
    return result;
}

/**
 * 위끝 k값까지의 BBP 급수를 계산한다
 * @param k 위끝 k값
 * @return 근사된 PI값
 */
long double calculatePI(int k) {
    long double result = 0;
    for (int i = 0; i < k + 1; i++) {
        result += getBBPResult(i);
    }
    return result;
}

/**
 * 과제에서 제시된 상수 PI 값을 구한다
 * @param k 위끝 k값
 * @return 과제에서 제시된 상수로 절삭된 근사된 PI값
 */
double calculateAssignmentFormPI(int k) {
    return (int) (calculatePI(k) * 100) / 100.0;
}

/**
 * 2. 사용자로부터 두 개의 실수를 입력 받은 후, 두 수의 곱을 계산하여 화면에 출력하는 프로그램을 작성하라.
 */
void runAssignment2() {
    long double real1;
    long double real2;
    printf("실수를 입력하시오: ");
    scanf("%Lf", &real1);
    printf("실수를 입력하시오: ");
    scanf("%Lf", &real2);
    printf("두 수의 곱은 %Lf입니다.", real1 * real2);
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

/**
 * 4. 사용자로부터 반지름의 길이를 입력 받아 구의 부피와 겉넓이를 계산하여 출력하는 프로그램을 작성하라.
 */
void runAssignment4() {
    printf("반지름을 입력하시오(cm): ");
    long double radius;
    scanf("%Lf", &radius);
    long double volume = 4.0 / 3 * PI * powByInteger(radius, 3);
    long double areaOfSphere = 4 * PI * powByInteger(radius, 2);
    printf("구의 부피는 %Lfcm^3이고, 구의 겉넓이는 %Lfcm^2입니다.", volume, areaOfSphere);
}

/**
 * 5. 피타고라스 정리를 이용해 두 직각변의 길이를 사용자로부터 입력 받아 빗변의 길이를 계산해 출력하는 프로그램을 작성하라.
 */
long double sqrt(long double a);

void runAssignment5() {
    long double a, b;
    printf("직각변의 길이를 입력하시오(cm): ");
    scanf("%Lf", &a);
    printf("직각변의 길이를 입력하시오(cm): ");
    scanf("%Lf", &b);
    printf("빗변의 길이는 %Lfcm입니다.", sqrt(powByInteger(a, 2) + powByInteger(b, 2)));
}


/**
 * Babylonian 법을 이용하여 제곱근을 계산한다.
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
 * @param x0 임의의 양의 실수 x0
 * @param a 제곱근을 구할 양의 실수
 * @return 근사된 제곱근 값
 */

long double babylonianSqrt(long double x0, long double a, int repeat) {
    long double xn = x0;

    for (int i = 0; i < repeat; i++) {
        xn = 1.0 / 2 * (xn + a / xn);
    }
    return xn;
}

/**
 * 한가지 매개변수만을 이용하여 Babylonian 법으로 제곱근을 계산한다.
 * @param a 제곱근을 구할 양의 실수
 * @return 근사된 제곱근 값
 */
const int SQRT_PRECISION = 10;

long double sqrt(long double a) {
    long double x0 = 0;
    while (x0 * x0 <= a) {
        x0 += 0.1;
    }
    return babylonianSqrt(x0, a, SQRT_PRECISION);
}


const int USE_ASSIGNMENT_PI = true;
const int PI_PRECISION = 100;

void init() {
    PI = USE_ASSIGNMENT_PI ? calculateAssignmentFormPI(PI_PRECISION) : calculatePI(PI_PRECISION);
}

int main() {
    init();
    int caseValue;
    while (true) {
        printf("과제 문항번호를 입력하세요 [1, 2, 3, 4, 5]\n");
        printf(" * 1. 사용자로부터 반지름의 길이를 입력 받아 원의 넓이를 계산하여 출력하는 프로그램을 작성하라.\n");
        printf(" * 2. 사용자로부터 두 개의 실수를 입력 받은 후, 두 수의 곱을 계산하여 화면에 출력하는 프로그램을 작성하라.\n");
        printf(" * 3. 다항식 10x^3+4x^2+7x+6의 값을 계산하는 프로그램을 작성하라. x의 값은 실수로 사용자에게 입력 받는다.\n");
        printf(" * 4. 사용자로부터 반지름의 길이를 입력 받아 구의 부피와 겉넓이를 계산하여 출력하는 프로그램을 작성하라.\n");
        printf(" * 5. 피타고라스 정리를 이용해 두 직각변의 길이를 사용자로부터 입력 받아 빗변의 길이를 계산해 출력하는 프로그램을 작성하라.\n");
        printf("문항 번호: ");
        scanf("%d", &caseValue);
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        switch (caseValue) {
            case 1:
                runAssignment1();
                break;
            case 2:
                runAssignment2();
                break;
            case 3:
                runAssignment3();
                break;
            case 4:
                runAssignment4();
                break;
            case 5:
                runAssignment5();
                break;
            default:
                printf("해당 문항 번호가 존재하지 않습니다.");
                break;
        }
        printf("\n");
        printf("==============================\n");
    }
}
