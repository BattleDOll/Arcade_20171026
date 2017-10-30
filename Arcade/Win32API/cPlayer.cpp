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
	m_fJumpPower = 12.5f;
	m_nMoveSpeed = 5.0f;

	m_isIdle = true;
	m_isRun = false;
	m_isLeftMove = false;
	m_isRightMove = false;

	SetLanding();
}

void cPlayer::Update()
{
	PlayerCollision();
	PlayerControl();
	Jump();

	// �÷��̾� �̵� ��
	m_fPosX = m_pPlayer->GetPosX();
	m_fPosY = m_pPlayer->GetPosY();

	// ���� �������� �� ó��
	if (m_pPlayer->GetPosY() >= 545)
	{
		m_pPlayer->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		m_isJumpping = true;

		// ���� �� �������� �߿� ���� ����
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 10) == false)
				SetLanding();
		}
	}
}

void cPlayer::MiniRender()
{
	HPEN hPen = (HPEN)CreatePen(0, 10, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	EllipseMakeCenter(g_hDC,
		m_pPlayer->GetPosX(),
		m_pPlayer->GetPosY(),
		50, 50);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	string str("ĳ���� Y ��ǥ : ");
	char szStr[128];
	str += itoa(m_fPosY, szStr, 10);
	TextOutA(g_hDC, 40, 575, str.c_str(), str.length());
}

void cPlayer::Render()
{
	if (m_isIdle && !m_isJumpping)//���̵�		
	{
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			8, 5);
	}
	else if (m_isRun && m_isRightMove && !m_isJumpping)// ������ �̵�
	{
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			1, 0, 8, 0, 3);
	}
	else if (m_isRun && m_isLeftMove && !m_isJumpping)// ���� �̵�
	{
		if (m_pPlayer->GetFrameY() < 6)
		{
			m_pPlayer->SetFrameY(7);
		}
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			0, 7, 7, 7, 3);
	}

	if (m_isJumpping && m_fGravity < m_fJumpPower)// ����
	{
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			1, 8);
	}
	else if (m_isJumpping && m_fGravity > m_fJumpPower)// ����
	{
		m_pPlayer->FrameRender(g_hDC,
			m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2,
			m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2,
			6, 9);
	}

}

void cPlayer::PlayerCollision()
{
	probeX = m_pPlayer->GetPosX() - m_pPlayer->GetFrameWidth() / 2;			//left
	probeX1 = m_pPlayer->GetPosX();											//center
	probeX2 = m_pPlayer->GetPosX() + m_pPlayer->GetFrameWidth() / 2;		//right

	probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 - 10;	//bottom
	probeY1 = m_pPlayer->GetPosY() - 10;											//center
	probeY2 = m_pPlayer->GetPosY() - m_pPlayer->GetFrameHeight() / 2 + 10;	//top


	if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY))
	{
		m_pPlayer->SetPosY(m_pPlayer->GetPosY() + 5);
	}
	else if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY - 5) /*&& g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX1, probeY2)*/)
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

		m_pPlayer->SetPosX(m_fPosX - m_nMoveSpeed);

		if (m_pPlayer->GetPosX() < 150 ) 
		{
			m_pPlayer->SetPosX(m_fPosX - 0);
			m_pMap->SetPosX(m_pMap->GetPosX() + m_nMoveSpeed); 
		}

		if (m_pMap->GetPosX() > 0)			//�� �̵�ó�� ��
		{
			m_pMap->SetPosX(0);
			m_pMap->SetPosX(m_pMap->GetPosX() + 0);
		}
	}

	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_isIdle = false;
		m_isRun = true;
		m_isRightMove = true;

		m_pPlayer->SetPosX(m_fPosX + m_nMoveSpeed);

		//�� �̵�ó�� ��
		if (m_pPlayer->GetPosX() > WINSIZEX / 3) // ĳ���� �̵��� ȭ�� �����κп��� ����
		{
			m_pPlayer->SetPosX(m_fPosX - 0);

			m_pMap->SetPosX(m_pMap->GetPosX() - m_nMoveSpeed);
		}
		if (m_pMap->GetPosX() < -1024) // �� ������ ��ũ�� ���߱�
		{
			m_pPlayer->SetPosX(m_fPosX + m_nMoveSpeed);

			m_pMap->SetPosX(-1024);
			m_pMap->SetPosX(m_pMap->GetPosX() + 0);
		}
		if (m_pPlayer->GetPosX() > 924) // �� ���ڶ����� ĳ���� ���߱�
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

		// ���� �� �������� �߿� ���� ����
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayer->GetPosY() + m_pPlayer->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 10) == false)
				SetLanding();
		}
	}
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
	m_isDobleJumpping = false;
}

