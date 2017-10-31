#pragma once

class cMap
{
private:
	cImage*		m_pImgBackground;			// �� ��� �̹���
	cImage*		m_pImgGround;				// �⺻ ���� �̹���	
	cImage*		m_pImgMapBuffer;			// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pImgMiniBuffer;			// �̴ϸ� ����
	cImage*		m_pImgMiniMap;
	cImage*		m_pObject_01;				// �����̴� ������Ʈ
	cImage*		m_pItem;					// �÷��̾� �̹��� ����


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

