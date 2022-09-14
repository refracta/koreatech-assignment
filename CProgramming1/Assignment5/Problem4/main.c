#include <stdio.h>

#define AVERAGE_PASS 1

/*
 * 4. 사용자로부터 3과목의 점수를 입력받아, 평균 60점 이상이면 합격, 평균 60점 미만이면 불합격을 출력하는 프로그램을 switch문을 이용해 작성하시오.
 */
int main() {
    double subjectA, subjectB, subjectC;
    printf("3과목의 점수를 입력하시오: ");
    scanf("%lf %lf %lf", &subjectA, &subjectB, &subjectC);
    double average = (subjectA + subjectB + subjectC) / 3;
    switch (average > 60) {
        case AVERAGE_PASS:
            printf("합격입니다.");
            break;
        default:
            printf("불합격입니다.");
            break;
    }
}
