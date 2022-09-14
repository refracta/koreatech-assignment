#include "stdafx.h"
#include "IppEnhance.h"

void IppInverse(IppByteImage& img)
{
	
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		INVERSE(p[i]);
	}
}

void IppBrightness(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		LIMIT(p[i], n);
	}
}

void IppInverse(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* pixel = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		INVERSE(pixel[i].r);
		INVERSE(pixel[i].g);
		INVERSE(pixel[i].b);
	}
}

void IppBrightness(IppRgbImage& img, int n)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		LIMIT(p[i].r, n);
		LIMIT(p[i].g, n);
		LIMIT(p[i].b, n);
	}
}