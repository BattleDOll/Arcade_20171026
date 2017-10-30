#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
{
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pObject = g_pImageManager->FindImage("Object");

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMiniBuffer = g_pImageManager->FindImage("MiniBuffer");

	m_pObject->SetPosX(240);
	m_pObject->SetPosY(512);

	m_nSourX = 0;				// 맵 X 좌표
}

cMap::~cMap()
{
}

void cMap::Setup()
{
}

void cMap::Update()
{
	MoveObject();

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
}

void cMap::Render()
{	
	// 픽셀 충돌 처리용 이미지 버퍼 //
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_nSourX, 0, 2048, 640);
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX() + m_nSourX, m_pObject->GetPosY(), 74, 32);

	// 미니 맵용 이미지 버퍼 //
	m_pImgBackground->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	//m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);

	// 백버퍼에 그린다.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	string str("맵 X 좌표 : ");
	char szStr[128];
	str += itoa(m_nSourX, szStr, 10);
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}

void cMap::MoveObject()
{
	if (m_bMoveRight && m_pObject->GetPosX() < 446)
	{
		m_pObject->SetPosX(m_pObject->GetPosX() + 1);
		if (m_pObject->GetPosX() >= 446)
			m_bMoveRight = false;
	}
	else if (m_pObject->GetPosX() > 240)
	{
		m_pObject->SetPosX(m_pObject->GetPosX() - 1);
		if (m_pObject->GetPosX() <= 240)
			m_bMoveRight = true;
	}
}