#pragma once
#include "enemyBase.h"

class BrontoBurt :public enemyBase
{
private:

public:
	BrontoBurt();
	virtual ~BrontoBurt();

	HRESULT init(float x, float y, float speed, int moveRange, bool up);
	void release();
	void update();
	void render();
	void draw(RECT rcFocus);
};

