#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgGround;		// 기본 지형 이미지
	cImage*		m_pObject;			// 움직이는 오브젝트
	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼

	float		m_nSourX;

	bool		m_bMoveRight;

	cPlayer*	m_pPlayer;

	void		MoveObject();

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	float GetMapPosX() { return m_pImgGround->GetPosX(); }
	void SetMapPosX(float x) { m_pImgGround->SetPosX(x); }
};

