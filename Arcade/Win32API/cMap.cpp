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
//	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 100, 100);
	
	// ����ۿ� �׸���.
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	// string ���ڿ� Ŭ���� : ���ڿ��� ���� ������ ����� �����ϴ� ex) +=
	string str("�� X ��ǥ : ");
	char szStr[128];
	//str += "asdfasdfsadf";
	str += itoa(m_nSourX, szStr, 10); // itoa => ��Ʈ���� ���ڿ��� ��ȯ (��ȯ �ҽ�, �ӽ� �����, ������ ����)
	TextOutA(g_hDC, 40, 600, str.c_str(), str.length());
}
