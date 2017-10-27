#pragma once
#include "cSingletonBase.h"
#include "cImage.h"

#define g_pImageManager cImageManager::GetInstance()

/*
자료구조 : map - 키 값과 데이터를 가지는 자료구조
*/

class cImageManager : public cSingletonBase<cImageManager>
{
private:
	map<string, cImage*>			m_mapImage;
	map<string, cImage*>::iterator	m_mapIter;

public:
	//==================================================================
	//		## 셋업 ##
	//==================================================================
	// 빈 비트맵 셋업
	cImage* AddImage(string key, int width, int height);
	// 이미지 파일 셋업
	cImage* AddImage(string key, const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 셋업
	cImage* AddImage(string key, const char* fileName, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	cImage* AddImage(string key, const char* fileName, int width, int height, int frameX, int frameY,
		int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//==================================================================
	//		## 이미지 검색 및 삭제 ##
	//==================================================================
	cImage* FindImage(string key);		// 이미지 찾기
	void DeleteImage(string key);		// 이미지 삭제
	void DeleteAll();					// 모든 이미지 삭제

	//==================================================================
	//		## 일반 렌더 ##
	//==================================================================
	void Render(string key, HDC hdc);
	void Render(string key, HDC hdc, int destX, int destY);
	void Render(string key, HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void Render(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## 알파 렌더 ##
	//==================================================================
	void AlphaRender(string key, HDC hdc, int destX, int destY, BYTE alpha);

	//==================================================================
	//		## 프레임 렌더 ##
	//==================================================================
	void FrameRender(string key, HDC hdc, int destX, int destY);
	void FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY);
	void FrameRender(string key, HDC hdc, int destX, int destY,
		int sourX, int sourY, int maxX, int maxY, int delay);
};

