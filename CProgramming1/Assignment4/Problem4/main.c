#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Boolean {
    false, true
};


const int QUERY_2K_FLAG_NUMBER = true;
// 주민등록번호 뒷자리 첫 숫자를 입력받을지 여부
const int DEFAULT_YEAR_2DIGIT = 19;
// QUERY_2K_FLAG_NUMBER가 false일 때 기본 값으로 사용할 연도.
const int MONTH_ARRAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 달의 일 수 배열

/**
 * 월과 일을 받아 1월 1일부터의 일 수를 반환한다.
 * @param m 월
 * @param d 일
 * @param isLeapYear 윤년 여부
 * @return 1월 1일부터 해당 월 일까지의 일 수
 */
int getTotalDay(int m, int d, int isLeapYear) {
    int t = 0;
    for (int i = 0; i < m - 1; i++) {
        t += MONTH_ARRAY[i];
    }

    return t + d + (isLeapYear && m > 2);
}

/**
 * 년을 받아 윤년인지의 여부를 반환한다.
 * @param y 년
 * @return 윤년 여부
 */
int isLeapYear(int y) {
    return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

/**
 * 4. 사용자에게 생년월일 6자리를 입력받아 나이를 계산하여 성인인지 아닌지를 판단하는 프로그램을 작성하라. 성인은 19살 이상이라고 가정한다.
 */
void runAssignment4() {
    char yymmdd[6 + 1];
    printf("생년월일 6자리(YYMMDD)를 입력하시오: ");
    scanf("%s", yymmdd);

    int by, bm, bd, cy, cm, cd;
    char yyyy[4 + 1], mm[2 + 1], dd[2 + 1];
    if (QUERY_2K_FLAG_NUMBER) {
        int flag2K;
        printf("주민등록번호 뒷자리 첫 숫자를 입력하시오:");
        scanf("%d", &flag2K);

        if (flag2K == 3 || flag2K == 4) {
            yyyy[0] = '2';
            yyyy[1] = '0';
        } else {
            yyyy[0] = '1';
            yyyy[1] = '9';
        }
    } else {
        char buf[1 + 1];
        sprintf(buf, "%d", DEFAULT_YEAR_2DIGIT / 10);
        yyyy[0] = buf[0];
        sprintf(buf, "%d", DEFAULT_YEAR_2DIGIT % 10);
        yyyy[1] = buf[0];
    }
    yyyy[2] = yymmdd[0];
    yyyy[3] = yymmdd[1];

    yyyy[4] = '\0';
    mm[0] = yymmdd[2];
    mm[1] = yymmdd[3];
    mm[2] = '\0';
    dd[0] = yymmdd[4];
    dd[1] = yymmdd[5];
    dd[2] = '\0';

    by = atoi(yyyy);
    bm = atoi(mm);
    bd = atoi(dd);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    cy = tm.tm_year + 1900;
    cm = tm.tm_mon + 1;
    cd = tm.tm_mday;


    int isLeapYearBY = isLeapYear(by);
    int isLeapYearCY = isLeapYear(tm.tm_year + 1900);
    int totalDayBY, totalDayCY;

    if (!isLeapYearBY && isLeapYearCY) {
        // 생년:평년, 현재:윤년인 경우 >>> 윤년 기준으로 일 수 비교
        totalDayBY = getTotalDay(bm, bd, true);
        totalDayCY = getTotalDay(cm, cd, isLeapYearBY);
    } else if (isLeapYearBY && !isLeapYearCY) {
        // 생년:윤년, 현재:평년인 경우 >>> 생일이 2월 29일 경우에만 3월 1일로 교체 후 평년 기준으로 일 수 비교
        totalDayBY = (bm == 2 && bd == 29) ? getTotalDay(3, 1, false) : getTotalDay(bm, bd, false);
        totalDayCY = getTotalDay(cm, cd, isLeapYearCY);
    } else {
        // 생년: 평년, 현재년: 평년 >>> 그대로 일 수 비교
        // 생년: 윤년, 현재년: 윤년 >>> 그대로 일 수 비교
        totalDayBY = getTotalDay(bm, bd, isLeapYearBY);
        totalDayCY = getTotalDay(cm, cd, isLeapYearCY);
    }
    int isAfterBirthday = totalDayBY <= totalDayCY;

    int standardAge = cy - by - !isAfterBirthday;
    int koreanAge = cy - by + 1;

    printf("생일: %d-%d-%d\n", by, bm, bd);
    printf("오늘: %d-%d-%d\n", cy, cm, cd);
    printf("세는 나이: %d\n", koreanAge);

    printf("만 나이: %d ", standardAge);
    printf(isAfterBirthday ? "(생일 지남)" : "(생일 이전)");
    printf("\n\n");
    printf("민법상 성인은 19세 이상 (생년 + 19인 해의 생일을 맞은 사람)입니다.\n");
    printf(standardAge >= 19 ? "당신은 민법상 성인입니다. " : "당신은 민법상 성인이 아닙니다. ");
    printf("\n");
    printf("청소년보호법상 성인은 19세가 되는 해의 1월 1일부터(생년 + 19 ≤ 현재년인 사람, 즉, 세는나이로 20세 이상)입니다.\n");
    printf(koreanAge >= 20 ? "당신은 청소년보호법상 성인입니다. " : "당신은 청소년보호법상 성인입니다.");
}

int main() {
    runAssignment4();
}
