#include <stdio.h>
#include <stdlib.h>

/**
 * 알파벳 문자 하나를 입력받아 알파벳 순서로 몇 번째 문자인지 반환한다
 * @param alphabet 알파벳 문자
 * @return 알파벳 순서
 */
int alpha(char alphabet) {
    int isUCAlphabet = 'A' <= alphabet && alphabet <= 'Z';
    int isLCAlphabet = 'a' <= alphabet && alphabet <= 'z';
    int isValid = isUCAlphabet || isLCAlphabet;
    if (!isValid) {
       return -1;
    }else{
        return alphabet - isUCAlphabet * 'A' - isLCAlphabet * 'a' + 1;
    }
}

/**
 * 알파벳 문자 하나를 입력받아 알파벳 순서로 몇 번째 문자인지 반환하는 alpha() 함수를 작성하고 결과를 출력하는 프로그램을 작성하시오. 단, 대소문자의 순서를 구별하지 않는다. 즉, 대문자 A나 소문자 a는 1번째 문자. alpha() 함수의 입력은 1개의 문자, 반환값은 순서를 나타내는 정수로 한다.
 */
int main() {
    char alphabet;
    printf("알파벳을 입력하시오: ");
    scanf("%c", &alphabet);
    int order = alpha(alphabet);
    if(order != -1){
        printf("%d번째 문자입니다.", order);
    }else{
        printf("입력한 문자가 알파벳 문자가 아닙니다.");
    }
}
