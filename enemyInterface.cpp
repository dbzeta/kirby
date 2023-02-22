#include "stdafx.h"
#include "enemyInterface.h"


enemyMove::enemyMove()
{
}


enemyMove::~enemyMove()
{
}

HRESULT enemyMove::init()
{
	_fSpeed = 0;

	_isRightMoving = true;

	return S_OK;
}

void enemyMove::release()
{

}

void enemyMove::update()
{
	if (_isRightMoving)
	{
		*_x += _fSpeed;

		if ((_startX + _range) <= *_x)
		{
			*_x = _startX + _range;
			_isRightMoving = false;
		}
	}

	if (!_isRightMoving)
	{
		*_x -= _fSpeed;

		if ((_startX - _range) >= *_x)
		{
			*_x = _startX - _range;
			_isRightMoving = true;
		}
	}
}

void enemyMove::render()
{

}

void enemyMove::move(float* x, float*y, float speed, int moveRange)
{
	_startX = *x;
	_startY = *y;

	_x = x;
	_y = y;

	_range = moveRange;
	_fSpeed = speed;
}

