#pragma once
class cImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_EMPTY,			// 빈 비트맵 로딩
		LOAD_FILE,			// 파일로 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		dwResID;		// 리소스 ID
		HDC			hMemDC;			// 메모리 DC
		HBITMAP		hBit;			// 비트맵
		HBITMAP		hOldBit;		// 올드 비트맵
		int			nWidth;			// 이미지 가로 크기
		int			nHeight;		// 이미지 세로 크기
		BYTE		btLoadType;		// 이미지 로드 타입

		int			nCurrFrameX;	// 현재 프레임 x
		int			nCurrFrameY;	// 현재 프레임 y
		int			nMaxFrameX;		// 최대 x축 프레임 갯수
		int			nMaxFrameY;		// 최대 y축 프레임 갯수
		int			nFrameWidth;	// 한 프레임 가로 길이
		int			nFrameHeight;	// 한 프레임 세로 길이

		float		fPosX;			// 이미지의 화면에서 x축(센터) 위치
		float		fPosY;			// 이미지의 화면에서 y축(센터) 위치
		int			nDelay;			// 이미지 애니메이션 딜레이

		tagImage()
		{
			dwResID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			nWidth = 0;
			nHeight = 0;
			btLoadType = LOAD_EMPTY;

			nCurrFrameX = 0;
			nCurrFrameY = 0;
			nMaxFrameX = 1;
			nMaxFrameY = 1;
			nFrameWidth = 0;
			nFrameHeight = 0;
			fPosX = WINSIZEX / 2.0f;
			fPosY = WINSIZEY / 2.0f;
			nDelay = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	m_pImageInfo;	// 이미지 정보 구조체
	char*			m_szFileName;	// 이미지 파일 이름
	bool			m_isTrans;		// 투명 효과 사용 여부 
	COLORREF		m_transColor;	// 투명으로 사용 할 색상 (마젠타 = RGB(255, 0, 255));

	BLENDFUNCTION	m_stBlendFunc;	// 알파블렌드 설정 구조체
	LPIMAGE_INFO	m_pBlendImage;	// 알파블렌드 이미지 정보 구조체

public:
	cImage();
	~cImage();

	//==================================================================
	//		## 셋업 ##
	//==================================================================
	// 빈 비트맵 셋업
	void Setup(int width, int height);
	// 이미지 파일 셋업
	void Setup(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 셋업
	void Setup(const char* fileName, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void Setup(const char* fileName, int width, int height, int frameX, int frameY,
		int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//알파블렌드 초기화
	void SetupForAlphaBlend();

	//==================================================================
	//		## 일반 렌더 ##
	//==================================================================
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## 알파 렌더 ##
	//==================================================================
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	//==================================================================
	//		## 프레임 렌더 ##
	//==================================================================
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int sourX, int sourY);
	void FrameRender(HDC hdc, int destX, int destY,
		int sourX, int sourY, int maxX, int maxY, int delay);

	//==================================================================
	//		## inline ## (인라인 함수들 - 겟터, 셋터)
	//==================================================================
	// 없앨 배경 색상 셋팅
	void SetTransColor(bool isTrans, COLORREF transColor);
	// 백버퍼 DC 얻기
	HDC GetMemDC() { return m_pImageInfo->hMemDC; }
	int GetWidth() { return m_pImageInfo->nWidth; }
	int GetHeight() { return m_pImageInfo->nHeight; }
	int GetFrameWidth() { return m_pImageInfo->nFrameWidth; }
	int GetFrameHeight() { return m_pImageInfo->nFrameHeight; }

	// 프레임 인덱스 겟터, 셋터
	int GetFrameX() { return m_pImageInfo->nCurrFrameX; }
	void SetFrameX(int x) { m_pImageInfo->nCurrFrameX = x; }
	int GetFrameY() { return m_pImageInfo->nCurrFrameY; }
	void SetFrameY(int y) { m_pImageInfo->nCurrFrameY = y; }

	// 맥스 프레임 겟터
	int GetMaxFrameX() { return m_pImageInfo->nMaxFrameX; }
	int GetMaxFrameY() { return m_pImageInfo->nMaxFrameY; }

	// 프레임 위치 겟터 셋터 (센터 정보)
	float GetPosX() { return m_pImageInfo->fPosX; }
	void SetPosX(float x) { m_pImageInfo->fPosX = x; }
	float GetPosY() { return m_pImageInfo->fPosY; }
	void SetPosY(float y) { m_pImageInfo->fPosY = y; }
	// 프레임 센터 위치 셋터
	void SetCenterX(float x) { m_pImageInfo->fPosX = x - m_pImageInfo->nFrameWidth / 2;	}
	void SetCenterY(float y) { m_pImageInfo->fPosY = y - m_pImageInfo->nFrameHeight / 2; }

	RECT GetBoundingBox()
	{
		return RectMakeCenter(m_pImageInfo->fPosX, m_pImageInfo->fPosY,
			m_pImageInfo->nFrameWidth, m_pImageInfo->nFrameHeight);
	}

	RECT GetBoundingBox(int adjX, int adjY)
	{
		return RectMakeCenter(m_pImageInfo->fPosX, m_pImageInfo->fPosY,
			m_pImageInfo->nFrameWidth - adjX, m_pImageInfo->nFrameHeight - adjY);
	}
};

