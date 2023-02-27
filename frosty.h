#pragma once
#include "enemyBase.h"

#define BOSS_SPEED 40
#define BOSS_JUMPPOWER 500

struct Ice
{
	RECT _iceRC;
	image* _iceImage;
	float _angle;
	float _x, _y;
	float _speed;
	float _gravity;
	bool _bFire;
};

class Frosty : public enemyBase
{
private:
	Ice _Ice;
	int _randMotion;
	int _jumpCount;
	int _dropJumpCount;


	bool _Drop;
public:
	Frosty() {}
	~Frosty() {}

	virtual HRESULT init(float x, float y, float speed, int moveRange);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
	void moveDash();
	void attack();
	void dropJump();
	void Jump();
	void Fire();
	void moveIce();
	bool getDrop() { return _Drop; }
	void Collision();

	inline RECT getIceRC() { return _Ice._iceRC; }
};

