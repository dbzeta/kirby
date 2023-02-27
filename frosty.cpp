#include "stdafx.h"
#include "Frosty.h"
#include "enemyManager.h"
#include "kirby.h"

HRESULT Frosty::init(float x, float y, float speed, int moveRange)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("frostyAttack", "image//Enemy//meddleBoss//Frosty//frosty_attack.bmp", 210, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyWalk", "image//Enemy//meddleBoss//Frosty//frosty_walk.bmp", 280, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyJump", "image//Enemy//meddleBoss//Frosty//frosty_walk.bmp", 280, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyDash", "image//Enemy//meddleBoss//Frosty//frosty_dash.bmp", 140, 140, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyDropJump", "image//Enemy//meddleBoss//Frosty//frosty_dropJump.bmp", 140, 140, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostydie", "image//Enemy//meddleBoss//Frosty//frosty_die.bmp", 140, 140, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyAttReady", "image//Enemy//meddleBoss//Frosty//frosty_hip.bmp", 350, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frostyStop", "image//Enemy//meddleBoss//Frosty//frosty_stop.bmp", 140, 140, 2, 2, true, RGB(255, 0, 255));

	_Ice._iceImage = IMAGEMANAGER->addImage("frostyIce", "image//Enemy//meddleBoss//Frosty//frosty_ice.bmp", 25, 25, true, RGB(255, 0, 255));

	_currentFrameX = _currentFrameY = 0;
	_count = _motionCount = _jumpCount = _dropJumpCount = _InvincibilityCount = 0;
	_x = _startX = x;
	_y = _startY = y;
	_fSpeed = BOSS_SPEED;
	_moveRange = moveRange;
	_bEat = false;

	_state = ENEMY_LEFT_STOP;

	_jumpPower = BOSS_JUMPPOWER;
	_gravity = 600;
	_nEnemyHP = 10;
	_Ice._bFire = false;
	_bDie = false;
	_isHit = false;
	_Drop = false;
	_boss = false;

	_randMotion = 0;

	return S_OK;
}

void Frosty::release()
{


}

void Frosty::update()
{
	_count += TIMEMANAGER->getElapsedTime();

	// 패턴 조합
	//----------------------------------------------------------------------------
	if (_state == ENEMY_RIGHT_STOP || _state == ENEMY_LEFT_STOP)
	{
		_motionCount += TIMEMANAGER->getElapsedTime();

		if (_motionCount > 3)
		{
			_randMotion = RND->getFromFloatTo(1, 4);
			_motionCount = 0;
			_currentFrameX = 0;
			_count = 0;
			_startX = _x;
			_startY = _y;

			if (_randMotion == 2)
			{
				RECT rcKirby = _em->getKirby()->getRect();
				float angle1 = getAngle(_x, _y, RECT_X_CENTER(rcKirby), RECT_Y_CENTER(rcKirby));

				if (RECT_X_CENTER(rcKirby) < _x)
				{
					if (angle1 > PI / 2.0f && angle1 < PI / 1.6f)
						_angle = PI / 1.6f;
					else if (angle1 > PI / 1.6f && angle1 < PI)
						_angle = PI / 1.3f;
					else _angle = PI;
				}

				else if (RECT_X_CENTER(rcKirby) > _x)
				{
					if (angle1 > PI / 3.3f && angle1 <  PI / 2.0f)
						_angle = PI / 3.3f;
					else if (angle1 < PI / 3.3f && angle1 > 0.0f)
						_angle = PI / 4.5f;
					else _angle = 0.0f;

				}
				else
					_angle = PI / 2.0f;
			}
		}
	}

	if (_isHit)
	{
		_InvincibilityCount += TIMEMANAGER->getElapsedTime();

		if (_InvincibilityCount > 2)
		{
			_isHit = false;
			_InvincibilityCount = 0;
		}

	}

	if (_randMotion == 1)
		moveDash();
	else if (_randMotion == 2)
		attack();
	else if (_randMotion == 3)
		dropJump();
	else if (_randMotion == 4)
		Jump();

	if (_state == ENEMY_RIGHT_READY || _state == ENEMY_LEFT_READY)
	{
		if (_currentFrameX == IMAGEMANAGER->findImage("frostyAttReady")->getMaxFrameX())
			Fire();

		_motionCount += TIMEMANAGER->getElapsedTime();

		if (_motionCount > 7)
		{
			if (_state == ENEMY_RIGHT_READY) _state = ENEMY_RIGHT_ATTACK;
			if (_state == ENEMY_LEFT_READY) _state = ENEMY_LEFT_ATTACK;
			_motionCount = 0;
			_currentFrameX = 0;
			_count = 0;
		}
	}

	if (_state == ENEMY_RIGHT_ATTACK || _state == ENEMY_LEFT_ATTACK)
	{
		_motionCount += TIMEMANAGER->getElapsedTime();
		moveIce();

		if (_motionCount > 7)
		{
			if (_state == ENEMY_RIGHT_ATTACK) _state = ENEMY_RIGHT_STOP;
			if (_state == ENEMY_LEFT_ATTACK) _state = ENEMY_LEFT_STOP;
			_motionCount = 0;
			_currentFrameX = 0;
			_count = 0;
			_Ice._bFire = false;
		}
	}


	// ----------------------------------------------------------------------------

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		if (_currentFrameX != 0 || _currentFrameY != 0)
		{
			_count = 0;
			_currentFrameX = _currentFrameY = 0;
			IMAGEMANAGER->findImage("frostyStop")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyStop")->setFrameY(_currentFrameY);
		}
		_randMotion = 0;
		break;
	case ENEMY_RIGHT_MOVE:case ENEMY_UP_JUMP:
		if (_currentFrameY != 0)
		{
			_currentFrameX = _currentFrameY = 0;
			IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyWalk")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyWalk")->getMaxFrameX())
			{
				_currentFrameX = 0;
				IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_RIGHT_DASH:
		if (_currentFrameY != 0)
		{
			_currentFrameX = _currentFrameY = 0;
			IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyDash")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.8)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyDash")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyDash")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_RIGHT_DIE:
		if (_currentFrameY != 0)
		{
			_currentFrameX = _currentFrameY = 0;
			IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostydie")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostydie")->getMaxFrameX())
			{
				_currentFrameX = 0;
				IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_RIGHT_HIT:
		break;
	case ENEMY_RIGHT_ATTACK:
		if (_currentFrameY != 0)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyAttack")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.5)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyAttack")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyAttack")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_STOP:
		if (_currentFrameX != 0 || _currentFrameY != 1)
		{
			_count = 0;
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyStop")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyStop")->setFrameY(_currentFrameY);
		}
		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyWalk")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyWalk")->getMaxFrameX())
			{
				_currentFrameX = 0;
				IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyWalk")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_DASH:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyDash")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.8)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyDash")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyDash")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyDash")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_DIE:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostydie")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.3)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostydie")->getMaxFrameX())
			{
				_currentFrameX = 0;
				IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostydie")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_HIT:
		break;
	case ENEMY_LEFT_ATTACK:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyAttack")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.5)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyAttack")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyAttack")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyAttack")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_RIGHT_READY:
		if (_currentFrameY != 0)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyAttReady")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.5)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyAttReady")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyAttReady")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_READY:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyAttReady")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 0.5)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyAttReady")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyAttReady")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyAttReady")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_LEFT_DROPJUMP:
		if (_currentFrameY != 1)
		{
			_currentFrameX = 0;
			_currentFrameY = 1;
			IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyDropJump")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 1)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyDropJump")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyDropJump")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	case ENEMY_RIGHT_DROPJUMP:
		if (_currentFrameY != 0)
		{
			_currentFrameX = _currentFrameY = 0;
			IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
			IMAGEMANAGER->findImage("frostyDropJump")->setFrameY(_currentFrameY);
			_count = 0;
		}

		if (_count > 1)
		{
			_count = 0;
			if (_currentFrameX >= IMAGEMANAGER->findImage("frostyDropJump")->getMaxFrameX())
			{
				_currentFrameX = IMAGEMANAGER->findImage("frostyDropJump")->getMaxFrameX();
				IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
			}
			else
			{
				IMAGEMANAGER->findImage("frostyDropJump")->setFrameX(_currentFrameX);
				++_currentFrameX;
			}
		}
		break;
	}

	if (_nEnemyHP <= 0)
		_bDie = true;
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	Collision();
}

void Frosty::render()
{

}

void Frosty::draw(RECT rcFocus)
{
	if (_bDie) return;
	int x, y;
	RECT rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:case ENEMY_LEFT_STOP:
		IMAGEMANAGER->findImage("frostyStop")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_MOVE:case ENEMY_LEFT_MOVE:case ENEMY_UP_JUMP:
		IMAGEMANAGER->findImage("frostyWalk")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DASH:case ENEMY_LEFT_DASH:
		IMAGEMANAGER->findImage("frostyDash")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_DIE:case ENEMY_LEFT_DIE:
		IMAGEMANAGER->findImage("frostydie")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_ATTACK:case ENEMY_LEFT_ATTACK:
		IMAGEMANAGER->findImage("frostyAttack")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_RIGHT_READY:case ENEMY_LEFT_READY:
		IMAGEMANAGER->findImage("frostyAttReady")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	case ENEMY_LEFT_DROPJUMP:case ENEMY_RIGHT_DROPJUMP:
		IMAGEMANAGER->findImage("frostyDropJump")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;
	}

	x = _Ice._iceRC.left - rcFocus.left;
	y = _Ice._iceRC.top - rcFocus.top;

	if (_state == ENEMY_RIGHT_READY || _state == ENEMY_LEFT_READY || _state == ENEMY_RIGHT_ATTACK || _state == ENEMY_LEFT_ATTACK)
		if (_Ice._bFire)
			_Ice._iceImage->render(getMemDC(), _Ice._iceRC.left, _Ice._iceRC.top);
}

void Frosty::moveDash()
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
		enemyBase::Dash(250, 3, ENEMY_LEFT_STOP);
	else if (_state == ENEMY_LEFT_DASH)
		enemyBase::Dash(250, 3, ENEMY_RIGHT_STOP);
}

void Frosty::attack()
{
	if (_state == ENEMY_LEFT_STOP)
		_state = ENEMY_LEFT_READY;
	if (_state == ENEMY_RIGHT_STOP)
		_state = ENEMY_RIGHT_READY;

}

void Frosty::dropJump()
{
	if (_state == ENEMY_LEFT_STOP)
		_state = ENEMY_LEFT_DROPJUMP;
	if (_state == ENEMY_RIGHT_STOP)
		_state = ENEMY_RIGHT_DROPJUMP;
	_fSpeed = BOSS_SPEED * 2;
	enemyBase::Followjump();
	_fSpeed = BOSS_SPEED;
	_Drop = false;

	if (_y > _startY)
	{
		_y = _startY;
		_jumpPower = BOSS_JUMPPOWER;
		++_dropJumpCount;
		_currentFrameX = 0;
		_count = 0;
		_Drop = true;
	}

	if (_dropJumpCount >= 3)
	{
		if (_x > WINSIZEX / 2)
			_state = ENEMY_LEFT_STOP;
		else
			_state = ENEMY_RIGHT_STOP;

		_jumpCount = 0;
		_jumpPower = BOSS_JUMPPOWER;
		_motionCount = 0;
		_currentFrameX;
		_randMotion = 0;
		_dropJumpCount = 0;
		_Drop = false;
	}
}

void Frosty::Jump()
{
	_state = ENEMY_UP_JUMP;
	enemyBase::jump();

	if (_y > _startY)
	{
		_y = _startY;
		_jumpPower = BOSS_JUMPPOWER;
		++_jumpCount;
	}

	if (_jumpCount >= 3)
	{
		if (_x > WINSIZEX / 2)
			_state = ENEMY_LEFT_STOP;
		else
			_state = ENEMY_RIGHT_STOP;

		_jumpCount = 0;
		_motionCount = 0;
		_randMotion = 0;
	}
}

void Frosty::Fire()
{
	if (!_Ice._bFire)
	{
		_Ice._bFire = true;
		_Ice._speed = 250;
		_Ice._gravity = 20;
		_Ice._x = _x + cosf(_angle) * 25;
		_Ice._y = _y + -sinf(_angle) * 25;
		_Ice._iceRC = RectMake(_Ice._x, _Ice._y, 20, 20);

		if (_em->getKirby()->getRect().left < _x)
		{
			if (_em->getKirby()->getRect().bottom < 100)
				_Ice._angle = PI / 1.8;
			else if (_em->getKirby()->getRect().bottom < 200)
				_Ice._angle = PI / 1.6;
			else _Ice._angle = PI / 1.4;
		}
		else if (_em->getKirby()->getRect().left > _x)
		{
			if (_em->getKirby()->getRect().bottom < 100)
				_Ice._angle = PI / 3;
			else if (_em->getKirby()->getRect().bottom < 200)
				_Ice._angle = PI / 4;
			else _Ice._angle = PI / 6;
		}
	}
}

void Frosty::moveIce()
{
	if (_Ice._bFire)
	{
		_Ice._x += cosf(_Ice._angle) * _Ice._speed * TIMEMANAGER->getElapsedTime();
		_Ice._y += -sinf(_Ice._angle) * (_Ice._speed - _Ice._gravity) * TIMEMANAGER->getElapsedTime();

		if (_em->getKirby()->getRect().left < _x) _Ice._angle += 0.02;
		else _Ice._angle -= 0.02;

		_Ice._iceRC = RectMake(_Ice._x, _Ice._y, 20, 20);

		if (_Ice._iceRC.left < 0)
			_Ice._bFire = false;
		else if (_Ice._iceRC.right > WINSIZEX)
			_Ice._bFire = false;
		else if (_Ice._iceRC.top < 0)
			_Ice._bFire = false;
		else if (_Ice._iceRC.bottom > _y + _imageEnemy->getFrameHeight())
		{
			if (_em->getKirby()->getRect().left < _x)
				_Ice._angle = PI / 1.2;
			else _Ice._angle = PI / 8;
		}
	}
}

void Frosty::Collision()
{
	RECT _cRC;

	if (IntersectRect(&_cRC, &_em->getKirby()->getRect(), &_Ice._iceRC))
	{
		_em->getKirby()->hitDamage(1, _Ice._iceRC);
	}
}