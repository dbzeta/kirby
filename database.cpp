#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	loadDatabase("database.txt");

	return S_OK;
}

void database::release()
{
	arrElements vTemp;
	for (iterElement miter = _mTotalElement.begin(); miter != _mTotalElement.end(); ++miter)
	{
		vTemp.push_back(miter->first);
		vTemp.push_back(miter->second);
	}
	TXTDATA->txtSave("database.txt", vTemp);
}

void database::loadDatabase(string name)
{
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (int i = 0; i < vTemp.size();)
	{
		_mTotalElement.insert(make_pair(vTemp[i], vTemp[i+1]));
		i += 2;
	}

	vTemp.clear();
}

string database::getElementData(string str)
{
	iterElement iter = _mTotalElement.find(str);

	if (iter != _mTotalElement.end())
	{
		return iter->second;
	}

	return "";
}

void database::addElementData(string str, string value)
{
	iterElement iter = _mTotalElement.find(str);

	if (iter == _mTotalElement.end())
	{
		_mTotalElement.insert(make_pair(str, value));
	}
}

void database::setElementData(string str, string value)
{
	iterElement iter = _mTotalElement.find(str);

	if (iter != _mTotalElement.end())
	{
		iter->second = value;
	}
}
