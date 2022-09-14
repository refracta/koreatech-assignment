/**
  @file Problem5.c
  @brief Lab1-5. ���� �ϳ��� ĳ���� ���� ��� (����� ����)
  @details WARNING: �� ���� Ǯ�̴� int�� ������ ũ�Ⱑ 32��Ʈ���� �����ϰ� ���۵Ǿ����ϴ�.
  */
#include <stdio.h>

/**
 * @brief ���� ���ڿ� �迭
 */
const char RACES[4][BUFSIZ] = {
        "�޸�",
        "��ũ",
        "�𵥵�",
        "����"
};

/**
 * @brief ĳ���� ������ �޾� unsigned int�� ������ ��ȯ�մϴ�.
 * @details ����(0:�޸�, 1:��ũ, 2:�𵥵�, 3:����), ����(0~63), ü��(0~4095), ����(0~4095)�� �޾� ĳ���� ������ int�� ���� �ϳ��� �����մϴ�. WARNING: ����׿� �Լ��Դϴ�.
 * @param raceIndex ĳ���� ���� ���� ��
 * @param level ĳ���� ����
 * @param hp ĳ���� ü��
 * @param mana ĳ���� ����
 * @return unsigned int������ ����� ĳ���� ����
 */
unsigned int generateData(int raceIndex, int level, int hp, int mana) {
    return (raceIndex << 30) + (level << 24) + (hp << 12) + (mana << 0);
}

/**
 * @brief ����ŷ ó���� ������ �����ɴϴ�.
 * @details ����ũ ������ ���� �־��� size ������ ���� ���� int ������ ������ ���� �������� 1�� ä�� ���� ��ȯ�մϴ�. size=1�̸� [00000000 00000000 00000000 00000001], size=10�̸� [00000000 00000000 00000011 11111111]�� ��ȯ�մϴ�.
 * @param size ���� ����
 * @return ����ŷ ó���� ����
 */
int getMaskInt(int size) {
    int mask = 1;
    for (int i = 0; i < size - 1; i++) {
        mask = (mask << 1) + 1;
    }
    return mask;
}

/**
 * @brief Shift Operator�� �̿��Ͽ� unsigned int�� �������� ���ϴ� ��Ʈ ������ ������ �����մϴ�.
 * @details �־��� �Ű����� ���� �´� ��Ʈ ������ ������ data �Ű��������� �����Ͽ� ��ȯ�մϴ�. shiftMargin=2, maskSize=6, data=[11100111 11111111 11111111 11111111]�� ��� [11<100111> 11111111 11111111 11111111] <100111>�� �����ϰ� �˴ϴ�.
 * @param shiftMargin �������κ��� �ǳ� �ٰ� ���� ��Ʈ�� ����
 * @param maskSize ���� ��Ʈ�� ����
 * @param data ������ ��� ������
 * @return ����� ��Ʈ ������ ����
 */
int extractData(int shiftMargin, int maskSize, unsigned int data) {
    int maskInt = getMaskInt(maskSize);
    data = data & (maskInt << (32 - maskSize - shiftMargin));
    data = data >> (32 - maskSize - shiftMargin);
    return data;
}

/**
 * @brief unsigned int�� ĳ���� ���� �����͸� �޾� ���� ���� ��ȯ�մϴ�.
 * @param data unsigned int�� ĳ���� ���� ������
 * @return ĳ���� ����
 */
unsigned char *extractRace(unsigned int data) {
    return (unsigned char *) RACES[extractData(0, 2, data)];
    // https://stackoverflow.com/questions/24830335/c-compiler-warning-return-discards-qualifiers-from-pointer-target-type
}

/**
 * @brief unsigned int�� ĳ���� ���� �����͸� �޾� ���� ���� ��ȯ�մϴ�.
 * @param data unsigned int�� ĳ���� ���� ������
 * @return ĳ���� ����
 */
int extractLevel(unsigned int data) {
    return extractData(2, 6, data);
}

/**
 * @brief unsigned int�� ĳ���� ���� �����͸� �޾� ü�� ���� ��ȯ�մϴ�.
 * @param data unsigned int�� ĳ���� ���� ������
 * @return ĳ���� ü��
 */
int extractHP(unsigned int data) {
    return extractData(2 + 6, 12, data);
}

/**
 * @brief unsigned int�� ĳ���� ���� �����͸� �޾� ���� ���� ��ȯ�մϴ�.
 * @param data unsigned int�� ĳ���� ���� ������
 * @return ĳ���� ����
 */
int extractMana(unsigned int data) {
    return extractData(2 + 6 + 12, 12, data);
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    unsigned int data;
    printf("������ �Է� �Ͻÿ�:");
    scanf("%d", &data);
    printf("����:%s Lv.%d HP:%d MP:%d", extractRace(data), extractLevel(data), extractHP(data), extractMana(data));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}