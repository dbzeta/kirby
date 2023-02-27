#pragma once
#include "singletonBase.h"
#include <vector>
class gameNode;

class drawManager : public singletonBase<drawManager*>
{
private:
	vector<gameNode*> _vDraw;
	RECT* _focus;

public:
	drawManager();
	virtual ~drawManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void sort();
};

