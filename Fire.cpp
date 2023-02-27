#include "stdafx.h"
#include "Fire.h"
#include "enemyManager.h"
#include "kirby.h"

Fire::Fire()
{
}


Fire::~Fire()
{
}

HRESULT Fire::init(float x, float y, float speed, int moveRange)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("fire_stop", "image//Enemy//Fire//기본.bmp", 90, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire_walk", "image//Enemy//Fire//걷기.bmp", 180, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire_attack", "image//Enemy//Fire//공격.bmp", 240, 40, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire_fire", "image//Enemy//Fire//불1.bmp", 136, 70, 2, 2, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _attCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;

	_nEnemyHP = 1;
	_mapGravity = 100;
	_bDie = false;
	_attack = false;
	_isHit = false;

	_state = ENEMY_LEFT_STOP;

	return S_OK;
}

void Fire::release()
{
}

void Fire::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = 0;
		_moveRange = _reSetMoveRange;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_fSpeed = _reSetSpeed;
		_attack = false;
		_isHit = false;

		_jumpPower = 10;
		_nEnemyHP = 1;
		_angle = PI / 1.6;

		return;
	}
	_count += TIMEMANAGER->getElapsedTime();
	//패턴 조합
	//------------------------------------------------------------------------
	if (!_isHit)
	{
		_motionCount += TIMEMANAGER->getElapsedTime();
		enemyBase::move();
		if (_motionCount > 3)
		{
			_motionCount = 0;
			if (_state == ENEMY_LEFT_MOVE)
			{
				_rcFire = RectMake(_rc.left - 68, _rc.top, IMAGEMANAGER->findImage("fire_fire")->getFrameWidth(), IMAGEMANAGER->findImage("fire_fire")->getFrameHeight());
				_attack = true;
				_state = ENEMY_LEFT_ATTACK;
			}

			if (_state == ENEMY_RIGHT_MOVE)
			{
				_rcFire = RectMake(_rc.right, _rc.top, IMAGEMANAGER->findImage("fire_fire")->getFrameWidth(), IMAGEMANAGER->findImage("fire_fire")->getFrameHeight());
				_attack = true;
				_state = ENEMY_RIGHT_ATTACK;
			}
		}

		if (_state == ENEMY_LEFT_ATTACK)
		{
			_attCount += TIMEMANAGER->getElapsedTime();

			if (_currentFrameX >= IMAGEMANAGER->findImage("fire_fire")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_count = 0;
			}

			IMAGEMANAGER->findImage("fire_fire")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("fire_fire")->setFrameY(1);
			if (_count > 0.7)
			{
				_count = 0;
				if (_currentFrameX >= IMAGEMANAGER->findImage("fire_fire")->getMaxFrameX())_currentFrameX = 0;
				else ++_currentFrameX;

				IMAGEMANAGER->findImage("fire_fire")->setFrameX(_currentFrameX);
				IMAGEMANAGER->findImage("fire_fire")->setFrameY(1);
			}

			if (_attCount > 3)
			{
				_attCount = 0;
				_state = ENEMY_LEFT_STOP;
				_attack = false;
			}

		}


		if (_state == ENEMY_RIGHT_ATTACK)
		{
			_attCount += TIMEMANAGER->getElapsedTime();

			if (_currentFrameX >= IMAGEMANAGER->findImage("fire_fire")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_count = 0;
			}
			IMAGEMANAGER->findImage("fire_fire")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("fire_fire")->setFrameY(0);

			if (_count > 0.7)
			{
				_count = 0;
				if (_currentFrameX >= IMAGEMANAGER->findImage("fire_fire")->getMaxFrameX())_currentFrameX = 0;
				else ++_currentFrameX;

				IMAGEMANAGER->findImage("fire_fire")->setFrameX(_currentFrameX);
				IMAGEMANAGER->findImage("fire_fire")->setFrameY(0);
			}

			if (_attCount > 3)
			{
				_attCount = 0;
				_state = ENEMY_RIGHT_STOP;
				_attack = false;
			}
		}
	}
	//-------------------------------------------------------------------------

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		if (_currentFrameX != 1)
		{
			_count = 0;
			_currentFrameX = 1;
		}
		IMAGEMANAGER->findImage("fire_stop")->setFrameX(_currentFrameX);

		if (_count > 2)
			_state = ENEMY_RIGHT_MOVE;
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_count = 0;
			_currentFrameX = 0;
		}
		IMAGEMANAGER->findImage("fire_stop")->setFrameX(_currentFrameX);

		if (_count > 2)
			_state = ENEMY_LEFT_MOVE;
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("fire_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("fire_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("fire_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("fire_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("fire_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_ATTACK:
		if (_currentFrameX < (IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("fire_attack")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("fire_attack")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_ATTACK:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("fire_attack")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("fire_attack")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 2;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("fire_attack")->setFrameX(_currentFrameX);

		}
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();
	Collision();

	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
}

void Fire::render()
{

}

void Fire::draw(RECT rcFocus)
{
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("fire_walk")->getFrameWidth(), IMAGEMANAGER->findImage("fire_walk")->getFrameHeight());
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
		IMAGEMANAGER->findImage("fire_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("fire_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_ATTACK: case ENEMY_LEFT_ATTACK:
		IMAGEMANAGER->findImage("fire_attack")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);

		break;
	}

	x = _rcFire.left - rcFocus.left;
	y = _rcFire.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + IMAGEMANAGER->findImage("fire_fire")->getFrameWidth(), y + IMAGEMANAGER->findImage("fire_fire")->getFrameHeight());
	}

	if (_attack)
		IMAGEMANAGER->findImage("fire_fire")->frameRender(getMemDC(), x, y, IMAGEMANAGER->findImage("fire_fire")->getFrameX(), IMAGEMANAGER->findImage("fire_fire")->getFrameY());


}


void Fire::Collision()
{
	RECT _cRC;

	if (IntersectRect(&_cRC, &_em->getKirby()->getRect(), &_rcFire))
	{
		_em->getKirby()->hitDamage(1, _rc);
	}
}