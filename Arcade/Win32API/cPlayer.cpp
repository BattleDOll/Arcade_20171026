#include "stdafx.h"
#include "cPlayer.h"

#include "cMap.h"

cPlayer::cPlayer()
{
	m_pPlayer = g_pImageManager->FindImage("Player");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}

cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_fJumpPower = 15.0f;
	m_fMoveSpeed = 5.0f;
	m_fObjSpeed = 0.0f;

	m_nRenSizeX = 1;
	m_nRenSizeY = 1;
	m_nReGetPosX = 1;
	m_nReGetPosY = 1;
	m_nReCollisionX = 1;
	m_nReCollisionY = 1;
	m_nSizeDelay = 300;

	m_isIdle = true;
	m_isRun = false;
	m_isLeftMove = false;
	m_isRightMove = false;

	m_fObjSpeed = 1;

	SetLanding();
}

void cPlayer::Update()
{
	PlayerCollision();
	PlayerControl();
	Jump();
	Diving();

	// 플레이어 연동 충돌 박스
	if (!m_pMap->GetItemGet())
	{
		rtBody = RectMakeCenter
		(
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() /2, 
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			m_pPlayer->GetFrameWidth(), 
			m_pPlayer->GetFrameHeight()
		);
	}
	if (m_pMap->GetItemGet())
	{
		rtBody = RectMakeCenter(m_pPlayer->GetPosX(), m_pPlayer->GetPosY(), m_pPlayer->GetFrameWidth()*2, m_pPlayer->GetFrameHeight()*2);
	}

	// 플레이어 이동 값
	m_fPosX = m_pPlayer->GetPosX();
	m_fPosY = m_pPlayer->GetPosY();
	
	// 맵 오브젝트 연동 충돌
	RECT rt;
	if (IntersectRect(&rt, &m_pMap->GetRTObject(), &rtBody))
	{
		if (!m_pMap->GetObjMoveRight())
		{
 			m_pPlayer->SetPosX(m_pPlayer->GetPosX() - m_pMap->GetObjSpeed());
		}
		if (m_pMap->GetObjMoveRight())
		{
			m_pPlayer->SetPosX(m_pPlayer->GetPosX() + m_pMap->GetObjSpeed());
		}
	}
	
	// 맵 아이템 렌더 On/Off
	RECT rt1;
	if (IntersectRect(&rt1, &m_pMap->GetRTItem(), &rtBody))
	{
		m_pMap->SetItemGet(true);
	}

	if (m_pMap->GetItemGet() && m_pMap->GetItemGet())
	{
		// 캐릭터 스케일 
		m_nRenSizeX = 2;
		m_nRenSizeY = 2;
		// 캐릭터 스케일에 따른 충돌 렉트 보정
		m_nReGetPosX = 2;
		m_nReGetPosY = 3;

		if (m_nSizeDelay > 0)
		{
			--m_nSizeDelay;
		}

		if (m_nSizeDelay <= 0)
		{
			m_nRenSizeX = 1;
			m_nRenSizeY = 1;

			m_nReGetPosX = 1;
			m_nReGetPosY = 1;

			m_nSizeDelay = 300;

			m_pMap->SetItemGet(false);
		}
	}
}	

void cPlayer::MiniRender()
{	
	//HPEN hPen = (HPEN)CreatePen(0, 10, RGB(255, 0, 0));
	//HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	//	EllipseMakeCenter(g_hDC,
	//		m_pPlayer->GetPosX(),
	//		m_pPlayer->GetPosY(),
	//		50, 50);

	//DeleteObject(hSelectPen);
	//DeleteObject(hPen);

	string str("캐릭터 X 좌표 : ");
	char szStr[128];
	str += itoa(m_fPosX, szStr, 10);
	TextOutA(g_hDC, 40, 575, str.c_str(), str.length());

	str = "사이즈 : ";
	str += itoa(m_nSizeDelay, szStr, 10);
	TextOutA(g_hDC, 40, 550, str.c_str(), str.length());
}

void cPlayer::Render()
{
	 // 캐릭터 충돌박스 확인 용
	if (!m_pMap->GetItemGet())
	{
		BoudingLineMake(g_hDC, 
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			m_pPlayer->GetFrameWidth(),
			m_pPlayer->GetFrameHeight());
	}
	if (m_pMap->GetItemGet())
	{
		RectangleMake(g_hDC, rtBody.left, rtBody.top, m_pPlayer->GetFrameWidth()*2, m_pPlayer->GetFrameHeight()*2);
	}

	if (m_isIdle && !m_isJumpping)//아이들		
	{
		if (m_pPlayer->GetFrameX() < 8 || m_pPlayer->GetFrameX() > 8)
		{
			m_pPlayer->SetFrameY(8);
		}
		if (m_pPlayer->GetFrameY() < 5 || m_pPlayer->GetFrameY() > 5)
		{
			m_pPlayer->SetFrameY(5);
		}
		m_pPlayer->FrameSiezRender(g_hDC,
			m_pPlayer->GetPosX() - (m_pPlayer->GetFrameWidth() / 2) * m_nReGetPosX,
			m_pPlayer->GetPosY() - (m_pPlayer->GetFrameHeight() / 2) * m_nReGetPosY,
			m_nRenSizeX, m_nRenSizeY, 8, 5);
	}
	else if (m_isRun && m_isRightMove && !m_isJumpping)// 오른쪽 이동
	{
		if (m_pPlayer->GetFrameX() > 1)
		{
			m_pPlayer->SetFrameY(1);
		}
		if (m_pPlayer->GetFrameY() > 0)
		{
			m_pPlayer->SetFrameY(0);
		}
		m_pPlayer->FrameSiezRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2 * m_nReGetPosX,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 * m_nReGetPosY,
			m_nRenSizeX, m_nRenSizeY, 1, 0, 8, 0, 3);
	}
	else if (m_isRun && m_isLeftMove && !m_isJumpping)// 왼쪽 이동
	{
		if (m_pPlayer->GetFrameX() > 0)
		{
			m_pPlayer->SetFrameY(0);
		}
		if (m_pPlayer->GetFrameY() < 7 || m_pPlayer->GetFrameY() > 7)
		{
			m_pPlayer->SetFrameY(7);
		}
		m_pPlayer->FrameSiezRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2 * m_nReGetPosX,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 * m_nReGetPosY,
			m_nRenSizeX, m_nRenSizeY, 0, 7, 7, 7, 3);
	}

	if (m_isJumpping && m_fGravity < m_fJumpPower)// 점프
	{
		if (m_pPlayer->GetFrameX() > 1)
		{
			m_pPlayer->SetFrameY(1);
		}
		if (m_pPlayer->GetFrameY() < 8 || m_pPlayer->GetFrameY() > 8)
		{
			m_pPlayer->SetFrameY(8);
		}
		m_pPlayer->FrameSiezRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2 * m_nReGetPosX,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 * m_nReGetPosY,
			m_nRenSizeX, m_nRenSizeY, 1, 8);
	}
	else if (m_isJumpping && m_fGravity > m_fJumpPower)// 착지
	{
		if (m_pPlayer->GetFrameX() < 6 || m_pPlayer->GetFrameX() > 6)
		{
			m_pPlayer->SetFrameY(6);
		}
		if (m_pPlayer->GetFrameY() < 9 || m_pPlayer->GetFrameY() > 9)
		{
			m_pPlayer->SetFrameY(9);
		}
		m_pPlayer->FrameSiezRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2 * m_nReGetPosX,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 * m_nReGetPosY,
			m_nRenSizeX, m_nRenSizeY, 6, 9);
	}
}

void cPlayer::PlayerCollision()
{
	probeX1 = m_pPlayer->GetPosX() - 10;	//left
	probeX2 = m_pPlayer->GetPosX() + 10;	//right

	probeY1 = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 - 10 ;	//bottom
	probeY2 = m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 + 10 ;	//top

		// 기본 지형 충돌
	if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY1) && 
		g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX2, probeY1))
	{
		m_pPlayer->SetPosY(m_pPlayer->GetPosY() + 15);	
	}
	else if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY1 - 5) &&
			 !g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX2, probeY1 - 5))
	{
		m_pPlayer->SetPosY(m_pPlayer->GetPosY() - 5);
	}
}

void cPlayer::PlayerControl()
{
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_isIdle = false;
		m_isRun = true;
		m_isLeftMove = true;
		m_isRightMove = false;

		m_pPlayer->SetPosX(m_fPosX - m_fMoveSpeed);

		if (m_pPlayer->GetPosX() < 150 ) 
		{
			m_pPlayer->SetPosX(m_fPosX - 0);
			m_pMap->SetMapPosX(m_pMap->GetMapPosX() + m_fMoveSpeed); 
		}

		if (m_pMap->GetMapPosX() > 0)			//맵 이동처리 용
		{
			m_pMap->SetMapPosX(0);
			m_pMap->SetMapPosX(m_pMap->GetMapPosX() + 0);
		}
	}

	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_isIdle = false;
		m_isRun = true;
		m_isRightMove = true;
		m_isLeftMove = false;

		m_pPlayer->SetPosX(m_fPosX + m_fMoveSpeed);

		//맵 이동처리 용
		if (m_pPlayer->GetPosX() > WINSIZEX / 3) // 캐릭터 이동시 화면 일정부분에서 고정
		{
			m_pPlayer->SetPosX(m_fPosX - 0);

			m_pMap->SetMapPosX(m_pMap->GetMapPosX() - m_fMoveSpeed);
		}
		if (m_pMap->GetMapPosX() < -1024) // 맵 끝에서 스크롤 멈추기
		{
			m_pPlayer->SetPosX(m_fPosX + m_fMoveSpeed);

			m_pMap->SetMapPosX(-1024);
			m_pMap->SetMapPosX(m_pMap->GetMapPosX() + 0);
		}
		if (m_pPlayer->GetPosX() > 924) // 맵 끝자락에서 캐릭터 멈추기
		{
			m_pPlayer->SetPosX(m_fPosX + 0);
		}
	}	
	else
	{
		m_isIdle = true;
		m_isRun = false;
		m_isLeftMove = false;
		m_isRightMove = false;
	}
}

void cPlayer::Jump()
{
	if ( g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		if (!m_isJumpping && !m_isDobleJumpping)
		{
			m_isJumpping = true;
		}
		else if (m_isJumpping && !m_isDobleJumpping)
		{
			m_isDobleJumpping = true;
			m_fGravity = 0;
		}
	}
	else if (m_isJumpping)
	{
		m_pPlayer->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 + m_fGravity;

			if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY + 5) &&
				!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX2, probeY + 5))
			{
				SetLanding();
			}
		}
	}
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
	m_isDobleJumpping = false;
}

void cPlayer::Diving()
{
	// 물에 떨어졌을 때 처리
	if (m_pPlayer->GetPosY() >= 550)
	{
		m_pPlayer->SetPosY(m_fPosY - (m_fJumpPower + 30) + m_fGravity);
		m_fGravity += GRAVITY;

		m_isJumpping = true;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			probeY1 = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 + m_fGravity;

			if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY1 + 5) &&
				!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX2, probeY1 + 5))
				SetLanding();
		}
	}
}

