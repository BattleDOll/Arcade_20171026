#pragma once

class cProgressBar;
class CMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayer;		// �÷��̾� �̹��� ����
	float			m_fPosX;
	float			m_fPosY;
	float			probeX;
	float			probeY;

	float			m_fJumpPower;		// ���� �Ŀ�
	float			m_fGravity;			// �߷� (������ ���)

	bool			m_isJumpping;		// ���� ���̳�?
	bool			m_isMoveLeft;
	bool			m_isMoveRight;

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;
	float			m_nMoveSpeed;

	cImage*			m_pImgMapBuffer;	// ��� ���� �̹���
	cImage*			m_pImgGround;

	float			m_nSourX;
public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render();

	void SetLanding();
	void PlayerControl();

	RECT GetBoundingBox() { return m_pPlayer->GetBoundingBox(); }
	float GetPosX() { return m_pPlayer->GetPosX(); }
	float GetPosY() { return m_pPlayer->GetPosY(); }
	float GetMoveSpeed() { return m_nMoveSpeed; }

	bool GetMoveLeft() { return m_isMoveLeft; }

	int GetDamageDelay() { return m_nDamageDelay; }
	void SetDamageDelay(int delay) { m_nDamageDelay = delay; }
};

