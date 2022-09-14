#include <stdio.h>

/**
 * 연산 횟수를 받아 연산 횟수를 출력한다.
 * @param tryAdd add 연산 횟수
 */
void count(int tryAdd) {
    printf("연산 횟수: %d\n", tryAdd);
}

/**
 * 두 수를 더해서 반환한다.
 * @param number1 숫자1
 * @param number2 숫자2
 * @return 숫자1 + 숫자2
 */
int add(int number1, int number2) {
    return number1 + number2;
}


/**
 * 두 정수를 입력받아 덧셈을 하는 함수 add()와 add() 함수가 몇 번 사용되었는지 출력하는 count() 함수를 작성하고 결과를 출력하는 프로그램을 작성하시오. count() 함수는 두 정수 모두 0을 입력하면 실행이 되도록 한다. add() 함수의 입력는 2개의 정수, 반환값은 덧셈 결과를 나타내는 정수로 한다. count() 함수의 입력은 add() 함수를 이용한 연산 횟수를 나타내는 1개의 정수, 반환값은 없는 것으로 한다.
 */
int main() {
    for (int tryAdd = 0;;) {
        int number1, number2;
        printf("숫자 두 개를 입력하시오: ");
        scanf("%d %d", &number1, &number2);
        if (number1 == 0 && number2 == 0) {
            count(tryAdd);
        } else {
            printf("덧셈 결과: %d\n", add(number1, number2));
            tryAdd++;
        }
    }
}

