#pragma once
#include "IppImage.h"

#define INVERSE(EXPR) EXPR = 255 - (EXPR)
#define LIMIT(EXPR, N) EXPR = limit(EXPR + N)

void IppInverse(IppByteImage& img);
void IppBrightness(IppByteImage& img, int n);

void IppInverse(IppRgbImage& img);
void IppBrightness(IppRgbImage& img, int n);