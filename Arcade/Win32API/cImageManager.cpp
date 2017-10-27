#include "stdafx.h"
#include "cImageManager.h"

cImage* cImageManager::AddImage(string key, int width, int height)
{
	// 추가 하려는 키 값에 해당하는 이미지가 존재하는지 확인
	cImage* img = FindImage(key);

	// 추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 반환
	// 그렇지 않은 경우 새로 추가하고 추가 된 녀석을 반환
	if (img == NULL)
	{
		img = new cImage;
		img->Setup(width, height);
		//m_mapImage.insert(pair<string, cImage*>(key, img));
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, frameX, frameY, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, int x, int y, bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, frameX, frameY, x, y, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::FindImage(string key)
{
	// 맵에서 키 값에 해당하는 자료를 찾아서 이터레이터에 넣는다.
	m_mapIter = m_mapImage.find(key);

	// 키 값에 해당하는 데이터가 있는 경우 데이터 값을 반환
	// first == 키 값, second == 데이터 값
	if (m_mapIter != m_mapImage.end())
		return m_mapIter->second;

	// 키 값에 해당하는 데이터가 없는 경우 널 반환
	return NULL;
}

void cImageManager::DeleteImage(string key)
{
	m_mapIter = m_mapImage.find(key);

	if (m_mapIter != m_mapImage.end())
	{
		// 이미지 해제
		//if (m_mapIter->second != NULL)
		//	delete m_mapIter->second;

		// 매크로 사용 위와 동일한 의미
		SAFE_DELETE(m_mapIter->second);

		// 맵에서 해당 키 자료 삭제(맵에서만 빠짐)
		m_mapImage.erase(m_mapIter);
	}
}

void cImageManager::DeleteAll()
{
	m_mapIter = m_mapImage.begin();

	// 전체 삭제
	while (m_mapIter != m_mapImage.end())
	{
		SAFE_DELETE(m_mapIter->second);
		m_mapIter = m_mapImage.erase(m_mapIter);
	}
}

void cImageManager::Render(string key, HDC hdc)
{
	// 이미지를 키 값으로 검색해서 그린다.
	cImage* img = FindImage(key);
	if (img) img->Render(hdc);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY, int sizeX, int sizeY)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY, sizeX, sizeY);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY, int sourX, int sourY,
	int sourWidth, int sourHeight)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void cImageManager::AlphaRender(string key, HDC hdc, int destX, int destY, BYTE alpha)
{
	cImage* img = FindImage(key);
	if (img) img->AlphaRender(hdc, destX, destY, alpha);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY, sourX, sourY);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY,
	int maxX, int maxY, int delay)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY, sourX, sourY, maxX, maxY, delay);
}
