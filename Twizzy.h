#pragma once
#include "enemyBase.h"

class Twizzy : public enemyBase
{
public:
	Twizzy();
	virtual ~Twizzy();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool type);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

