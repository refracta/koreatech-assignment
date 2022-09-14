/**
  @file Problem3.c
  @brief Lab6-3. ���� ���̺� (�迵�� ����)
*/

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

/**
  @brief �־��� ���ڿ��� �ܾ� ������ �м��Ͽ� wordTable�� ������ �����մϴ�.
  @param inputMessage ��� ���ڿ�
  @param wordTable ��� ���� �迭
  @return �ܾ��� ����
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
  @brief ���� �Լ��Դϴ�.
*/
int main() {
    const char *inputMessage = "Welcome to C2 lecture";
    printf("%s\n", inputMessage);
    int wordTable[1000][2];
    memset(wordTable, -1, sizeof(int) * 1000 * 2);
    int wordsize = split(inputMessage, wordTable);
    printf("�� �ܾ� ���� %d\n", wordsize);
    for (int cc = 0; cc < wordsize; cc++) {
        printf("�� �ܾ��� ù��° �ڸ�: %d, �ܾ��� ����: %d\t", wordTable[cc][0], wordTable[cc][1]);
        for (int ci = 0; ci < wordTable[cc][1]; ci++) {
            printf("%c", inputMessage[wordTable[cc][0] + ci]);
        }
        printf("\n");
    }
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
