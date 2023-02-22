#pragma once
#include "enemyBase.h"

class Tooky : public enemyBase
{
public:
	Tooky();
	virtual ~Tooky();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool type);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

