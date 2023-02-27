#pragma once
#include "enemyBase.h"

struct Electric
{
	
};

class Beem : public enemyBase
{
private:
	RECT _rcFire;

	float _attCount;
	int attcurrent;
public:
	Beem();
	virtual ~Beem();

	virtual HRESULT init(float x, float y, float speed, int moveRange);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
	void Collision();
};

