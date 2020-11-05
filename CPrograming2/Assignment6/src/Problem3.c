/**
  @file Problem3.c
  @brief Lab6-3. 워드 테이블 (김영우 조교)
*/

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

/**
  @brief 주어진 문자열을 단어 단위로 분석하여 wordTable에 정보를 저장합니다.
  @param inputMessage 대상 문자열
  @param wordTable 대상 정보 배열
  @return 단어의 개수
*/
int split(const char *inputMessage, int wordTable[1000][2]) {
    int i = -1;
    int index = 0;
    int previousIndex = 0;
    while (i++, true) {
        int isSpace = inputMessage[i] == ' ';
        int isEnd = inputMessage[i] == '\0';
        if (isSpace || isEnd) {
            wordTable[index][0] = previousIndex;
            wordTable[index][1] = i - previousIndex;
            previousIndex = i + 1;
            index++;
            if (isEnd) {
                break;
            }
        }
    }
    return index;
}

/**
  @brief 시작 함수입니다.
*/
int main() {
    const char *inputMessage = "Welcome to C2 lecture";
    printf("%s\n", inputMessage);
    int wordTable[1000][2];
    memset(wordTable, -1, sizeof(int) * 1000 * 2);
    int wordsize = split(inputMessage, wordTable);
    printf("총 단어 개수 %d\n", wordsize);
    for (int cc = 0; cc < wordsize; cc++) {
        printf("각 단어의 첫번째 자리: %d, 단어의 길이: %d\t", wordTable[cc][0], wordTable[cc][1]);
        for (int ci = 0; ci < wordTable[cc][1]; ci++) {
            printf("%c", inputMessage[wordTable[cc][0] + ci]);
        }
        printf("\n");
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
