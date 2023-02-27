#pragma once
#include "enemyBase.h"

class WaddleDoo : public enemyBase
{
public:
	WaddleDoo();
	virtual ~WaddleDoo();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool up);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

