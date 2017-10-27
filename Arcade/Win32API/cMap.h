#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgGround;		// �⺻ ���� �̹���
	cImage*		m_pObject;			// �����̴� ������Ʈ
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����

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

