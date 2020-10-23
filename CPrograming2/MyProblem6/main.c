#include <stdio.h>
#include "remscinterface.h"
#define MSG_LENGTH 72

void convert_endian(int *data) {
    // Your code!
}

int main() {
    init(convert_endian);
    // remscinterface.c의 내부 동작을 초기화하는 함수입니다.
    // remscinterface.c의 내부 함수가 우리가 구현한 convert_endian를 사용할 수 있도록 
    // 해당 함수의 포인터를 매개변수로 전달합니다.
 
    char msg[MSG_LENGTH] = "Scheduling in Heterogeneous Computing Environments for Proximity Queries";
    // = {'S', 'c', 'h', ..., 'i', 'e', 's'}; (윗줄과 동일한 코드입니다.)
    for (int i = 0; i < MSG_LENGTH; i++) {
        send_data(msg[i]);
    }
}