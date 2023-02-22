#include "stdafx.h"
#include "BroomHatter.h"
#include "enemyBase.h"


BroomHatter::BroomHatter()
{
}


BroomHatter::~BroomHatter()
{
}

HRESULT BroomHatter::init(float x, float y, float speed, int moveRange, bool type)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("BHWalk", "image//Enemy//BroomHatter//걷기.bmp", 320, 40, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BHStop", "image//Enemy//BroomHatter//기본.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BHHit", "image//Enemy//BroomHatter//맞을때.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isJump = _reSetType = type;
	_bEat = true;

	_state = ENEMY_LEFT_MOVE;
	_jumpPower = 200;
	_gravity = 70;
	_nEnemyHP = 2;

	_mapGravity = 100;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void BroomHatter::release()
{
	
}

void BroomHatter::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_moveRange = _reSetMoveRange;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_fSpeed = _reSetSpeed;
		_isJump = _reSetType;

		_state = ENEMY_LEFT_MOVE;
		_jumpPower = 200;
		_gravity = 70;
		_nEnemyHP = 1;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();

	//패턴 조합
	//--------------------------------------------------------------
	if (!_isHit)
	{
		if (!_isJump)							// 타입1
		{
			enemyBase::move();
		}

		if (_isJump)							// 타입2
		{
			if (_state != ENEMY_UP_JUMP)
			{
				enemyBase::move();
				if (_motionCount > 5)
				{
					_motionCount = 0;
					_resetState = _state;
					_state = ENEMY_UP_JUMP;
				}
			}

			if (_state == ENEMY_UP_JUMP)
				enemyBase::jump();
		}
	}
	//------------------------------------------------------------------
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
		if (_currentFrameX != 1)
		{
			_currentFrameX = 1;
			IMAGEMANAGER->findImage("BHStop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("BHWalk")->setFrameX(_currentFrameX);
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("BHWalk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:
		if (_currentFrameX != 1)
		{
			_currentFrameX = 1;
			_count = 0;
		}
		IMAGEMANAGER->findImage("BHHit")->setFrameX(_currentFrameX);
		if (_count > 3)
		{
			if (_isJump)
				_state = ENEMY_UP_JUMP;

			_state = ENEMY_RIGHT_MOVE;
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("BHStop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("BHWalk")->setFrameX(_currentFrameX);
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = ((IMAGEMANAGER->findImage("BHWalk")->getMaxFrameX() + 1) / 2) - 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("BHWalk")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			_count = 0;
		}
		IMAGEMANAGER->findImage("BHHit")->setFrameX(_currentFrameX);
		if (_count > 3)
		{
			if (_isJump)
				_state = ENEMY_UP_JUMP;

			_state = ENEMY_LEFT_MOVE;
		}
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	if (_nEnemyHP <= 0)
		_bDie = true;
}

void BroomHatter::render()
{
	
}

void BroomHatter::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("BHWalk")->getFrameWidth(), IMAGEMANAGER->findImage("BHWalk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	switch (_state)
	{
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE: case ENEMY_UP_JUMP:
		IMAGEMANAGER->findImage("BHWalk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("BHHit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("BHStop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}
}
