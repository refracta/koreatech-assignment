/*! \file */
#ifndef PROJECT_H
#define PROJECT_H

#include <Arduino.h>
#include "RGDotMatrixRenderer.h"
#include "RGDotMatrixFont.h"
#include "SoundController.h"
#include "Tune.h"
#include "EEPROMUtils.h"

#define NOTE_PREVIEW 3
#define NUM_OF_MUSIC_DATA 4
#define CUSTOM_MUSIC_INDEX 3

// 디버그 플래그
#define DEBUG_MODE
#ifdef DEBUG_MODE
#define debug(P) Serial.print(P)
#define debugln(P) Serial.println(P)
#else
#define debug(P)
#define debugln(P)
#endif

// 버튼
#define BUTTON1_PIN 8
#define BUTTON2_PIN A3
#define BUTTON3_PIN 0
#define BUTTON4_PIN 1
#define NUM_OF_BUTTON 4

#define IS_BUTTON_PRESSED(BUTTON_PIN) (!digitalRead(BUTTON_PIN))
#define IS_ANY_BUTTON_PRESSED() (IS_BUTTON_PRESSED(BUTTON1_PIN) || IS_BUTTON_PRESSED(BUTTON2_PIN) || IS_BUTTON_PRESSED(BUTTON3_PIN) || IS_BUTTON_PRESSED(BUTTON4_PIN))

#define DISABLE_SERIAL_PIN_BUTTONS() pinMode(BUTTON3_PIN, INPUT); pinMode(BUTTON4_PIN, INPUT);
#define ENABLE_SERIAL_PIN_BUTTONS() pinMode(BUTTON3_PIN, INPUT_PULLUP); pinMode(BUTTON4_PIN, INPUT_PULLUP);

const int BUTTON_PINS[] = {BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN, BUTTON4_PIN};

// 렌더러와 렌더 버퍼
RGDotMatrixRenderer renderer((int[]) {A4, A5, 2, 3, 4, 5, 6, 7}, (int[]) {10, 10, 11, 11, 12, 12, 13, 13}, A0, A1, A2);
DotMatrixImage *rib = nullptr; // Single renderImageBuffer
int ribSize;
int playIndex = 0;
RGDotMatrixImage renderImage;

// 딜레이 하이재킹
void (*_delay)(unsigned long) = delay;

#define delay(MS) delayWithCustomHandler(MS)

void (*customHandler)(unsigned long, unsigned long);

void delayWithCustomHandler(unsigned long ms) {
    unsigned long current = millis();
    unsigned long delta;
    while ((delta = millis() - current) < ms) {
        if (customHandler) {
            customHandler(current, ms - delta);
        }
    }
}

// 음악 데이터
String musicData[NUM_OF_MUSIC_DATA];
int musicDataCursor = 0;
SoundController soundController(9, delayWithCustomHandler);

void initMusicData() {
    musicData[0] = F(
            "TAKE ON ME:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5");
    musicData[1] = F(
            "THE SIMPSONS:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6");
    musicData[2] = F(
            "ENTERTAINER:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6");
    musicData[3] = F("CUSTOM:");
}

// 게임 상태
enum GameStatus {
    MAIN_SCREEN, SELECT_MUSIC_SCREEN, GAME_SCREEN, GAME_RESULT_SCREEN
};
boolean isInited = false;
GameStatus previousStatus;
GameStatus currentStatus = MAIN_SCREEN;

// 인게임 노트 데이터 처리
char nextNotes[3];
boolean isHit = false;
int BASE_TIME;

// 인게임 렌더링
unsigned long long FONT_NOTE_COLS[] = {FONT_NOTE_COL1, FONT_NOTE_COL2, FONT_NOTE_COL3, FONT_NOTE_COL4};
unsigned long long FONT_GAME_COLS[] = {FONT_GAME_COL1, FONT_GAME_COL2, FONT_GAME_COL3, FONT_GAME_COL4};
struct TimeBasedRGDotMatrix {
    RGDotMatrixImage image;
    long targetTime;
};
#define NUM_OF_TIME_BASED_EFFECT 3
TimeBasedRGDotMatrix timeBasedEffects[NUM_OF_TIME_BASED_EFFECT];

// 인게임 데이터
int maxCombo = 0;
int combo = 0;
unsigned int score = 0;

// 스크롤 메시지 버퍼
#define MESSAGE_BUFFER_LENGTH 20
char message[MESSAGE_BUFFER_LENGTH];
int messageLen;

void changeGameStatus(GameStatus);

#endif
