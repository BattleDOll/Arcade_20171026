#include "stdafx.h"
#include "cFileDataManager.h"


void cFileDataManager::txtSave(char* saveFileName, vector<string> vecData)
{
	HANDLE file;
	char szBuf[128];
	DWORD write;

	// 널문자 == '\0'

	strncpy_s(szBuf, 128, vectorArrayCombine(vecData), 126);

	file = CreateFile(saveFileName,
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, szBuf, strlen(szBuf), &write, NULL);

	CloseHandle(file);
}

char* cFileDataManager::vectorArrayCombine(vector<string> vArray)
{
	char szBuf[128];
	ZeroMemory(szBuf, sizeof(szBuf)); // 할당 범위의 모든 공간을 0으로 초기화

	// strcpy : 문자열 복사
	// strcat : 문자열 붙이기
	// strcmp : 문자열 비교

	//string str = "123123";
	//char szBuf2[7] = "123123";
	//strcpy_s(szBuf2, str.c_str());

	for (int i = 0; i < vArray.size(); ++i)
	{
		// szBuf = "123"; vArray[i].c_str() = "456"
		// strcat(szBuf, vArray[i].c_str()) ==> szBuf == "123456"
		strcat(szBuf, vArray[i].c_str());

		if (i < vArray.size() - 1)
			strcat(szBuf, ",");
	}

	return szBuf;
}

vector<string> cFileDataManager::txtLoad(char * loadFileName)
{
	HANDLE file;
	char szBuf[128];
	DWORD read;

	ZeroMemory(szBuf, sizeof(szBuf));

	file = CreateFile(loadFileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, szBuf, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(szBuf);
}

vector<string> cFileDataManager::charArraySeparation(char charArray[])
{
	vector<string> vecArray;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	if (token != NULL)
		vecArray.push_back(token);

	while ((token = strtok(NULL, separator)) != NULL)
	{
		vecArray.push_back(token);
	}

	return vecArray;
}