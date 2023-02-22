#include "stdafx.h"
#include "Stone.h"


Stone::Stone()
{
}


Stone::~Stone()
{
}

HRESULT Stone::init(float x, float y, float speed, int moveRange, bool type)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("stone_stop", "image//Enemy//Stone//기본.bmp", 666, 35, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stone_walk", "image//Enemy//Stone//걷기.bmp", 592, 35, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stone_jump", "image//Enemy//Stone//점프.bmp", 74, 35, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stone_hit", "image//Enemy//Stone//맞을때.bmp", 74, 35, 2, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isMove = _reSetType = type;
	_bEat = true;

	_state = ENEMY_LEFT_STOP;
	_nEnemyHP = 2;

	_bDie = false;
	_mapGravity = 100;
	_isHit = false;

	return S_OK;
}

void Stone::release()
{
}

void Stone::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_moveRange = _reSetMoveRange;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_fSpeed = _reSetSpeed;
		_isMove = _reSetType;

		_state = ENEMY_LEFT_STOP;
		_nEnemyHP = 2;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();
	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{
		if (_isMove)
		{
			enemyBase::Followmove();
		}

		else if (!_isMove)
		{

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
		if (_currentFrameX < (IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("stone_stop")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("stone_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("stone_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("stone_walk")->setFrameX(_currentFrameX);
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

		IMAGEMANAGER->findImage("stone_hit")->setFrameX(_currentFrameX);

		if (_count > 3)
		{
			if (_isMove)
				_state = ENEMY_RIGHT_MOVE;

			_state = ENEMY_LEFT_STOP;
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("stone_stop")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = _currentFrameX = ((IMAGEMANAGER->findImage("stone_stop")->getMaxFrameX() + 1) / 2) - 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("stone_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("stone_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = _currentFrameX = ((IMAGEMANAGER->findImage("stone_walk")->getMaxFrameX() + 1) / 2) - 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("stone_walk")->setFrameX(_currentFrameX);
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

		IMAGEMANAGER->findImage("stone_hit")->setFrameX(_currentFrameX);

		if (_count > 3)
		{
			if (_isMove)
				_state = ENEMY_LEFT_MOVE;

			_state = ENEMY_RIGHT_STOP;
		}
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	if (_nEnemyHP <= 0) _bDie = true;
}

void Stone::render()
{

}

void Stone::draw(RECT rcFocus)
{
	if (!_bDie)
	{
		int x, y;
		RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("stone_walk")->getFrameWidth(), IMAGEMANAGER->findImage("stone_walk")->getFrameHeight());
		if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

		x = rc.left - rcFocus.left;
		y = rc.top - rcFocus.top;

		if (_debug)
		{
			Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
		}

		switch (_state)
		{
		case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE:
			IMAGEMANAGER->findImage("stone_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
			break;
		case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
			break;
		case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
			IMAGEMANAGER->findImage("stone_hit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
			break;
		case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
			IMAGEMANAGER->findImage("stone_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
			break;
		}
	}
}
