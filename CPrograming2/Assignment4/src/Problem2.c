/**
  @file Problem2.c
  @brief Lab4-2. �޷� ����⣨��5)
*/
#include <stdio.h>
#include <math.h>

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    printf("* 1582�� 10�� 15�� ���� ��¥�� �����մϴ�.\n");
    printf("����� �⵵�� ���� �Է��Ͻÿ�(yyyy mm):");
    int y, m;
    scanf("%d %d", &y, &m);

    int a, b, c, d;
    a = (m <= 2 ? y - 1 : y) / 100;
    b = (m <= 2 ? y - 1 : y) % 100;
    c = m <= 2 ? m + 12 : m;
    d = 1;
    // ������ ���Ŀ� �ʿ��� a, b, c, d�� �ʱ�ȭ�մϴ�.

    int days_of_week_index =
            (int) (floor((21 * a) / 4.0) + floor((5 * b) / 4.0) + floor((26 * (c + 1)) / 10.0) + d - 1) % 7;
    // ���� ������ ���մϴ�.
    int is_leap_year = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
    // ���� ���θ� Ȯ���մϴ�.
    int days[12] = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // ���� �� �� �迭�� �ʱ�ȭ�մϴ�.
    printf("�� �� ȭ �� �� �� ��\n");
    for (int i = 0; i < days_of_week_index; i++) {
        printf("   ");
    }
    // ù ���� 1�� ���ʿ� ���� ���ڸ� ����մϴ�.
    for (int d = 1; d <= days[m - 1]; d++) {
        printf("%2d ", d);
        if ((days_of_week_index + d - 1) % 7 == 6) {
            printf("\n");
        }
    }
    // �޷� ���
    printf("\n");
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}