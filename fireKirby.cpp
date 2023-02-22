#include "stdafx.h"
#include "fireKirby.h"
#include "kirby.h"
#include "enemyManager.h"

fireKirby::fireKirby()
{
}

fireKirby::~fireKirby()
{
}

HRESULT fireKirby::init()
{
	initImage();

	_kirby->setState(RIGHT_STOP);
	_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_STOP");
	_motion->start();

	_bullet.startCX = _bullet.cx = 0;
	_bullet.startCY = _bullet.cy = 0;
	_bullet.isAttackRight = true;
	_bullet.isFire = false;
	_bullet.isCollision = false;

	return S_OK;
}

void fireKirby::release()
{

}

void fireKirby::update()
{
	KEYANIMANAGER->update();
	moveBullet();
	checkCollision();
}

void fireKirby::render(RECT rcFocus)
{
	_rc = _kirby->getRect();
	RECT eatRC = _kirby->getEatRect();
	RECT enemyRC = _kirby->getEnemyRect();

	int x, y;
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rcFocus, &_rc))return;
	x = _rc.left - rcFocus.left;
	y = _rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), eatRC.left - rcFocus.left, eatRC.top - rcFocus.top,
			eatRC.left - rcFocus.left + (eatRC.right - eatRC.left),
			eatRC.top - rcFocus.top + (eatRC.bottom - eatRC.top));
	
		Rectangle(getMemDC(), x, y, x + (_rc.right - _rc.left), y + (_rc.bottom - _rc.top));

		Rectangle(getMemDC(), enemyRC.left - rcFocus.left, enemyRC.top - rcFocus.top,
			enemyRC.left - rcFocus.left + (enemyRC.right - enemyRC.left),
			enemyRC.top - rcFocus.top + (enemyRC.bottom - enemyRC.top));

		TCHAR str[100];
		sprintf(str, "LIFE : %d   HP : %d", _kirby->getLife(), _kirby->getHp());
		TextOut(getMemDC(), 500, 100, str, strlen(str));


	};

	_image->aniRender(getMemDC(), x, y, _motion);
	renderBullet(rcFocus);

}

void fireKirby::createBullet()
{

	_bullet.startCX = _bullet.cx = _kirby->getCenterX();
	_bullet.startCY = _bullet.cy = _kirby->getCenterY();
	_bullet.isFire = true;


	if (_kirby->getState() == LEFT_ATTACK)
	{
		_bullet.isAttackRight = false;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("불커비_LEFT_FIRE_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("불커비_FIRE_ATTACK");
		_bullet.bulletMotion->start();
	}
	else if (_kirby->getState() == RIGHT_ATTACK)
	{
		_bullet.isAttackRight = true;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FIRE_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("불커비_FIRE_ATTACK");
		_bullet.bulletMotion->start();
	}

	_bullet.rc = RectMakeCenter(_bullet.cx, _bullet.cy, _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());

}

void fireKirby::moveBullet()
{
	// ATTACK READY 모션 종료가 되면 ATTACK 실행
	if (_bullet.isFire && !_motion->isPlay() &&
		(_motion == KEYANIMANAGER->findAnimation("불커비_RIGHT_ATTACK_READY") ||
		_motion == KEYANIMANAGER->findAnimation("불커비_LEFT_ATTACK_READY")) )
	{
		// 오른쪽이면
		if (_bullet.isAttackRight)
		{
			_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_ATTACK");
			_bullet.bulletMotion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FIRE_ATTACK");
		}
		// 왼쪽이면
		else
		{
			_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_ATTACK");
			_bullet.bulletMotion = KEYANIMANAGER->findAnimation("불커비_LEFT_FIRE_ATTACK");
		}
		_motion->start();
		_bullet.bulletMotion->start();

	}

	if (_bullet.isFire && _motion == KEYANIMANAGER->findAnimation("불커비_RIGHT_ATTACK"))
	{
		// 오른쪽에 렉트 생성
		_bullet.rc = RectMakeCenter(_kirby->getRect().right + _bullet.image->getFrameWidth() / 2, _kirby->getCenterY(), _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}
	else if (_bullet.isFire && _motion == KEYANIMANAGER->findAnimation("불커비_LEFT_ATTACK"))
	{
		// 왼쪽에 렉트 생성
		_bullet.rc = RectMakeCenter(_kirby->getRect().left - _bullet.image->getFrameWidth() / 2, _kirby->getCenterY(), _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}
	// 불커비가 이제 공격안하면 지워줘야지
	else if (_bullet.isFire &&
		(_motion == KEYANIMANAGER->findAnimation("불커비_RIGHT_STOP") ||
		_motion == KEYANIMANAGER->findAnimation("불커비_LEFT_STOP")))
	{
		_bullet.isFire = false;
		_bullet.isCollision = false;
		_bullet.startCX = _bullet.startCY = _bullet.cx = _bullet.cy = 0;
		_bullet.rc = RectMakeCenter(0, 0, 0, 0);
		_bullet.bulletMotion->stop();
	}

}

void fireKirby::renderBullet(RECT rcFocus)
{
	int x = _bullet.rc.left - rcFocus.left;
	int y = _bullet.rc.top - rcFocus.top;

	if (_bullet.isFire && 
		(_motion == KEYANIMANAGER->findAnimation("불커비_RIGHT_ATTACK") ||
		_motion == KEYANIMANAGER->findAnimation("불커비_LEFT_ATTACK")))
	{
		if (_debug)
		{
			Rectangle(getMemDC(), x, y, x + (_bullet.rc.right - _bullet.rc.left), y + (_bullet.rc.bottom - _bullet.rc.top));
		}
		_bullet.image->aniRender(getMemDC(), x, y, _bullet.bulletMotion);

	}
}

void fireKirby::checkCollision()
{
	if (_bullet.isFire)
	{
		_em = _kirby->getEnemyManager();

		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRC(), &_bullet.rc))
			{
				_em->getVEnemy()[i]->hitDamage(2);
				_bullet.isCollision = true;
			}
		}

	}
}


void fireKirby::setMotion()
{

	STATE state = _kirby->getState();
	int aa = 0;
	switch (state)
	{
	case LEFT_STOP:
		_image = IMAGEMANAGER->findImage("불커비_STOP");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_STOP");
		_motion->start();
		break;
	case RIGHT_STOP:
		_image = IMAGEMANAGER->findImage("불커비_STOP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_STOP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_UP:
		_image = IMAGEMANAGER->findImage("불커비_LOW_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_LOW_STOP_UP");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_UP:
		_image = IMAGEMANAGER->findImage("불커비_LOW_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_LOW_STOP_UP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_LOW_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_LOW_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_LOW_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_LOW_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_UP:
		_image = IMAGEMANAGER->findImage("불커비_HIGH_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_HIGH_STOP_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_UP:
		_image = IMAGEMANAGER->findImage("불커비_HIGH_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_HIGH_STOP_UP");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_HIGH_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_HIGH_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_SIT:
		_image = IMAGEMANAGER->findImage("불커비_SIT");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_image = IMAGEMANAGER->findImage("불커비_SIT");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_SIT");
		_motion->start();
		break;
	case LEFT_LOW_SIT_DOWN:
		break;
	case RIGHT_LOW_SIT_DOWN:
		break;
	case LEFT_LOW_SIT_UP:
		break;
	case RIGHT_LOW_SIT_UP:
		break;
	case LEFT_HIGH_SIT_DOWN:
		break;
	case RIGHT_HIGH_SIT_DOWN:
		break;
	case LEFT_HIGH_SIT_UP:
		break;
	case RIGHT_HIGH_SIT_UP:
		break;
	case LEFT_MOVE:
		_image = IMAGEMANAGER->findImage("불커비_MOVE");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_MOVE");
		_motion->start();
		break;
	case RIGHT_MOVE:
		_image = IMAGEMANAGER->findImage("불커비_MOVE");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_MOVE");
		_motion->start();
		break;
	case LEFT_LOW_MOVE:
		break;
	case RIGHT_LOW_MOVE:
		break;
	case LEFT_HIGH_MOVE:
		break;
	case RIGHT_HIGH_MOVE:
		break;
	case LEFT_DASH:
		_image = IMAGEMANAGER->findImage("불커비_DASH");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_DASH");
		_motion->start();
		break;
	case RIGHT_DASH:
		_image = IMAGEMANAGER->findImage("불커비_DASH");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_DASH");
		_motion->start();
		break;
	case LEFT_FLY_EAT:
		_image = IMAGEMANAGER->findImage("불커비_FLY_EAT");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_image = IMAGEMANAGER->findImage("불커비_FLY_EAT");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_image = IMAGEMANAGER->findImage("불커비_FLY_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_image = IMAGEMANAGER->findImage("불커비_FLY_UP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_FLY_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_FLY_DOWN");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_image = IMAGEMANAGER->findImage("불커비_FLY");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_image = IMAGEMANAGER->findImage("불커비_FLY");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FLY");
		_motion->start();
		break;
	case LEFT_FLY_MOVE:
		break;
	case RIGHT_FLY_MOVE:
		break;
	case LEFT_JUMP_UP:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_JUMP_UP");
		_motion->start();
		break;
	case RIGHT_JUMP_UP:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_JUMP_UP");
		_motion->start();
		break;
	case LEFT_JUMP_TURN:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_JUMP_TURN");
		_motion->start();
		break;
	case RIGHT_JUMP_TURN:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_JUMP_TURN");
		_motion->start();
		break;
	case LEFT_JUMP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_JUMP_DOWN");
		_motion->start();
		break;
	case RIGHT_JUMP_DOWN:
		_image = IMAGEMANAGER->findImage("불커비_JUMP");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_JUMP_DOWN");
		_motion->start();
		break;
	case LEFT_KICK:
		_image = IMAGEMANAGER->findImage("불커비_KICK");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_image = IMAGEMANAGER->findImage("불커비_KICK");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_KICK");
		_motion->start();
		break;
	case LEFT_FALL:
		_image = IMAGEMANAGER->findImage("불커비_FALL");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_FALL");
		_motion->start();
		break;
	case RIGHT_FALL:
		_image = IMAGEMANAGER->findImage("불커비_FALL");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_FALL");
		_motion->start();
		break;
	case LEFT_ATTACK:
		_image = IMAGEMANAGER->findImage("불커비_ATTACK");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_ATTACK_READY");
		_motion->start();
		createBullet();
		break;
	case RIGHT_ATTACK:
		_image = IMAGEMANAGER->findImage("불커비_ATTACK");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_ATTACK_READY");
		_motion->start();
		createBullet();
		break;
	case LEFT_RETURN:
		break;
	case RIGHT_RETURN:
		break;
	case LEFT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("노말커비_LEFT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("노말커비_COLLISION");
		_motion->start();
		break;
	case RIGHT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("노말커비_RIGHT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("노말커비_COLLISION");
		_motion->start();
		break;
	case LEFT_TURN:
		break;
	case RIGHT_TURN:
		break;
	case LEFT_OPEN_DOOR:
		_image = IMAGEMANAGER->findImage("불커비_OPENDOOR");
		_motion = KEYANIMANAGER->findAnimation("불커비_LEFT_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_image = IMAGEMANAGER->findImage("불커비_OPENDOOR");
		_motion = KEYANIMANAGER->findAnimation("불커비_RIGHT_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}

}

void fireKirby::initImage()
{
	// 이미지 추가

	// STOP
	_image = IMAGEMANAGER->addFrameImage("불커비_STOP", "image\\characters\\kirby\\불커비\\fireKirby_idle_평지.bmp", 232 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_STOP_UP", "image\\characters\\kirby\\불커비\\fireKirby_idle_높은언덕_올라갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_STOP_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_idle_높은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_STOP_UP", "image\\characters\\kirby\\불커비\\fireKirby_idle_낮은언덕_올라갈때.bmp", 232 * 2, 70 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_STOP_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_idle_낮은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// MOVE
	IMAGEMANAGER->addFrameImage("불커비_MOVE", "image\\characters\\kirby\\불커비\\fireKirby_walk.bmp", 580 * 2, 78 * 2, 20, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_STOP_UP", "image\\characters\\kirby\\불커비\\fireKirby_idle_높은언덕_올라갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_STOP_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_idle_높은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_STOP_UP", "image\\characters\\kirby\\불커비\\fireKirby_idle_낮은언덕_올라갈때.bmp", 232 * 2, 70 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_STOP_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_idle_낮은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// SIT
	IMAGEMANAGER->addFrameImage("불커비_SIT", "image\\characters\\kirby\\불커비\\fireKirby_down_평지.bmp", 232 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_SIT_UP", "image\\characters\\kirby\\불커비\\fireKirby_down_높은언덕_올라갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_HIGH_SIT_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_down_높은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_SIT_UP", "image\\characters\\kirby\\불커비\\fireKirby_down_낮은언덕_올라갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_LOW_SIT_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_down_낮은언덕_내려갈때.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// JUMP
	IMAGEMANAGER->addFrameImage("불커비_JUMP", "image\\characters\\kirby\\불커비\\fireKirby_jump.bmp", 352 * 2, 82 * 2, 11, 2, true, RGB(255, 0, 255));

	// DASH
	IMAGEMANAGER->addFrameImage("불커비_DASH", "image\\characters\\kirby\\불커비\\fireKirby_dash.bmp", 352 * 2, 76 * 2, 8, 2, true, RGB(255, 0, 255));

	// FLY
	IMAGEMANAGER->addFrameImage("불커비_FLY_EAT", "image\\characters\\kirby\\불커비\\fireKirby_fly_eat.bmp", 160 * 2, 80 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_FLY", "image\\characters\\kirby\\불커비\\fireKirby_fly.bmp", 480 * 2, 88 * 2, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_FLY_UP", "image\\characters\\kirby\\불커비\\fireKirby_fly_up.bmp", 256 * 2, 88 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불커비_FLY_DOWN", "image\\characters\\kirby\\불커비\\fireKirby_fly_down.bmp", 192 * 2, 88 * 2, 6, 2, true, RGB(255, 0, 255));

	// KICK
	IMAGEMANAGER->addFrameImage("불커비_KICK", "image\\characters\\kirby\\불커비\\fireKirby_tackle.bmp", 230 * 2, 74 * 2, 5, 2, true, RGB(255, 0, 255));

	// FALL
	IMAGEMANAGER->addFrameImage("불커비_FALL", "image\\characters\\kirby\\불커비\\fireKirby_fall.bmp", 513 * 2, 82 * 2, 19, 2, true, RGB(255, 0, 255));

	// OPEN DOOR
	IMAGEMANAGER->addFrameImage("불커비_OPENDOOR", "image\\characters\\kirby\\불커비\\fireKirby_enter_door.bmp", 104 * 2, 74 * 2, 4, 2, true, RGB(255, 0, 255));

	// ATTACK
	IMAGEMANAGER->addFrameImage("불커비_ATTACK", "image\\characters\\kirby\\불커비\\fireKirby_attack.bmp", 408 * 2, 76 * 2, 12, 2, true, RGB(255, 0, 255));

	// FIRE ATTACK
	_bullet.image = IMAGEMANAGER->addFrameImage("불커비_FIRE_ATTACK", "image\\characters\\kirby\\불커비\\fireKirby_fire_attack.bmp", 416 * 2, 64 * 2, 13, 2, true, RGB(255, 0, 255));



	// 키 애니메이션 추가

	// STOP
	int arrFireKirbyRightStop[] = { 0,1,2,3,0,1,2,3,0,1,2,3, 0,1,2,3,4,5,6,7,0,1,2,3 };
	int arrFireKirbyLeftStop[] = { 15,14,13,12,15,14,13,12,15,14,13,12,15,14,13,12,11,10,9,8,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_STOP", "불커비_STOP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_STOP", "불커비_STOP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_HIGH_STOP_UP", "불커비_HIGH_STOP_UP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_HIGH_STOP_UP", "불커비_HIGH_STOP_UP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_HIGH_STOP_DOWN", "불커비_HIGH_STOP_DOWN", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_HIGH_STOP_DOWN", "불커비_HIGH_STOP_DOWN", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_LOW_STOP_UP", "불커비_LOW_STOP_UP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_LOW_STOP_UP", "불커비_LOW_STOP_UP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_LOW_STOP_DOWN", "불커비_LOW_STOP_DOWN", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_LOW_STOP_DOWN", "불커비_LOW_STOP_DOWN", arrFireKirbyLeftStop, 24, 20, true);

	// MOVE
	int arrFireKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	int arrFireKirbyLeftMove[] = { 39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_MOVE", "불커비_MOVE", arrFireKirbyRightMove, 20, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_MOVE", "불커비_MOVE", arrFireKirbyLeftMove, 20, 20, true);

	// SIT
	int arrFireKirbyRightSit[] = { 0,1,2,3,0,1,2,3,0,1,2,3, 0,1,2,3,4,5,6,7,0,1,2,3 };
	int arrFireKirbyLeftSit[] = { 15,14,13,12,15,14,13,12,15,14,13,12,15,14,13,12,11,10,9,8,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_SIT", "불커비_SIT", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_SIT", "불커비_SIT", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_HIGH_SIT_UP", "불커비_HIGH_SIT_UP", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_HIGH_SIT_UP", "불커비_HIGH_SIT_UP", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_HIGH_SIT_DOWN", "불커비_HIGH_SIT_DOWN", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_HIGH_SIT_DOWN", "불커비_HIGH_SIT_DOWN", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_LOW_SIT_UP", "불커비_LOW_SIT_UP", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_LOW_SIT_UP", "불커비_LOW_SIT_UP", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_LOW_SIT_DOWN", "불커비_LOW_SIT_DOWN", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_LOW_STOP_DOWN", "불커비_LOW_SIT_DOWN", arrFireKirbyLeftSit, 24, 20, true);

	// 불 커비 JUMP UP
	int arrFireKirbyRightJumpUp[] = { 0,1 };
	int arrFireKirbyLefttJumpUp[] = { 21,20 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_JUMP_UP", "불커비_JUMP", arrFireKirbyRightJumpUp, 2, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_JUMP_UP", "불커비_JUMP", arrFireKirbyLefttJumpUp, 2, 22, true);

	// 불 커비 JUMP TURN
	int arrFireKirbyRightJumpTurn[] = { 2,3,4,5,6,7,8,9 };
	int arrFireKirbyLeftJumpTurn[] = { 19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_JUMP_TURN", "불커비_JUMP", arrFireKirbyRightJumpTurn, 8, 35, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_JUMP_TURN", "불커비_JUMP", arrFireKirbyLeftJumpTurn, 8, 35, false);

	// 불 커비 JUMP DOWN
	int arrFireKirbyRightJumpDown[] = { 10,10 };
	int arrFireKirbyLeftJumpDown[] = { 11,11 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_JUMP_DOWN", "불커비_JUMP", arrFireKirbyRightJumpDown, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_JUMP_DOWN", "불커비_JUMP", arrFireKirbyLeftJumpDown, 2, 22, false);

	// 불 커비 DASH
	int arrFireKirbuRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrFireKirbuLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_DASH", "불커비_DASH", arrFireKirbuRightDash, 8, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_DASH", "불커비_DASH", arrFireKirbuLeftDash, 8, 33, true);

	// 불 커비 FLY EAT ( 바람을빨아들인다 )
	int arrFireKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrFireKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FLY_EAT", "불커비_FLY_EAT", arrFireKirbyRightFlyEat, 5, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FLY_EAT", "불커비_FLY_EAT", arrFireKirbyLeftFlyEat, 5, 22, false);

	// 불 커비 FLY (L / R)
	int arrFireKirbyRightFly[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int arrFireKirbyLeftFly[] = { 29,28,27,26,25,24,23,22,21,20,19,18,17,16,15 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FLY", "불커비_FLY", arrFireKirbyRightFly, 15, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FLY", "불커비_FLY", arrFireKirbyLeftFly, 15, 22, true);

	// 불 커비 FlY UP (L / R)
	int arrFireKirbyRightFlyUp[] = { 0,1,2,3,4,5,6,7 };
	int arrFireKirbyLeftFlyUp[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FLY_UP", "불커비_FLY_UP", arrFireKirbyRightFlyUp, 8, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FLY_UP", "불커비_FLY_UP", arrFireKirbyLeftFlyUp, 8, 12, true);

	// 불 커비 FLY DOWN (L / R)
	int arrFireKirbyRightFlyDown[] = { 0,1,2,3,4,5 };
	int arrFireKirbyLeftFlyDown[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FLY_DOWN", "불커비_FLY_DOWN", arrFireKirbyRightFlyDown, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FLY_DOWN", "불커비_FLY_DOWN", arrFireKirbyLeftFlyDown, 6, 9, true);

	// 불 커비 KICK
	int arrFireKirbyRightKick[] = { 0,1,2,3,4 };
	int arrFireKirbyLeftKick[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_KICK", "불커비_KICK", arrFireKirbyRightKick, 5, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_KICK", "불커비_KICK", arrFireKirbyLeftKick, 5, 12, false);

	// 불 커비 FALL
	int arrFireKirbyRightFall[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	int arrFireKirbyLeftFall[] = { 37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FALL", "불커비_FALL", arrFireKirbyRightFall, 19, 28, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FALL", "불커비_FALL", arrFireKirbyLeftFall, 19, 28, false);

	// 불 커비 OPENDOOR
	int arrFireKirbyRightOpenDoor[] = { 0,1,2,3 };
	int arrFireKirbyLeftOpenDoor[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_OPENDOOR", "불커비_OPENDOOR", arrFireKirbyRightOpenDoor, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_OPENDOOR", "불커비_OPENDOOR", arrFireKirbyLeftOpenDoor, 4, 22, false);
	
	// 불 커비 ATTACK READY ( 장전 )
	int arrFireKirbyRightAttackReady[] = { 0,1,2,3,4,5 };
	int arrFireKirbyLeftAttackReady[] = { 23,22,21,20,19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_ATTACK_READY", "불커비_ATTACK", arrFireKirbyRightAttackReady, 6, 18, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_ATTACK_READY", "불커비_ATTACK", arrFireKirbyLeftAttackReady, 6, 18, false);
	
	// 불 커비 ATTACK ( 발사 )
	int arrFireKirbyRightAttackStart[] = { 6,7,8,9 };
	int arrFireKirbyLeftAttackStart[] = { 17,16,15,14 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_ATTACK", "불커비_ATTACK", arrFireKirbyRightAttackStart, 4, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_ATTACK", "불커비_ATTACK", arrFireKirbyLeftAttackStart, 4, 22, true);

	// 불 커비 ATTACK END ( 종료 )
	int arrFireKirbyRightAttackEnd[] = { 10,11 };
	int arrFireKirbyLeftAttackEnd[] = { 13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_ATTACK_END", "불커비_ATTACK", arrFireKirbyRightAttackEnd, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_ATTACK_END", "불커비_ATTACK", arrFireKirbyLeftAttackEnd, 2, 22, false);
	
	// 불 커비 FIRE ATTACK
	int arrFireKirbyRightFireAttack[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	int arrFireKirbyLeftFireAttack[] = { 25,24,23,22,21,20,19,18,17,16,15,14,13 };
	KEYANIMANAGER->addArrayFrameAnimation("불커비_RIGHT_FIRE_ATTACK", "불커비_FIRE_ATTACK", arrFireKirbyRightFireAttack, 13, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("불커비_LEFT_FIRE_ATTACK", "불커비_FIRE_ATTACK", arrFireKirbyLeftFireAttack, 13, 22, true);


}
