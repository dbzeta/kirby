#pragma once
#include "enemyBase.h"

class Cutter : public enemyBase
{
public:
	Cutter();
	virtual ~Cutter();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool up);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

