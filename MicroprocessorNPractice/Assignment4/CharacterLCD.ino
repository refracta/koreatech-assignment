#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>

#define SWITCH_PIN 2
#define LC_D0_PIN 6
#define LC_D1_PIN 5
#define LC_D2_PIN 4
#define LC_D3_PIN 3
#define LC_ENABLE_PIN 11
#define LC_RS_PIN 12
#define SHIFT_DELAY 500

int switchCount = 0;
boolean isPressing = false;

// 스위치 상태를 확인하고, 스위치 카운트를 증가시킨다.
void switchHandler() {
    int switchStatus = !digitalRead(SWITCH_PIN);
    if (switchStatus && !isPressing) {
        isPressing = true;
        switchCount++;
    } else if (!switchStatus && isPressing) {
        isPressing = false;
    }
}

// 스크린 글자 배열
char screen[16 * 2];
const char *TARGET_STRING = "refracta";
LiquidCrystal lcd(LC_RS_PIN, LC_ENABLE_PIN, LC_D0_PIN, LC_D1_PIN, LC_D2_PIN, LC_D3_PIN);

// 스크린에 글자 배열을 출력
void display() {
    lcd.setCursor(0, 0);
    for (int i = 0; i < 16; i++) {
        lcd.print(screen[i]);
    }
    lcd.setCursor(0, 1);
    for (int i = 16; i < 32; i++) {
        lcd.print(screen[i]);
    }
}

// 글자를 왼쪽으로 한글자씩 밀기
void shiftLeft() {
    char s0 = screen[0];
    for (int i = 1; i < 16 * 2; ++i) {
        screen[i - 1] = screen[i];
    }
    screen[16 * 2 - 1] = s0;
}

void setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchHandler, CHANGE);
    // 스위치 핀 모드, 인터럽트 설정
    memset(screen, ' ', 16 * 2);
    // 글자 배열을 ' '로 초기화
    strncpy(screen, TARGET_STRING, strlen(TARGET_STRING));
    // 글자 배열에 TARGET_STRING을 복사
    lcd.begin(16, 2);
    lcd.noCursor();
    lcd.noBlink();
    // LCD 초기화
    Serial.begin(9600);
}

void loop() {
    if (switchCount == 1) {
        display();
    } else if (switchCount != 0 && switchCount % 2 == 0) {
        display();
        shiftLeft();
        delay(SHIFT_DELAY);
    }
}