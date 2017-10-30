#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
	m_pImgBackBuffer = g_pImageManager->AddImage("BackBuffer", 2048, WINSIZEY);
	g_pKeyManager->Setup();
}


cGameNode::~cGameNode()
{
	g_pKeyManager->ReleaseInstance();

	g_pImageManager->DeleteAll();
	g_pImageManager->ReleaseInstance();
}

void cGameNode::Update()
{
	//RECT rt = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 300);
	InvalidateRect(g_hWnd, NULL, false);
}

LRESULT cGameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	g_hDC = m_pImgBackBuffer->GetMemDC();

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		srand(time(NULL));
		rand();
		break;
	case WM_TIMER:
		this->Update();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render();
		m_pImgBackBuffer->Render(hdc);
		EndPaint(hWnd, &ps);
	break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hWnd, message, wParam, lParam);
}
