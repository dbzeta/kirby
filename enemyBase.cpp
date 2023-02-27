#include "stdafx.h"
#include "enemyBase.h"
#include "enemyManager.h"
#include "kirby.h"
#include "mapManager.h"


enemyBase::enemyBase()
{
}


enemyBase::~enemyBase()
{
}

HRESULT enemyBase::init()
{
	
	return S_OK;
}

void enemyBase::release()
{

}

void enemyBase::update()
{

}

void enemyBase::render()
{

}

void enemyBase::draw(RECT rcFocus)
{
}

void enemyBase::Followmove()
{
	if (_x > _em->getKirby()->getRect().left)
	{
		_x -= _fSpeed* TIMEMANAGER->getElapsedTime();
		_state = ENEMY_LEFT_MOVE;
	}
	if (_x < _em->getKirby()->getRect().left)
	{
		_x += _fSpeed* TIMEMANAGER->getElapsedTime();
		_state = ENEMY_RIGHT_MOVE;
	}
}

void enemyBase::move()
{
	if (_state == ENEMY_RIGHT_MOVE)
	{
		_x += _fSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX + _moveRange) <= _x)
		{
			_x = _startX + _moveRange;
			_startX = _x;
			_state = ENEMY_LEFT_MOVE;
		}
	}

	if (_state == ENEMY_LEFT_MOVE)
	{
		_x -= _fSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX - _moveRange) >= _x)
		{
			_x = _startX - _moveRange;
			_startX = _x;
			_state = ENEMY_RIGHT_MOVE;
		}
	}
}

void enemyBase::move(ENEMY_STATE nextMotion)
{
	if (_state == ENEMY_RIGHT_MOVE)
	{
		_x += _fSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX + _moveRange) <= _x)
		{
			_x = _startX + _moveRange;
			_startX = _x;
			_state = nextMotion;
			_currentFrameX = 0;
		}
	}

	if (_state == ENEMY_LEFT_MOVE)
	{
		_x -= _fSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX - _moveRange) >= _x)
		{
			_x = _startX - _moveRange;
			_startX = _x;
			_state = nextMotion;
			_currentFrameX = 0;
		}
	}
}

void enemyBase::jump()
{
	_y -= _jumpPower * TIMEMANAGER->getElapsedTime();
	_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
}


void enemyBase::Followjump()
{
	_y -= _jumpPower * TIMEMANAGER->getElapsedTime();
	_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();

	if (_state == ENEMY_LEFT_DROPJUMP)
		_x -= _fSpeed * TIMEMANAGER->getElapsedTime();

	if (_state == ENEMY_RIGHT_DROPJUMP)
		_x += _fSpeed * TIMEMANAGER->getElapsedTime();
	
}

void enemyBase::Fly()
{
	if (_isUpFly)
	{
		_state = ENEMY_LEFT_FLY;

		if (_y >= _startY - 100)
			_y -= _fSpeed * TIMEMANAGER->getElapsedTime();
		else
		{
			_startY = _y;
			_isUpFly = false;
		}
	}
	else
	{
		_state = ENEMY_LEFT_FLY;

		_x += cosf(_angle)  * _fSpeed * TIMEMANAGER->getElapsedTime();
		_y += -sinf(_angle) * _fSpeed * TIMEMANAGER->getElapsedTime();

		if (_y < _startY - 100)
		{
			if (_angle <= PI*1.35)
				_angle += 0.1;
		}
		else if (_y > _startY)
			if (_angle <= PI*1.6)
				_angle -= 0.1;
	}
}

void enemyBase::FollowFly()
{
	if (_x > _em->getKirby()->getRect().left)
	{
		_x -= _fSpeed * TIMEMANAGER->getElapsedTime();
		_state = ENEMY_LEFT_FLY;
	}
	else if (_x < _em->getKirby()->getRect().left)
	{
		_x += _fSpeed * TIMEMANAGER->getElapsedTime();
		_state = ENEMY_RIGHT_FLY;
	}
	if (_y > _em->getKirby()->getRect().top)
		_y -= _fSpeed * TIMEMANAGER->getElapsedTime();

	else if (_y < _em->getKirby()->getRect().top)
		_y += _fSpeed * TIMEMANAGER->getElapsedTime();
}

void enemyBase::Dash(float dashRange, float dashSpeed, ENEMY_STATE nextMotion)
{
	if (_state == ENEMY_RIGHT_DASH)
	{
		_x += _fSpeed * dashSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX + dashRange) <= _x)
		{
			_state = nextMotion;
			_startX = _x;
		}
	}

	if (_state == ENEMY_LEFT_DASH)
	{
		_x -= _fSpeed * dashSpeed * TIMEMANAGER->getElapsedTime();

		if ((_startX - dashRange) >= _x)
		{
			_state = nextMotion;
			_startX = _x;
		}
	}
}

void enemyBase::Gravity()
{
	
}

void enemyBase::PixelCollision()
{
	int width = _imageEnemy->getFrameWidth();
	int height = _imageEnemy->getFrameHeight();
	image* map = _em->getMapManager()->getPixalCrushImage();
	bool isCollision = false;

	//¿Þ
	for (int i = _x + width / 2; i > _x; --i)
	{
		for (int j = _y; j < _y + height; ++j)
		{
			COLORREF color = GetPixel(map->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 0 & b == 255)
			{
				_x = i;
				isCollision = true;

				if (_state == ENEMY_LEFT_MOVE)
					_state = ENEMY_RIGHT_MOVE;
				break;
			}
		}
		if (isCollision)
			break;
	}
	//¿À
	for (int i = _x + width / 2; i < _x + width; ++i)
	{
		for (int j = _y; j < _y + height; ++j)
		{
			COLORREF color = GetPixel(map->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 0 & b == 255)
			{
				_x = i - width;
				isCollision = true;
				if (_state == ENEMY_RIGHT_MOVE)
					_state = ENEMY_LEFT_MOVE;
				break;
			}
		}
		if (isCollision)
			break;
	}

	isCollision = false;
	for (int i = _y + height / 3 * 2; i < _y + height; ++i)
	{
		COLORREF color = GetPixel(map->getMemDC(), _x + width / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 & b == 0)
		{
			_y = i - height;
			_startY = _y;
			_mapGravity = 0;
			_jumpPower = 200;
			isCollision = true;
			if(_state == ENEMY_UP_JUMP)
				_state = _resetState;
			break;
		}
		else
			_mapGravity = 100;
	}
}

void enemyBase::hitDamage(int damage)
{
	int aa = 0;

	if (_isHit) return;
	
	int a = 0;

	_nEnemyHP -= damage;
	_isHit = true;

	//if (!_boss) return;
	if (_em->getKirby()->getRect().left > _x)
	{
		_state = ENEMY_RIGHT_HIT;
		_x -= 20;
	}
	else if (_em->getKirby()->getRect().left <= _x)
	{
		_state = ENEMY_LEFT_HIT;
		_x += 20;
	}
}
