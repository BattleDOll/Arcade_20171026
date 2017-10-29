#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
{
	m_pImgGround = g_pImageManager->FindImage("Map");	

	m_pImgGround1 = g_pImageManager->FindImage("Map_01");
//	m_pImgGround2 = g_pImageManager->FindImage("Map_02");

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pObject = g_pImageManager->FindImage("Object");

	m_pObject->SetPosX(100);
	m_pObject->SetPosY(200);

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
	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
}

void cMap::Render()
{	
	// 픽셀 충돌 처리용 이미지 버퍼에 그림을 그린다.
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_nSourX, 0, 2048, 640);
//	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 100, 100);
	
	// 백버퍼에 그린다.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	// string 문자열 클래스 : 문자열에 대한 연산자 사용이 가능하다 ex) +=
	string str("맵 X 좌표 : ");
	char szStr[128];
	//str += "asdfasdfsadf";
	str += itoa(m_nSourX, szStr, 10); // itoa => 인트형을 문자열로 변환 (변환 소스, 임시 저장소, 숫자의 진수)
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}
