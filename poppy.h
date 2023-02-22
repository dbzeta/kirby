#pragma once
#include "enemyBase.h"

class poppy : public enemyBase
{
private:

public:
	poppy();
	virtual ~poppy();

	virtual HRESULT init(float x, float y, float speed, int moveRange);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);

	void jumpMove(float moveSpeed, bool loop);
	void followJumpMove();
};

