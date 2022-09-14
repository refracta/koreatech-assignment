/**
 * refracta - 마이크로프로세서및실습 (CSE124-02)
 * 과제 3 IR Sensor 소스 코드
 */
#include <IRremote.h>
#include <LiquidCrystal.h>

#define BUZZER_PIN 10
#define RECEIVE_PIN 7

#define LC_D0_PIN 5
#define LC_D1_PIN 4
#define LC_D2_PIN 3
#define LC_D3_PIN 2
#define LC_ENABLE_PIN 11
#define LC_RS_PIN 12

#define IR_CH_MINUS 0xFFA25D
#define IR_CH 0xFF629D
#define IR_CH_PLUS 0xFFE21D
#define IR_PREV 0xFF22DD
#define IR_NEXT 0xFF02FD
#define IR_PAUSE 0xFFC23D
#define IR_MINUS 0xFFE01F
#define IR_PLUS 0xFFA857
#define IR_EQ 0xFF906F
#define IR_0 0XFF6897
#define IR_100 0xFF9867
#define IR_200 0xFFB04F
#define IR_1 0xFF30CF
#define IR_2 0xFF18E7
#define IR_3 0xFF7A85
#define IR_4 0xFF10EF
#define IR_5 0xFF38C7
#define IR_6 0xFF5AA5
#define IR_7 0xFF42BD
#define IR_8 0xFF4AB5
#define IR_9 0xFF52AD
#define IR_NUM_OF_BUTTONS 21

int BUTTON_VALUES[] = {IR_CH_MINUS, IR_CH, IR_CH_PLUS, IR_PREV, IR_NEXT, IR_PAUSE, IR_MINUS, IR_PLUS, IR_EQ, IR_0,
                       IR_100, IR_200, IR_1, IR_2, IR_3, IR_4, IR_5, IR_6, IR_7, IR_8, IR_9};
char CALCULATOR_SYMBOLS[] = {'E', '(', ')', 'B', 'C', '/', '-', '+', '*', '0', '<', '>', '1', '2', '3', '4', '5', '6',
                             '7', '8', '9'};

char toChar(int signal) {
    for (int i = 0; i < IR_NUM_OF_BUTTONS; i++) {
        if (BUTTON_VALUES[i] == signal) {
            return CALCULATOR_SYMBOLS[i];
        }
    }
    return '\0';
}

LiquidCrystal lcd(LC_RS_PIN, LC_ENABLE_PIN, LC_D0_PIN, LC_D1_PIN, LC_D2_PIN, LC_D3_PIN);
IRrecv irr(RECEIVE_PIN);
decode_results results;

#define SUCCESS_TUNE() playTone('g', 5, 200);
#define FAIL_TUNE() playTone('F', 6, 100); playTone('F', 6, 100);

/*
 * data from https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * 아두이노 튜토리얼 문서의 헤더 파일을 배열 형태로 정리한 것, 각 음계의 진동수의 상수 정의이다.
 */
const int frequencies[] =
        {
                31,                                                                        // octave 0
                33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,                            // octave 1
                65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123,                        // octave 2
                131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,                // octave 3
                262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,                // octave 4
                523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,                // octave 5
                1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,    // octave 6
                2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,    // octave 7
                4186, 4435, 4699, 4978                                                     // octave 8
        };


// "도 도# 레 레# 미 파 파# 솔 솔# 라 라# 시" 순의 출력 처리용 character 배열
const char notes[] = {'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g', 'G', 'a', 'A', 'b'}; // length = 12

// note에 해당하는 notes의 index를 반환한다.
int getNoteIndex(char note) {
    for (int i = 0; i < 12; i++) {
        if (notes[i] == note) {
            return i;
        }
    }
    return -1;
}

// note, octave의 출력으로 duration 동안 부저에 소리를 출력하는 함수
void playTone(char note, int octave, int duration) {
    int frequency = frequencies[getNoteIndex(note) - 11 + octave * 12];
    tone(BUZZER_PIN, frequency, duration);
    delay(duration);
    noTone(BUZZER_PIN);
}

int getReceiveSignal() {
    int value = 0;
    if (irr.decode(&results)) {
        if (results.decode_type == NEC) {
            value = results.value;
        }
        irr.resume();
    }
    return value;
}

char screen[32] = {0,};
int cursor = 0;

void clear(bool withZero) {
    for (int i = 0; i < 32; i++) {
        screen[i] = 0;
    }
    lcd.clear();
    if (withZero) {
        lcd.print('0');
    }
    lcd.home();
    cursor = 0;
}

#define IS_ADD_TYPE(c) ((c) == '+' || (c) == '-')
#define IS_MULTI_TYPE(c) ((c) == '*' || (c) == '/')
#define IS_OPERATOR(c) (IS_ADD_TYPE(c) || IS_MULTI_TYPE(c))
#define IS_PARENTHESES(c) ((c) == ')' || (c) == ')')
#define IS_DIGIT(c) ('0' <= (c) && (c) <= '9')
#define STACK_SIZE 64

// 주어진 표현식의 소괄호 쌍이 닫혀있는지 검사한다.
bool isValidParentheses(char *target) {
    int length = strlen(target);
    if (length == 0) { return true; }
    // if (length % 2 == 1) { return false; }
    char stack[32] = {0,};
    int stackCursor = 0;
    for (int i = 0; i < length; i++) {
        char c = target[i];
        if (c == '(') {
            stack[stackCursor++] = c;
        } else if (c == ')') {
            if (stackCursor == 0) {
                return false;
            } else {
                stack[--stackCursor] = '\0';
            }
        }
    }
    return stackCursor == 0;
}

// 주어진 표현식을 검증한다. (소괄호 쌍 검사, 연산자와 피연산자가 올바른 형태로 나타났는지 검사)
bool isValidExpression(char *target) {
    if (!isValidParentheses(target)) {
        return false;
    }
    int operatorCount = 0;
    int operandCount = 0;
    char prev = '(';
    int length = strlen(target);
    for (int i = 0; i < length; i++) {
        char c = target[i];
        if (IS_OPERATOR(c)) {
            if (operandCount == 0) {
                return false;
            }
            operandCount = 0;
            ++operatorCount;
            if (operatorCount > 1) {
                return false;
            }
        } else if (!IS_DIGIT(prev) && IS_DIGIT(c)) {
            operatorCount = 0;
            ++operandCount;
            if (operandCount > 1) {
                return false;
            }
        }
        prev = c;
    }
    return operatorCount == 0;
}

// 함수 포인터로 이용되는 표현식 계산 소기능 함수들
bool isOperatorPredicate(char c) {
    return IS_OPERATOR(c);
}

bool isLPPredicate(char c) {
    return c == '(';
}

bool isMultiTypePredicate(char c) {
    return IS_MULTI_TYPE(c);
}

bool isLPAndAddTypePredicate(char c) {
    return c == '(' || IS_ADD_TYPE(c);
}

bool alwaysFalsePredicate(char c) {
    return false;
}

String postfix;

// stack에서 postfix String에 덧붙일 요소들을 이동시킨다.
int moveOperatorsToPostfix(char *stack, int stackCursor, bool (*pushPredicate)(char), bool (*stopPredicate)(char)) {
    int originalStackCursor = stackCursor;
    while (stackCursor != 0) {
        char top = stack[stackCursor - 1];
        if (pushPredicate(top)) {
            postfix += top;
            postfix += ' ';
            stackCursor--;
        } else if (stopPredicate(top)) {
            break;
        }
    }
    return stackCursor - originalStackCursor;
}

// infix 표현식을 postfix 형태로 변환시킨다.
String toPostfix(char *infix) {
    postfix = "";
    char stack[STACK_SIZE];
    int stackCursor = 0;
    int length = strlen(infix);
    int n = 0;
    bool processingDigit = false;
    for (int i = 0; i < length; i++) {
        char c = infix[i];
        if (IS_DIGIT(c)) {
            processingDigit = true;
            n = (c - '0') + n * 10;
        } else if (c == '(') {
            stack[stackCursor++] = c;
        } else if (c == ')' || IS_OPERATOR(c)) {
            if (processingDigit) {
                postfix += String(n) + " ";
                n = 0;
                processingDigit = false;
            }
            if (IS_OPERATOR(c)) {
                if (stackCursor == 0) {
                    stack[stackCursor++] = c;
                } else {
                    if (IS_ADD_TYPE(c)) {
                        stackCursor += moveOperatorsToPostfix(stack, stackCursor, isOperatorPredicate, isLPPredicate);
                    } else {
                        stackCursor += moveOperatorsToPostfix(stack, stackCursor, isMultiTypePredicate,
                                                              isLPAndAddTypePredicate);
                    }
                    stack[stackCursor++] = c;
                }
            } else {
                stackCursor += moveOperatorsToPostfix(stack, stackCursor, isOperatorPredicate, isLPPredicate);
                int top = stack[stackCursor - 1];
                if (top == '(') { stackCursor--; }
            }
        }
    }
    if (processingDigit) {
        postfix += String(n) + " ";
    }
    stackCursor += moveOperatorsToPostfix(stack, stackCursor, isOperatorPredicate, alwaysFalsePredicate);
    postfix = postfix.substring(0, postfix.length() - 1);
    return postfix;
}

// postfix 형태를 가지는 표현식의 실제 연산 결과를 얻는다.
int evaluatePostfix(String postfix) {
    int stack[STACK_SIZE];
    int stackCursor = 0;
    int n = 0;
    bool processingDigit = false;
    int length = postfix.length();
    for (int i = 0; i < length; i++) {
        char c = postfix[i];
        if (IS_DIGIT(c)) {
            processingDigit = true;
            n = (c - '0') + n * 10;
        } else if (c == ' ') {
            if (processingDigit) {
                stack[stackCursor++] = n;
                n = 0;
                processingDigit = false;
            }
        } else if (IS_OPERATOR(c)) {
            int n2 = stack[--stackCursor];
            int n1 = stack[--stackCursor];
            switch (c) {
                case '+':
                    stack[stackCursor++] = n1 + n2;
                    break;
                case '-':
                    stack[stackCursor++] = n1 - n2;
                    break;
                case '*':
                    stack[stackCursor++] = n1 * n2;
                    break;
                default:
                    stack[stackCursor++] = n1 / n2;
                    break;
            }
        }
    }
    return stack[--stackCursor];
}

bool evalStatus = true;

// 계산기 표현식을 매개변수로 받아 해당 표현식의 평가값을 반환한다. 구문, 문법 오류가 나지 않으면 evalStatus의 값을 false로, 오류가 나면 true로 변경한다.
int evaluate(char *target) {
    if (!isValidExpression(target)) {
        evalStatus = false;
        return 0;
    } else {
        evalStatus = true;
        return evaluatePostfix(toPostfix(target));
    }
}

// 현재 계산기 화면을 직렬 통신 출력으로 내보낸다.
void printToSerial() {
    Serial.println("<CalculatorScreen>");
    Serial.print('[');
    for (int i = 0; i < 16; i++) {
        if (screen[i]) {
            Serial.print(screen[i]);
        } else {
            Serial.print(' ');
        }
    }
    Serial.println(']');
    Serial.print('[');
    for (int i = 16; i < 32; i++) {
        if (screen[i]) {
            Serial.print(screen[i]);
        } else {
            Serial.print(' ');
        }
    }
    Serial.println(']');
}

// LCD, IR 수신부 초기화
void setup() {
    lcd.begin(16, 2);
    lcd.blink();
    clear(true);
    irr.enableIRIn();
    Serial.begin(9600);
}

int eval = 0;
bool waitClear = false;

// 사용자의 계산기 입력이 처리되는 루프
void loop() {
    lcd.cursor();
    char input = toChar(getReceiveSignal());
    if (input) {
        if (waitClear) {
            waitClear = false;
            clear(true);
        }
        switch (input) {
            case 'C':
                // Clear
                SUCCESS_TUNE();
                clear(true);
                break;
            case 'B':
                // Backspace
                if (cursor > 0) {
                    SUCCESS_TUNE();
                    if (screen[cursor] && cursor < 32) {
                        int c = cursor;
                        for (; c < 32; c++) {
                            if (screen[c]) {
                                screen[c - 1] = screen[c];
                                lcd.setCursor((c - 1) % 16, (c - 1) / 16);
                                lcd.print(screen[c - 1]);
                            } else {
                                break;
                            }
                        }
                        screen[c - 1] = '\0';
                        if (c - 2 == 15) {
                            lcd.setCursor(0, 1);
                        }
                        lcd.print(' ');
                        cursor--;
                        lcd.setCursor(cursor % 16, cursor / 16);
                    } else {
                        cursor--;
                        screen[cursor] = '\0';
                        lcd.setCursor(cursor % 16, cursor / 16);
                        lcd.print(' ');
                        lcd.setCursor(cursor % 16, cursor / 16);
                    }
                } else {
                    FAIL_TUNE();
                }
                break;
            case 'E':
                // Enter
                if (cursor == 0 && !screen[cursor]) {
                    FAIL_TUNE();
                    return;
                }
                eval = evaluate(screen);
                clear(false);
                lcd.noBlink();
                if (evalStatus) {
                    SUCCESS_TUNE();
                    lcd.print("=");
                    lcd.print(eval);
                    Serial.print("EVAL: ");
                    Serial.println(eval);
                } else {
                    FAIL_TUNE();
                    lcd.print("SYNTAX ERROR!");
                    Serial.println("EVAL: SYNTAX ERROR!");
                }
                waitClear = true;
                break;
            case '<':
                // 커서 왼쪽으로 옮기기
                if (0 < cursor) {
                    SUCCESS_TUNE();
                    cursor--;
                    lcd.setCursor(cursor % 16, cursor / 16);
                } else {
                    FAIL_TUNE();
                }
                break;
            case '>':
                // 커서 오른쪽으로 옮기기
                if (cursor < 32 - 1 && screen[cursor]) {
                    SUCCESS_TUNE();
                    cursor++;
                    lcd.setCursor(cursor % 16, cursor / 16);
                } else {
                    FAIL_TUNE();
                }
                break;
            default:
                // 비기능 키 입력 구현
                if (cursor < 32) {
                    SUCCESS_TUNE();
                    lcd.print(input);
                    if (cursor == 15) {
                        lcd.setCursor(0, 1);
                    }
                    screen[cursor] = input;
                    cursor++;
                } else {
                    FAIL_TUNE();
                }
                break;
        }
        printToSerial();
    }
}