#pragma once
#include "IppImage.h"

#define INVERSE(EXPR) EXPR = 255 - (EXPR)
#define LIMIT(EXPR, N) EXPR = limit(EXPR + N)

void IppInverse(IppByteImage& img);
void IppInverse(IppRgbImage& img);

void IppBrightness(IppByteImage& img, int n);
void IppBrightness(IppRgbImage& img, int n);

void IppContrast(IppByteImage& img, int n);
void IppContrast(IppRgbImage& img, int n);

bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAdd(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3);

bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppSub(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3);