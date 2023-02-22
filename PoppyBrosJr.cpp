#include "stdafx.h"
#include "PoppyBrosJr.h"


PoppyBrosJr::PoppyBrosJr()
{
}


PoppyBrosJr::~PoppyBrosJr()
{
}

HRESULT PoppyBrosJr::init(float x, float y, float speed, int moveRange, bool up)
{
	//모든 프레임 세팅은 오른쪽
	IMAGEMANAGER->addFrameImage("poppyJr_walk", "image//Enemy//poppyBrosJr//걷기.bmp", 88, 52, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("poppyJr_walk")->setFrameX(0);
	IMAGEMANAGER->findImage("poppyJr_walk")->setFrameY(0);

	IMAGEMANAGER->addFrameImage("poppyJr_hit", "image//Enemy//poppyBrosJr//맞을때.bmp", 19, 52, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("poppyJr_hit")->setFrameX(0);
	IMAGEMANAGER->findImage("poppyJr_hit")->setFrameY(0);

	IMAGEMANAGER->addFrameImage("poppyJr_apple", "image//Enemy//poppyBrosJr//사과.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("poppyJr_apple")->setFrameX(0);
	IMAGEMANAGER->findImage("poppyJr_apple")->setFrameY(0);

	IMAGEMANAGER->addFrameImage("poppyJr_tomato", "image//Enemy//poppyBrosJr//토마토.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("poppyJr_tomato")->setFrameX(0);
	IMAGEMANAGER->findImage("poppyJr_tomato")->setFrameY(0);

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

void PoppyBrosJr::release()
{
}

void PoppyBrosJr::update()
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

void PoppyBrosJr::render()
{

}

void PoppyBrosJr::draw(RECT rcFocus)
{
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("poppyJr_walk")->getFrameWidth(), IMAGEMANAGER->findImage("beem_walk")->getFrameHeight());
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
