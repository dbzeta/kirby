#pragma once
#include "gameNode.h"

class mapManager;
class enemyManager;
class uiManager;
class kirby;

class gameScene : public gameNode
{
	enemyManager* _em;
	mapManager* _mm;
	uiManager* _uim;
	kirby* _kirby;

public:
	gameScene();
	virtual ~gameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

