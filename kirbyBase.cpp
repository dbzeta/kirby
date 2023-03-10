#include "stdafx.h"
#include "kirbyBase.h"
#include "kirby.h"
#include "enemyManager.h"


kirbyBase::kirbyBase()
{
}


kirbyBase::~kirbyBase()
{
}

HRESULT kirbyBase::init()
{

	initImage();

	_kirby->setState(RIGHT_STOP);
	_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_STOP");
	_motion->start();

	_bullet.startCX = _bullet.cx = 0;
	_bullet.startCY = _bullet.cy = 0;
	_bullet.isAttackRight = true;
	_bullet.isFire = false;
	_bullet.isCollision = false;


	return S_OK;
}

void kirbyBase::release()
{
}

void kirbyBase::update()
{
	KEYANIMANAGER->update();
	checkCollision();
	moveBullet();

}

void kirbyBase::render(RECT rcFocus)
{
	_rc = _kirby->getRect();
	RECT eatRC = _kirby->getEatRect();
	RECT enemyRC = _kirby->getEnemyRect();


	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rcFocus, &_rc))return;
	_defaultX = _rc.left - rcFocus.left;
	_defaultY = _rc.top - rcFocus.top;

	if (_debug)
	{
		Rectangle(getMemDC(), eatRC.left - rcFocus.left, eatRC.top - rcFocus.top,
			eatRC.left - rcFocus.left + (eatRC.right - eatRC.left),
			eatRC.top - rcFocus.top + (eatRC.bottom - eatRC.top));

		Rectangle(getMemDC(), _defaultX, _defaultY, _defaultX + (_rc.right - _rc.left), _defaultY + (_rc.bottom - _rc.top));

		Rectangle(getMemDC(), enemyRC.left - rcFocus.left, enemyRC.top - rcFocus.top,
			enemyRC.left - rcFocus.left + (enemyRC.right - enemyRC.left),
			enemyRC.top - rcFocus.top + (enemyRC.bottom - enemyRC.top));

		TCHAR str[100];
		sprintf(str, "LIFE : %d   HP : %d", _kirby->getLife(), _kirby->getHp());
		TextOut(getMemDC(), 500, 100, str, strlen(str));

	}

	_image->aniRender(getMemDC(), _defaultX, _defaultY, _motion);
	
	renderBullet(rcFocus);

}


void kirbyBase::createBullet()
{

	_bullet.startCX = _bullet.cx = _kirby->getCenterX();
	_bullet.startCY = _bullet.cy = _kirby->getCenterY();
	_bullet.isFire = true;


	if (_kirby->getState() == LEFT_THROW)
	{
		_bullet.isAttackRight = false;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_STAR_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("畴富目厚_STAR_ATTACK");
		_bullet.bulletMotion->start();
	}
	else if (_kirby->getState() == RIGHT_THROW)
	{
		_bullet.isAttackRight = true;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_STAR_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("畴富目厚_STAR_ATTACK");
		_bullet.bulletMotion->start();
	}

	_bullet.rc = RectMakeCenter(_bullet.cx, _bullet.cy, _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());

}

void kirbyBase::moveBullet()
{

	if (_bullet.isFire && _bullet.isAttackRight)
	{
		_bullet.cx += 5;
		_bullet.rc = RectMakeCenter(_bullet.cx, _bullet.cy, _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}
	else if(_bullet.isFire && !_bullet.isAttackRight)
	{
		_bullet.cx -= 5;
		_bullet.rc = RectMakeCenter(_bullet.cx, _bullet.cy, _bullet.image->getFrameWidth(), _bullet.image->getFrameHeight());
	}

	// 荤芭府甫 逞绢啊芭唱 面倒 (利 捞尔 何婬闷阑锭)捞搁 檬扁拳
	if (abs(_bullet.startCX - _bullet.cx) > 250 || _bullet.isCollision)
	{
		_bullet.bulletMotion->stop();
		_bullet.startCX = _bullet.startCY = _bullet.cx = _bullet.cy = 0;
		_bullet.rc = RectMakeCenter(0, 0, 0, 0);
		_bullet.isFire = false;
		_bullet.isCollision = false;
	}

}

void kirbyBase::renderBullet(RECT rcFocus)
{
	int x = _bullet.rc.left - rcFocus.left;
	int y = _bullet.rc.top - rcFocus.top;

	if (_bullet.isFire)
	{
		if (_debug)
		{
			Rectangle(getMemDC(), x, y, x + (_bullet.rc.right - _bullet.rc.left), y + (_bullet.rc.bottom - _bullet.rc.top));
		}
		_bullet.image->aniRender(getMemDC(), x, y, _bullet.bulletMotion);
		
	}
}

void kirbyBase::checkCollision()
{
	if (_bullet.isFire)
	{
		_em = _kirby->getEnemyManager();

		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			if (_em->getVEnemy()[i]->getDie()) continue;

			int a = _em->getVEnemy().size();
			RECT temp;
			if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRC(), &_bullet.rc))
			{
				_em->getVEnemy()[i]->hitDamage(2);
				_bullet.isCollision = true;
			}
		}

	}
}


void kirbyBase::setMotion()
{
	STATE state = _kirby->getState();

	switch (state)
	{
	case LEFT_STOP:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_STOP");
			_image = IMAGEMANAGER->findImage("畴富目厚_STOP");
			_motion->start();
		}

		//蹲动捞
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_STOP");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_STOP");
			_motion->start();
		}
		break;
	case RIGHT_STOP:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_STOP");
			_image = IMAGEMANAGER->findImage("畴富目厚_STOP");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_STOP");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_STOP");
			_motion->start();
		}
		break;
	case LEFT_LOW_STOP_UP:
		break;
	case RIGHT_LOW_STOP_UP:
		break;
	case LEFT_LOW_STOP_DOWN:
		break;
	case RIGHT_LOW_STOP_DOWN:
		break;
	case LEFT_HIGH_STOP_UP:
		break;
	case RIGHT_HIGH_STOP_UP:
		break;
	case LEFT_HIGH_STOP_DOWN:
		break;
	case RIGHT_HIGH_STOP_DOWN:
		break;
	case LEFT_SIT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_SIT");
		_image = IMAGEMANAGER->findImage("畴富目厚_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_SIT");
		_image = IMAGEMANAGER->findImage("畴富目厚_SIT");
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
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_MOVE");
			_image = IMAGEMANAGER->findImage("畴富目厚_MOVE");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_MOVE");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_MOVE");
			_motion->start();
		}
		break;
	case RIGHT_MOVE:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_MOVE");
			_image = IMAGEMANAGER->findImage("畴富目厚_MOVE");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_MOVE");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_MOVE");
			_motion->start();
		}
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
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_DASH");
			_image = IMAGEMANAGER->findImage("畴富目厚_DASH");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_DASH");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_MOVE");
			_motion->start();
		}
		break;
	case RIGHT_DASH:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_DASH");
			_image = IMAGEMANAGER->findImage("畴富目厚_DASH");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_DASH");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_MOVE");
			_motion->start();
		}
		break;
	case LEFT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_FLY_UP");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_FLY_UP");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_FLY");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_FLY");
		_image = IMAGEMANAGER->findImage("畴富目厚_FLY");
		_motion->start();
		break;
	case LEFT_JUMP_UP:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_UP:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case LEFT_JUMP_TURN:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_TURN:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case LEFT_JUMP_DOWN:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_DOWN:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("畴富目厚_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_JUMP");
			_motion->start();
		}
		break;
	case LEFT_KICK:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_KICK");
		_image = IMAGEMANAGER->findImage("畴富目厚_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_KICK");
		_image = IMAGEMANAGER->findImage("畴富目厚_KICK");
		_motion->start();
		break;
	case LEFT_EAT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_EAT");
		_image = IMAGEMANAGER->findImage("畴富目厚_伙虐扁");
		_motion->start();
		SOUNDMANAGER->play("eat", atof(DATABASE->getElementData("effectVolume").c_str()));
		break;
	case RIGHT_EAT:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_EAT");
		_image = IMAGEMANAGER->findImage("畴富目厚_伙虐扁");
		_motion->start();
		SOUNDMANAGER->play("eat", atof(DATABASE->getElementData("effectVolume").c_str()));
		break;
	case LEFT_EATING:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_EATING");
		_image = IMAGEMANAGER->findImage("畴富目厚_伙虐扁");
		_motion->start();
		break;
	case RIGHT_EATING:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_EATING");
		_image = IMAGEMANAGER->findImage("畴富目厚_伙虐扁");
		_motion->start();
		break;
	case LEFT_THROW:
		_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_THROW");
		_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_柜扁");
		_motion->start();
		EFFECTMANAGER->play("ATTACK", _defaultX , _defaultY + _image->getFrameHeight() / 2);
		createBullet();
		break;
	case RIGHT_THROW:
		_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_THROW");
		_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_柜扁");
		_motion->start();
		EFFECTMANAGER->play("ATTACK", _defaultX + _image->getFrameWidth(), _defaultY + _image->getFrameHeight() / 2);
		createBullet();
		break;
	case LEFT_FALL:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_FALL");
		_image = IMAGEMANAGER->findImage("畴富目厚_FALL");
		_motion->start();
		break;
	case RIGHT_FALL:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_FALL");
		_image = IMAGEMANAGER->findImage("畴富目厚_FALL");
		_motion->start();
		break;
	case LEFT_ATTACK:
		break;
	case RIGHT_ATTACK:
		break;
	case LEFT_RETURN:
		break;
	case RIGHT_RETURN:
		break;
	case LEFT_CRASH:
		//救蹲动捞
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("畴富目厚_COLLISION");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_LEFT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_COLLISION");
			_motion->start(); 
		}
		break;
	case RIGHT_CRASH:
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("畴富目厚_COLLISION");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("蹲蹲茄畴富目厚_RIGHT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("蹲蹲茄畴富目厚_COLLISION");
			_motion->start();
		}
		break;
	case LEFT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_LEFT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("畴富目厚_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("畴富目厚_RIGHT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("畴富目厚_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}
}



void kirbyBase::initImage()
{
	// 捞固瘤 眠啊

	//STOP
	_image = IMAGEMANAGER->addFrameImage("畴富目厚_STOP", "image\\characters\\kirby\\畴富目厚\\kirby_idle_乞瘤.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_HIGH_STOP_UP", "image\\characters\\kirby\\畴富目厚\\kirby_idle_臭篮攫傣_棵扼哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_HIGH_STOP_DOWN", "image\\characters\\kirby\\畴富目厚\\kirby_idle_臭篮攫傣_郴妨哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_LOW_STOP_UP", "image\\characters\\kirby\\畴富目厚\\kirby_idle_撤篮攫傣_棵扼哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_LOW_STOP_DOWN", "image\\characters\\kirby\\畴富目厚\\kirby_idle_撤篮攫傣_郴妨哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//SIT
	IMAGEMANAGER->addFrameImage("畴富目厚_SIT", "image\\characters\\kirby\\畴富目厚\\kirby_down_乞瘤.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_HIGH_SIT_UP", "image\\characters\\kirby\\畴富目厚\\kirby_down_臭篮攫傣_棵扼哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_HIGH_SIT_DOWN", "image\\characters\\kirby\\畴富目厚\\kirby_down_臭篮攫傣_郴妨哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_LOW_SIT_UP", "image\\characters\\kirby\\畴富目厚\\kirby_down_撤篮攫傣_棵扼哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_LOW_SIT_DOWN", "image\\characters\\kirby\\畴富目厚\\kirby_down_撤篮攫傣_郴妨哎锭.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//蹲动捞
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_STOP", "image\\characters\\kirby\\畴富目厚\\fat_kirby_idle_乞瘤.bmp", 58 * 2, 56 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_HIGH_STOP_UP", "image\\characters\\kirby\\畴富目厚\\fat_kirby_idle_臭篮攫傣_棵扼哎锭.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_HIGH_STOP_DOWN", "image\\characters\\kirby\\畴富目厚\\fat_kirby_idle_臭篮攫傣_郴妨哎锭.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_LOW_STOP_UP", "image\\characters\\kirby\\畴富目厚\\fat_kirby_idle_撤篮攫傣_棵扼哎锭.bmp", 58 * 2, 52 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_LOW_STOP_DOWN", "image\\characters\\kirby\\畴富目厚\\fat_kirby_idle_撤篮攫傣_郴妨哎锭.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_MOVE", "image\\characters\\kirby\\畴富目厚\\fat_kirby_walk.bmp", 464 * 2, 58 * 2, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_CRASH", "image\\characters\\kirby\\畴富目厚\\fat_kirby_collision_normal.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_THROW", "image\\characters\\kirby\\畴富目厚\\fat_kirby_柜扁.bmp", 135 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_JUMP", "image\\characters\\kirby\\畴富目厚\\fat_kirby_jump.bmp", 248 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));

	//MOVE
	IMAGEMANAGER->addFrameImage("畴富目厚_MOVE", "image\\characters\\kirby\\畴富目厚\\kirby_walk.bmp", 270 * 2, 54 * 2, 10, 2, true, RGB(255, 0, 255));

	//FLY
	IMAGEMANAGER->addFrameImage("畴富目厚_FLY", "image\\characters\\kirby\\畴富目厚\\kirby_fly_idle.bmp", 216 * 2, 54 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_FLY_EAT", "image\\characters\\kirby\\畴富目厚\\kirby_fly_eat.bmp", 125 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_FLY_UP", "image\\characters\\kirby\\畴富目厚\\kirby_fly_up.bmp", 162 * 2, 54 * 2, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("畴富目厚_FLY_DOWN", "image\\characters\\kirby\\畴富目厚\\kirby_fly_down.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//伙虐扁
	IMAGEMANAGER->addFrameImage("畴富目厚_伙虐扁", "image\\characters\\kirby\\畴富目厚\\kirby_伙虐扁.bmp", 162 * 2, 54 * 2, 6, 2, true, RGB(255, 0, 255));

	//柜扁
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_柜扁", "image\\characters\\kirby\\畴富目厚\\fat_kirby_柜扁.bmp", 135 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));

	//巩凯扁
	IMAGEMANAGER->addFrameImage("畴富目厚_OPENDOOR", "image\\characters\\kirby\\畴富目厚\\kirby_enter_door.bmp", 96 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//措浆
	IMAGEMANAGER->addFrameImage("畴富目厚_DASH", "image\\characters\\kirby\\畴富目厚\\kirby_dash.bmp", 216 * 2, 54 * 2, 8, 2, true, RGB(255, 0, 255));

	//JUMP
	IMAGEMANAGER->addFrameImage("畴富目厚_JUMP", "image\\characters\\kirby\\畴富目厚\\kirby_jump.bmp", 290 * 2, 54 * 2, 10, 2, true, RGB(255, 0, 255));

	//TACKLE
	IMAGEMANAGER->addFrameImage("畴富目厚_KICK", "image\\characters\\kirby\\畴富目厚\\kirby_tackle.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//FALL
	IMAGEMANAGER->addFrameImage("畴富目厚_FALL", "image\\characters\\kirby\\畴富目厚\\kirby_fall.bmp", 468 * 2, 52 * 2, 18, 2, true, RGB(255, 0, 255));

	//COLLISION
	IMAGEMANAGER->addFrameImage("畴富目厚_COLLISION", "image\\characters\\kirby\\畴富目厚\\kirby_collision_normal.bmp", 243 * 2, 54 * 2, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("蹲蹲茄畴富目厚_COLLISION", "image\\characters\\kirby\\畴富目厚\\fat_kirby_collision_normal.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//OPEN DOOR
	IMAGEMANAGER->addFrameImage("畴富目厚_OPEN_DOOR", "image\\characters\\kirby\\畴富目厚\\kirby_collision_normal.bmp", 96 * 2, 46 * 2, 4, 2, true, RGB(255, 0, 255));

	//ATTACK ( 喊 朝扼皑 )
	_bullet.image = IMAGEMANAGER->addFrameImage("畴富目厚_STAR_ATTACK", "image\\characters\\kirby\\畴富目厚\\kirby_star_attack.bmp", 92, 48, 2, 1, true, RGB(255, 0, 255));

	_changeEffect = IMAGEMANAGER->addFrameImage("CHANGE","image\\effects\\ChangeEffect.bmp", 1360*2, 80*2, 17, 1, true, RGB(255, 0, 255));
	_attackEffect = IMAGEMANAGER->addFrameImage("ATTACK", "image\\effects\\Attack.bmp", 372*2, 63*2, 6, 1, true, RGB(255, 0, 255));


	// KEYANIMANAGER俊 虐蔼 眠啊

	// 畴富 目厚 STOP ( LEFT / RIGHT ) 
	int arrNormalKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrNormalKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_STOP", "畴富目厚_STOP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_STOP", "畴富目厚_STOP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_HIGH_STOP_UP", "畴富目厚_HIGH_STOP_UP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_HIGH_STOP_UP", "畴富目厚_HIGH_STOP_UP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_HIGH_STOP_DOWN", "畴富目厚_HIGH_STOP_DOWN", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_HIGH_STOP_DOWN", "畴富目厚_HIGH_STOP_DOWN", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_LOW_STOP_UP", "畴富目厚_LOW_STOP_UP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_LOW_STOP_UP", "畴富目厚_LOW_STOP_UP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_LOW_STOP_DOWN", "畴富目厚_LOW_STOP_DOWN", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_LOW_STOP_DOWN", "畴富目厚_LOW_STOP_DOWN", arrNormalKirbyLeftStop, 13, 6, true);

	// 蹲蹲茄 畴富 目厚 STOP ( LEFT / RIGHT ) 
	int arrFatNormalKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrFatNormalKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_STOP", "蹲蹲茄畴富目厚_STOP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_STOP", "蹲蹲茄畴富目厚_STOP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_HIGH_STOP_UP", "蹲蹲茄畴富目厚_HIGH_STOP_UP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_HIGH_STOP_UP", "蹲蹲茄畴富目厚_HIGH_STOP_UP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_HIGH_STOP_DOWN", "蹲蹲茄畴富目厚_HIGH_STOP_DOWN", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_HIGH_STOP_DOWN", "蹲蹲茄畴富目厚_HIGH_STOP_DOWN", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_LOW_STOP_UP", "蹲蹲茄畴富目厚_LOW_STOP_UP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_LOW_STOP_UP", "蹲蹲茄畴富目厚_LOW_STOP_UP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_LOW_STOP_DOWN", "蹲蹲茄畴富目厚_LOW_STOP_DOWN", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_LOW_STOP_DOWN", "蹲蹲茄畴富目厚_LOW_STOP_DOWN", arrFatNormalKirbyLeftStop, 13, 6, true);

	// 畴富 目厚 SIT ( LEFT / RIGHT ) 
	int arrNormalKirbyRightSit[] = { 0, 1 };
	int arrNormalKirbyLeftSit[] = { 3, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_SIT", "畴富目厚_SIT", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_SIT", "畴富目厚_SIT", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_HIGH_SIT_UP", "畴富目厚_HIGH_SIT_UP", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_HIGH_SIT_UP", "畴富目厚_HIGH_SIT_UP", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_HIGH_SIT_DOWN", "畴富目厚_HIGH_SIT_DOWN", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_HIGH_SIT_DOWN", "畴富目厚_HIGH_SIT_DOWN", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_LOW_SIT_UP", "畴富目厚_LOW_SIT_UP", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_LOW_SIT_UP", "畴富目厚_LOW_SIT_UP", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_LOW_SIT_DOWN", "畴富目厚_LOW_SIT_DOWN", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_LOW_SIT_DOWN", "畴富目厚_LOW_SIT_DOWN", arrNormalKirbyLeftSit, 2, 6, true);

	// 畴富 目厚 MOVE ( LEFT / RIGHT )
	int arrNormalKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9 };
	int arrNormalKirbyLeftMove[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_MOVE", "畴富目厚_MOVE", arrNormalKirbyRightMove, 10, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_MOVE", "畴富目厚_MOVE", arrNormalKirbyLeftMove, 10, 9, true);

	// 蹲蹲捞 MOVE
	int arrFatNormalKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int arrFatNormalKirbyLeftMove[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_MOVE", "蹲蹲茄畴富目厚_MOVE", arrFatNormalKirbyRightMove, 16, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_MOVE", "蹲蹲茄畴富目厚_MOVE", arrFatNormalKirbyLeftMove, 16, 12, true);


	// 畴富 目厚 FLY EAT ( 官恩阑弧酒甸牢促 )
	int arrNormalKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrNormalKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_FLY_EAT", "畴富目厚_FLY_EAT", arrNormalKirbyRightFlyEat, 5, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_FLY_EAT", "畴富目厚_FLY_EAT", arrNormalKirbyLeftFlyEat, 5, 22, false);

	// 畴富 目厚 FLY (L / R)
	int arrNormalKirbyRightFly[] = { 0,1,2,3,4,5,6,7 };
	int arrNormalKirbyLeftFly[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_FLY", "畴富目厚_FLY", arrNormalKirbyRightFly, 8, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_FLY", "畴富目厚_FLY", arrNormalKirbyLeftFly, 8, 9, true);

	// 畴富 目厚 FlY UP (L / R)
	int arrNormalKirbyRightFlyUp[] = { 0,1,2,3,4,5 };
	int arrNormalKirbyLeftFlyUp[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_FLY_UP", "畴富目厚_FLY_UP", arrNormalKirbyRightFlyUp, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_FLY_UP", "畴富目厚_FLY_UP", arrNormalKirbyLeftFlyUp, 6, 9, true);

	// 畴富 目厚 FLY DOWN (L / R)
	int arrNormalKirbyRightFlyDown[] = { 0,1,2,3 };
	int arrNormalKirbyLeftFlyDown[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_FLY_DOWN", "畴富目厚_FLY_DOWN", arrNormalKirbyRightFlyDown, 4, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_FLY_DOWN", "畴富目厚_FLY_DOWN", arrNormalKirbyLeftFlyDown, 4, 9, true);

	// 畴富 目厚 伙虐扁 ( L / R )
	int arrNormalKirbyRightEat[] = { 0,1,2,3,4 };
	int arrNormalKirbyLeftEat[] = { 11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_EAT", "畴富目厚_伙虐扁", arrNormalKirbyRightEat, 5, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_EAT", "畴富目厚_伙虐扁", arrNormalKirbyLeftEat, 5, 12, true);

	// 畴富 目厚 拌加 伙虐扁 ( L / R )
	int arrNormalKirbyRightEating[] = { 3,4 };
	int arrNormalKirbyLeftEating[] = { 8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_EATING", "畴富目厚_伙虐扁", arrNormalKirbyRightEating, 2, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_EATING", "畴富目厚_伙虐扁", arrNormalKirbyLeftEating, 2, 12, true);

	// 蹲蹲茄 畴富 目厚 柜扁
	int arrFatNormalKirbyRightThrow[] = { 0,1,2,3,4 };
	int arrFatNormalKirbyLeftThrow[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_THROW", "蹲蹲茄畴富目厚_柜扁", arrFatNormalKirbyRightThrow, 5, 26, false);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_THROW", "蹲蹲茄畴富目厚_柜扁", arrFatNormalKirbyLeftThrow, 5, 26, false);

	// 畴富 目厚 巩凯扁
	int arrNormalKirbyRightOpenDoor[] = { 0,1,2,3 };
	int arrNormalKirbyLeftOpenDoor[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_OPENDOOR", "畴富目厚_OPENDOOR", arrNormalKirbyRightOpenDoor, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_OPENDOOR", "畴富目厚_OPENDOOR", arrNormalKirbyLeftOpenDoor, 4, 22, false);

	// 畴富 目厚 措浆
	int arrNormalKirbyRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrNormalKirbyLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_DASH", "畴富目厚_DASH", arrNormalKirbyRightDash, 8, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_DASH", "畴富目厚_DASH", arrNormalKirbyLeftDash, 8, 33, true);

	// 蹲蹲茄 畴富 目厚 措浆
	int arrFatNormalKirbyRightDash[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int arrFatNormalKirbyLeftDash[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_DASH", "蹲蹲茄畴富目厚_MOVE", arrFatNormalKirbyRightMove, 16, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_DASH", "蹲蹲茄畴富目厚_MOVE", arrFatNormalKirbyLeftMove, 16, 33, true);

	// 畴富 目厚 JUMP UP
	int arrNormalKirbyRightJumpUp[] = { 0 };
	int arrNormalKirbyLeftJumpUp[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_JUMP_UP", "畴富目厚_JUMP", arrNormalKirbyRightJumpUp, 1, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_JUMP_UP", "畴富目厚_JUMP", arrNormalKirbyLeftJumpUp, 1, 22, true);

	// 畴富 目厚 JUMP TURN
	int arrNormalKirbyRightJumpTurn[] = { 1,2,3,4,5,6,7,8 };
	int arrNormalKirbyLeftJumpTurn[] = { 18,17,16,15,14,13,12,11 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_JUMP_TURN", "畴富目厚_JUMP", arrNormalKirbyRightJumpTurn, 8, 35, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_JUMP_TURN", "畴富目厚_JUMP", arrNormalKirbyLeftJumpTurn, 8, 35, false);

	// 畴富 目厚 JUMP DOWN
	int arrNormalKirbyRightJumpDown[] = { 9,9 };
	int arrNormalKirbyLeftJumpDown[] = { 10,10 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_JUMP_DOWN", "畴富目厚_JUMP", arrNormalKirbyRightJumpDown, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_JUMP_DOWN", "畴富目厚_JUMP", arrNormalKirbyLeftJumpDown, 2, 22, false);

	// 蹲蹲茄 畴富 目厚 JUMP UP
	int arrFatNormalKirbyRightJumpUp[] = { 0 };
	int arrFatNormalKirbyLeftJumpUp[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_UP", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyRightJumpUp, 1, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_UP", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyLeftJumpUp, 1, 12, true);

	// 蹲蹲茄 畴富 目厚 JUMP TURN
	int arrFatNormalKirbyRightJumpTurn[] = { 1,2,3,4,5,6 };
	int arrFatNormalKirbyLeftJumpTurn[] = { 14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_TURN", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyRightJumpTurn, 6, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_TURN", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyLeftJumpTurn, 6, 22, false);

	// 蹲蹲茄 畴富 目厚 JUMP DOWN
	int arrFatNormalKirbyRightJumpDown[] = { 7,7 };
	int arrFatNormalKirbyLeftJumpDown[] = { 8,8 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_JUMP_DOWN", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyRightJumpDown, 2, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_JUMP_DOWN", "蹲蹲茄畴富目厚_JUMP", arrFatNormalKirbyLeftJumpDown, 2, 12, false);

	// 畴富 目厚 怕努( KICK )
	int arrNormalKirbyRightKick[] = { 0 };
	int arrNormalKirbyLeftKick[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_KICK", "畴富目厚_KICK", arrNormalKirbyRightKick, 1, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_KICK", "畴富目厚_KICK", arrNormalKirbyLeftKick, 1, 12, true);

	// 畴富 目厚 冻绢瘤绰芭 ( FALL )
	int arrNormalKirbyRightFall[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,17,17 };
	int arrNormalKirbyLeftFall[] = { 35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,18,18 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_FALL", "畴富目厚_FALL", arrNormalKirbyRightFall, 20, 30, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_FALL", "畴富目厚_FALL", arrNormalKirbyLeftFall, 20, 30, false);

	// 畴富 目厚 老馆 面倒
	int arrNormalKirbyRightNormalCollision[] = { 0,1,2,3,4,5,6,7,8 };
	int arrNormalKirbyLeftNormalCollision[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_NORMAL_COLLISION", "畴富目厚_COLLISION", arrNormalKirbyRightNormalCollision, 9, 30, false);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_NORMAL_COLLISION", "畴富目厚_COLLISION", arrNormalKirbyLeftNormalCollision, 9, 30, false);

	// 蹲蹲茄 畴富 目厚 老馆 面倒
	int arrFatNormalKirbyRightNormalCollision[] = { 0,1,2,3 };
	int arrFatNormalKirbyLeftNormalCollision[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_RIGHT_NORMAL_COLLISION", "蹲蹲茄畴富目厚_COLLISION", arrFatNormalKirbyRightNormalCollision, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("蹲蹲茄畴富目厚_LEFT_NORMAL_COLLISION", "蹲蹲茄畴富目厚_COLLISION", arrFatNormalKirbyLeftNormalCollision, 4, 22, false);

	// STAR ATTACK
	int arrNormalKirbyRightStarAttack[] = { 0,1 };
	int arrNormalKirbyLeftStarAttack[] = { 1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_RIGHT_STAR_ATTACK", "畴富目厚_STAR_ATTACK", arrNormalKirbyRightStarAttack, 2, 14, true);
	KEYANIMANAGER->addArrayFrameAnimation("畴富目厚_LEFT_STAR_ATTACK", "畴富目厚_STAR_ATTACK", arrNormalKirbyLeftStarAttack, 2, 14, true);


	// 捞棋飘 眠啊
	EFFECTMANAGER->addEffect("ATTACK", "ATTACK", _attackEffect->getWidth(), _attackEffect->getHeight(), _attackEffect->getFrameWidth(), _attackEffect->getFrameHeight(), 12, TIMEMANAGER->getElapsedTime(), 3);
	EFFECTMANAGER->addEffect("CHANGE", "CHANGE", _changeEffect->getWidth(), _changeEffect->getHeight(), _changeEffect->getFrameWidth(), _changeEffect->getFrameHeight(), 12, TIMEMANAGER->getElapsedTime(), 3);


}

