	// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <time.h>
#include <string.h>
#include <map>
#include <assert.h>

using namespace std;

//==================================================================
//		## 디파인문 - 메크로 ## (윈도우창 초기화)
//==================================================================
#define WINNAME (LPCWSTR)(TEXT("코딩 지옥에 오신걸 환영 합니다."))
#define WINSTARTX		0
#define WINSTARTY		0
#define WINSIZEX		1024
#define WINSIZEY		624
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#define PURE			= 0
#define PI				3.141592654f
#define GRAVITY			0.3f

#include "MacroUtility.h"

//==================================================================
//		## 메크로함수 ## (클래스 동적할당된 부분 해제)
//==================================================================
#define SAFE_DELETE(p)		{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY	{ if(p) { delete[] (p); (p) = NULL; } }

//==================================================================
//		## 매니져 추가 ##
//==================================================================
#include "cKeyManager.h"
#include "cImage.h"
#include "cImageManager.h"
#include "cFileDataManager.h"
#include "cPixelCollision.h"

//==================================================================
//		## 전역변수 ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern HDC			g_hDC;