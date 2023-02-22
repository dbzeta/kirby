#include "stdafx.h"
#include "Cappy.h"


Cappy::Cappy()
{
}


Cappy::~Cappy()
{
}

HRESULT Cappy::init(float x, float y, float speed, int moveRange, bool up)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("cappy_walk", "image//Enemy//Cappy//걷기.bmp", 104 * RATE, 25 * RATE, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cappy_hit", "image//Enemy//Cappy//맞을때.bmp", 52 * RATE, 25 * RATE, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cappy_head", "image//Enemy//Cappy//머리.bmp", 27 * RATE, 16 * RATE, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("cappy_head")->setX(_headX);
	IMAGEMANAGER->findImage("cappy_head")->setY(_headY);

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _headX = _reSetX = x;
	_y = _startY = _headY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_patternPlay = _reSetType = up;
	_bEat = true;

	_state = ENEMY_RIGHT_MOVE;

	_jumpPower = 7;
	_gravity = 0.5f;
	_nEnemyHP = 2;
	_mapGravity = 100;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void Cappy::release()
{
}

void Cappy::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_moveRange = _reSetMoveRange ;
		_x = _startX = _headX = _reSetX;
		_y = _startY = _headY = _reSetY;
		_fSpeed = _reSetSpeed;
		_patternPlay = _reSetType;

		_state = ENEMY_RIGHT_MOVE;

		_jumpPower = 7;
		_gravity = 0.5f;
		_nEnemyHP = 1;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();

	_headX = _x;

	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{
		if (!_patternPlay)
		{
			move();
		}

		else if (_patternPlay)
		{
			if (_state == ENEMY_UP_JUMP)
			{
				if (_motionCount > 2)
				{
					_motionCount = 0;
					_state = _resetState;
					//_state = ENEMY_UP_JUMP;
				}
			}
			else
			{
				move();
				if (_motionCount > 3)
				{
					_motionCount = 0;
					_resetState = _state;
					_state = ENEMY_UP_JUMP;
				}
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
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("cappy_walk")->getFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("cappy_walk")->getFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("cappy_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("cappy_walk")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("cappy_walk")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:
		break;
	case ENEMY_LEFT_STOP:
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("cappy_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("cappy_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("cappy_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("cappy_walk")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:
		break;
	case ENEMY_UP_JUMP:
		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX == 1) _currentFrameX = 2;
			else _currentFrameX = 1;

			IMAGEMANAGER->findImage("cappy_walk")->setFrameX(_currentFrameX);
		}

		//모자 움직임
		_headY -= _jumpPower;
		_jumpPower -= _gravity;

		if (_headY > _y)
		{
			_headY = _y;
			_jumpPower = 7;
		}
		break;
	}

	//_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	//PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (_nEnemyHP <= 0) _bDie = true;
}

void Cappy::render()
{

}

void Cappy::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("cappy_walk")->getFrameWidth(), IMAGEMANAGER->findImage("cappy_walk")->getFrameHeight());
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
		IMAGEMANAGER->findImage("cappy_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_UP_JUMP:
		IMAGEMANAGER->findImage("cappy_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		IMAGEMANAGER->findImage("cappy_head")->render(getMemDC(), _headX, _headY);
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
