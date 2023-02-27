#include "stdafx.h"
#include "Tooky.h"


Tooky::Tooky()
{
}


Tooky::~Tooky()
{
}

HRESULT Tooky::init(float x, float y, float speed, int moveRange, bool type)
{
	_imageEnemy =  IMAGEMANAGER->addFrameImage("tooky_stop", "image//Enemy//Tooky//기본.bmp", 66, 33, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tooky_fly", "image//Enemy//Tooky//날때.bmp", 132, 33, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tooky_hit", "image//Enemy//Tooky//맞을때.bmp", 66, 33, 2, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isJump = _reSetType = type;
	_bEat = true;

	_jumpPower = 150;
	_nEnemyHP = 2;
	_angle = PI / 1.6;
	_gravity = 600;

	_bDie = false;
	_mapGravity = 100;
	_isHit = false;

	return S_OK;
}

void Tooky::release()
{
}

void Tooky::update()
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

		_jumpPower = 150;
		_nEnemyHP = 2;
		_angle = PI / 1.6;
		_gravity = 600;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();
	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{
		if (!_isJump)								// 타입1
		{
			enemyBase::Fly();
		}

		else
		{
			if (_state != ENEMY_UP_JUMP)			// 타입2
			{
				_fSpeed = 100;
				enemyBase::Followmove();
				if (_motionCount > 0.3)
				{
					_motionCount = 0;
					_resetState = _state;
					_state = ENEMY_UP_JUMP;
				}
			}
			else if (_state == ENEMY_UP_JUMP)	// 상태가 끝나면 다시 초기화한다.
			{
				enemyBase::Followjump();

				_y += _mapGravity * TIMEMANAGER->getElapsedTime();
			}
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
			IMAGEMANAGER->findImage("tooky_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX != 1)
		{
			_currentFrameX = 1;
			IMAGEMANAGER->findImage("tooky_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_FLY:
		if (_currentFrameX < (IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);
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

			IMAGEMANAGER->findImage("tooky_hit")->setFrameX(_currentFrameX);

		if (_count > 3)
		{
			if (_isUpFly)
				_state = ENEMY_LEFT_FLY;

			_state = ENEMY_LEFT_MOVE;
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_FLY:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("tooky_fly")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("tooky_fly")->setFrameX(_currentFrameX);

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
		IMAGEMANAGER->findImage("tooky_hit")->setFrameX(_currentFrameX);
		if (_count > 3)
		{
			if (_isUpFly)
				_state = ENEMY_LEFT_FLY;

			_state = ENEMY_RIGHT_MOVE;
		}
		break;
	case ENEMY_UP_FLY:
		break;
	}

	
	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (_nEnemyHP <= 0) _bDie = true;
}

void Tooky::render()
{

}

void Tooky::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("tooky_fly")->getFrameWidth(), IMAGEMANAGER->findImage("tooky_fly")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	switch (_state)
	{
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE: case ENEMY_UP_JUMP:
		IMAGEMANAGER->findImage("tooky_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_FLY: case ENEMY_LEFT_FLY:case ENEMY_UP_FLY:
		IMAGEMANAGER->findImage("tooky_fly")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("tooky_hit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("tooky_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}
}
