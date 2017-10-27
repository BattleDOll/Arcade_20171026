#include "stdafx.h"
#include "cImage.h"


cImage::cImage()
	: m_pImageInfo(NULL)
	, m_szFileName(NULL)
	, m_isTrans(false)
	, m_transColor(RGB(0, 0, 0))
	, m_pBlendImage(NULL)
{
}


cImage::~cImage()
{
	// 이미지 정보가 있는 경우에만 해제
	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBit);
		DeleteObject(m_pImageInfo->hBit);
		DeleteDC(m_pImageInfo->hMemDC);

		if (m_szFileName) delete m_szFileName;
		delete m_pImageInfo;
	}

	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBit);
		DeleteObject(m_pBlendImage->hBit);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}
}

// 빈 비트맵 셋업
void cImage::Setup(int width, int height)
{
	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	// 이미지 정보 새로 생성 및 초기화
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_EMPTY;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width;
	m_pImageInfo->nFrameHeight = height;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);
}

// 이미지 파일 셋업
void cImage::Setup(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	// 이미지 정보 새로 생성 및 초기화
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width;
	m_pImageInfo->nFrameHeight = height;

	assert(m_pImageInfo->hBit && "이미지 파일을 읽어오지 못 했다.");

	// 파일 이름
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// 투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);
}

// 프레임 이미지 셋업
void cImage::Setup(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	// 이미지 정보 새로 생성 및 초기화
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;

	assert(m_pImageInfo->hBit && "프레임 이미지 파일을 읽어오지 못 했다.");

	// 파일 이름
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// 투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const char * fileName, int width, int height, int frameX, int frameY,
	int x, int y, bool isTrans, COLORREF transColor)
{
	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	// 이미지 정보 새로 생성 및 초기화
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->fPosX = x - width / frameX / 2.0f;
	m_pImageInfo->fPosY = y - height / frameY / 2.0f;

	assert(m_pImageInfo->hBit && "프레임 이미지 파일을 읽어오지 못 했다.");

	// 파일 이름
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// 투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);
}

// 알파블렌드에 사용 할 빈 비트맵을 하나 생성
void cImage::SetupForAlphaBlend()
{
	// 알파블렌드 구조체 초기화 (기본 값을 바꿀 일이 없음)
	m_stBlendFunc.BlendOp = AC_SRC_OVER;
	m_stBlendFunc.BlendFlags = 0;
	m_stBlendFunc.AlphaFormat = 0;

	// DC 가져오기
	HDC hdc = GetDC(g_hWnd);

	// 이미지 정보 새로 생성 및 초기화
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->btLoadType = LOAD_EMPTY;
	m_pBlendImage->dwResID = 0;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
	m_pBlendImage->hOldBit = (HBITMAP)SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hBit);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// DC 해제
	ReleaseDC(g_hWnd, hdc);
}

// 화면의 좌측 상단 부터 그린다.
void cImage::Render(HDC hdc)
{
	if (m_isTrans)	// 배경색을 없앨 경우
	{
		// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
		GdiTransparentBlt(
			hdc,					// 복사 할 장소의 DC
			0,						// 복사 될 좌표 시작 지점 X
			0,						// 복사 될 좌표 시작 지점 Y
			m_pImageInfo->nWidth,	// 복사 될 이미지의 가로 크기
			m_pImageInfo->nHeight, // 복사 될 이미지의 세로 크기
			m_pImageInfo->hMemDC,	// 복사 할 대상 DC
			0,						// 복사 시작 지점 X
			0,						// 복사 시작 지점 Y
			m_pImageInfo->nWidth,	// 복사 영역 가로 크기
			m_pImageInfo->nHeight,	// 복사 영역 세로 크기
			m_transColor			// 복사 할 때 제외 할 색상(투명처리)
		);
	}
	else // 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		// 메모리DC에 그려진것을 화면DC로 고속복사를 한다
		BitBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// 지정 된 위치에 그린다.
void cImage::Render(HDC hdc, int destX, int destY)
{
	if (m_isTrans)	// 배경색을 없앨 경우
	{
		// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
		GdiTransparentBlt(
			hdc,					// 복사 할 장소의 DC
			destX,					// 복사 될 좌표 시작 지점 X
			destY,					// 복사 될 좌표 시작 지점 Y
			m_pImageInfo->nWidth,	// 복사 될 이미지의 가로 크기
			m_pImageInfo->nHeight, // 복사 될 이미지의 세로 크기
			m_pImageInfo->hMemDC,	// 복사 할 대상 DC
			0,						// 복사 시작 지점 X
			0,						// 복사 시작 지점 Y
			m_pImageInfo->nWidth,	// 복사 영역 가로 크기
			m_pImageInfo->nHeight,	// 복사 영역 세로 크기
			m_transColor			// 복사 할 때 제외 할 색상(투명처리)
		);
	}
	else // 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		// 메모리DC에 그려진것을 화면DC로 고속복사를 한다
		BitBlt(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void cImage::Render(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{
	// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
	GdiTransparentBlt(
		hdc,					// 복사 할 장소의 DC
		destX,					// 복사 될 좌표 시작 지점 X
		destY,					// 복사 될 좌표 시작 지점 Y
		sizeX,					// 복사 될 이미지의 가로 크기
		sizeY,					// 복사 될 이미지의 세로 크기
		m_pImageInfo->hMemDC,	// 복사 할 대상 DC
		0,						// 복사 시작 지점 X
		0,						// 복사 시작 지점 Y
		m_pImageInfo->nWidth,	// 복사 영역 가로 크기
		m_pImageInfo->nHeight,	// 복사 영역 세로 크기
		m_transColor			// 복사 할 때 제외 할 색상(투명처리)
	);
}

// 지정 된 위치에 원하는 부분을 그린다.
void cImage::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (m_isTrans)	// 배경색을 없앨 경우
	{
		// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
		GdiTransparentBlt(
			hdc,					// 복사 할 장소의 DC
			destX,					// 복사 될 좌표 시작 지점 X
			destY,					// 복사 될 좌표 시작 지점 Y
			sourWidth,				// 복사 될 이미지의 가로 크기
			sourHeight,				// 복사 될 이미지의 세로 크기
			m_pImageInfo->hMemDC,	// 복사 할 대상 DC
			sourX,					// 복사 시작 지점 X
			sourY,					// 복사 시작 지점 Y
			sourWidth,				// 복사 영역 가로 크기
			sourHeight,				// 복사 영역 세로 크기
			m_transColor			// 복사 할 때 제외 할 색상(투명처리)
		);
	}
	else // 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		// 메모리DC에 그려진것을 화면DC로 고속복사를 한다
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			m_pImageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void cImage::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파블렌드 처음 사용시 초기화
	if (!m_pBlendImage) SetupForAlphaBlend();

	// 알파값 초기화
	m_stBlendFunc.SourceConstantAlpha = alpha;

	if (m_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그려준다
		BitBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc, destX, destY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타 값을 없애준다)
		GdiTransparentBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다
		GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
	}
	else
	{
		// 알파블렌드 옵션 값을 사용해서 그린다.
		GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
	}
}

void cImage::FrameRender(HDC hdc, int destX, int destY)
{
	if (m_isTrans)	// 배경색을 없앨 경우
	{
		// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
		GdiTransparentBlt(
			hdc,					// 복사 할 장소의 DC
			destX,					// 복사 될 좌표 시작 지점 X
			destY,					// 복사 될 좌표 시작 지점 Y
			m_pImageInfo->nFrameWidth,	// 복사 될 이미지의 가로 크기
			m_pImageInfo->nFrameHeight, // 복사 될 이미지의 세로 크기
			m_pImageInfo->hMemDC,	// 복사 할 대상 DC
			m_pImageInfo->nCurrFrameX * m_pImageInfo->nFrameWidth, // 현재 프레임의 시작지점 X
			m_pImageInfo->nCurrFrameY * m_pImageInfo->nFrameHeight,// 현재 프레임의 시작지점 Y
			m_pImageInfo->nFrameWidth,	// 복사 영역 가로 크기
			m_pImageInfo->nFrameHeight,	// 복사 영역 세로 크기
			m_transColor			// 복사 할 때 제외 할 색상(투명처리)
		);
	}
	else // 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		// 메모리DC에 그려진것을 화면DC로 고속복사를 한다
		BitBlt(hdc, destX, destY,
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nCurrFrameX * m_pImageInfo->nFrameWidth,
			m_pImageInfo->nCurrFrameY * m_pImageInfo->nFrameHeight,
			SRCCOPY);
	}
}

void cImage::FrameRender(HDC hdc, int destX, int destY, int sourX, int sourY)
{
	if (m_isTrans)	// 배경색을 없앨 경우
	{
		// GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사를 하는 함수
		GdiTransparentBlt(
			hdc,					// 복사 할 장소의 DC
			destX,					// 복사 될 좌표 시작 지점 X
			destY,					// 복사 될 좌표 시작 지점 Y
			m_pImageInfo->nFrameWidth,	// 복사 될 이미지의 가로 크기
			m_pImageInfo->nFrameHeight, // 복사 될 이미지의 세로 크기
			m_pImageInfo->hMemDC,	// 복사 할 대상 DC
			sourX * m_pImageInfo->nFrameWidth, // 현재 프레임의 시작지점 X
			sourY * m_pImageInfo->nFrameHeight,// 현재 프레임의 시작지점 Y
			m_pImageInfo->nFrameWidth,	// 복사 영역 가로 크기
			m_pImageInfo->nFrameHeight,	// 복사 영역 세로 크기
			m_transColor			// 복사 할 때 제외 할 색상(투명처리)
		);
	}
	else // 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		// 메모리DC에 그려진것을 화면DC로 고속복사를 한다
		BitBlt(hdc, destX, destY,
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,
			m_pImageInfo->hMemDC,
			sourX * m_pImageInfo->nFrameWidth,
			sourY * m_pImageInfo->nFrameHeight,
			SRCCOPY);
	}
}

// 애니메이션 구간 및 딜레이 설정 프레임 렌더
void cImage::FrameRender(HDC hdc, int destX, int destY,
	int sourX, int sourY, int maxX, int maxY, int delay)
{
	if (m_pImageInfo->nDelay >= delay)
	{
		m_pImageInfo->nDelay = 0;

		if (m_pImageInfo->nCurrFrameX >= maxX)
			m_pImageInfo->nCurrFrameX = sourX;
		else
			++m_pImageInfo->nCurrFrameX;

		if (m_pImageInfo->nCurrFrameY >= maxY)
			m_pImageInfo->nCurrFrameY = sourY;
		else
			++m_pImageInfo->nCurrFrameY;
	}
	else
		++m_pImageInfo->nDelay;

	FrameRender(hdc, destX, destY);
}

void cImage::SetTransColor(bool isTrans, COLORREF transColor)
{
	m_isTrans = isTrans;
	m_transColor = transColor;
}