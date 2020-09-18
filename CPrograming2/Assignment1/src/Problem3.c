/**
  @file Problem3.c
  @brief Lab1-3. ������ ��ȯ (�迵�� ����)
  @details WARNING: �� ���� Ǯ�̴� int�� ������ ũ�Ⱑ 32��Ʈ���� �����ϰ� ���۵Ǿ����ϴ�.
  */
#include <stdio.h>

/**
 * @brief int�� ������ �޾� �ش� ������ ������ ������ ����մϴ�.
 * @details �ݺ��� ���ο��� Shift Operator�� �̿��Ͽ� �ش� �ڸ��� ��Ʈ�� �����ϴ��� �˻��Ͽ� �ش� ��Ʈ�� �ڸ��� ����մϴ�.
 * @param dec int�� ����
 */
void printBinaryForm(int dec) {
    int mask;
    for (int i = 32 - 1; i >= 0; i--) {
        mask = 1 << i;
        printf("%d", dec & mask ? 1 : 0);
        // dec & mask == 0�� ��쿡�� 0�� ��µǰ� ��.
        i % 8 == 0 ? printf(" ") : 0;
    }
    printf("\n");
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    printf("��ȯ�� �������� �Է��Ͻÿ�:");
    int dec;
    scanf("%d", &dec);
    printBinaryForm(dec);
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
