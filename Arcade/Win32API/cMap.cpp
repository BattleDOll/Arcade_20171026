#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
{
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pObject_01 = g_pImageManager->FindImage("Object");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMiniBuffer = g_pImageManager->FindImage("MiniBuffer");

}

cMap::~cMap()
{	
}

void cMap::Setup()
{
	m_pObject_01->SetPosX(240);
	m_pObject_01->SetPosY(512);

	m_fMapSourX = 0;				// 맵 X 좌표
	m_fObjMOveSpeedX = 1;			// 오브젝트 이동 속도
}

void cMap::Update()
{
	MoveObject();

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);

	m_rtObject = RectMakeCenter(m_pObject_01->GetPosX() + m_pObject_01->GetFrameWidth() / 2 + m_fMapSourX,
		m_pObject_01->GetPosY() + m_pObject_01->GetFrameHeight() / 2,
		m_pObject_01->GetFrameWidth(),
		m_pObject_01->GetFrameHeight());
}

void cMap::Render()
{	
	// 픽셀 충돌 처리용 이미지 버퍼 //
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_fMapSourX, 0, 2048, 640);
	m_pObject_01->Render(m_pImgMapBuffer->GetMemDC(), m_pObject_01->GetPosX() + m_fMapSourX, m_pObject_01->GetPosY(), 74, 32);

	// 미니 맵용 이미지 버퍼 //
	m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	//m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);

	// 백버퍼에 그린다.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	RectangleMake(g_hDC, m_rtObject);

	string str("맵 X 좌표 : ");
	char szStr[128];
	str += itoa(m_fMapSourX, szStr, 10);
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}

void cMap::MoveObject()
{
	if (m_bMoveRight && m_pObject_01->GetPosX() < 446)
	{
		m_pObject_01->SetPosX(m_pObject_01->GetPosX() + m_fObjMOveSpeedX);

		if (m_pObject_01->GetPosX() >= 446)
			m_bMoveRight = false;
	}
	else if (m_pObject_01->GetPosX() > 240)
	{
		m_pObject_01->SetPosX(m_pObject_01->GetPosX() - m_fObjMOveSpeedX);
		
		if (m_pObject_01->GetPosX() <= 240)
			m_bMoveRight = true;
	}
}