#pragma once
#include "enemyBase.h"



class Fire : public enemyBase
{
private:
	RECT _rcFire;

	float _attCount;
public:
	Fire();
	virtual ~Fire();

	virtual HRESULT init(float x, float y, float speed, int moveRange);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
	void Collision();
};

