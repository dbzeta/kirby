#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{

	return S_OK;
}

void txtData::release()
{

}

//세이브
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[1024];
	DWORD write;

	strncpy_s(str, 1024, vectorArrayCombine(vStr), 1022);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 1024, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[1024];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//100, 100, 50, 6
		strncat_s(str, 1024, vArray[i].c_str(), 1022);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}

//로드
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[1024] = "";
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 1024, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	//100 ,100 ,50 , 6

	token = strtok(charArray, separator);
	if(token != NULL)
		vArray.push_back(token);

	//문자열의 맨 뒤에 NULL이 나올때까지 계속 잘라라
	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}