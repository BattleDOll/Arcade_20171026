#pragma once

class cMap
{
private:
	cImage*		m_pImgBackground;			// 뒷 배경 이미지
	cImage*		m_pImgGround;				// 기본 지형 이미지	
	cImage*		m_pImgMapBuffer;			// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼
	cImage*		m_pImgMiniBuffer;			// 미니맵 버퍼
	cImage*		m_pImgMiniMap;
	cImage*		m_pObject_01;				// 움직이는 오브젝트
	cImage*		m_pItem;					// 플레이어 이미지 파일


	RECT		m_rtObject;
	RECT		m_rtItem;

	float		m_fMapSourX;
	float		m_fObjMOveSpeedX;

	bool		m_isMoveRight;
	bool		m_isMoveUp;
	bool		m_isItemGet;

	void		MoveObject();
public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	RECT GetRTObject() { return m_rtObject; }
	RECT GetRTItem() { return m_rtItem; }

	float GetMapPosX() { return m_fMapSourX; }
	void SetMapPosX(float setx) { m_fMapSourX = setx; }
	float GetObj01PosX() { return m_pObject_01->GetPosX(); }
	float GetObj01PosY() { return m_pObject_01->GetPosY(); }
	bool GetObjMoveRight() { return m_isMoveRight; }
	float GetObjSpeed() { return m_fObjMOveSpeedX; }
	bool GetItemGet() { return m_isItemGet; }
	void SetItemGet(bool get) { m_isItemGet = get; }
};

