#pragma once

class cMap
{
private:
	cImage*		m_pImgBackground;			// �� ��� �̹���
	cImage*		m_pImgGround;				// �⺻ ���� �̹���	
	cImage*		m_pImgMapBuffer;			// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pImgMiniBuffer;			// �̴ϸ� ����
	cImage*		m_pObject;					// �����̴� ������Ʈ

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

