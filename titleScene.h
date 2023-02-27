#pragma once

#include "gameNode.h"

class titleScene : public gameNode
{
protected:
	int _alpha;
	bool _canKey;

public:
	titleScene();
	virtual ~titleScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void changeScene();

};

