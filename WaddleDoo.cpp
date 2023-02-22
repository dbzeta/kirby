#include "stdafx.h"
#include "WaddleDoo.h"


WaddleDoo::WaddleDoo()
{
}


WaddleDoo::~WaddleDoo()
{
}

HRESULT WaddleDoo::init(float x, float y, float speed, int moveRange, bool up)
{
	//모든 프레임 세팅은 오른쪽
	IMAGEMANAGER->addFrameImage("waddleDoo_stop_um", "image//Enemy//waddleDoo//기본_우산.bmp", 66, 80, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_stop_um")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_stop_um")->setFrameY(1);

	IMAGEMANAGER->addFrameImage("waddleDoo_walk", "image//Enemy//waddleDoo//걷기.bmp", 115, 44, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_walk")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_walk")->setFrameY(1);

	IMAGEMANAGER->addFrameImage("waddleDoo_fly_um", "image//Enemy//waddleDoo//날때_우산.bmp", 115, 76, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_fly_um")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_fly_um")->setFrameY(1);

	IMAGEMANAGER->addFrameImage("waddleDoo_attack_ready", "image//Enemy//waddleDoo//공격준비.bmp", 48, 38, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_attack_ready")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_attack_ready")->setFrameY(1);

	IMAGEMANAGER->addFrameImage("waddleDoo_hit", "image//Enemy//waddleDoo//맞을때.bmp", 42, 40, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_hit")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_hit")->setFrameY(1);

	IMAGEMANAGER->addFrameImage("waddleDoo_hit_um", "image//Enemy//waddleDoo//맞을때_우산.bmp", 42, 74, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("waddleDoo_hit_um")->setFrameX(0);
	IMAGEMANAGER->findImage("waddleDoo_hit_um")->setFrameY(1);

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

void WaddleDoo::release()
{
}

void WaddleDoo::update()
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

void WaddleDoo::render()
{

}

void WaddleDoo::draw(RECT rcFocus)
{
	int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("waddleDoo_walk")->getFrameWidth(), IMAGEMANAGER->findImage("beem_walk")->getFrameHeight());
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
