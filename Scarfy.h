#pragma once
#include "enemyBase.h"

class Scarfy : public enemyBase
{
private:
	bool _bChange;
public:
	Scarfy();
	virtual ~Scarfy();

	HRESULT init(float x, float y, float speed, int moveRange, bool up);
	void release();
	void update();
	void render();
	void draw(RECT rcFocus);
};

