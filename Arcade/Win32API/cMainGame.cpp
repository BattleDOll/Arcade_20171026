#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMainGame::Setup()
{
	m_pMap->Setup();
	m_pPlayer->Setup();
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pImgBackground->Render(g_hDC, 0, 0);

		m_pMap->Render();
		MiniMapRender();
		m_pPlayer->Render();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void cMainGame::LoadImageFromFile()
{
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/map.bmp", 6144, 624);

	/* �� */
	g_pImageManager->AddImage("Map", "images/map_magenta.bmp", 6144, 624);
	g_pImageManager->AddImage("MapBuffer", 6144, 624)->SetTransColor(true, RGB(255, 0, 255));

	/* �̴ϸ� */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", 1024, 104);

	/* ���α׷����� */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* ������ ������Ʈ*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 894, 894, true, RGB(255, 255, 255));

	/* �÷��̾� */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, WINSIZEX / 3, MAP1_Y, true, RGB(255, 0, 255));

	/* ���� */
}

void cMainGame::MiniMapRender()
{
	m_pPlayer->MiniRender();

	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0, 1024, 104);
	m_pImgMiniMap->Render(m_pImgBackground->GetMemDC(),0, 0);
}
