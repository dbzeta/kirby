#include "stdafx.h"
#include "Grizzo.h"


Grizzo::Grizzo()
{
}


Grizzo::~Grizzo()
{
}

HRESULT Grizzo::init(float x, float y, float speed, int moveRange, bool up)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("grizzo_stop", "image//Enemy//Grizzo//기본.bmp", 168, 72, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grizzo_walk", "image//Enemy//Grizzo//걷기.bmp", 336, 72, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grizzo_hit", "image//Enemy//Grizzo//맞을때.bmp", 168, 72, 2, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isUpFly = _reSetType = up;
	_bEat = true;


	_state = ENEMY_LEFT_MOVE;
	_jumpPower = 10;
	_nEnemyHP = 2;

	_mapGravity = 100;
	_bDie = false;
	_isHit = false;

	return S_OK;
}

void Grizzo::release()
{
}

void Grizzo::update()
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


		_state = ENEMY_LEFT_STOP;
		_nEnemyHP = 2;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();

	//------------------------------------------------------------------------
	//패턴 조합
	if (!_isHit)
	{
		if (_state == ENEMY_RIGHT_STOP)
			_state = ENEMY_RIGHT_MOVE;
		else if (_state == ENEMY_LEFT_STOP)
			_state = ENEMY_LEFT_MOVE;


		if (_state == ENEMY_RIGHT_MOVE)
			enemyBase::move(ENEMY_RIGHT_DASH);
		else if (_state == ENEMY_LEFT_MOVE)
			enemyBase::move(ENEMY_LEFT_DASH);

		if (_state == ENEMY_RIGHT_DASH)
			enemyBase::Dash(100, 3, ENEMY_LEFT_STOP);
		else if (_state == ENEMY_LEFT_DASH)
			enemyBase::Dash(100, 3, ENEMY_RIGHT_STOP);
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
		if (_currentFrameX != 1)
		{
			_count = 0;
			_currentFrameX = 1;
		}
		IMAGEMANAGER->findImage("grizzo_stop")->setFrameX(_currentFrameX);
		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX < (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.4)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_HIT:
		if (_currentFrameX != 1)
		{
			_count = 0;
			_currentFrameX = 1;
		}

		IMAGEMANAGER->findImage("grizzo_hit")->setFrameX(_currentFrameX);

		if (_count > 3)
		{
			_state = ENEMY_LEFT_STOP;
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("grizzo_stop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.4)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_HIT:
		if (_currentFrameX != 0)
		{
			_count = 0;
			_currentFrameX = 0;
		}

		IMAGEMANAGER->findImage("grizzo_hit")->setFrameX(_currentFrameX);

		if (_count > 3)
		{
			_state = ENEMY_RIGHT_STOP;

		}
		break;
	case ENEMY_LEFT_DASH:
		if (_currentFrameX >= (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.1)
		{
			_count = 0;
			if (_currentFrameX <= 0)_currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_RIGHT_DASH:
		if (_currentFrameX < (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.1)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX()) _currentFrameX = (IMAGEMANAGER->findImage("grizzo_walk")->getMaxFrameX() + 1) / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("grizzo_walk")->setFrameX(_currentFrameX);
		}
		break;
	}

	_y += _mapGravity * TIMEMANAGER->getElapsedTime();

	PixelCollision();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (_nEnemyHP <= 0) _bDie = true;
}

void Grizzo::render()
{

}

void Grizzo::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("grizzo_walk")->getFrameWidth(), IMAGEMANAGER->findImage("grizzo_walk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	switch (_state)
	{
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE:case ENEMY_LEFT_DASH:case ENEMY_RIGHT_DASH:
		IMAGEMANAGER->findImage("grizzo_walk")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("grizzo_hit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("grizzo_stop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}
}
