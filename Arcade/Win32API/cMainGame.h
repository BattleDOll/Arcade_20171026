#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	cImage*			m_pImgGround;			// 맵 이미지
	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼 1
	cImage*			m_pImgMiniBuffer;		// 미니맵용 이미지 버퍼 2

	bool			m_isPlaying;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();

	virtual void Update() override;
	virtual void Render() override;  
};