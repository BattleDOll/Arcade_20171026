#pragma once
#include "cSingletonBase.h"

#define g_pFileDataManager cFileDataManager::GetInstance()

class cFileDataManager : public cSingletonBase<cFileDataManager>
{
public:
	// 세이브
	void txtSave(char* saveFileName, vector<string> vecData);
	// 로드
	vector<string> txtLoad(char* loadFileName);

private:
	char* vectorArrayCombine(vector<string> vArray);
	vector<string> charArraySeparation(char charArray[]);
};

