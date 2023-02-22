#pragma once
#include "enemyBase.h"
#define JUMP_POWER 170

class WaddleDee : public enemyBase
{
public:
	WaddleDee();
	virtual ~WaddleDee();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool type);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

