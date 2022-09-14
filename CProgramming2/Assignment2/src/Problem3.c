/**
  @file Problem3.c
  @brief Lab2-3. ī�� ��Ʋ ���� (�迵�� ����)
  @details WARNING: �� ���� Ǯ�̴� int�� ������ ũ�Ⱑ 32��Ʈ���� �����ϰ� ���۵Ǿ����ϴ�.
*/
#include <stdio.h>

/**
 * @brief ����ŷ ó���� ������ �����ɴϴ�.
 * @details ����ũ ������ ���� �־��� size ������ ���� ���� int ������ Binary Form ���� �������� 1�� ä�� ���� ��ȯ�մϴ�. size=1�̸� [00000000 00000000 00000000 00000001], size=10�̸� [00000000 00000000 00000011 11111111]�� ��ȯ�մϴ�.
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
 * @brief Shift Operator�� �̿��Ͽ� unsigned int�� ������ ���ϴ� �κп� �����͸� �����մϴ�.
 * @details �־��� �Ű����� ���� �´� baseData�� ��Ʈ ������ newData�� ���� �����մϴ�. shiftMargin=2, maskSize=4, baseData=[00000000 00000000 00000000 00000000], baseData=[00000000 00000000 00000000 0100<0010>]�� ��� [00<0010>00 00000000 00000000 00000000] <0010>�� �����ϰ� �˴ϴ�.
 * @param shiftMargin �������κ��� �ǳ� �ٰ� ������ ��Ʈ�� ����
 * @param baseData ������ ��� ������
 * @param maskSize ���� ����
 * @param newData ������ ��� ������
 * @return ������ ������
 */
int injectData(int shiftMargin, int maskSize, unsigned int baseData, unsigned int newData) {
    int maskInt = getMaskInt(maskSize);
    newData = (maskInt & newData) << (32 - maskSize - shiftMargin);
    baseData = baseData & ~(maskInt << (32 - maskSize - shiftMargin));
    return baseData + newData;
}

/**
 * @brief ī�� ���� ������ �������Դϴ�.
 */
typedef enum CardData {
    PRICE, DEFAULT_HP, CURRENT_HP, DEFAULT_ATK, CURRENT_ATK
};

/**
 * @brief ���� ����� �������Դϴ�. ��ȣ �ı�, ī�� ����, �� ����, ��� ������ ��찡 �ֽ��ϴ�.
 */
typedef enum BattleStatus {
    MUTUAL_DESTROYED, CARD_SURVIVED, ENEMY_SURVIVED, ALL_SURVIVED
};

const char *cardName[5] = {"�����", "����", "�Ƹ�", "�ǿ���", "�̺�"};
int cardData[5] = {0x33331, 0x11222, 0x22221, 0x55333, 0x44222};

/**
 * @brief �ҽ� ���ø��� ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
int getCardData(int number) {
    return cardData[number];
}
/**
 * @brief �ҽ� ���ø��� ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
int getData(unsigned int data, int index) {
    return extractData(12 + 20 - (index + 1) * 4, 4, data);
}
/**
 * @brief �ҽ� ���ø��� ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
int updateData(unsigned int data, int index, int value) {
    return injectData(12 + 20 - (index + 1) * 4, 4, data, value);
}

/**
 * @brief �ҽ� ���ø��� ���ǵ� �Լ��� ���� �� ����ü�Դϴ�.
 */
void battleResult(int cardData, int enemyData) {
    int status = 0;
    status += getData(cardData, CURRENT_HP) > getData(enemyData, CURRENT_ATK);
    status += (getData(enemyData, CURRENT_HP) > getData(cardData, CURRENT_ATK)) * 2;
    switch (status) {
        case MUTUAL_DESTROYED:
            printf("�� ī�� ��� �ı��Ǿ� ���º��Դϴ�.\n");
            break;
        case CARD_SURVIVED:
            printf("�� ī�尡 �¸��߽��ϴ�.\n");
            break;
        case ENEMY_SURVIVED:
            printf("��� ī�尡 �¸��߽��ϴ�.\n");
            break;
        case ALL_SURVIVED:
            printf("�� ī�尡 ��� �ı����� �ʾ����� ���º��Դϴ�.\n");
            break;
    }
}

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
    printf("��� ī�� ���� \n");
    for (int i = 0; i < 5; i++) {
        printf("%s : ���ݷ� %d, ü�� %d, ���� %d\n", cardName[i], getData(cardData[i], DEFAULT_ATK),
               getData(cardData[i], DEFAULT_HP), getData(cardData[i], PRICE));
    }
    printf("--------------------------------------------------\n");

    int mycardNumber = 3; //�� ī�尡 � ī������
    int mycardData = getCardData(mycardNumber); //�� ī���� �⺻ ������ �ҷ��ɴϴ�
    printf("���� ������ �ִ� ī��� [%s] �Դϴ�. \n", cardName[mycardNumber]);

    int enemycardNumber = 1; //��� ī�尡 � ī������
    int enemycardData = getCardData(enemycardNumber); //��� ī���� �⺻ ������ �ҷ��ɴϴ�
    printf("��밡 ������ �ִ� ī��� [%s] �Դϴ�. \n", cardName[enemycardNumber]);

    printf("--------------------------------------------------\n");
    printf("���� ��� [%s] vs [%s] \n", cardName[mycardNumber], cardName[enemycardNumber]);
    battleResult(mycardData, enemycardData); //���� ��� ���

    mycardData = updateData(mycardData, CURRENT_HP,
                            getData(mycardData, CURRENT_HP) - getData(enemycardData, CURRENT_ATK)); // �� ī���� ���¸� ������Ʈ �մϴ�. ���̳ʽ� ü�µ� ����մϴ�
    printf("%s : ������ݷ� %d, ����ü�� %d, ���� %d\n", cardName[mycardNumber], getData(mycardData, CURRENT_ATK), getData(mycardData, CURRENT_HP),
           getData(mycardData, PRICE));
    printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}