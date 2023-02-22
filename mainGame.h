#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	int _winSizeX;
	int _winSizeY;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	mainGame();
	~mainGame();
};

