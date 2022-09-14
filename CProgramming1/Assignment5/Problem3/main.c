#include <stdio.h>

/*
 * 3. 사용자로부터 년도를 입력받아 그 해의 띠를 출력하는 프로그램을 switch문을 이용해 작성하시오. 참고로 2020년은 쥐띠의 해이고, 쥐, 소, 호랑이, 토끼, 용, 뱀, 말, 양, 원숭이, 닭, 개, 돼지, 12개의 띠가 돌아가며 계속된다.
 */
int main() {
    int year;
    printf("년도를 입력하시오: ");
    scanf("%d", &year);

    switch ((year - 4) % 12 + 1) {
        case 1:
            printf("쥐");
            break;
        case 2:
            printf("소");
            break;
        case 3:
            printf("호랑이");
            break;
        case 4:
            printf("토끼");
            break;
        case 5:
            printf("용");
            break;
        case 6:
            printf("뱀");
            break;
        case 7:
            printf("말");
            break;
        case 8:
            printf("양");
            break;
        case 9:
            printf("원숭이");
            break;
        case 10:
            printf("닭");
            break;
        case 11:
            printf("개");
            break;
        case 12:
            printf("돼지");
            break;
    }

}
