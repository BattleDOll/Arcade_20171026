#pragma once

class cMap
{
private:
	cImage*		m_pImgBackground;			// 뒷 배경 이미지
	cImage*		m_pImgGround;				// 기본 지형 이미지	
	cImage*		m_pImgMapBuffer;			// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼
	cImage*		m_pImgMiniBuffer;			// 미니맵 버퍼
	cImage*		m_pObject;					// 움직이는 오브젝트

	float		m_nSourX;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	float GetPosX() { return m_nSourX; }
	void SetPosX(float setx) { m_nSourX = setx; }
};

