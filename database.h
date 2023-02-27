#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class database : public singletonBase <database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, string> arrElement;
	typedef map<string, string>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	string getElementData(string str);
	void addElementData(string str, string value);
	void setElementData(string str, string value);

	database();
	~database();
};

