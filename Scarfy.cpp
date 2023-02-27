#include "stdafx.h"
#include "Scarfy.h"


Scarfy::Scarfy()
{
}


Scarfy::~Scarfy()
{
}

HRESULT Scarfy::init(float x, float y, float speed, int moveRange, bool up)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("ScarfyStop", "image//Enemy//Scarfy//기본.bmp", 160, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScarfyChange", "image//Enemy//Scarfy//변신.bmp", 160, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScarfyHit", "image//Enemy//Scarfy//맞을때.bmp", 160, 40, 4, 1, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_fSpeed = _reSetSpeed = speed;
	_isUpFly = _reSetType = up;
	_bEat = false;

	_state = ENEMY_LEFT_STOP;
	_nEnemyHP = 2;
	_bChange = false;
	_isHit = false;

	_mapGravity = 100;
	_bDie = false;

	return S_OK;
}

void Scarfy::release()
{

}

void Scarfy::update()
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
		_bChange = false;
		_isHit = false;
		return;
	}

	_count += TIMEMANAGER->getElapsedTime();
	

	//패턴 조합
	//--------------------------------------------------------------
	if (!_bChange)
	{

	}

	else if (_bChange)
	{
		enemyBase::FollowFly();
	}
	//------------------------------------------------------------------

	if (_isHit)
	{
		_state = ENEMY_RIGHT_HIT;
		_motionCount += TIMEMANAGER->getElapsedTime();

		if (_motionCount > 3)
		{
			_isHit = false;
			_bChange = true;
			_motionCount = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown('7'))
	{
		if(!_isHit) 
		_isHit = true;
	}

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		if (_currentFrameX < (IMAGEMANAGER->findImage("ScarfyStop")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = 2;
			IMAGEMANAGER->findImage("ScarfyStop")->setFrameX(_currentFrameX);
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("ScarfyStop")->getMaxFrameX())_currentFrameX = IMAGEMANAGER->findImage("ScarfyStop")->getMaxFrameX() / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyStop")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_FLY:
		if (_currentFrameX < (IMAGEMANAGER->findImage("ScarfyChange")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = 2;
			IMAGEMANAGER->findImage("ScarfyChange")->setFrameX(_currentFrameX);
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("ScarfyChange")->getMaxFrameX())_currentFrameX = IMAGEMANAGER->findImage("ScarfyChange")->getMaxFrameX() / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyChange")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:
		if (_currentFrameX < (IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() + 1) / 2)
		{
			_currentFrameX = (IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() + 1) / 2;
			IMAGEMANAGER->findImage("ScarfyHit")->setFrameX(_currentFrameX);
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX())_currentFrameX = IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() / 2;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyHit")->setFrameX(_currentFrameX);
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX >= ((IMAGEMANAGER->findImage("ScarfyStop")->getMaxFrameX() + 1) / 2))
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("ScarfyStop")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("ScarfyStop")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyStop")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_FLY:
		if (_currentFrameX >= ((IMAGEMANAGER->findImage("ScarfyChange")->getMaxFrameX() + 1) / 2))
		{
			_currentFrameX = 1;
			IMAGEMANAGER->findImage("ScarfyChange")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyChange")->setFrameX(_currentFrameX);

		}
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:
		if (_currentFrameX >= ((IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() + 1) / 2))
		{
			_currentFrameX = ((IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() + 1) / 2) - 1;
			IMAGEMANAGER->findImage("ScarfyHit")->setFrameX(_currentFrameX);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = ((IMAGEMANAGER->findImage("ScarfyHit")->getMaxFrameX() + 1) / 2) - 1;
			else --_currentFrameX;

			IMAGEMANAGER->findImage("ScarfyHit")->setFrameX(_currentFrameX);

		}
		break;
	}
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (_nEnemyHP <= 0) _bDie = true;
}

void Scarfy::render()
{

}

void Scarfy::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("ScarfyStop")->getFrameWidth(), IMAGEMANAGER->findImage("ScarfyStop")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	switch (_state)
	{
	case ENEMY_RIGHT_FLY: case ENEMY_LEFT_FLY:
		IMAGEMANAGER->findImage("ScarfyChange")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		IMAGEMANAGER->findImage("ScarfyHit")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("ScarfyStop")->frameRender(getMemDC(), x, y, _currentFrameX, _currentFrameY);
		break;
	}
}
