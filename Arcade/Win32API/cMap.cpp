#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
{
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pObject_01 = g_pImageManager->FindImage("Object");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMiniBuffer = g_pImageManager->FindImage("MiniBuffer");
	m_pItem = g_pImageManager->FindImage("Item");
}

cMap::~cMap()
{	
}

void cMap::Setup()
{
	m_pObject_01->SetPosX(240);
	m_pObject_01->SetPosY(512);

	m_pItem->SetPosX(100);		// 1055
	m_pItem->SetPosY(500);		//270

	m_fMapSourX = 0;				// �� X ��ǥ
	m_fObjMOveSpeedX = 1;			// ������Ʈ �̵� �ӵ�

	m_isItemGet = false;
}

void cMap::Update()
{
	MoveObject();

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);

	// ������Ʈ ���� �ѱ�� �ڽ�
	m_rtObject = RectMakeCenter(m_pObject_01->GetPosX() + m_pObject_01->GetFrameWidth() / 2 + m_fMapSourX,
		m_pObject_01->GetPosY() + m_pObject_01->GetFrameHeight() / 2,
		m_pObject_01->GetFrameWidth(),
		m_pObject_01->GetFrameHeight());

	// ������ ���� �ѱ�� �ڽ�
	m_rtItem = RectMakeCenter(m_pItem->GetPosX()+ m_fMapSourX, 
		m_pItem->GetPosY(),
		m_pItem->GetFrameWidth(),
		m_pItem->GetFrameHeight());
}

void cMap::Render()
{	
	// ������Ʈ �浹 Ȯ�� ��
	//RectangleMake(g_hDC, m_rtObject);

	// ������ �浹 Ȯ�� ��
	//RectangleMake(g_hDC, m_rtItem);

	// �ȼ� �浹 ó���� �̹��� ���� //
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_fMapSourX, 0, 2048, 640);
	m_pObject_01->Render(m_pImgMapBuffer->GetMemDC(), m_pObject_01->GetPosX() + m_fMapSourX, m_pObject_01->GetPosY(), 74, 32);
	if (m_isItemGet == false)
	{
		m_pItem->FrameRender(m_pImgMapBuffer->GetMemDC(), m_pItem->GetPosX() - m_pItem->GetFrameWidth() / 2 + m_fMapSourX, m_pItem->GetPosY() - m_pItem->GetFrameHeight() / 2, 3, 11, 3, 11, 0);
	}

	// �̴� �ʿ� �̹��� ���� //
	//m_pImgBackground->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	//m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	
	// ����ۿ� �׸���.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);
	//m_pImgMiniBuffer->Render(g_hDC, 0, 0);



	string str("�� X ��ǥ : ");
	char szStr[128];
	str += itoa(m_fMapSourX, szStr, 10);
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}

void cMap::MoveObject()
{
	// ������Ʈ ����
	if (m_isMoveRight && m_pObject_01->GetPosX() < 446)
	{
		m_pObject_01->SetPosX(m_pObject_01->GetPosX() + m_fObjMOveSpeedX);

		if (m_pObject_01->GetPosX() >= 446)
			m_isMoveRight = false;
	}
	else if (m_pObject_01->GetPosX() > 240)
	{
		m_pObject_01->SetPosX(m_pObject_01->GetPosX() - m_fObjMOveSpeedX);
		
		if (m_pObject_01->GetPosX() <= 240)
			m_isMoveRight = true;
	}

	// ������ ����
	if (m_isMoveUp && m_pItem->GetPosY() < 270)
	{
		m_pItem->SetPosY(m_pItem->GetPosY() + m_fObjMOveSpeedX);

		if (m_pItem->GetPosY() >= 270)
			m_isMoveUp = false;
	}
	else if (m_pItem->GetPosY() > 240)
	{
		m_pItem->SetPosY(m_pItem->GetPosY() - m_fObjMOveSpeedX);

		if (m_pItem->GetPosY() <= 240)
			m_isMoveUp = true;
	}
}