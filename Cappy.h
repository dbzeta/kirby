#pragma once
#include "enemyBase.h"

class Cappy : public enemyBase
{
	int _headX, _headY;

public:
	Cappy();
	virtual ~Cappy();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool up);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

