#pragma once
#include "gameNode.h"

class kirby;
class enemyManager;
class uiManager : public gameNode
{
protected:
	kirby* _kirby;
	enemyManager* _em;

	int _kirbyHP;
	int _kirbyLife;
	int _score;
	int* _bossHP;
	bool _visibleBossHP;

public:
	uiManager();
	virtual ~uiManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setKirbyMemoryLink(kirby* kirby) { _kirby = kirby; }
	void setEmMemoryLink(enemyManager* em) { _em = em; }

	inline int getScore() { return _score; }
	inline void setScore(int score) { _score = score; }
	void setBoss(int* bossHP) { _bossHP = bossHP; }
	void setBossHPBar(bool value) { _visibleBossHP = value; }
};

