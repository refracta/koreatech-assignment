/**
  @file Problem3.c
  @brief Lab1-3. 이진수 변환 (김영우 조교)
  @details WARNING: 본 예제 풀이는 int형 변수의 크기가 32비트임을 상정하고 제작되었습니다.
  */
#include <stdio.h>

/**
 * @brief int형 정수를 받아 해당 변수의 이진수 형태을 출력합니다.
 * @details 반복문 내부에서 Shift Operator를 이용하여 해당 자리의 비트가 존재하는지 검사하여 해당 비트의 자리를 출력합니다.
 * @param dec int형 정수
 */
void printBinaryForm(int dec) {
    int mask;
    for (int i = 32 - 1; i >= 0; i--) {
        mask = 1 << i;
        printf("%d", dec & mask ? 1 : 0);
        // dec & mask == 0인 경우에만 0이 출력되게 됨.
        i % 8 == 0 ? printf(" ") : 0;
    }
    printf("\n");
}

/**
 * @brief 시작 함수입니다.
 */
int main() {
    printf("변환할 십진수를 입력하시오:");
    int dec;
    scanf("%d", &dec);
    printBinaryForm(dec);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
