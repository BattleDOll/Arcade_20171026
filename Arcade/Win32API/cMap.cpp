#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
{
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pObject = g_pImageManager->FindImage("Object");

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMiniBuffer = g_pImageManager->FindImage("MiniBuffer");

	m_pObject->SetPosX(100);
	m_pObject->SetPosY(200);

	m_nSourX = 0;				// �� X ��ǥ
}

cMap::~cMap()
{
}

void cMap::Setup()
{
}

void cMap::Update()
{	
	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
}

void cMap::Render()
{	
	// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_nSourX, 0, 2048, 640);
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX() + m_nSourX, m_pObject->GetPosY(), 100, 100);
	
	// ����ۿ� �׸���.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	// �̴� �ʿ� �̹��� ����
	m_pImgBackground->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);


//	m_pImgMiniBuffer->Render(g_hDC, 0, 0);

	string str("�� X ��ǥ : ");
	char szStr[128];
	str += itoa(m_nSourX, szStr, 10);
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}
