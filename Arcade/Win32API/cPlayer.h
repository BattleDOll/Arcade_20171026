#pragma once

class cProgressBar;
class CMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayer;		// 플레이어 이미지 파일
	float			m_fPosX;
	float			m_fPosY;
	float			probeX;
	float			probeY;

	float			m_fJumpPower;		// 점프 파워
	float			m_fGravity;			// 중력 (점프시 사용)

	bool			m_isJumpping;		// 점프 중이냐?
	bool			m_isMoveLeft;
	bool			m_isMoveRight;

	int				m_nMapYPos;			// 플레이어의 바닥위 설정 (맵에 따라 다르게 설정이 필요)
	int				m_nDamageDelay;		// 연속 데미지 방지용 딜레이(무적 모드)

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;
	float			m_nMoveSpeed;

	cImage*			m_pImgMapBuffer;	// 배경 정보 이미지
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

