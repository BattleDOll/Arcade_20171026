#include "stdafx.h"
#include "cProgressBar.h"


cProgressBar::cProgressBar(string strBack, string strFront, int width, int heigth)
{
	m_imgBack = g_pImageManager->FindImage(strBack);
	m_imgFront = g_pImageManager->FindImage(strFront);

	m_nWidth = width;
	m_nHeight = heigth;
}


cProgressBar::~cProgressBar()
{
}

void cProgressBar::Update()
{
	m_rt = RectMakeCenter(m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}

void cProgressBar::Render()
{
	m_imgBack->Render(g_hDC, m_rt.left, m_rt.top, m_nWidth, m_nHeight);
	m_imgFront->Render(g_hDC, m_rt.left, m_rt.top, m_nCurrWidth, m_nHeight);
}

void cProgressBar::SetGauge(float maxGauge, float currGauge)
{
	// 현재 체력 / 전체 체력 비율로 크기를 계산한다.
	m_nCurrWidth = (currGauge / maxGauge) * m_nWidth;
}
