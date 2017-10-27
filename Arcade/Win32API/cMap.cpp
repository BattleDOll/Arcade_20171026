#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"

cMap::cMap()
{
	m_pImgGround = g_pImageManager->FindImage("Map");

	m_pObject = g_pImageManager->FindImage("Object");
	m_pObject->SetPosX(100);
	m_pObject->SetPosY(400);
	m_bMoveRight = true;

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");

	m_pPlayer = new cPlayer;
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	m_nSourX = 0;
}

void cMap::Update()
{
	//if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	//	g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
	if (m_pPlayer->GetMoveLeft() /* && m_pPlayer->GetPosX() > WINSIZEX / 3 */)
	{
		m_nSourX -= 3;
		
	}
}

void cMap::Render()
{

	// 픽셀 충돌 처리용 이미지 버퍼에 그림을 그린다.
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_nSourX, 0);
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 100, 100);

	// 백버퍼에 그린다.
	m_pImgMapBuffer->Render(g_hDC, m_nSourX, 0);
}

void cMap::MoveObject()
{
}