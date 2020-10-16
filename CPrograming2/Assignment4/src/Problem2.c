/**
  @file Problem2.c
  @brief Lab4-2. 달력 만들기（팀5)
*/
#include <stdio.h>
#include <math.h>

/**
 * @brief 시작 함수입니다.
 */
int main() {
    printf("* 1582년 10월 15일 이후 날짜만 지원합니다.\n");
    printf("출력할 년도와 달을 입력하시오(yyyy mm):");
    int y, m;
    scanf("%d %d", &y, &m);

    int a, b, c, d;
    a = (m <= 2 ? y - 1 : y) / 100;
    b = (m <= 2 ? y - 1 : y) % 100;
    c = m <= 2 ? m + 12 : m;
    d = 1;
    // 제라의 공식에 필요한 a, b, c, d를 초기화합니다.

    int days_of_week_index =
            (int) (floor((21 * a) / 4.0) + floor((5 * b) / 4.0) + floor((26 * (c + 1)) / 10.0) + d - 1) % 7;
    // 요일 색인을 구합니다.
    int is_leap_year = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
    // 윤년 여부를 확인합니다.
    int days[12] = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 월별 일 수 배열을 초기화합니다.
    printf("일 월 화 수 목 금 토\n");
    for (int i = 0; i < days_of_week_index; i++) {
        printf("   ");
    }
    // 첫 주의 1일 왼쪽에 공백 문자를 출력합니다.
    for (int d = 1; d <= days[m - 1]; d++) {
        printf("%2d ", d);
        if ((days_of_week_index + d - 1) % 7 == 6) {
            printf("\n");
        }
    }
    // 달력 출력
    printf("\n");
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}