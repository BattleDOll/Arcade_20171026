#pragma once
#include "cImage.h"

class cGameNode
{
protected:
	cImage*		m_pImgBackBuffer;

public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Update();
	virtual void Render() PURE;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

