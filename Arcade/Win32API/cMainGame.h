#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	cImage*			m_pImgGround;			// �� �̹���
	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ���� 1
	cImage*			m_pImgMiniBuffer;		// �̴ϸʿ� �̹��� ���� 2

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