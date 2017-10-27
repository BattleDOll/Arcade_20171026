#pragma once
#include "cSingletonBase.h"
#include <bitset>

#define g_pKeyManager cKeyManager::GetInstance()

using namespace std;

#define KEYMAX 256

class cKeyManager :	public cSingletonBase<cKeyManager>
{
private:
	bitset<KEYMAX> m_bitKeyUp;
	bitset<KEYMAX> m_bitKeyDown;

public:
	// 키 매니져 초기화
	void Setup();

	// 키가 한번 눌림
	bool isOnceKeyDown(int key);
	// 키가 눌렸다 땜
	bool isOnceKeyUp(int key);
	// 키를 누르고 있음
	bool isStayKeyDown(int key);
	// 토글키(키고 끄는 키)
	bool isToggleKey(int key);
};