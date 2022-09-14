/*! \file */
#ifndef RGDOTMATRIXRENDERER_H
#define RGDOTMATRIXRENDERER_H

#include <Arduino.h>
#include "RGDotMatrixConst.h"
#include "RGDotMatrixImage.h"
#include "RGDotMatrixFont.h"

int generateLeftScrollImage(DotMatrixImage images[], String text) {
    int len = text.length();
    int index = 0;
    for (int i = 0; i < len; i++) {
        unsigned long long currentFont = toSimpleFont(text.charAt(i));
        unsigned long long nextFont = toSimpleFont(text.charAt((i + 1) % len));
        unsigned long long doubleNextFont = toSimpleFont(text.charAt((i + 2) % len));
        DotMatrixImage currentImage = {currentFont};
        DotMatrixImage nextImage = {nextFont};
        DotMatrixImage doubleNextImage = {doubleNextFont};

        images[index++] = currentImage | nextImage.shift(RIGHT, 5);
        images[index++] = currentImage.shift(LEFT, 1) | nextImage.shift(RIGHT, 4);
        images[index++] = currentImage.shift(LEFT, 2) | nextImage.shift(RIGHT, 3);
        images[index++] = currentImage.shift(LEFT, 3) | nextImage.shift(RIGHT, 2) | doubleNextImage.shift(RIGHT, 7);
        images[index++] = nextImage.shift(RIGHT, 1) | doubleNextImage.shift(RIGHT, 6);
    }
    return index;
}

DotMatrixImage generateLeftScrollImage(String text, int frame) {
    int charIndex = frame / 5;
    int animateIndex = frame % 5;
    int len = text.length();
    unsigned long long currentFont = toSimpleFont(text.charAt(charIndex));
    unsigned long long nextFont = toSimpleFont(text.charAt((charIndex + 1) % len));
    unsigned long long doubleNextFont = toSimpleFont(text.charAt((charIndex + 2) % len));
    DotMatrixImage currentImage = {currentFont};
    DotMatrixImage nextImage = {nextFont};
    DotMatrixImage doubleNextImage = {doubleNextFont};

    DotMatrixImage result = nextImage.shift(RIGHT, 5 - animateIndex);
    if (animateIndex < 4) {
        result = result | (animateIndex == 0 ? currentImage : currentImage.shift(LEFT, animateIndex));
    }
    if (animateIndex > 2) {
        result = result | doubleNextImage.shift(RIGHT, 10 - animateIndex);
    }
    return result;
}


class RGDotMatrixRenderer {
private:
    void shiftRegister(unsigned char data) {
        digitalWrite(ST_CP_PIN, LOW);
        for (int i = 0; i < 8; i++) {
            digitalWrite(SH_CP_PIN, LOW);
            digitalWrite(DS_PIN, (data & (0x80 >> i)) ? HIGH : LOW);
            digitalWrite(SH_CP_PIN, HIGH);
        }
        digitalWrite(ST_CP_PIN, HIGH);
    }

    inline void controlRowPulse(unsigned char data) {
        shiftRegister(0x80 >> data);
    }

public:
    int DS_PIN;
    int ST_CP_PIN;
    int SH_CP_PIN;

    int RED_PINS[MATRIX_SIZE];

    int GREEN_PINS[MATRIX_SIZE];

    RGDotMatrixRenderer(int *RED_PINS, int *GREEN_PINS, int DS_PIN, int ST_CP_PIN, int SH_CP_PIN) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            this->RED_PINS[i] = RED_PINS[i];
            this->GREEN_PINS[i] = GREEN_PINS[i];
        }
        this->DS_PIN = DS_PIN;
        this->ST_CP_PIN = ST_CP_PIN;
        this->SH_CP_PIN = SH_CP_PIN;
    };

    void init() {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            pinMode(RED_PINS[i], OUTPUT);
            pinMode(GREEN_PINS[i], OUTPUT);
        }
        pinMode(DS_PIN, OUTPUT);
        pinMode(ST_CP_PIN, OUTPUT);
        pinMode(SH_CP_PIN, OUTPUT);
    }

    void clearAllLED() {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                digitalWrite(RED_PINS[j], HIGH);
                digitalWrite(GREEN_PINS[j], HIGH);
                controlRowPulse(i);
            }
        }
    }

    void displayImage(RGDotMatrixImage &image, unsigned int illuminance = 0) {
        for (int r = 0; r < MATRIX_SIZE; r++) {
            RGDotMatrixImage current = image.shift(UP, r) & 0xFF;

            for (int c = 0; c < MATRIX_SIZE; c++) {
                digitalWrite(RED_PINS[c], bitRead(current.redImage, c) ? LOW : HIGH);
                digitalWrite(GREEN_PINS[c], bitRead(current.greenImage, c) ? LOW : HIGH);
                controlRowPulse(r);
                delayMicroseconds(illuminance);
                controlRowPulse(-1);
            }

            for (int c = 0; c < MATRIX_SIZE; c++) {
                digitalWrite(RED_PINS[c], HIGH); // LED OFF
                digitalWrite(GREEN_PINS[c], HIGH); // LED OFF
            }
        }
    }
};

#endif
