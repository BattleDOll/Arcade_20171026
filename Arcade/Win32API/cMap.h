#pragma once

class cMap
{
private:
	cImage*		m_pImgGround;		// �⺻ ���� �̹���	
	cImage*		m_pImgGround1;
	cImage*		m_pImgGround2;
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pObject;			// �����̴� ������Ʈ

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

