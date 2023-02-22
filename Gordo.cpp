#include "stdafx.h"
#include "Gordo.h"


Gordo::Gordo()
{
}


Gordo::~Gordo()
{
}

HRESULT Gordo::init(float x, float y, float speed, int moveRange, bool up)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("gordo_move", "image//Enemy//Gordo//움직임.bmp", 78, 24, 3, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isUpFly = _reSetType = up;
	_bEat = true;

	_nEnemyHP = 2;
	_mapGravity = 100;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void Gordo::release()
{
}

void Gordo::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_moveRange = _reSetMoveRange;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_fSpeed = _reSetSpeed;
		_isUpFly = _reSetType;
		_isHit = false;
		return;
	}
	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{

	}
	//-------------------------------------------------------------------------
	_count += TIMEMANAGER->getElapsedTime();

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		break;
	case ENEMY_RIGHT_MOVE:
		break;
	case ENEMY_RIGHT_FLY:
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:

		if (_count > 3)
		{
			if (_isMove)
				_state = ENEMY_LEFT_MOVE;

			_state = ENEMY_RIGHT_STOP;
		}
		break;
	case ENEMY_LEFT_STOP:
		break;
	case ENEMY_LEFT_MOVE:
		break;
	case ENEMY_LEFT_FLY:
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:

		if (_count > 3)
		{
			if (_isMove)
				_state = ENEMY_LEFT_MOVE;

			_state = ENEMY_RIGHT_STOP;
		}
		break;
	case ENEMY_UP_FLY:
		break;
	case ENEMY_END:
		break;
	}


	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
}

void Gordo::render()
{

}

void Gordo::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("gordo_move")->getFrameWidth(), IMAGEMANAGER->findImage("beem_walk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	switch (_state)
	{
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE:case ENEMY_UP_FLY:
		break;
	case ENEMY_RIGHT_FLY: case ENEMY_LEFT_FLY:
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		break;
	}
}
