/*! \file */
#include "Project.h"

void renderTarget(unsigned long current, unsigned long left) {
    renderer.displayImage(renderImage);
}

void handleMainScreenDelay(unsigned long current, unsigned long left) {
    renderer.displayImage(renderImage);
    if (IS_ANY_BUTTON_PRESSED()) {
        changeGameStatus(SELECT_MUSIC_SCREEN);
        SUCCESS_TUNE(soundController);
    }
}

void handleMusicSelectScreenDelay(unsigned long current, unsigned long left) {
    renderer.displayImage(renderImage);
    if (IS_BUTTON_PRESSED(BUTTON1_PIN)) {
        musicDataCursor = (musicDataCursor - 1 + NUM_OF_MUSIC_DATA) % NUM_OF_MUSIC_DATA;
        changeGameStatus(SELECT_MUSIC_SCREEN);
        SUCCESS_TUNE(soundController);
    } else if (IS_BUTTON_PRESSED(BUTTON4_PIN)) {
        musicDataCursor = (musicDataCursor + 1) % NUM_OF_MUSIC_DATA;
        changeGameStatus(SELECT_MUSIC_SCREEN);
        SUCCESS_TUNE(soundController);
    } else if (IS_BUTTON_PRESSED(BUTTON2_PIN)) {
        changeGameStatus(GAME_SCREEN);
        SUCCESS_TUNE(soundController);
    } else if (IS_BUTTON_PRESSED(BUTTON3_PIN)) {
        score = READ_SCORE(musicDataCursor);
        maxCombo = READ_COMBO(musicDataCursor);
        changeGameStatus(GAME_RESULT_SCREEN);
        SUCCESS_TUNE(soundController);
    }
}

int getEmptyTBEIndex() {
    for (int i = 0; i < NUM_OF_TIME_BASED_EFFECT; i++) {
        if (timeBasedEffects[i].targetTime <= 0) {
            return i;
        }
    }
    return 0;
}

void handleGameScreenDelay(unsigned long current, unsigned long left) {
    RGDotMatrixImage temp = renderImage;
    for (int i = 0; i < NUM_OF_BUTTON; i++) {
        if (IS_BUTTON_PRESSED(BUTTON_PINS[i])) {
            renderImage = renderImage & (RGDotMatrixImage) {~FONT_NOTE_COLS[i], FONT_FULL} |
                          (RGDotMatrixImage) {FONT_EMPTY, FONT_NOTE_COLS[i]};
        }
    }

    int timeFactor = left / BASE_TIME;
    int targetIndex;
    unsigned long long targetNote;
    boolean isValid;


    int previewEffectIndexes[3] = {-1, -1, -1};
    if (nextNotes[0]) {
        previewEffectIndexes[0] = targetIndex = getNoteIndex(nextNotes[0]) % 4;
        targetNote = FONT_NOTE_COLS[targetIndex];
        isValid = IS_BUTTON_PRESSED(BUTTON_PINS[targetIndex]);

        if (!isHit) {
            if (timeFactor < 8) {
                renderImage = renderImage | (RGDotMatrixImage) {targetNote, FONT_EMPTY}.shift(UP, timeFactor);
            } else {
                renderImage = renderImage | (RGDotMatrixImage) {targetNote, FONT_EMPTY}.shift(UP, 7);
            }
            if (isValid) {
                isHit = true;
                combo++;
                if (combo > maxCombo) {
                    maxCombo = combo;
                }
                long effectTime = current + 250;
                if (timeFactor < 4) {
                    score += 30 * (1 + combo / 10.0);
                    timeBasedEffects[getEmptyTBEIndex()] = {
                            (RGDotMatrixImage) {FONT_EMPTY,
                                                FONT_GAME_COLS[targetIndex]}, effectTime};
                } else if (timeFactor < 8) {
                    score += 20 * (1 + combo / 10.0);
                    timeBasedEffects[getEmptyTBEIndex()] = {
                            (RGDotMatrixImage) {FONT_GAME_COLS[targetIndex],
                                                FONT_GAME_COLS[targetIndex]}, effectTime};
                } else {
                    score += 1 * (1 + combo / 10.0);
                    timeBasedEffects[getEmptyTBEIndex()] = {(RGDotMatrixImage) {FONT_GAME_COLS[targetIndex]},
                                                            effectTime};
                }
            }
        }
    }

    for (int i = 1; i < 3; i++) {
        char nextNote = nextNotes[i];
        if (nextNote) {
            targetIndex = getNoteIndex(nextNote) % 4;
            boolean isNewPosition = targetIndex != previewEffectIndexes[0] && targetIndex != previewEffectIndexes[1] &&
                                    targetIndex != previewEffectIndexes[2];
            previewEffectIndexes[i] = targetIndex;
            targetNote = FONT_NOTE_COLS[targetIndex];
            if (isNewPosition) {
                renderImage = renderImage | (RGDotMatrixImage) {i == 1 ? targetNote : FONT_EMPTY, targetNote}.shift(UP,
                                                                                                                    7);
            }
        }
    }


    for (int i = 0; i < NUM_OF_TIME_BASED_EFFECT; i++) {
        if (0 < timeBasedEffects[i].targetTime && current <= timeBasedEffects[i].targetTime) {
            renderImage = renderImage | timeBasedEffects[i].image;
        } else {
            timeBasedEffects[i].targetTime = 0;
        }
    }

    int maxRenderCombo = combo < 8 ? combo : 8;
    for (int i = 0; i < maxRenderCombo; i++) {
        renderImage.redImage ^= 1ULL << (7 * 8 + i);
        renderImage.greenImage |= 1ULL << (7 * 8 + i);
    }

    renderer.displayImage(renderImage);
    renderImage = temp;
}

void handleGameResultDelay(unsigned long current, unsigned long left) {
    renderer.displayImage(renderImage);
    if (IS_ANY_BUTTON_PRESSED()) {
        changeGameStatus(SELECT_MUSIC_SCREEN);
        SUCCESS_TUNE(soundController);
    }
}

void changeGameStatus(GameStatus status) {
    customHandler = renderTarget;
    previousStatus = currentStatus;
    currentStatus = status;
    isInited = false;
}

void nextHandler(NoteData *notes, int size) {
    for (int i = 0; i < NOTE_PREVIEW; i++) {
        nextNotes[i] = (i < size && notes[i].note != 'p') ? notes[i].note : NULL;
    }
    if (!isHit) {
        combo = 0;
    }
    isHit = false;
}

void initGameStatus() {
    free(rib);
    ribSize = 0;
    playIndex = 0;
    isInited = true;
    if (currentStatus == MAIN_SCREEN) {
        strcpy(message, "RHYTHM STAR!");
        messageLen = strlen(message);
        ribSize = messageLen * 5;
        customHandler = handleMainScreenDelay;
    } else if (currentStatus == SELECT_MUSIC_SCREEN) {
        String &data = musicData[musicDataCursor];
        data.substring(0, data.indexOf(":")).toCharArray(message, MESSAGE_BUFFER_LENGTH);
        messageLen = strlen(message);
        message[messageLen++] = ' ';
        message[messageLen] = '\0';
        ribSize = messageLen * 5;
        customHandler = handleMusicSelectScreenDelay;
    } else if (currentStatus == GAME_SCREEN) {
        customHandler = renderTarget;
        renderImage = {(DotMatrixImage{FONT_3}).shift(RIGHT, 2).rawImage, FONT_FULL};
        soundController.playTone('g', 5, 200);
        delay(800);
        renderImage = {(DotMatrixImage{FONT_2}).shift(RIGHT, 2).rawImage, FONT_FULL};
        soundController.playTone('g', 5, 200);
        delay(800);
        renderImage = {(DotMatrixImage{FONT_1}).shift(RIGHT, 2).rawImage, FONT_FULL};
        soundController.playTone('g', 5, 200);
        delay(800);
        renderImage = {((DotMatrixImage) {FONT_G} | (DotMatrixImage) {FONT_O}.shift(RIGHT, 4)).rawImage, FONT_FULL};
        soundController.playTone('g', 7, 200);
        delay(800);

        customHandler = handleGameScreenDelay;
        renderImage = {FONT_UNDERLINE, FONT_EMPTY};
        String &data = musicData[musicDataCursor];
        BASE_TIME = getRTTTLMinDuration(data) / 8;
        // BASE_TIME = 30; fix base time

        combo = 0;
        score = 0;
        if (strcmp(message, "CUSTOM ") == 0) {
            soundController.playRTTTLFromEEPROM(CUSTOM_MUSIC_DATA_START,
                                                CUSTOM_MUSIC_DATA_START + READ_CUSTOM_MUSIC_LENGTH(), nextHandler,
                                                NOTE_PREVIEW);
        } else {
            soundController.playRTTTL(data, nextHandler, NOTE_PREVIEW);
        }
        nextNotes[0] = nextNotes[1] = nextNotes[2] = 0;
        if (score >= READ_SCORE(musicDataCursor)) {
            WRITE_SCORE(musicDataCursor, score);
            WRITE_COMBO(musicDataCursor, maxCombo);
        }
        changeGameStatus(GAME_RESULT_SCREEN);
    } else if (currentStatus == GAME_RESULT_SCREEN) {
        sprintf(message, "S=%u C=%u ", score, maxCombo);
        messageLen = strlen(message);
        customHandler = handleGameResultDelay;
    }
}

void runMainScreen() {
    renderImage = {generateLeftScrollImage(message, playIndex).rawImage, FONT_FULL};
    delay(100);
    playIndex = (playIndex + 1) % ribSize;

    int numOfRead = 0;
    while (Serial.available()) {
        EEPROM.write(CUSTOM_MUSIC_DATA_START + numOfRead++, Serial.read());
        _delay(9);
    }
    if (numOfRead == 7) {
        for (int i = 0; i < EEPROM.length(); i++) {
            EEPROM.write(i, 0);
        }
        Serial.println("clear eeprom successfully!");
    } else if (numOfRead) {
        WRITE_CUSTOM_MUSIC_LENGTH(numOfRead);
        Serial.print(READ_CUSTOM_MUSIC_LENGTH());
        Serial.println(" length saved!");
        /*
        for (int i = CUSTOM_MUSIC_DATA_START; i < CUSTOM_MUSIC_DATA_START + numOfRead; i++) {
            Serial.print((char) EEPROM.read(i));
        }
        Serial.println();
        */
        musicDataCursor = CUSTOM_MUSIC_INDEX;
        changeGameStatus(SELECT_MUSIC_SCREEN);
        _delay(300);
    }
}

void runMusicSelectScreen() {
    renderImage = {generateLeftScrollImage(message, playIndex).rawImage, 0};
    delay(100);
    playIndex = (playIndex + 1) % ribSize;
}

void runGameScreen() {
    delay(1000);
}

void runGameResultScreen() {
    renderImage = {generateLeftScrollImage(message, playIndex).rawImage, 0};
    ribSize = messageLen * 5;
    delay(100);
    playIndex = (playIndex + 1) % ribSize;
}

void setup() {
    Serial.begin(1200);
    renderer.init();
    soundController.init();
    initMusicData();

    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);

    changeGameStatus(MAIN_SCREEN);
}

void loop() {
    if (isInited) {
        switch (currentStatus) {
            case MAIN_SCREEN:
                runMainScreen();
                break;
            case SELECT_MUSIC_SCREEN:
                runMusicSelectScreen();
                break;
            case GAME_SCREEN:
                runGameScreen();
                break;
            case GAME_RESULT_SCREEN:
                runGameResultScreen();
                break;
        }
    } else {
        initGameStatus();
    }
}
