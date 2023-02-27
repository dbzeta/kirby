#include "stdafx.h"
#include "Beem.h"
#include "enemyManager.h"
#include "kirby.h"

Beem::Beem()
{
}


Beem::~Beem()
{
}

HRESULT Beem::init(float x, float y, float speed, int moveRange)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("beem_walk", "image//Enemy//Beem//걷기.bmp", 160, 35, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beem_attack", "image//Enemy//Beem//공격.bmp", 160, 35, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beem_attack_ready", "image//Enemy//Beem//공격준비.bmp", 160, 35, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beem_hit", "image//Enemy//Beem//맞을때.bmp", 80, 35, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beem_beem", "image//Enemy//Beem//전기.bmp", 490, 160, 7, 2, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = attcurrent = 0;
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
	_bEat = true;

	_state = ENEMY_LEFT_STOP;

	return S_OK;
}

void Beem::release()
{
}

void Beem::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _attCount = 0;
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
				_rcFire = RectMake(_rc.left - 65, _rc.top - 55, IMAGEMANAGER->findImage("beem_beem")->getFrameWidth(), IMAGEMANAGER->findImage("beem_beem")->getFrameHeight());
				_attack = true;
				_state = ENEMY_LEFT_ATTACK;
				_currentFrameX = IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX();
			}

			if (_state == ENEMY_RIGHT_MOVE)
			{
				_rcFire = RectMake(_rc.right, _rc.top - 55, IMAGEMANAGER->findImage("beem_beem")->getFrameWidth(), IMAGEMANAGER->findImage("beem_beem")->getFrameHeight());
				_attack = true;
				_state = ENEMY_RIGHT_ATTACK;
				_currentFrameX = 0;
			}
		}

		if (_state == ENEMY_LEFT_ATTACK)
		{
			_attCount += TIMEMANAGER->getElapsedTime();

			if (attcurrent <= 0)
			{
				attcurrent = IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX();
				_count = 0;
			}

			IMAGEMANAGER->findImage("beem_beem")->setFrameX(attcurrent);
			IMAGEMANAGER->findImage("beem_beem")->setFrameY(1);
			if (_attCount > 0.4)
			{
				_attCount = 0;
				if (attcurrent < 0)attcurrent = IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX();
				else --attcurrent;

				IMAGEMANAGER->findImage("beem_beem")->setFrameX(attcurrent);
				IMAGEMANAGER->findImage("beem_beem")->setFrameY(1);

				if (attcurrent <= 0)
				{
					_attack = false;
					attcurrent = 0;
					_state = ENEMY_LEFT_STOP;;
				}
			}

			/*if (_attCount > 3)
			{
			_attCount = 0;
			_state = ENEMY_LEFT_STOP;
			_attack = false;
			}*/

		}


		if (_state == ENEMY_RIGHT_ATTACK)
		{
			_attCount += TIMEMANAGER->getElapsedTime();

			if (attcurrent >= IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX())
			{
				attcurrent = 0;
				_count = 0;
			}

			IMAGEMANAGER->findImage("beem_beem")->setFrameX(attcurrent);
			IMAGEMANAGER->findImage("beem_beem")->setFrameY(0);
			if (_attCount > 0.4)
			{
				_attCount = 0;
				if (attcurrent < 0)attcurrent = IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX();
				else ++attcurrent;

				IMAGEMANAGER->findImage("beem_beem")->setFrameX(attcurrent);
				IMAGEMANAGER->findImage("beem_beem")->setFrameY(0);

				if (attcurrent >= IMAGEMANAGER->findImage("beem_beem")->getMaxFrameX())
				{
					_attack = false;
					_state = ENEMY_RIGHT_STOP;;
					attcurrent = 0;
				}
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
		IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);

		if (_count > 2)
			_state = ENEMY_RIGHT_MOVE;
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_count = 0;
			_currentFrameX = 0;
		}
		IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);

		if (_count > 2)
			_state = ENEMY_LEFT_MOVE;
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("beem_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("beem_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_ATTACK:
		if (_currentFrameX < (IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("beem_attack")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX())_currentFrameX = (IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("beem_attack")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_ATTACK:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("beem_attack")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("beem_attack")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 2;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("beem_attack")->setFrameX(_currentFrameX);

		}
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	PixelCollision();
	Collision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (_nEnemyHP <= 0) _bDie = true;
}

void Beem::render()
{

}

void Beem::draw(RECT rcFocus)
{
	int x, y;
	RECT rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
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
		IMAGEMANAGER->findImage("beem_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("beem_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_ATTACK: case ENEMY_LEFT_ATTACK:
		IMAGEMANAGER->findImage("beem_attack")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);

		break;
	}

	x = _rcFire.left - rcFocus.left;
	y = _rcFire.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + IMAGEMANAGER->findImage("beem_beem")->getFrameWidth(), y + IMAGEMANAGER->findImage("beem_beem")->getFrameHeight());
	}

	if (_attack)
		IMAGEMANAGER->findImage("beem_beem")->frameRender(getMemDC(), x, y, attcurrent, IMAGEMANAGER->findImage("beem_beem")->getFrameY());
}

void Beem::Collision()
{
	RECT _cRC;

	if (IntersectRect(&_cRC, &_em->getKirby()->getRect(), &_rcFire))
	{
		_em->getKirby()->hitDamage(1, _rc);
	}
}