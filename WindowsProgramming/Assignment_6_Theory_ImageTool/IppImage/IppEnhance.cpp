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

void IppContrast(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(p[i] + (p[i] - 128) * n / 100));
	}
}

void IppContrast(IppRgbImage& img, int n)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i].r = static_cast<BYTE>(limit(p[i].r + (p[i].r - 128) * n / 100));
		p[i].g = static_cast<BYTE>(limit(p[i].g + (p[i].g - 128) * n / 100));
		p[i].b = static_cast<BYTE>(limit(p[i].b + (p[i].b - 128) * n / 100));
	}
}


bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = limit(p1[i] + p2[i]);
	}
	return true;
}

bool IppAdd(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE* p1 = img1.GetPixels();
	RGBBYTE* p2 = img2.GetPixels();
	RGBBYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r + p2[i].r);
		p3[i].g = limit(p1[i].g + p2[i].g);
		p3[i].b = limit(p1[i].b + p2[i].b);
	}
	return true;
}

bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = limit(p1[i] - p2[i]);
	}
	return true;
}

bool IppSub(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE* p1 = img1.GetPixels();
	RGBBYTE* p2 = img2.GetPixels();
	RGBBYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r - p2[i].r);
		p3[i].g = limit(p1[i].g - p2[i].g);
		p3[i].b = limit(p1[i].b - p2[i].b);
	}
	return true;
}
