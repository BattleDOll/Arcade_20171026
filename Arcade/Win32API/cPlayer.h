#pragma once

class cMap;

class cPlayer
{
private:
	cMap*	m_pMap;			// 맵 참조

	cImage*	m_pPlayer;		// 플레이어 이미지 파일
	cImage*	m_pImgMapBuffer;	// 배경 정보 이미지 ( 충돌관련 )

	float	m_fPosX;
	float	m_fPosY;
	float	probeX;
	float	probeX1;
	float	probeX2;
	float	probeY;
	float	probeY1;
	float	probeY2;

	float	m_nMoveSpeed;
	float	m_fJumpPower;		// 점프 파워
	float	m_fGravity;			// 중력 (점프시 사용)

	bool	m_isJumpping;		// 점프 중이냐?
	bool	m_isDobleJumpping;	// 이중 점프 가능??
	bool	m_isIdle;
	bool	m_isRun;
	bool	m_isLeftMove;		// 이동 방향 체크
	bool	m_isRightMove;		// 이동 방향 체크
	

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

