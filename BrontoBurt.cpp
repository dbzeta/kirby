#include "stdafx.h"
#include "BrontoBurt.h"
#include "enemyManager.h"
#include "kirby.h"

BrontoBurt::BrontoBurt()
{
}


BrontoBurt::~BrontoBurt()
{
}

HRESULT BrontoBurt::init(float x, float y, float speed, int moveRange, bool up)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("BBWalk", "image//Enemy//BrontoBurt//걷기.bmp", 140, 35, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BBStop", "image//Enemy//BrontoBurt//기본.bmp", 70, 35, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BBFly", "image//Enemy//BrontoBurt//날때.bmp", 210, 35, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BBHit", "image//Enemy//BrontoBurt//맞을때.bmp", 70, 35, 2, 1, true, RGB(255, 0, 255));


	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isUpFly = _reSetType =up;
	_bEat = true;

	_state = ENEMY_LEFT_FLY;
	_nEnemyHP = 2;
	_mapGravity = 100;
	_angle = PI / 1.6;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void BrontoBurt::release()
{

}

void BrontoBurt::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_fSpeed = _reSetSpeed;
		_state = ENEMY_LEFT_FLY;
		_nEnemyHP = 1;
		_angle = PI / 1.6;
		_isUpFly = _reSetType;
		_moveRange = _reSetMoveRange;
		_isHit = false;
		return;
	}
	_count += TIMEMANAGER->getElapsedTime();
	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{
		if (_isUpFly)								// 타입1
		{
			enemyBase::Fly();
		}

		else if (!_isUpFly)							// 타입2
		{
			enemyBase::Fly();
		}
	}
	//-------------------------------------------------------------------------
	if (_isHit)
	{
		_InvincibilityCount += TIMEMANAGER->getElapsedTime();

		if (_InvincibilityCount > 2)
		{
			_isHit = false;
			_InvincibilityCount = 0;
		}

	}

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("BBStop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("BBWalk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("BBWalk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_FLY:
		if (_currentFrameX < (IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("BBFly")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("BBFly")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("BBFly")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:
		if (_currentFrameX != 1)
		{
			_count = 0;
			_currentFrameX = 1;
		}
		IMAGEMANAGER->findImage("BBHit")->setFrameX(_currentFrameX);

		if (_count > 3)
			_state = ENEMY_LEFT_FLY;
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("BBStop")->setFrameX(_currentFrameX);
		}

		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("BBWalk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("BBWalk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("BBWalk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_FLY:case ENEMY_UP_FLY:
		if (_currentFrameX >= ((IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2))
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("BBFly")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = ((IMAGEMANAGER->findImage("BBFly")->getMaxFrameX() + 1) / 2) - 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("BBFly")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:
		if (_currentFrameX != 0)
		{
			_count = 0;
			_currentFrameX = 0;
		}
		IMAGEMANAGER->findImage("BBHit")->setFrameX(_currentFrameX);
		if (_count > 3)
			_state = ENEMY_LEFT_FLY;
		break;
	}

	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	if (_nEnemyHP <= 0)
		_bDie = true;
}

void BrontoBurt::render()
{

}

void BrontoBurt::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("BBWalk")->getFrameWidth(), IMAGEMANAGER->findImage("BBWalk")->getFrameHeight());
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
		IMAGEMANAGER->findImage("BBWalk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_FLY: case ENEMY_LEFT_FLY:
		IMAGEMANAGER->findImage("BBFly")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("BBHit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("BBStop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}

	
}

