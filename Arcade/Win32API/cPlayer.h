#pragma once

class cMap;

class cPlayer
{
private:
	cMap*	m_pMap;			// �� ����

	cImage*	m_pPlayer;		// �÷��̾� �̹��� ����
	cImage*	m_pImgMapBuffer;	// ��� ���� �̹��� ( �浹���� )

	float	m_fPosX;
	float	m_fPosY;
	float	probeX;
	float	probeX1;
	float	probeX2;
	float	probeY;
	float	probeY1;
	float	probeY2;

	float	m_nMoveSpeed;
	float	m_fJumpPower;		// ���� �Ŀ�
	float	m_fGravity;			// �߷� (������ ���)

	bool	m_isJumpping;		// ���� ���̳�?
	bool	m_isDobleJumpping;	// ���� ���� ����??
	bool	m_isIdle;
	bool	m_isRun;
	bool	m_isLeftMove;		// �̵� ���� üũ
	bool	m_isRightMove;		// �̵� ���� üũ
	

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render(); 

	void PlayerCollision();
	void PlayerControl();
	void Jump();
	void SetLanding();

	RECT GetBoundingBox() { return m_pPlayer->GetBoundingBox(); }

	void SetMap(cMap * map) { m_pMap = map; }
};

