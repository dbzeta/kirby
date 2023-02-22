#include "stdafx.h"
#include "WaddleDee.h"


WaddleDee::WaddleDee()
{
}


WaddleDee::~WaddleDee()
{
}

HRESULT WaddleDee::init(float x, float y, float speed, int moveRange, bool type)
{
	_imageEnemy =  IMAGEMANAGER->addFrameImage("waddleDee_stop", "image//Enemy//WaddleDee//기본.bmp", 88, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("waddleDee_walk", "image//Enemy//WaddleDee//걷기.bmp", 176, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("waddleDee_hit", "image//Enemy//WaddleDee//맞을때.bmp", 88, 40, 2, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isJump = _reSetType = type;
	_bEat = true;

	_state = _resetState = ENEMY_LEFT_MOVE;

	_jumpPower = JUMP_POWER;
	_nEnemyHP = 2;
	_gravity = 70;

	_mapGravity = 100;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void WaddleDee::release()
{
}

void WaddleDee::update()
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

		_state = _resetState = ENEMY_LEFT_MOVE;

		_jumpPower = JUMP_POWER;
		_nEnemyHP = 1;
		_gravity = 600;
		_isHit = false;
		return;
	}

	if (_isHit)
	{
		_InvincibilityCount += TIMEMANAGER->getElapsedTime();

		if (_InvincibilityCount > 3)
		{
			_isHit = false;
			_InvincibilityCount = 0;
		}

	}

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();
	//패턴 조합
	//------------------------------------------------------------------------
	if (!_isHit)
	{
		if (!_isJump)							// 타입1
		{
			enemyBase::Followmove();
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
					_startY = _y;
				}
			}

			if (_state == ENEMY_UP_JUMP)
				enemyBase::jump();
		}
	}
	//-------------------------------------------------------------------------
	_count += TIMEMANAGER->getElapsedTime();

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("waddleDee_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);

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
			_state = ENEMY_LEFT_MOVE;
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("waddleDee_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_UP_JUMP:
		if (_resetState == ENEMY_LEFT_MOVE)
		{
			if (_currentFrameX >= (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2)
			{
				_currentFrameX = ((IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2) - 1;
				IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);
				_count = 0;
			}

			if (_count > 0.1)
			{
				_count = 0;
				if (_currentFrameX <= 0)_currentFrameX = 1;
				else --_currentFrameX;

				IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);

			}
		}
		else
		{
			if (_currentFrameX < (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2)
			{
				_currentFrameX = (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2;
				IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);
				_count = 0;
			}

			if (_count > 0.1)
			{
				_count = 0;
				if (_currentFrameX >= IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("waddleDee_walk")->getMaxFrameX() + 1) / 2;
				else ++_currentFrameX;

				IMAGEMANAGER->findImage("waddleDee_walk")->setFrameX(_currentFrameX);

			}
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
		IMAGEMANAGER->findImage("waddleDee_hit")->setFrameX(_currentFrameX);
		if (_count > 3)
			_state = ENEMY_RIGHT_MOVE;
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	if (_nEnemyHP <= 0) 
	{
		_bDie = true;
	}
}

void WaddleDee::render()
{

}

void WaddleDee::draw(RECT rcFocus)
{
	if (_bDie) return;

	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("waddleDee_walk")->getFrameWidth(), IMAGEMANAGER->findImage("waddleDee_walk")->getFrameHeight());
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
		IMAGEMANAGER->findImage("waddleDee_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("waddleDee_hit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("waddleDee_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}
}
