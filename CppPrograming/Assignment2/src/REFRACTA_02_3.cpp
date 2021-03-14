#include <iostream>
#include <cstdio>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(WIN32)
#define getch() _getch()
#endif

int compare(char* n1, char* n2) {
    int l1 = strlen(n1);
    int l2 = strlen(n2);
    return l1 < l2 ? -1 : (l1 > l2 ? 1 : strcmp(n1, n2));
}

char* next_bigint(bool use_secure) {
    char* buf = (char*)malloc(sizeof(char));
    int i = 0;
    while (true) {
        char c = getch();
        if (('0' <= c && c <= '9') && !(i == 0 && c == '0')) {
            buf[i++] = c;
            buf = (char*) realloc(buf, sizeof(char) * (i + 1));
            use_secure ? printf("*") : printf("%c", c);
        }
        else if (c == '\r' && i != 0) {
            buf[i] = '\0';
            printf("\n");
            return buf;
        }
    }
}

int main() {
    int i = 0, cmp;
    printf("���� �Է�(�ڸ��� ������): ");
    char* n = next_bigint(true);
    int nl = strlen(n);
    char* input = NULL;
    for (; i < 10; i++) {
        printf("[%2dȸ] (0, 10^%d) ������ �� ���� =>", i + 1, nl);
        free(input);
        input = next_bigint(false);
        cmp = compare(n, input);
        if (cmp == 0) break;
        else if (cmp == 1) {
            printf(" �� ū �����Դϴ�!\n");
        }
        else {
            printf(" �� ���� �����Դϴ�!\n");
        }
    }
    printf(" %s !!! ������ %s\n", (cmp == 0) ? "����" : "����", input);
    printf(" ���� ���� = %d\n", nl * (10 - i));
    free(input);
    free(n);
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
    return 0;
}