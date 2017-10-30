#include "stdafx.h"
#include "cMainGame.h"

#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pImgMiniBuffer = g_pImageManager->FindImage("MiniBuffer");

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
	m_pPlayer->SetMap(m_pMap); // 맵 참조
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
	// 흰색으로 이미지를 칠한다.
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
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/background.bmp", 2048, WINSIZEY);

	/* 맵 */
	m_pImgGround = g_pImageManager->AddImage("Map", "images/foreground_magenta.bmp", 2048, WINSIZEY);
	g_pImageManager->AddImage("MapBuffer", 2048, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵 */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX, 128);
	g_pImageManager->AddImage("MiniBuffer", WINSIZEX, 128)->SetTransColor(true, RGB(255, 0, 255));

	/* 프로그레스바 */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* 지형물 오브젝트*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 74, 32, true, RGB(255, 255, 255));

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 150, WINSIZEY / 2, true, RGB(255, 0, 255));

	/* 몬스터 */
}

void cMainGame::MiniMapRender()
{
	m_pPlayer->MiniRender();
	m_pImgBackground->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
	m_pImgMiniBuffer->Render(g_hDC, 0, 0);

//	m_pImgMiniBuffer->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
//	m_pImgMiniBuffer->Render(m_pImgBackBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
//	m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, 128);
//	m_pImgMiniMap->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
}

//void cMainGame::MiniMapRender()
//{
//	m_pPlayer->MiniRender();
//	m_pImgGround->Render(m_pImgMiniBuffer->GetMemDC(), 0, 0, WINSIZEX, 128);
//	m_pImgMiniBuffer->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
//}