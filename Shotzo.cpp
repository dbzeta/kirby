#include "stdafx.h"
#include "Shotzo.h"
#include "enemyManager.h"
#include "kirby.h"

Shotzo::Shotzo()
{
}


Shotzo::~Shotzo()
{
}

HRESULT Shotzo::init(float x, float y, float speed, int moveRange)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("shotzo_stop", "image//Enemy//shotzo//±âº»1.bmp", 588, 44, 14, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("shotzo_boom", "image//Enemy//shotzo//ÆøÅº.bmp", 20, 20, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _InvincibilityCount = 0;
	_moveRange = _reSetMoveRange = moveRange;
	_x = _startX = _reSetX = x;
	_y = _startY = _reSetY = y;
	_bullet._speed = _reSetSpeed = speed;
	_bEat = false;

	_angle = PI / 2;
	_bullet.fire = false;

	_bDie = false;

	return S_OK;
}

void Shotzo::release()
{
}

void Shotzo::update()
{
	if (_bDie)
	{
		_currentFrameX = _currentFrameY = 0;
		_count = _motionCount = _InvincibilityCount = 0;
		_moveRange = _reSetMoveRange;
		_x = _startX = _reSetX;
		_y = _startY = _reSetY;
		_bullet._speed = _reSetSpeed;

		_angle = PI / 2;
		_bullet.fire = false;

		return;
	}

	_count += TIMEMANAGER->getElapsedTime();

	AngleMove();
	fire();

	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
}

void Shotzo::render()
{

}

void Shotzo::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), x, y, x + _imageEnemy->getFrameWidth(), y + _imageEnemy->getFrameHeight());
	}

	_imageEnemy->frameRender(getMemDC(), x, y, _imageEnemy->getFrameX(), 0);

	if (_bullet.fire)
	{
		rc = { _bullet._rc.left, _bullet._rc.top, _bullet._rc.right, _bullet._rc.bottom };
		if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

		x = _bullet._rc.left - rcFocus.left;
		y = _bullet._rc.top - rcFocus.top;

		if (_debug)
		{
			Rectangle(getMemDC(), x, y, x + IMAGEMANAGER->findImage("shotzo_boom")->getFrameWidth(), y + IMAGEMANAGER->findImage("shotzo_boom")->getFrameHeight());
		}
		IMAGEMANAGER->findImage("shotzo_boom")->render(getMemDC(),x, y);
	}
}

void Shotzo::AngleMove()
{
	int frame;
	float angle;

	angle = _angle + PI14;
	if (angle > PI2)
		angle -= PI2;

	frame = int(angle / PI6);
	_imageEnemy->setFrameX(frame);

	RECT rcKirby = _em->getKirby()->getRect();
	float angle1 = getAngle(_x, _y, RECT_X_CENTER(rcKirby), RECT_Y_CENTER(rcKirby));

	if (RECT_X_CENTER(rcKirby) < _x)
	{
		if ( angle1 > PI / 2.0f && angle1 < PI / 1.6f)
			_angle = PI / 1.6f;
		else if (angle1 > PI / 1.6f && angle1 < PI)
			_angle = PI / 1.3f;
		else _angle = PI ;
	}

	else if (RECT_X_CENTER(rcKirby) > _x)
	{
		if (angle1 > PI / 3.3f && angle1 <  PI/2.0f)
			_angle = PI / 3.3f;
		else if (angle1 < PI / 3.3f && angle1 > 0.0f)
			_angle = PI / 4.5f;
		else _angle = 0.0f;

	}
	else
		_angle = PI / 2.0f;
}

void Shotzo::fire()
{
	if (_em->getKirby()->getRect().left > _x - _moveRange && _em->getKirby()->getRect().left < _x + _moveRange)
	{
		if (!_bullet.fire)
		{
			_bullet.fire = true;
			_bullet._angle = _angle;
			_bullet._x = _bullet._fireX = _x + cosf(_angle) * 25;
			_bullet._y = _bullet._fireY = _y + -sinf(_angle) * 25;
			_bullet._rc = RectMake(_bullet._x, _bullet._y, 20, 20);
		}
	}
	if (_bullet.fire)
	{
		_bullet._x += cosf(_bullet._angle) * _bullet._speed * TIMEMANAGER->getElapsedTime();
		_bullet._y += -sinf(_bullet._angle) * _bullet._speed * TIMEMANAGER->getElapsedTime();

		_bullet._rc = RectMake(_bullet._x, _bullet._y, 20, 20);

		if (_moveRange < getDistance(_bullet._x, _bullet._y, _bullet._fireX, _bullet._fireY))
			_bullet.fire = false;
	}
}

void Shotzo::Collision()
{
	RECT _cRC;

	if (IntersectRect(&_cRC, &_em->getKirby()->getRect(), &_bullet._rc))
	{
		_em->getKirby()->hitDamage(1, _rc);
	}
}