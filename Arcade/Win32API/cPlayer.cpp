#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
//	m_pImgGround = g_pImageManager->FindImage("BackGround");

	m_pPlayer = g_pImageManager->FindImage("Player");

	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront", m_pPlayer->GetFrameWidth(), 10);

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));
	saveData.push_back(itoa(m_fCurrHp, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;
	m_nMoveSpeed = 3.0f;
	m_isMoveLeft = false;
	m_isMoveRight = false;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);

	SetLanding();

	//vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");

	//if (!vecLoad.empty())
	//{
	//	m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
	//	m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
	//	m_fCurrHp = atoi(vecLoad[2].c_str());
	//}
}

void cPlayer::Update()
{
	PlayerControl();

	// 플레이어 이동 값
	m_fPosX = m_pPlayer->GetPosX();
	m_fPosY = m_pPlayer->GetPosY();

	// 맵 이동 값
	 m_pImgGround->SetPosX(m_nSourX);


	probeX = m_pPlayer->GetPosX();
	probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 - 10;

	if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
		m_pPlayer->SetPosY(m_pPlayer->GetPosY() + 5);
	else if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
		m_pPlayer->SetPosY(m_pPlayer->GetPosY() - 5);



	if (m_nDamageDelay > 0)
		--m_nDamageDelay;

	m_pHpBar->SetPosX(m_fPosX);
	m_pHpBar->SetPosY(m_fPosY - m_pPlayer->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();
}

void cPlayer::MiniRender()
{
	HPEN hPen = (HPEN)CreatePen(0, 20, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	BoudingLineMake(g_hDC,
		m_pPlayer->GetPosX() + m_pPlayer->GetFrameWidth() / 2 - WINSIZEX / 3,
		m_pPlayer->GetPosY() - WINSIZEY + ( WINSIZEY - m_pPlayer->GetPosY()),
		1024, 624);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}

void cPlayer::Render()
{
	//HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	//HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);
	//
	//BoudingLineMake(g_hDC, m_pPlayer->GetBoundingBox().left,
	//	m_pPlayer->GetBoundingBox().top,
	//	m_pPlayer->GetFrameWidth(),
	//	m_pPlayer->GetFrameHeight());
	//
	//DeleteObject(hSelectPen);
	//DeleteObject(hPen);

	// 무적 모드 중에는 반짝이게 표현
	if (m_nDamageDelay % 2 == 0)
	{
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			1, 0, 8, 0, 3);
	}

	m_pHpBar->Render();
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
}

void cPlayer::PlayerControl()
{
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_isMoveRight = true;
		m_pPlayer->SetPosX(m_fPosX - m_nMoveSpeed);

	}
	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_isMoveLeft = true;
	//	m_pPlayer->SetPosX(m_fPosX + m_nMoveSpeed);
	}
	else
	{
		m_isMoveRight = false;
		m_isMoveLeft = false;
	}

	if (g_pKeyManager->isStayKeyDown('W'))
	{
		m_pPlayer->SetPosY(m_fPosY - m_nMoveSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		m_pPlayer->SetPosY(m_fPosY + m_nMoveSpeed);
	}

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{
		m_pPlayer->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
				SetLanding();
		}
	}
}
