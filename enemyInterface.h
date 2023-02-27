#pragma once
#include "gameNode.h"

class enemyMove : public gameNode
{
private:
	float _fSpeed;
	float* _x;
	float* _y;
	float _startX;
	float _startY;
	int _range;

	bool _isRightMoving;

public:
	enemyMove();
	~enemyMove();

	HRESULT init();
	void release();
	void update();
	void render();

	void move(float* x, float*y, float speed, int moveRange);

	bool getisRightMoving() { return _isRightMoving;}

};

