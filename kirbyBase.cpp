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
	_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_STOP");
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
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_STAR_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("�븻Ŀ��_STAR_ATTACK");
		_bullet.bulletMotion->start();
	}
	else if (_kirby->getState() == RIGHT_THROW)
	{
		_bullet.isAttackRight = true;
		_bullet.bulletMotion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_STAR_ATTACK");
		_bullet.image = IMAGEMANAGER->findImage("�븻Ŀ��_STAR_ATTACK");
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

	// ��Ÿ��� �Ѿ�ų� �浹 (�� �̶� �΋H������)�̸� �ʱ�ȭ
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
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_STOP");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_STOP");
			_motion->start();
		}

		//�׶���
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_STOP");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_STOP");
			_motion->start();
		}
		break;
	case RIGHT_STOP:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_STOP");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_STOP");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_STOP");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_STOP");
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
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_SIT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_SIT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_SIT");
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
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_MOVE");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_MOVE");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_MOVE");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_MOVE");
			_motion->start();
		}
		break;
	case RIGHT_MOVE:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_MOVE");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_MOVE");
			_motion->start();
		}

		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_MOVE");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_MOVE");
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
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_DASH");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_DASH");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_DASH");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_MOVE");
			_motion->start();
		}
		break;
	case RIGHT_DASH:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_DASH");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_DASH");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_DASH");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_MOVE");
			_motion->start();
		}
		break;
	case LEFT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_FLY_UP");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_FLY_UP");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_FLY");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_FLY");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FLY");
		_motion->start();
		break;
	case LEFT_JUMP_UP:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_UP:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_UP");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case LEFT_JUMP_TURN:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_TURN:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_TURN");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case LEFT_JUMP_DOWN:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case RIGHT_JUMP_DOWN:
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_JUMP");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_DOWN");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_JUMP");
			_motion->start();
		}
		break;
	case LEFT_KICK:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_KICK");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_KICK");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_KICK");
		_motion->start();
		break;
	case LEFT_EAT:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_EAT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_��Ű��");
		_motion->start();
		SOUNDMANAGER->play("eat", atof(DATABASE->getElementData("effectVolume").c_str()));
		break;
	case RIGHT_EAT:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_EAT");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_��Ű��");
		_motion->start();
		SOUNDMANAGER->play("eat", atof(DATABASE->getElementData("effectVolume").c_str()));
		break;
	case LEFT_EATING:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_EATING");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_��Ű��");
		_motion->start();
		break;
	case RIGHT_EATING:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_EATING");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_��Ű��");
		_motion->start();
		break;
	case LEFT_THROW:
		_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_THROW");
		_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_���");
		_motion->start();
		EFFECTMANAGER->play("ATTACK", _defaultX , _defaultY + _image->getFrameHeight() / 2);
		createBullet();
		break;
	case RIGHT_THROW:
		_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_THROW");
		_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_���");
		_motion->start();
		EFFECTMANAGER->play("ATTACK", _defaultX + _image->getFrameWidth(), _defaultY + _image->getFrameHeight() / 2);
		createBullet();
		break;
	case LEFT_FALL:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_FALL");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FALL");
		_motion->start();
		break;
	case RIGHT_FALL:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_FALL");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_FALL");
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
		//�ȶ׶���
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_COLLISION");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_LEFT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_COLLISION");
			_motion->start(); 
		}
		break;
	case RIGHT_CRASH:
		if (!_kirby->getIsFull())
		{
			_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("�븻Ŀ��_COLLISION");
			_motion->start();
		}
		else
		{
			_motion = KEYANIMANAGER->findAnimation("�׶��ѳ븻Ŀ��_RIGHT_NORMAL_COLLISION");
			_image = IMAGEMANAGER->findImage("�׶��ѳ븻Ŀ��_COLLISION");
			_motion->start();
		}
		break;
	case LEFT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_LEFT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("�븻Ŀ��_RIGHT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("�븻Ŀ��_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}
}



void kirbyBase::initImage()
{
	// �̹��� �߰�

	//STOP
	_image = IMAGEMANAGER->addFrameImage("�븻Ŀ��_STOP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_idle_����.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_HIGH_STOP_UP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_idle_�������_�ö󰥶�.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_HIGH_STOP_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\kirby_idle_�������_��������.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_LOW_STOP_UP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_idle_�������_�ö󰥶�.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_LOW_STOP_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\kirby_idle_�������_��������.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//SIT
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_SIT", "image\\characters\\kirby\\�븻Ŀ��\\kirby_down_����.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_HIGH_SIT_UP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_down_�������_�ö󰥶�.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_HIGH_SIT_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\kirby_down_�������_��������.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_LOW_SIT_UP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_down_�������_�ö󰥶�.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_LOW_SIT_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\kirby_down_�������_��������.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//�׶���
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_STOP", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_idle_����.bmp", 58 * 2, 56 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_HIGH_STOP_UP", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_idle_�������_�ö󰥶�.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_HIGH_STOP_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_idle_�������_��������.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_LOW_STOP_UP", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_idle_�������_�ö󰥶�.bmp", 58 * 2, 52 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_LOW_STOP_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_idle_�������_��������.bmp", 58 * 2, 58 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_MOVE", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_walk.bmp", 464 * 2, 58 * 2, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_CRASH", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_collision_normal.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_THROW", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_���.bmp", 135 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_JUMP", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_jump.bmp", 248 * 2, 74 * 2, 8, 2, true, RGB(255, 0, 255));

	//MOVE
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_MOVE", "image\\characters\\kirby\\�븻Ŀ��\\kirby_walk.bmp", 270 * 2, 54 * 2, 10, 2, true, RGB(255, 0, 255));

	//FLY
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_FLY", "image\\characters\\kirby\\�븻Ŀ��\\kirby_fly_idle.bmp", 216 * 2, 54 * 2, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_FLY_EAT", "image\\characters\\kirby\\�븻Ŀ��\\kirby_fly_eat.bmp", 125 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_FLY_UP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_fly_up.bmp", 162 * 2, 54 * 2, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_FLY_DOWN", "image\\characters\\kirby\\�븻Ŀ��\\kirby_fly_down.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//��Ű��
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_��Ű��", "image\\characters\\kirby\\�븻Ŀ��\\kirby_��Ű��.bmp", 162 * 2, 54 * 2, 6, 2, true, RGB(255, 0, 255));

	//���
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_���", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_���.bmp", 135 * 2, 54 * 2, 5, 2, true, RGB(255, 0, 255));

	//������
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_OPENDOOR", "image\\characters\\kirby\\�븻Ŀ��\\kirby_enter_door.bmp", 96 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//�뽬
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_DASH", "image\\characters\\kirby\\�븻Ŀ��\\kirby_dash.bmp", 216 * 2, 54 * 2, 8, 2, true, RGB(255, 0, 255));

	//JUMP
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_JUMP", "image\\characters\\kirby\\�븻Ŀ��\\kirby_jump.bmp", 290 * 2, 54 * 2, 10, 2, true, RGB(255, 0, 255));

	//TACKLE
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_KICK", "image\\characters\\kirby\\�븻Ŀ��\\kirby_tackle.bmp", 58 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//FALL
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_FALL", "image\\characters\\kirby\\�븻Ŀ��\\kirby_fall.bmp", 468 * 2, 52 * 2, 18, 2, true, RGB(255, 0, 255));

	//COLLISION
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_COLLISION", "image\\characters\\kirby\\�븻Ŀ��\\kirby_collision_normal.bmp", 243 * 2, 54 * 2, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�׶��ѳ븻Ŀ��_COLLISION", "image\\characters\\kirby\\�븻Ŀ��\\fat_kirby_collision_normal.bmp", 108 * 2, 54 * 2, 4, 2, true, RGB(255, 0, 255));

	//OPEN DOOR
	IMAGEMANAGER->addFrameImage("�븻Ŀ��_OPEN_DOOR", "image\\characters\\kirby\\�븻Ŀ��\\kirby_collision_normal.bmp", 96 * 2, 46 * 2, 4, 2, true, RGB(255, 0, 255));

	//ATTACK ( �� ���� )
	_bullet.image = IMAGEMANAGER->addFrameImage("�븻Ŀ��_STAR_ATTACK", "image\\characters\\kirby\\�븻Ŀ��\\kirby_star_attack.bmp", 92, 48, 2, 1, true, RGB(255, 0, 255));

	_changeEffect = IMAGEMANAGER->addFrameImage("CHANGE","image\\effects\\ChangeEffect.bmp", 1360*2, 80*2, 17, 1, true, RGB(255, 0, 255));
	_attackEffect = IMAGEMANAGER->addFrameImage("ATTACK", "image\\effects\\Attack.bmp", 372*2, 63*2, 6, 1, true, RGB(255, 0, 255));


	// KEYANIMANAGER�� Ű�� �߰�

	// �븻 Ŀ�� STOP ( LEFT / RIGHT ) 
	int arrNormalKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrNormalKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_STOP", "�븻Ŀ��_STOP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_STOP", "�븻Ŀ��_STOP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_HIGH_STOP_UP", "�븻Ŀ��_HIGH_STOP_UP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_HIGH_STOP_UP", "�븻Ŀ��_HIGH_STOP_UP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_HIGH_STOP_DOWN", "�븻Ŀ��_HIGH_STOP_DOWN", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_HIGH_STOP_DOWN", "�븻Ŀ��_HIGH_STOP_DOWN", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_LOW_STOP_UP", "�븻Ŀ��_LOW_STOP_UP", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_LOW_STOP_UP", "�븻Ŀ��_LOW_STOP_UP", arrNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_LOW_STOP_DOWN", "�븻Ŀ��_LOW_STOP_DOWN", arrNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_LOW_STOP_DOWN", "�븻Ŀ��_LOW_STOP_DOWN", arrNormalKirbyLeftStop, 13, 6, true);

	// �׶��� �븻 Ŀ�� STOP ( LEFT / RIGHT ) 
	int arrFatNormalKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrFatNormalKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_STOP", "�׶��ѳ븻Ŀ��_STOP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_STOP", "�׶��ѳ븻Ŀ��_STOP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_HIGH_STOP_UP", "�׶��ѳ븻Ŀ��_HIGH_STOP_UP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_HIGH_STOP_UP", "�׶��ѳ븻Ŀ��_HIGH_STOP_UP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_HIGH_STOP_DOWN", "�׶��ѳ븻Ŀ��_HIGH_STOP_DOWN", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_HIGH_STOP_DOWN", "�׶��ѳ븻Ŀ��_HIGH_STOP_DOWN", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_LOW_STOP_UP", "�׶��ѳ븻Ŀ��_LOW_STOP_UP", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_LOW_STOP_UP", "�׶��ѳ븻Ŀ��_LOW_STOP_UP", arrFatNormalKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_LOW_STOP_DOWN", "�׶��ѳ븻Ŀ��_LOW_STOP_DOWN", arrFatNormalKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_LOW_STOP_DOWN", "�׶��ѳ븻Ŀ��_LOW_STOP_DOWN", arrFatNormalKirbyLeftStop, 13, 6, true);

	// �븻 Ŀ�� SIT ( LEFT / RIGHT ) 
	int arrNormalKirbyRightSit[] = { 0, 1 };
	int arrNormalKirbyLeftSit[] = { 3, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_SIT", "�븻Ŀ��_SIT", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_SIT", "�븻Ŀ��_SIT", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_HIGH_SIT_UP", "�븻Ŀ��_HIGH_SIT_UP", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_HIGH_SIT_UP", "�븻Ŀ��_HIGH_SIT_UP", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_HIGH_SIT_DOWN", "�븻Ŀ��_HIGH_SIT_DOWN", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_HIGH_SIT_DOWN", "�븻Ŀ��_HIGH_SIT_DOWN", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_LOW_SIT_UP", "�븻Ŀ��_LOW_SIT_UP", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_LOW_SIT_UP", "�븻Ŀ��_LOW_SIT_UP", arrNormalKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_LOW_SIT_DOWN", "�븻Ŀ��_LOW_SIT_DOWN", arrNormalKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_LOW_SIT_DOWN", "�븻Ŀ��_LOW_SIT_DOWN", arrNormalKirbyLeftSit, 2, 6, true);

	// �븻 Ŀ�� MOVE ( LEFT / RIGHT )
	int arrNormalKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9 };
	int arrNormalKirbyLeftMove[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_MOVE", "�븻Ŀ��_MOVE", arrNormalKirbyRightMove, 10, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_MOVE", "�븻Ŀ��_MOVE", arrNormalKirbyLeftMove, 10, 9, true);

	// �׶��� MOVE
	int arrFatNormalKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int arrFatNormalKirbyLeftMove[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_MOVE", "�׶��ѳ븻Ŀ��_MOVE", arrFatNormalKirbyRightMove, 16, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_MOVE", "�׶��ѳ븻Ŀ��_MOVE", arrFatNormalKirbyLeftMove, 16, 12, true);


	// �븻 Ŀ�� FLY EAT ( �ٶ������Ƶ��δ� )
	int arrNormalKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrNormalKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_FLY_EAT", "�븻Ŀ��_FLY_EAT", arrNormalKirbyRightFlyEat, 5, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_FLY_EAT", "�븻Ŀ��_FLY_EAT", arrNormalKirbyLeftFlyEat, 5, 22, false);

	// �븻 Ŀ�� FLY (L / R)
	int arrNormalKirbyRightFly[] = { 0,1,2,3,4,5,6,7 };
	int arrNormalKirbyLeftFly[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_FLY", "�븻Ŀ��_FLY", arrNormalKirbyRightFly, 8, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_FLY", "�븻Ŀ��_FLY", arrNormalKirbyLeftFly, 8, 9, true);

	// �븻 Ŀ�� FlY UP (L / R)
	int arrNormalKirbyRightFlyUp[] = { 0,1,2,3,4,5 };
	int arrNormalKirbyLeftFlyUp[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_FLY_UP", "�븻Ŀ��_FLY_UP", arrNormalKirbyRightFlyUp, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_FLY_UP", "�븻Ŀ��_FLY_UP", arrNormalKirbyLeftFlyUp, 6, 9, true);

	// �븻 Ŀ�� FLY DOWN (L / R)
	int arrNormalKirbyRightFlyDown[] = { 0,1,2,3 };
	int arrNormalKirbyLeftFlyDown[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_FLY_DOWN", "�븻Ŀ��_FLY_DOWN", arrNormalKirbyRightFlyDown, 4, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_FLY_DOWN", "�븻Ŀ��_FLY_DOWN", arrNormalKirbyLeftFlyDown, 4, 9, true);

	// �븻 Ŀ�� ��Ű�� ( L / R )
	int arrNormalKirbyRightEat[] = { 0,1,2,3,4 };
	int arrNormalKirbyLeftEat[] = { 11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_EAT", "�븻Ŀ��_��Ű��", arrNormalKirbyRightEat, 5, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_EAT", "�븻Ŀ��_��Ű��", arrNormalKirbyLeftEat, 5, 12, true);

	// �븻 Ŀ�� ��� ��Ű�� ( L / R )
	int arrNormalKirbyRightEating[] = { 3,4 };
	int arrNormalKirbyLeftEating[] = { 8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_EATING", "�븻Ŀ��_��Ű��", arrNormalKirbyRightEating, 2, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_EATING", "�븻Ŀ��_��Ű��", arrNormalKirbyLeftEating, 2, 12, true);

	// �׶��� �븻 Ŀ�� ���
	int arrFatNormalKirbyRightThrow[] = { 0,1,2,3,4 };
	int arrFatNormalKirbyLeftThrow[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_THROW", "�׶��ѳ븻Ŀ��_���", arrFatNormalKirbyRightThrow, 5, 26, false);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_THROW", "�׶��ѳ븻Ŀ��_���", arrFatNormalKirbyLeftThrow, 5, 26, false);

	// �븻 Ŀ�� ������
	int arrNormalKirbyRightOpenDoor[] = { 0,1,2,3 };
	int arrNormalKirbyLeftOpenDoor[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_OPENDOOR", "�븻Ŀ��_OPENDOOR", arrNormalKirbyRightOpenDoor, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_OPENDOOR", "�븻Ŀ��_OPENDOOR", arrNormalKirbyLeftOpenDoor, 4, 22, false);

	// �븻 Ŀ�� �뽬
	int arrNormalKirbyRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrNormalKirbyLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_DASH", "�븻Ŀ��_DASH", arrNormalKirbyRightDash, 8, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_DASH", "�븻Ŀ��_DASH", arrNormalKirbyLeftDash, 8, 33, true);

	// �׶��� �븻 Ŀ�� �뽬
	int arrFatNormalKirbyRightDash[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int arrFatNormalKirbyLeftDash[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_DASH", "�׶��ѳ븻Ŀ��_MOVE", arrFatNormalKirbyRightMove, 16, 33, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_DASH", "�׶��ѳ븻Ŀ��_MOVE", arrFatNormalKirbyLeftMove, 16, 33, true);

	// �븻 Ŀ�� JUMP UP
	int arrNormalKirbyRightJumpUp[] = { 0 };
	int arrNormalKirbyLeftJumpUp[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_JUMP_UP", "�븻Ŀ��_JUMP", arrNormalKirbyRightJumpUp, 1, 22, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_JUMP_UP", "�븻Ŀ��_JUMP", arrNormalKirbyLeftJumpUp, 1, 22, true);

	// �븻 Ŀ�� JUMP TURN
	int arrNormalKirbyRightJumpTurn[] = { 1,2,3,4,5,6,7,8 };
	int arrNormalKirbyLeftJumpTurn[] = { 18,17,16,15,14,13,12,11 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_JUMP_TURN", "�븻Ŀ��_JUMP", arrNormalKirbyRightJumpTurn, 8, 35, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_JUMP_TURN", "�븻Ŀ��_JUMP", arrNormalKirbyLeftJumpTurn, 8, 35, false);

	// �븻 Ŀ�� JUMP DOWN
	int arrNormalKirbyRightJumpDown[] = { 9,9 };
	int arrNormalKirbyLeftJumpDown[] = { 10,10 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_JUMP_DOWN", "�븻Ŀ��_JUMP", arrNormalKirbyRightJumpDown, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_JUMP_DOWN", "�븻Ŀ��_JUMP", arrNormalKirbyLeftJumpDown, 2, 22, false);

	// �׶��� �븻 Ŀ�� JUMP UP
	int arrFatNormalKirbyRightJumpUp[] = { 0 };
	int arrFatNormalKirbyLeftJumpUp[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_UP", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyRightJumpUp, 1, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_UP", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyLeftJumpUp, 1, 12, true);

	// �׶��� �븻 Ŀ�� JUMP TURN
	int arrFatNormalKirbyRightJumpTurn[] = { 1,2,3,4,5,6 };
	int arrFatNormalKirbyLeftJumpTurn[] = { 14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_TURN", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyRightJumpTurn, 6, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_TURN", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyLeftJumpTurn, 6, 22, false);

	// �׶��� �븻 Ŀ�� JUMP DOWN
	int arrFatNormalKirbyRightJumpDown[] = { 7,7 };
	int arrFatNormalKirbyLeftJumpDown[] = { 8,8 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_JUMP_DOWN", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyRightJumpDown, 2, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_JUMP_DOWN", "�׶��ѳ븻Ŀ��_JUMP", arrFatNormalKirbyLeftJumpDown, 2, 12, false);

	// �븻 Ŀ�� ��Ŭ( KICK )
	int arrNormalKirbyRightKick[] = { 0 };
	int arrNormalKirbyLeftKick[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_KICK", "�븻Ŀ��_KICK", arrNormalKirbyRightKick, 1, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_KICK", "�븻Ŀ��_KICK", arrNormalKirbyLeftKick, 1, 12, true);

	// �븻 Ŀ�� �������°� ( FALL )
	int arrNormalKirbyRightFall[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,17,17 };
	int arrNormalKirbyLeftFall[] = { 35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,18,18 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_FALL", "�븻Ŀ��_FALL", arrNormalKirbyRightFall, 20, 30, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_FALL", "�븻Ŀ��_FALL", arrNormalKirbyLeftFall, 20, 30, false);

	// �븻 Ŀ�� �Ϲ� �浹
	int arrNormalKirbyRightNormalCollision[] = { 0,1,2,3,4,5,6,7,8 };
	int arrNormalKirbyLeftNormalCollision[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_NORMAL_COLLISION", "�븻Ŀ��_COLLISION", arrNormalKirbyRightNormalCollision, 9, 30, false);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_NORMAL_COLLISION", "�븻Ŀ��_COLLISION", arrNormalKirbyLeftNormalCollision, 9, 30, false);

	// �׶��� �븻 Ŀ�� �Ϲ� �浹
	int arrFatNormalKirbyRightNormalCollision[] = { 0,1,2,3 };
	int arrFatNormalKirbyLeftNormalCollision[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_RIGHT_NORMAL_COLLISION", "�׶��ѳ븻Ŀ��_COLLISION", arrFatNormalKirbyRightNormalCollision, 4, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("�׶��ѳ븻Ŀ��_LEFT_NORMAL_COLLISION", "�׶��ѳ븻Ŀ��_COLLISION", arrFatNormalKirbyLeftNormalCollision, 4, 22, false);

	// STAR ATTACK
	int arrNormalKirbyRightStarAttack[] = { 0,1 };
	int arrNormalKirbyLeftStarAttack[] = { 1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_RIGHT_STAR_ATTACK", "�븻Ŀ��_STAR_ATTACK", arrNormalKirbyRightStarAttack, 2, 14, true);
	KEYANIMANAGER->addArrayFrameAnimation("�븻Ŀ��_LEFT_STAR_ATTACK", "�븻Ŀ��_STAR_ATTACK", arrNormalKirbyLeftStarAttack, 2, 14, true);


	// ����Ʈ �߰�
	EFFECTMANAGER->addEffect("ATTACK", "ATTACK", _attackEffect->getWidth(), _attackEffect->getHeight(), _attackEffect->getFrameWidth(), _attackEffect->getFrameHeight(), 12, TIMEMANAGER->getElapsedTime(), 3);
	EFFECTMANAGER->addEffect("CHANGE", "CHANGE", _changeEffect->getWidth(), _changeEffect->getHeight(), _changeEffect->getFrameWidth(), _changeEffect->getFrameHeight(), 12, TIMEMANAGER->getElapsedTime(), 3);


}

