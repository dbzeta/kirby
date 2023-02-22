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
	_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_STOP");
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
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FIRE_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("��Ŀ��_FIRE_ATTACK");
		_bullet.bulletMotion->start();
	}
	else if (_kirby->getState() == RIGHT_ATTACK)
	{
		_bullet.isAttackRight = true;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FIRE_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("��Ŀ��_FIRE_ATTACK");
		_bullet.bulletMotion->start();
	}

	_bullet.rc = RectMakeCenter(_bullet.cx, _bullet.cy, _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());

}

void fireKirby::moveBullet()
{
	// ATTACK READY ��� ���ᰡ �Ǹ� ATTACK ����
	if (_bullet.isFire && !_motion->isPlay() &&
		(_motion == KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK_READY") ||
		_motion == KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK_READY")) )
	{
		// �������̸�
		if (_bullet.isAttackRight)
		{
			_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK");
			_bullet.bulletMotion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FIRE_ATTACK");
		}
		// �����̸�
		else
		{
			_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK");
			_bullet.bulletMotion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FIRE_ATTACK");
		}
		_motion->start();
		_bullet.bulletMotion->start();

	}

	if (_bullet.isFire && _motion == KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK"))
	{
		// �����ʿ� ��Ʈ ����
		_bullet.rc = RectMakeCenter(_kirby->getRect().right + _bullet.image->getFrameWidth() / 2, _kirby->getCenterY(), _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}
	else if (_bullet.isFire && _motion == KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK"))
	{
		// ���ʿ� ��Ʈ ����
		_bullet.rc = RectMakeCenter(_kirby->getRect().left - _bullet.image->getFrameWidth() / 2, _kirby->getCenterY(), _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}
	// ��Ŀ�� ���� ���ݾ��ϸ� ���������
	else if (_bullet.isFire &&
		(_motion == KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_STOP") ||
		_motion == KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_STOP")))
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
		(_motion == KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK") ||
		_motion == KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK")))
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
		_image = IMAGEMANAGER->findImage("��Ŀ��_STOP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_STOP");
		_motion->start();
		break;
	case RIGHT_STOP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_STOP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_STOP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_UP");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_UP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_UP");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_SIT:
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_SIT");
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
		_image = IMAGEMANAGER->findImage("��Ŀ��_MOVE");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_MOVE");
		_motion->start();
		break;
	case RIGHT_MOVE:
		_image = IMAGEMANAGER->findImage("��Ŀ��_MOVE");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_MOVE");
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
		_image = IMAGEMANAGER->findImage("��Ŀ��_DASH");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_DASH");
		_motion->start();
		break;
	case RIGHT_DASH:
		_image = IMAGEMANAGER->findImage("��Ŀ��_DASH");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_DASH");
		_motion->start();
		break;
	case LEFT_FLY_EAT:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_EAT");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_EAT");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_UP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_DOWN");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY");
		_motion->start();
		break;
	case LEFT_FLY_MOVE:
		break;
	case RIGHT_FLY_MOVE:
		break;
	case LEFT_JUMP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_UP");
		_motion->start();
		break;
	case RIGHT_JUMP_UP:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_UP");
		_motion->start();
		break;
	case LEFT_JUMP_TURN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_TURN");
		_motion->start();
		break;
	case RIGHT_JUMP_TURN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_TURN");
		_motion->start();
		break;
	case LEFT_JUMP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_DOWN");
		_motion->start();
		break;
	case RIGHT_JUMP_DOWN:
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_DOWN");
		_motion->start();
		break;
	case LEFT_KICK:
		_image = IMAGEMANAGER->findImage("��Ŀ��_KICK");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_image = IMAGEMANAGER->findImage("��Ŀ��_KICK");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_KICK");
		_motion->start();
		break;
	case LEFT_FALL:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FALL");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FALL");
		_motion->start();
		break;
	case RIGHT_FALL:
		_image = IMAGEMANAGER->findImage("��Ŀ��_FALL");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FALL");
		_motion->start();
		break;
	case LEFT_ATTACK:
		_image = IMAGEMANAGER->findImage("��Ŀ��_ATTACK");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK_READY");
		_motion->start();
		createBullet();
		break;
	case RIGHT_ATTACK:
		_image = IMAGEMANAGER->findImage("��Ŀ��_ATTACK");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK_READY");
		_motion->start();
		createBullet();
		break;
	case LEFT_RETURN:
		break;
	case RIGHT_RETURN:
		break;
	case LEFT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_COLLISION");
		_motion->start();
		break;
	case RIGHT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_COLLISION");
		_motion->start();
		break;
	case LEFT_TURN:
		break;
	case RIGHT_TURN:
		break;
	case LEFT_OPEN_DOOR:
		_image = IMAGEMANAGER->findImage("��Ŀ��_OPENDOOR");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_image = IMAGEMANAGER->findImage("��Ŀ��_OPENDOOR");
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}

}

void fireKirby::initImage()
{
	// �̹��� �߰�

	// STOP
	_image = IMAGEMANAGER->addFrameImage("��Ŀ��_STOP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_����.bmp", 232 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_�ö󰥶�.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_�ö󰥶�.bmp", 232 * 2, 70 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// MOVE
	IMAGEMANAGER->addFrameImage("��Ŀ��_MOVE", "image\\characters\\kirby\\��Ŀ��\\fireKirby_walk.bmp", 580 * 2, 78 * 2, 20, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_�ö󰥶�.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_�ö󰥶�.bmp", 232 * 2, 70 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_idle_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// SIT
	IMAGEMANAGER->addFrameImage("��Ŀ��_SIT", "image\\characters\\kirby\\��Ŀ��\\fireKirby_down_����.bmp", 232 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_SIT_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_down_�������_�ö󰥶�.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_SIT_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_down_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_SIT_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_down_�������_�ö󰥶�.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_SIT_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_down_�������_��������.bmp", 216 * 2, 72 * 2, 8, 2, true, RGB(255, 0, 255));

	// JUMP
	IMAGEMANAGER->addFrameImage("��Ŀ��_JUMP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_jump.bmp", 352 * 2, 82 * 2, 11, 2, true, RGB(255, 0, 255));

	// DASH
	IMAGEMANAGER->addFrameImage("��Ŀ��_DASH", "image\\characters\\kirby\\��Ŀ��\\fireKirby_dash.bmp", 352 * 2, 76 * 2, 8, 2, true, RGB(255, 0, 255));

	// FLY
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_EAT", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fly_eat.bmp", 160 * 2, 80 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fly.bmp", 480 * 2, 88 * 2, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_UP", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fly_up.bmp", 256 * 2, 88 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_DOWN", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fly_down.bmp", 192 * 2, 88 * 2, 6, 2, true, RGB(255, 0, 255));

	// KICK
	IMAGEMANAGER->addFrameImage("��Ŀ��_KICK", "image\\characters\\kirby\\��Ŀ��\\fireKirby_tackle.bmp", 230 * 2, 74 * 2, 5, 2, true, RGB(255, 0, 255));

	// FALL
	IMAGEMANAGER->addFrameImage("��Ŀ��_FALL", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fall.bmp", 513 * 2, 82 * 2, 19, 2, true, RGB(255, 0, 255));

	// OPEN DOOR
	IMAGEMANAGER->addFrameImage("��Ŀ��_OPENDOOR", "image\\characters\\kirby\\��Ŀ��\\fireKirby_enter_door.bmp", 104 * 2, 74 * 2, 4, 2, true, RGB(255, 0, 255));

	// ATTACK
	IMAGEMANAGER->addFrameImage("��Ŀ��_ATTACK", "image\\characters\\kirby\\��Ŀ��\\fireKirby_attack.bmp", 408 * 2, 76 * 2, 12, 2, true, RGB(255, 0, 255));

	// FIRE ATTACK
	_bullet.image = IMAGEMANAGER->addFrameImage("��Ŀ��_FIRE_ATTACK", "image\\characters\\kirby\\��Ŀ��\\fireKirby_fire_attack.bmp", 416 * 2, 64 * 2, 13, 2, true, RGB(255, 0, 255));



	// Ű �ִϸ��̼� �߰�

	// STOP
	int arrFireKirbyRightStop[] = { 0,1,2,3,0,1,2,3,0,1,2,3, 0,1,2,3,4,5,6,7,0,1,2,3 };
	int arrFireKirbyLeftStop[] = { 15,14,13,12,15,14,13,12,15,14,13,12,15,14,13,12,11,10,9,8,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_STOP", "��Ŀ��_STOP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_STOP", "��Ŀ��_STOP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_STOP_UP", "��Ŀ��_HIGH_STOP_UP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_STOP_UP", "��Ŀ��_HIGH_STOP_UP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_STOP_DOWN", "��Ŀ��_HIGH_STOP_DOWN", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_STOP_DOWN", "��Ŀ��_HIGH_STOP_DOWN", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_STOP_UP", "��Ŀ��_LOW_STOP_UP", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_STOP_UP", "��Ŀ��_LOW_STOP_UP", arrFireKirbyLeftStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_STOP_DOWN", "��Ŀ��_LOW_STOP_DOWN", arrFireKirbyRightStop, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_STOP_DOWN", "��Ŀ��_LOW_STOP_DOWN", arrFireKirbyLeftStop, 24, 20, true);

	// MOVE
	int arrFireKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	int arrFireKirbyLeftMove[] = { 39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_MOVE", "��Ŀ��_MOVE", arrFireKirbyRightMove, 20, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_MOVE", "��Ŀ��_MOVE", arrFireKirbyLeftMove, 20, 20, true);

	// SIT
	int arrFireKirbyRightSit[] = { 0,1,2,3,0,1,2,3,0,1,2,3, 0,1,2,3,4,5,6,7,0,1,2,3 };
	int arrFireKirbyLeftSit[] = { 15,14,13,12,15,14,13,12,15,14,13,12,15,14,13,12,11,10,9,8,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_SIT", "��Ŀ��_SIT", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_SIT", "��Ŀ��_SIT", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_SIT_UP", "��Ŀ��_HIGH_SIT_UP", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_SIT_UP", "��Ŀ��_HIGH_SIT_UP", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_SIT_DOWN", "��Ŀ��_HIGH_SIT_DOWN", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_SIT_DOWN", "��Ŀ��_HIGH_SIT_DOWN", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_SIT_UP", "��Ŀ��_LOW_SIT_UP", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_SIT_UP", "��Ŀ��_LOW_SIT_UP", arrFireKirbyLeftSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_SIT_DOWN", "��Ŀ��_LOW_SIT_DOWN", arrFireKirbyRightSit, 24, 20, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_STOP_DOWN", "��Ŀ��_LOW_SIT_DOWN", arrFireKirbyLeftSit, 24, 20, true);

	// �� Ŀ�� JUMP UP
	int arrFireKirbyRightJumpUp[] = { 0,1 };
	int arrFireKirbyLefttJumpUp[] = { 21,20 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_UP", "��Ŀ��_JUMP", arrFireKirbyRightJumpUp, 2, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_UP", "��Ŀ��_JUMP", arrFireKirbyLefttJumpUp, 2, 22, true);

	// �� Ŀ�� JUMP TURN
	int arrFireKirbyRightJumpTurn[] = { 2,3,4,5,6,7,8,9 };
	int arrFireKirbyLeftJumpTurn[] = { 19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_TURN", "��Ŀ��_JUMP", arrFireKirbyRightJumpTurn, 8, 35, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_TURN", "��Ŀ��_JUMP", arrFireKirbyLeftJumpTurn, 8, 35, false);

	// �� Ŀ�� JUMP DOWN
	int arrFireKirbyRightJumpDown[] = { 10,10 };
	int arrFireKirbyLeftJumpDown[] = { 11,11 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_DOWN", "��Ŀ��_JUMP", arrFireKirbyRightJumpDown, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_DOWN", "��Ŀ��_JUMP", arrFireKirbyLeftJumpDown, 2, 22, false);

	// �� Ŀ�� DASH
	int arrFireKirbuRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrFireKirbuLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_DASH", "��Ŀ��_DASH", arrFireKirbuRightDash, 8, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_DASH", "��Ŀ��_DASH", arrFireKirbuLeftDash, 8, 33, true);

	// �� Ŀ�� FLY EAT ( �ٶ������Ƶ��δ� )
	int arrFireKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrFireKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_EAT", "��Ŀ��_FLY_EAT", arrFireKirbyRightFlyEat, 5, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_EAT", "��Ŀ��_FLY_EAT", arrFireKirbyLeftFlyEat, 5, 22, false);

	// �� Ŀ�� FLY (L / R)
	int arrFireKirbyRightFly[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int arrFireKirbyLeftFly[] = { 29,28,27,26,25,24,23,22,21,20,19,18,17,16,15 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY", "��Ŀ��_FLY", arrFireKirbyRightFly, 15, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY", "��Ŀ��_FLY", arrFireKirbyLeftFly, 15, 22, true);

	// �� Ŀ�� FlY UP (L / R)
	int arrFireKirbyRightFlyUp[] = { 0,1,2,3,4,5,6,7 };
	int arrFireKirbyLeftFlyUp[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_UP", "��Ŀ��_FLY_UP", arrFireKirbyRightFlyUp, 8, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_UP", "��Ŀ��_FLY_UP", arrFireKirbyLeftFlyUp, 8, 12, true);

	// �� Ŀ�� FLY DOWN (L / R)
	int arrFireKirbyRightFlyDown[] = { 0,1,2,3,4,5 };
	int arrFireKirbyLeftFlyDown[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_DOWN", "��Ŀ��_FLY_DOWN", arrFireKirbyRightFlyDown, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_DOWN", "��Ŀ��_FLY_DOWN", arrFireKirbyLeftFlyDown, 6, 9, true);

	// �� Ŀ�� KICK
	int arrFireKirbyRightKick[] = { 0,1,2,3,4 };
	int arrFireKirbyLeftKick[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_KICK", "��Ŀ��_KICK", arrFireKirbyRightKick, 5, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_KICK", "��Ŀ��_KICK", arrFireKirbyLeftKick, 5, 12, false);

	// �� Ŀ�� FALL
	int arrFireKirbyRightFall[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	int arrFireKirbyLeftFall[] = { 37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FALL", "��Ŀ��_FALL", arrFireKirbyRightFall, 19, 28, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FALL", "��Ŀ��_FALL", arrFireKirbyLeftFall, 19, 28, false);

	// �� Ŀ�� OPENDOOR
	int arrFireKirbyRightOpenDoor[] = { 0,1,2,3 };
	int arrFireKirbyLeftOpenDoor[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_OPENDOOR", "��Ŀ��_OPENDOOR", arrFireKirbyRightOpenDoor, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_OPENDOOR", "��Ŀ��_OPENDOOR", arrFireKirbyLeftOpenDoor, 4, 22, false);
	
	// �� Ŀ�� ATTACK READY ( ���� )
	int arrFireKirbyRightAttackReady[] = { 0,1,2,3,4,5 };
	int arrFireKirbyLeftAttackReady[] = { 23,22,21,20,19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_ATTACK_READY", "��Ŀ��_ATTACK", arrFireKirbyRightAttackReady, 6, 18, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_ATTACK_READY", "��Ŀ��_ATTACK", arrFireKirbyLeftAttackReady, 6, 18, false);
	
	// �� Ŀ�� ATTACK ( �߻� )
	int arrFireKirbyRightAttackStart[] = { 6,7,8,9 };
	int arrFireKirbyLeftAttackStart[] = { 17,16,15,14 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_ATTACK", "��Ŀ��_ATTACK", arrFireKirbyRightAttackStart, 4, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_ATTACK", "��Ŀ��_ATTACK", arrFireKirbyLeftAttackStart, 4, 22, true);

	// �� Ŀ�� ATTACK END ( ���� )
	int arrFireKirbyRightAttackEnd[] = { 10,11 };
	int arrFireKirbyLeftAttackEnd[] = { 13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_ATTACK_END", "��Ŀ��_ATTACK", arrFireKirbyRightAttackEnd, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_ATTACK_END", "��Ŀ��_ATTACK", arrFireKirbyLeftAttackEnd, 2, 22, false);
	
	// �� Ŀ�� FIRE ATTACK
	int arrFireKirbyRightFireAttack[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	int arrFireKirbyLeftFireAttack[] = { 25,24,23,22,21,20,19,18,17,16,15,14,13 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FIRE_ATTACK", "��Ŀ��_FIRE_ATTACK", arrFireKirbyRightFireAttack, 13, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FIRE_ATTACK", "��Ŀ��_FIRE_ATTACK", arrFireKirbyLeftFireAttack, 13, 22, true);


}
