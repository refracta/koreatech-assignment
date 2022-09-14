/*! \file */
#ifndef RGDOTMATRIXIMAGE_H
#define RGDOTMATRIXIMAGE_H

#include "RGDotMatrixConst.h"

enum ShiftDirection {
    UP, DOWN, LEFT, RIGHT
};

static inline int rotate90IndexMapper(int r, int c) {
    return (MATRIX_SIZE - c - 1) * MATRIX_SIZE + r;
}

static inline int rotate180IndexMapper(int r, int c) {
    return (MATRIX_SIZE - 1 - r) * MATRIX_SIZE + MATRIX_SIZE - 1 - c;
}

static inline int rotate270IndexMapper(int r, int c) {
    return c * MATRIX_SIZE + MATRIX_SIZE - 1 - r;
}

inline unsigned long long transform(unsigned long long value, int(*indexMapper)(int r, int c)) {
    unsigned long long result = 0;
    for (int r = 0; r < MATRIX_SIZE; r++) {
        for (int c = 0; c < MATRIX_SIZE; c++) {
            int flatIndex = r * MATRIX_SIZE + c;
            int rotatedIndex = indexMapper(r, c);
            unsigned long long rotatedIndexValue = value & (1ULL << rotatedIndex);
            result += (1ULL << flatIndex) * (rotatedIndexValue ? 1ULL : 0ULL);
        }
    }
    return result;
}

class DotMatrixImage {
public:
    unsigned long long rawImage;

    inline DotMatrixImage transform(int(*indexMapper)(int r, int c)) {
        return {::transform(rawImage, indexMapper)};
    }

    inline DotMatrixImage rotate90() {
        return transform(rotate90IndexMapper);
    }

    inline DotMatrixImage rotate180() {
        return transform(rotate180IndexMapper);
    }

    inline DotMatrixImage rotate270() {
        return transform(rotate270IndexMapper);
    }

    DotMatrixImage shift(ShiftDirection direction, int shift) {
        switch (direction) {
            case UP:
                return *this >> shift * MATRIX_SIZE;
            case DOWN:
                return *this << shift * MATRIX_SIZE;
            case LEFT:
                return (rotate90() >> shift * MATRIX_SIZE).rotate270();
            case RIGHT:
                return (rotate90() << shift * MATRIX_SIZE).rotate270();
        }
    }

    DotMatrixImage operator<<(const int shift) {
        return {rawImage << shift};
    }

    DotMatrixImage operator>>(const int shift) {
        return {rawImage >> shift};
    }

    DotMatrixImage operator|(const DotMatrixImage &image) {
        return {rawImage | image.rawImage};
    }

    DotMatrixImage operator|(const int &target) {
        return {rawImage | target};
    }

    DotMatrixImage operator&(const DotMatrixImage &image) {
        return {rawImage & image.rawImage};
    }

    DotMatrixImage operator&(const int &target) {
        return {rawImage & target};
    }
};

class RGDotMatrixImage {
public:
    unsigned long long redImage;
    unsigned long long greenImage;

    inline RGDotMatrixImage transform(int(*indexMapper)(int r, int c)) {
        return {::transform(redImage, indexMapper), ::transform(greenImage, indexMapper)};
    }

    inline RGDotMatrixImage rotate90() {
        return transform(rotate90IndexMapper);
    }

    inline RGDotMatrixImage rotate180() {
        return transform(rotate180IndexMapper);
    }

    inline RGDotMatrixImage rotate270() {
        return transform(rotate270IndexMapper);
    }

    RGDotMatrixImage shift(ShiftDirection direction, int shift) {
        switch (direction) {
            case UP:
                return *this >> shift * MATRIX_SIZE;
            case DOWN:
                return *this << shift * MATRIX_SIZE;
            case LEFT:
                return (rotate90() >> shift * MATRIX_SIZE).rotate270();
            case RIGHT:
                return (rotate90() << shift * MATRIX_SIZE).rotate270();
        }
    }

    RGDotMatrixImage operator<<(const int shift) {
        return {redImage << shift, greenImage << shift};
    }

    RGDotMatrixImage operator>>(const int shift) {
        return {redImage >> shift, greenImage >> shift};
    }

    RGDotMatrixImage operator^(const RGDotMatrixImage &image) {
        return {redImage ^ image.redImage, greenImage ^ image.greenImage};
    }

    RGDotMatrixImage operator^(const int &target) {
        return {redImage ^ target, greenImage ^ target};
    }

    RGDotMatrixImage operator|(const RGDotMatrixImage &image) {
        return {redImage | image.redImage, greenImage | image.greenImage};
    }

    RGDotMatrixImage operator|(const int &target) {
        return {redImage | target, greenImage | target};
    }

    RGDotMatrixImage operator&(const RGDotMatrixImage &image) {
        return {redImage & image.redImage, greenImage & image.greenImage};
    }

    RGDotMatrixImage operator&(const int &target) {
        return {redImage & target, greenImage & target};
    }
};


#endif