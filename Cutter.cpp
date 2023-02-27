#include "stdafx.h"
#include "Cutter.h"


Cutter::Cutter()
{
}


Cutter::~Cutter()
{
}

HRESULT Cutter::init(float x, float y, float speed, int moveRange, bool up)
{
	//모든 프레임 세팅은 오른쪽
	IMAGEMANAGER->addFrameImage("cutter_walk", "image//Enemy//Cutter//걷기.bmp", 104, 25, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("cutter_walk")->setFrameX(2);
	IMAGEMANAGER->findImage("cutter_walk")->setFrameY(0);

	IMAGEMANAGER->addFrameImage("cutter_attack", "image//Enemy//Cutter//공격.bmp", 150, 25, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("cutter_attack")->setFrameX(3);
	IMAGEMANAGER->findImage("cutter_attack")->setFrameY(0);

	IMAGEMANAGER->addFrameImage("cutter_hit", "image//Enemy//Cutter//맞을때.bmp", 25, 25, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("cutter_hit")->setFrameX(0);
	IMAGEMANAGER->findImage("cutter_hit")->setFrameY(0);

	_currentFrameX = _currentFrameY = 0;
	_x = _startX = x;
	_y = _startY = y;
	_fSpeed = speed;
	_count = 0;
	_moveRange = moveRange;

	_state = ENEMY_RIGHT_MOVE;

	_jumpPower = 10;
	_nEnemyHP = 1;
	_angle = PI / 1.6;
	_bDie = false;
	_isUpFly = up;

	return S_OK;
}

void Cutter::release()
{
}

void Cutter::update()
{
	if (_bDie) return;
	//------------------------------------------------------------------------
	//패턴 조합

	//-------------------------------------------------------------------------
	_count += TIMEMANAGER->getElapsedTime();

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:
		break;
	case ENEMY_RIGHT_MOVE:
		break;
	case ENEMY_RIGHT_FLY:
		break;
	case ENEMY_RIGHT_STAGGER:
		break;
	case ENEMY_RIGHT_DIE:
		break;
	case ENEMY_RIGHT_HIT:
		break;
	case ENEMY_LEFT_STOP:
		break;
	case ENEMY_LEFT_MOVE:
		break;
	case ENEMY_LEFT_FLY:
		break;
	case ENEMY_LEFT_STAGGER:
		break;
	case ENEMY_LEFT_DIE:
		break;
	case ENEMY_LEFT_HIT:
		break;
	case ENEMY_UP_FLY:
		break;
	case ENEMY_END:
		break;
	}
}

void Cutter::render()
{

}

void Cutter::draw(RECT rcFocus)
{
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("cutter_walk")->getFrameWidth(), IMAGEMANAGER->findImage("beem_walk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;

	switch (_state)
	{
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE:case ENEMY_UP_FLY:
		break;
	case ENEMY_RIGHT_FLY: case ENEMY_LEFT_FLY:
		break;
	case ENEMY_RIGHT_STAGGER:
		break;
	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		break;
	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		break;
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
		break;
	case ENEMY_LEFT_STAGGER:
		break;
	}
}
