#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 정수의 문자열 자릿수를 계산한다.
 * @param integer
 * @return 정수의 문자열 자릿수
 */
int getIntegerStringLength(int integer) {
    if (integer == 0) {
        return 1;
    } else if (integer > 0) {
        return (int) floor(log10(integer)) + 1;
    } else if (integer < 0) {
        return (int) floor(log10(abs(integer))) + 2;
    }
}

/**
 * 가변적인 실행 환경에서 한글 한 문자([가-힣])가 차지하는 길이를 가져온다.
 * @return 한글 한 문자의 길이
 */
int getHangulSize() {
    return strlen("힣");
}


const char *ZERO_SECONDS_STR = "0초";

/**
 * 총 시간의 초 환산값을 "${Hours}시간 ${Minutes}분 ${Seconds}초" 꼴의 문자열로 반환한다. 주의: 동적 할당된 포인터가 반환됨!
 * @param totalSeconds 총 시간의 초 환산값
 * @return "${Hours}시간 ${Minutes}분 ${Seconds}초"
 */
char *getKoreanTimeStr(int totalSeconds) {
    if (totalSeconds <= 0) {
        char *sb = malloc(sizeof(char) * (strlen(ZERO_SECONDS_STR) + 1));
        strcpy(sb, ZERO_SECONDS_STR);
        return sb;
    }
    int length = 0;
    int hours = floor(totalSeconds / (60 * 60));
    int minutes = floor((totalSeconds - (hours * 60 * 60)) / 60);
    int seconds = totalSeconds - (hours * 60 * 60) - (minutes * 60);

    int hoursLength = hours > 0 ? getIntegerStringLength(hours) : 0;
    int minutesLength = minutes > 0 ? getIntegerStringLength(minutes) : 0;
    int secondsLength = seconds > 0 ? getIntegerStringLength(seconds) : 0;

    length += hoursLength + minutesLength + secondsLength;
    length += (hours > 0) + (minutes > 0) + (seconds > 0) - 1;

    int hangulSize = getHangulSize();
    length += (hours > 0 ? (2 * hangulSize) : 0) + (minutes > 0 ? (1 * hangulSize) : 0) +
              (seconds > 0 ? (1 * hangulSize) : 0);

    char *sb = malloc(sizeof(char) * (length + 1));

    if (hours > 0) {
        char hoursStr[hoursLength];
        sprintf(hoursStr, "%d시간", hours);
        strcat(sb, hoursStr);
        if (minutes > 0 || seconds > 0) {
            strcat(sb, " ");
        }
    }
    if (minutes > 0) {
        char minutesStr[minutesLength];
        sprintf(minutesStr, "%d분", minutes);
        strcat(sb, minutesStr);
        if (seconds > 0) {
            strcat(sb, " ");
        }
    }
    if (seconds > 0) {
        char secondsStr[secondsLength];
        sprintf(secondsStr, "%d초", seconds);
        strcat(sb, secondsStr);
    }
    return sb;
}

/**
 * 4. 초만으로 표기된 시간을 입력받아 시, 분, 초로 계산하여 표기할 수 있도록 하는 프로그램을 작성하라. 입력되는 초는 항상 1시간을 넘는다고 가정한다.
 */
void runAssignment4() {
    printf("초를 입력하시오:");
    int seconds;
    scanf("%d", &seconds);
    char *timeStr = getKoreanTimeStr(seconds);
    printf("%s입니다.", timeStr);
    printf("\n");
    free(timeStr);
}


int main() {
    runAssignment4();
}
