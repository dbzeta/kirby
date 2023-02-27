#pragma once
#include "enemyBase.h"

class Grizzo : public enemyBase
{
public:
	Grizzo();
	virtual ~Grizzo();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool up);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

