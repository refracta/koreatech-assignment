#include <stdio.h>
#include "remscinterface.h"
#define MSG_LENGTH 72

void convert_endian(int *data) {
    // Your code!
}

int main() {
    init(convert_endian);
    // remscinterface.c�� ���� ������ �ʱ�ȭ�ϴ� �Լ��Դϴ�.
    // remscinterface.c�� ���� �Լ��� �츮�� ������ convert_endian�� ����� �� �ֵ��� 
    // �ش� �Լ��� �����͸� �Ű������� �����մϴ�.
 
    char msg[MSG_LENGTH] = "Scheduling in Heterogeneous Computing Environments for Proximity Queries";
    // = {'S', 'c', 'h', ..., 'i', 'e', 's'}; (���ٰ� ������ �ڵ��Դϴ�.)
    for (int i = 0; i < MSG_LENGTH; i++) {
        send_data(msg[i]);
    }
}