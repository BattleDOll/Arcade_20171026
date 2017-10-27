#include "stdafx.h"
#include "cPixelCollision.h"


bool cPixelCollision::CheckPixel(cImage* img, float x, float y)
{
	COLORREF color = GetPixel(img->GetMemDC(), x, y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (r == 255 && g == 0 && b == 255)
		return true;

	return false;
}

void cPixelCollision::RemovePixel(cImage* img, float x, float y)
{
	SetPixel(img->GetMemDC(), x, y, RGB(255, 0, 255));
}

void cPixelCollision::RemoveBrush(cImage* img, float x, float y, int size)
{
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(img->GetMemDC(), hBrush);
	HPEN hPen = (HPEN)CreatePen(0, 1, RGB(255, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(img->GetMemDC(), hPen);

	EllipseMakeCenter(img->GetMemDC(), x, y, size, size);

	DeleteObject(hOldPen);
	DeleteObject(hPen);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
}

void cPixelCollision::DrawImage(cImage* img, cImage* drawImg, float x, float y, int sizeX, int sizeY)
{
	drawImg->Render(img->GetMemDC(), x, y, sizeX, sizeY);
}
