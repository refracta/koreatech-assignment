/*! \file */
#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>

#define IS_DIGIT(N) (N >= '0' && N <= '9')
#define IS_PLAYABLE_NOTE(N) (N == 'c' || N == 'C' || N == 'd' || N == 'D' || N == 'e' || N == 'f' || N == 'F' || N == 'g' || N == 'G' || N == 'a' || N =='A' || N == 'b' || N == 'p')
#define OCTAVE_OFFSET 0

#define NOTE rtttl.charAt(cursor)
#define NOTE_PP rtttl.charAt(cursor++)

/*
 * data from https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * 아두이노 튜토리얼 문서의 헤더 파일을 배열 형태로 정리한 것, 각 음계의 진동수의 상수 정의이다.
 */
const int frequencies[] = {
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

// note에 해당하는 notes의 index를 반환한다.
inline int getNoteIndex(char note) {
    switch (note) {
        case 'c':
            return 0;
        case 'C':
            return 1;
        case 'd':
            return 2;
        case 'D':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'F':
            return 6;
        case 'g':
            return 7;
        case 'G':
            return 8;
        case 'a':
            return 9;
        case 'A':
            return 10;
        case 'b':
            return 11;
        default:
            return -1;
    }
}

int getRTTTLMinDuration(String &rtttl) {
    int minDuration = 32767;

    int size = rtttl.length();
    byte defaultDuration = 4;
    int bpm = 63;
    int num;
    long noteTime;
    long duration;
    int cursor;

    // RTTTL 기본 포맷: d=N,o=N,b=NNN:
    while (NOTE != ':') {
        cursor++;
    }    // 곡 제목 넘김
    cursor++;
    // ':' 넘기기

    // get default duration
    if (NOTE == 'd') {
        cursor++;
        cursor++;
        // "d=" 넘기기
        num = 0;
        while (IS_DIGIT(NOTE)) {
            num = (num * 10) + (NOTE_PP - '0');
        }
        if (num > 0) {
            defaultDuration = num;
        }
        cursor++;
        // "," 넘기기
    }

    // 기본 옥타브 설정
    if (NOTE == 'o') {
        cursor++;
        cursor++;
        cursor++;
        // "," 넘기기
    }

    // BPM 설정
    if (NOTE == 'b') {
        cursor++;
        cursor++;
        // "b=" 넘기기
        num = 0;
        while (IS_DIGIT(NOTE)) {
            num = (num * 10) + (NOTE_PP - '0');
        }
        bpm = num;
        cursor++;
        // "," 넘기기
    }
    noteTime = (60 * 1000L / bpm) * 4;
    // 메인 루프


    while (cursor < size) {
        // 가능한 경우, 노트 박자 계산
        num = 0;
        while (IS_DIGIT(NOTE)) {
            num = (num * 10) + (NOTE_PP - '0');
        }

        if (num) {
            duration = noteTime / num;
        } else {
            duration = noteTime / defaultDuration;
        }

        cursor++;

        if (NOTE == '#') {
            cursor++;
        }

        // "." 스트로크 박자 처리
        if (NOTE == '.') {
            duration += duration / 2;
            cursor++;
        }

        // 옥타브 처리
        if (IS_DIGIT(NOTE)) {
            cursor++;
        }

        if (NOTE == ',') {
            cursor++;
        }

        if (duration < minDuration) {
            minDuration = duration;
        }
    }
    return minDuration;
}

struct NoteData {
    char note;
    int octave;
    int duration;
};

class SoundController {
private:
    int buzzerPin;

    void (*delayFunction)(unsigned long);

public:
    SoundController(int buzzerPin, void (*delayFunction)(unsigned long)) : buzzerPin(buzzerPin),
                                                                           delayFunction(delayFunction) {}

    void init() {
        pinMode(buzzerPin, OUTPUT);
    }

    void playTone(char note, int octave, int duration) {
        if (note == 'p') {
            delayFunction(duration);
            return;
        }
        int frequency = frequencies[getNoteIndex(note) - 11 + octave * 12];
        tone(buzzerPin, frequency, duration);
        delayFunction(duration);
        noTone(buzzerPin);
    }

    void playTone(NoteData &data) {
        playTone(data.note, data.octave, data.duration);
    }

    void playRTTTL(String &rtttl, void (*nextHandler)(NoteData *queue, int size),
                   int numOfNext) {
        int size = rtttl.length();
        byte defaultDuration = 4;
        byte octave = 6;
        int bpm = 63;
        int num;
        long noteTime;
        long duration;
        char note;
        byte scale;
        int cursor;



        // RTTTL 기본 포맷: d=N,o=N,b=NNN:
        while (NOTE != ':') {
            cursor++;
        }    // 곡 제목 넘김
        cursor++;
        // ':' 넘기기

        // get default duration
        if (NOTE == 'd') {
            cursor++;
            cursor++;
            // "d=" 넘기기
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }
            if (num > 0) {
                defaultDuration = num;
            }
            cursor++;
            // "," 넘기기
        }

        // 기본 옥타브 설정
        if (NOTE == 'o') {
            cursor++;
            cursor++;
            // "o=" 넘기기
            num = NOTE_PP - '0';
            if (num >= 3 && num <= 7) {
                octave = num;
            }
            cursor++;
            // "," 넘기기
        }

        // BPM 설정
        if (NOTE == 'b') {
            cursor++;
            cursor++;
            // "b=" 넘기기
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }
            bpm = num;
            cursor++;
            // "," 넘기기
        }
        noteTime = (60 * 1000L / bpm) * 4;
        // 메인 루프

        NoteData *queue = (NoteData *) malloc(sizeof(NoteData) * numOfNext);
        int queueCursor = 0;
        while (cursor < size) {
            // 가능한 경우, 노트 박자 계산
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }

            if (num) {
                duration = noteTime / num;
            } else {
                duration = noteTime / defaultDuration;
            }

            note = NOTE;
            cursor++;

            if (NOTE == '#') {
                note = toupper(note);
                cursor++;
            }

            // "." 스트로크 박자 처리
            if (NOTE == '.') {
                duration += duration / 2;
                cursor++;
            }

            // 옥타브 처리
            if (IS_DIGIT(NOTE)) {
                scale = NOTE - '0';
                cursor++;
            } else {
                scale = octave;
            }

            scale += OCTAVE_OFFSET;

            if (NOTE == ',') {
                cursor++;
            }

            if (queueCursor == numOfNext) {
                nextHandler(queue, queueCursor);
                playTone(queue[0]);
                for (int i = 1; i < numOfNext; i++) {
                    queue[i - 1] = queue[i];
                }
                queueCursor--;
            }
            if (IS_PLAYABLE_NOTE(note)) {
                queue[queueCursor++] = {note, scale, duration};
            }

        }
        int leftSize = queueCursor;
        for (int i = 0; i < leftSize; i++) {
            nextHandler(queue + i, numOfNext - i);
            playTone(queue[i]);
        }
        free(queue);
    }

#define NOTE EEPROM.read(cursor)
#define NOTE_PP EEPROM.read(cursor++)

    void playRTTTLFromEEPROM(int start, int end, void (*nextHandler)(NoteData *queue, int size),
                             int numOfNext) {
        int size = end - start;
        byte defaultDuration = 4;
        byte octave = 6;
        int bpm = 63;
        int num;
        long noteTime;
        long duration;
        char note;
        byte scale;
        int cursor = start;

        // RTTTL 기본 포맷: d=N,o=N,b=NNN:
        while (NOTE != ':') {
            cursor++;
        }    // 곡 제목 넘김
        cursor++;
        // ':' 넘기기

        // get default duration
        if (NOTE == 'd') {
            cursor++;
            cursor++;
            // "d=" 넘기기
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }
            if (num > 0) {
                defaultDuration = num;
            }
            cursor++;
            // "," 넘기기
        }

        // 기본 옥타브 설정
        if (NOTE == 'o') {
            cursor++;
            cursor++;
            // "o=" 넘기기
            num = NOTE_PP - '0';
            if (num >= 3 && num <= 7) {
                octave = num;
            }
            cursor++;
            // "," 넘기기
        }

        // BPM 설정
        if (NOTE == 'b') {
            cursor++;
            cursor++;
            // "b=" 넘기기
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }
            bpm = num;
            cursor++;
            // "," 넘기기
        }
        noteTime = (60 * 1000L / bpm) * 4;
        // 메인 루프

        NoteData *queue = (NoteData *) malloc(sizeof(NoteData) * numOfNext);
        int queueCursor = 0;
        while (cursor < end) {
            // 가능한 경우, 노트 박자 계산
            num = 0;
            while (IS_DIGIT(NOTE)) {
                num = (num * 10) + (NOTE_PP - '0');
            }

            if (num) {
                duration = noteTime / num;
            } else {
                duration = noteTime / defaultDuration;
            }

            note = NOTE;
            cursor++;

            if (NOTE == '#') {
                note = toupper(note);
                cursor++;
            }

            // "." 스트로크 박자 처리
            if (NOTE == '.') {
                duration += duration / 2;
                cursor++;
            }

            // 옥타브 처리
            if (IS_DIGIT(NOTE)) {
                scale = NOTE - '0';
                cursor++;
            } else {
                scale = octave;
            }

            scale += OCTAVE_OFFSET;

            if (NOTE == ',') {
                cursor++;
            }

            if (queueCursor == numOfNext) {
                nextHandler(queue, queueCursor);
                playTone(queue[0]);
                for (int i = 1; i < numOfNext; i++) {
                    queue[i - 1] = queue[i];
                }
                queueCursor--;
            }

            if (IS_PLAYABLE_NOTE(note)) {
                queue[queueCursor++] = {note, scale, duration};
            }

        }
        int leftSize = queueCursor;
        for (int i = 0; i < leftSize; i++) {
            nextHandler(queue + i, numOfNext - i);
            playTone(queue[i]);
        }
        free(queue);
    }

#undef NOTE
#undef NOTE_PP
};

#endif