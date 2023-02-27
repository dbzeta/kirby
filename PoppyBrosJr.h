#pragma once
#include "enemyBase.h"

class PoppyBrosJr :	public enemyBase
{
public:
	PoppyBrosJr();
	virtual ~PoppyBrosJr();

	virtual HRESULT init(float x, float y, float speed, int moveRange, bool up);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

