#pragma once
#include "cSingletonBase.h"

#define g_pPixelManager cPixelCollision::GetInstance()

class cPixelCollision :	public cSingletonBase<cPixelCollision>
{
public:
	bool CheckPixel(cImage* img, float x, float y);
	void RemovePixel(cImage* img, float x, float y);
	void RemoveBrush(cImage* img, float x, float y, int size);
	void DrawImage(cImage* img, cImage* drawImg, float x, float y, int sizeX, int sizeY);
};

