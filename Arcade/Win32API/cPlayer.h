#pragma once

class cMap;

class cPlayer
{
private:
	cMap*	m_pMap;			// 맵 참조

	cImage*	m_pPlayer;		// 플레이어 이미지 파일
	cImage*	m_pImgMapBuffer;	// 배경 정보 이미지 ( 충돌관련 )

	RECT	rtBody;

	float	m_fPosX;
	float	m_fPosY;
//	float	probeX;
	float	probeX1;
	float	probeX2;
	float	probeY;
	float	probeY1;
	float	probeY2;

	float	m_fMoveSpeed;
	float	m_fObjSpeed;
	float	m_fJumpPower;		// 점프 파워
	float	m_fGravity;			// 중력 (점프시 사용)

	int		m_nRenSizeX;		// 프레임 렌더  X 사이즈 변경
	int		m_nRenSizeY;		// 프레임 렌더  Y 사이즈 변경
	int		m_nReGetPosX;		// 프레임 렌더 사이즈 변경 시 포지션 보정
	int		m_nReGetPosY;		// 프레임 렌더 사이즈 변경 시 포지션 보정
	int		m_nReCollisionX;	// 프레임 렌더 사이즈 변경 시 충돌 보정
	int		m_nReCollisionY;	// 프레임 렌더 사이즈 변경 시 충돌 보정

	int		m_nSizeDelay;

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
	void Diving();

	RECT GetBoundingBox() { return m_pPlayer->GetBoundingBox(); }

	void SetMap(cMap * map) { m_pMap = map; }
};

