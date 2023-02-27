#pragma once
#include "enemyBase.h"

struct Bullet
{
	float _speed;
	float _angle;
	float _x, _y;
	float _fireX, _fireY;
	RECT _rc;
	bool fire;
};

class Shotzo :	public enemyBase
{
private:
	Bullet _bullet;
public:
	Shotzo();
	virtual ~Shotzo();

	virtual HRESULT init(float x, float y, float speed, int moveRange);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);

	void AngleMove();
	void fire();

	void Collision();

	RECT getBulletRC() { return _bullet._rc; }
	RECT getRC() { return _rc; }
};

