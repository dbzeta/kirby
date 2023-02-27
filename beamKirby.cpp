#include "stdafx.h"
#include "beamKirby.h"
#include "kirby.h"


beamKirby::beamKirby()
{
}


beamKirby::~beamKirby()
{
}


HRESULT beamKirby::init()
{
	initImage();

	_kirby->setState(RIGHT_STOP);
	_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_STOP");
	_motion->start();

	return S_OK;
}

void beamKirby::release()
{

}

void beamKirby::update()
{
	KEYANIMANAGER->update();
	if(_kirby->getState() == LEFT_ATTACK || _kirby->getState() == RIGHT_ATTACK)
	{
		beamMove();
	}
}

void beamKirby::render(RECT rcFocus)
{
	_rc = _kirby->getRect();
	RECT eatRC = _kirby->getEatRect();
	
	if(_kirby->getState() == LEFT_ATTACK || _kirby->getState() == RIGHT_ATTACK)
	{
		for(int i=0;i<6;i++)
		{
			IMAGEMANAGER->findImage("BEAM")->frameRender(getMemDC(),_beam[i].rc.left - rcFocus.left-20, _beam[i].rc.top - rcFocus.top-15,i,0);
		}
	}

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

		for (int i = 0; i < 6; i++)
		{
			Rectangle(getMemDC(),_beam[i].x-rcFocus.left,_beam[i].y-rcFocus.top,_beam[i].x-rcFocus.left+30,_beam[i].y-rcFocus.top+30);
		}
	}

	_image->aniRender(getMemDC(), x, y, _motion);

}


void  beamKirby::setMotion()
{
	STATE state = _kirby->getState();

	switch (state)
	{
	case LEFT_STOP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_STOP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_STOP");
		_motion->start();
		break;
	case RIGHT_STOP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_STOP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_STOP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_LOW_STOP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_STOP_UP");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_LOW_STOP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_STOP_UP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_LOW_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_LOW_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_HIGH_STOP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_STOP_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_HIGH_STOP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_STOP_UP");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_HIGH_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_HIGH_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_STOP_DOWN");
		break;
	case LEFT_SIT:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_SIT");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_SIT");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_SIT");
		_motion->start();
		break;
	case LEFT_LOW_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_LOW_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_SIT_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_LOW_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_SIT_DOWN");
		_motion->start();
		break;
	case LEFT_LOW_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_LOW_SIT_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_SIT_UP");
		_motion->start();
		break;
	case RIGHT_LOW_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_LOW_SIT_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_LOW_SIT_UP");
		break;
	case LEFT_HIGH_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_HIGH_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_SIT_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_HIGH_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_SIT_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_HIGH_SIT_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_SIT_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_HIGH_SIT_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_HIGH_SIT_UP");
		_motion->start();
		break;
	case LEFT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_MOVE");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_MOVE");
		_motion->start();
		break;
	case RIGHT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_MOVE");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_MOVE");
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
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_DASH");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_DASH");
		_motion->start();
		break;
	case RIGHT_DASH:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_DASH");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_DASH");
		_motion->start();
		break;
	case LEFT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_FLY_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_FLY_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_FLY");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_FLY");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_FLY");
		_motion->start();
		break;
	case LEFT_JUMP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_JUMP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case RIGHT_JUMP_UP:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_JUMP_UP");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case LEFT_JUMP_TURN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case RIGHT_JUMP_TURN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case LEFT_JUMP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_JUMP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_SIT");
		_motion->start();
		break;
	case RIGHT_JUMP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_JUMP_DOWN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_SIT");
		_motion->start();
		break;
	case LEFT_KICK:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_KICK");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_KICK");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_KICK");
		_motion->start();
		break;
	case LEFT_THROW:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_THROW");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_THROW");
		_motion->start();
		break;
	case RIGHT_THROW:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_THROW");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_THROW");
		_motion->start();
		break;
	case LEFT_FALL:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case RIGHT_FALL:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_JUMP");
		_motion->start();
		break;
	case LEFT_ATTACK:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_ATTACK");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_ATTACK");
		_motion->start();
		attack();
		_kirby->setIsAttack(true);
		break;
	case RIGHT_ATTACK:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_ATTACK");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_ATTACK");
		_motion->start();
		attack();
		_kirby->setIsAttack(true);
		break;
	case LEFT_RETURN:
		break;
	case RIGHT_RETURN:
		break;
	case LEFT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("³ë¸»Ä¿ºñ_LEFT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("³ë¸»Ä¿ºñ_COLLISION");
		_motion->start();
		break;
	case RIGHT_CRASH:
		_motion = KEYANIMANAGER->findAnimation("³ë¸»Ä¿ºñ_RIGHT_NORMAL_COLLISION");
		_image = IMAGEMANAGER->findImage("³ë¸»Ä¿ºñ_COLLISION");
		_motion->start();
		break;
	case LEFT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_LEFT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("ºöÄ¿ºñ_RIGHT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("ºöÄ¿ºñ_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}
}


void  beamKirby::initImage()
{
	///////////////////// ºö Ä¿ºñ //////////////////////////////
	//ÀÌ¹ÌÁö Ãß°¡

	//STOP
	_image = IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_STOP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_STOP.bmp", 64 * 2, 64 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_HIGH_STOP_UP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_HIGH_STOP_UP.bmp", 58 * 2, 66 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_HIGH_STOP_DOWN", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_HIGH_STOP_DOWN.bmp", 60 * 2, 66 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_LOW_STOP_UP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_LOW_STOP_UP.bmp", 62 * 2, 62 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_LOW_STOP_DOWN", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_LOW_STOP_DOWN.bmp", 58 * 2, 64 * 2, 2, 2, true, RGB(255, 0, 255));

	//SIT
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_SIT", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_SIT.bmp", 60 * 2, 50 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_HIGH_SIT_UP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_HIGH_SIT_UP.bmp", 62 * 2, 52 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_HIGH_SIT_DOWN", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_HIGH_SIT_DOWN.bmp", 60 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_LOW_SIT_UP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_LOW_SIT_UP.bmp", 62 * 2, 56 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_LOW_SIT_DOWN", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_LOW_SIT_DOWN.bmp", 60 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//MOVE
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_MOVE", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_MOVE.bmp", 360 * 2, 60 * 2, 12, 2, true, RGB(255, 0, 255));


	//FLY	
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_FLY_EAT", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_FLY_EAT.bmp", 165 * 2, 62 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_FLY_UP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_FLY_UP.bmp", 204 * 2, 76 * 2, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_FLY_DOWN", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_FLY_DOWN.bmp", 136 * 2, 76 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_FLY", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_FLY.bmp", 288 * 2, 80 * 2, 8, 2, true, RGB(255, 0, 255));


	//¹®¿­±â
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_OPENDOOR", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_OPENDOOR.bmp", 160 * 2, 60 * 2, 5, 2, true, RGB(255, 0, 255));


	//´ë½¬
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_DASH", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_DASH.bmp", 264 * 2, 60 * 2, 8, 2, true, RGB(255, 0, 255));


	//JUMP
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_JUMP", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_JUMP.bmp", 702 * 2, 88 * 2, 18, 2, true, RGB(255, 0, 255));


	//TACKLE
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_KICK", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_TACKLE.bmp", 144 * 2, 60 * 2, 3, 2, true, RGB(255, 0, 255));


	//°ø°Ý
	IMAGEMANAGER->addFrameImage("ºöÄ¿ºñ_ATTACK", "image\\characters\\kirby\\ºöÄ¿ºñ\\BEAM_ATTACK.bmp", 570 * 2, 58 * 2, 15, 2, true, RGB(255, 0, 255));

	//Ãß¶ô

	//ºö
	IMAGEMANAGER->addFrameImage("BEAM", "image\\characters\\kirby\\ºöÄ¿ºñ\\ºö.bmp", 168 * 2, 26 * 2, 6, 1, true, RGB(255, 0, 255));

	//½ºÆÄÅ©
	IMAGEMANAGER->addFrameImage("SPARK", "image\\characters\\kirby\\ºöÄ¿ºñ\\½ºÆÄÅ©.bmp", 72 * 2, 22 * 2, 3, 1, true, RGB(255, 0, 255));


	//Å°°ª Ãß°¡
	// ºö Ä¿ºñ STOP ( LEFT / RIGHT ) 
	int arrBeamKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrBeamKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_STOP", "ºöÄ¿ºñ_STOP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_STOP", "ºöÄ¿ºñ_STOP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_HIGH_STOP_UP", "ºöÄ¿ºñ_HIGH_STOP_UP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_HIGH_STOP_UP", "ºöÄ¿ºñ_HIGH_STOP_UP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_HIGH_STOP_DOWN", "ºöÄ¿ºñ_HIGH_STOP_DOWN", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_HIGH_STOP_DOWN", "ºöÄ¿ºñ_HIGH_STOP_DOWN", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_LOW_STOP_UP", "ºöÄ¿ºñ_LOW_STOP_UP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_LOW_STOP_UP", "ºöÄ¿ºñ_LOW_STOP_UP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_LOW_STOP_DOWN", "ºöÄ¿ºñ_LOW_STOP_DOWN", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_LOW_STOP_DOWN", "ºöÄ¿ºñ_LOW_STOP_DOWN", arrBeamKirbyLeftStop, 13, 6, true);

	// ºö Ä¿ºñ SIT ( LEFT / RIGHT ) 
	int arrBeamKirbyRightSit[] = { 0, 1 };
	int arrBeamKirbyLeftSit[] = { 3, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_SIT", "ºöÄ¿ºñ_SIT", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_SIT", "ºöÄ¿ºñ_SIT", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_HIGH_SIT_UP", "ºöÄ¿ºñ_HIGH_SIT_UP", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_HIGH_SIT_UP", "ºöÄ¿ºñ_HIGH_SIT_UP", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_HIGH_SIT_DOWN", "ºöÄ¿ºñ_HIGH_SIT_DOWN", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_HIGH_SIT_DOWN", "ºöÄ¿ºñ_HIGH_SIT_DOWN", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_LOW_SIT_UP", "ºöÄ¿ºñ_LOW_SIT_UP", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_LOW_SIT_UP", "ºöÄ¿ºñ_LOW_SIT_UP", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_LOW_SIT_DOWN", "ºöÄ¿ºñ_LOW_SIT_DOWN", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_LOW_SIT_DOWN", "ºöÄ¿ºñ_LOW_SIT_DOWN", arrBeamKirbyLeftSit, 2, 6, true);



	// ºö Ä¿ºñ MOVE ( LEFT / RIGHT )
	int arrBeamKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	int arrBeamKirbyLeftMove[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_MOVE", "ºöÄ¿ºñ_MOVE", arrBeamKirbyRightMove, 12, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_MOVE", "ºöÄ¿ºñ_MOVE", arrBeamKirbyLeftMove, 12, 9, true);


	// ºö Ä¿ºñ ¹®¿­±â
	int arrBeamKirbyRightOpenDoor[] = { 9,8,7,6,5 };
	int arrBeamKirbyLeftOpenDoor[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_OPENDOOR", "ºöÄ¿ºñ_OPENDOOR", arrBeamKirbyRightOpenDoor, 5, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_OPENDOOR", "ºöÄ¿ºñ_OPENDOOR", arrBeamKirbyLeftOpenDoor, 5, 12, false);


	// ºö Ä¿ºñ ´ë½¬
	int arrBeamKirbyRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrBeamKirbyLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_DASH", "ºöÄ¿ºñ_DASH", arrBeamKirbyRightDash, 8, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_DASH", "ºöÄ¿ºñ_DASH", arrBeamKirbyLeftDash, 8, 12, true);


	// ºö Ä¿ºñ JUMP UP
	int arrBeamKirbyRightJumpUp[] = { 1,0 };
	int arrBeamKirbyLeftJumpUp[] = { 34,35 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_JUMP_UP", "ºöÄ¿ºñ_JUMP", arrBeamKirbyRightJumpUp, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_JUMP_UP", "ºöÄ¿ºñ_JUMP", arrBeamKirbyLeftJumpUp, 2, 22, false);


	// ºö Ä¿ºñ JUMP TURN
	int arrBeamKirbyRightJumpTurn[] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	int arrBeamKirbyLeftJumpTurn[] = { 33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_JUMP_TURN", "ºöÄ¿ºñ_JUMP", arrBeamKirbyRightJumpTurn, 14, 33, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_JUMP_TURN", "ºöÄ¿ºñ_JUMP", arrBeamKirbyLeftJumpTurn, 14, 33, false);

	// ºö Ä¿ºñ JUMP DOWN
	int arrBeamKirbyRightJumpDown[] = { 0,0 };
	int arrBeamKirbyLeftJumpDown[] = { 3,3 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_JUMP_DOWN", "ºöÄ¿ºñ_SIT", arrBeamKirbyRightJumpDown, 2, 9, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_JUMP_DOWN", "ºöÄ¿ºñ_SIT", arrBeamKirbyLeftJumpDown, 2, 9, false);


	// ºö Ä¿ºñ ÅÂÅ¬( KICK )
	int arrBeamKirbyRightKick[] = { 0,1,1,1,1,1,1,2 };
	int arrBeamKirbyLeftKick[] = { 5,4,4,4,4,4,4,3 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_KICK", "ºöÄ¿ºñ_KICK", arrBeamKirbyRightKick, 8, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_KICK", "ºöÄ¿ºñ_KICK", arrBeamKirbyLeftKick, 8, 6, true);


	// ºö Ä¿ºñ °ø°Ý ATTACK
	int arrBeamKirbyRightAttack[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int arrBeamKirbyLeftAttack[] = { 29,28,27,26,25,24,23,22,21,20,19,18,17,16,15 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_ATTACK", "ºöÄ¿ºñ_ATTACK", arrBeamKirbyRightAttack, 15, 15, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_ATTACK", "ºöÄ¿ºñ_ATTACK", arrBeamKirbyLeftAttack, 15, 15, false);

	// ºö Ä¿ºñ FLY_EAT
	int arrBeamKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrBeamKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_FLY_EAT", "ºöÄ¿ºñ_FLY_EAT", arrBeamKirbyRightFlyEat, 5, 9, false);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_FLY_EAT", "ºöÄ¿ºñ_FLY_EAT", arrBeamKirbyLeftFlyEat, 5, 9, false);


	// ºö Ä¿ºñ FLY (L / R)
	int arrBeamKirbyRightFly[] = { 0,1,2,3,4,5,6,7 };
	int arrBeamKirbyLeftFly[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_FLY", "ºöÄ¿ºñ_FLY", arrBeamKirbyRightFly, 8, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_FLY", "ºöÄ¿ºñ_FLY", arrBeamKirbyLeftFly, 8, 9, true);


	// ºö Ä¿ºñ FlY UP (L / R)
	int arrBeamKirbyRightFlyUp[] = { 0,1,2,3,4,5 };
	int arrBeamKirbyLeftFlyUp[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_FLY_UP", "ºöÄ¿ºñ_FLY_UP", arrBeamKirbyRightFlyUp, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_FLY_UP", "ºöÄ¿ºñ_FLY_UP", arrBeamKirbyLeftFlyUp, 6, 9, true);

	// ºö Ä¿ºñ FLY DOWN (L / R)
	int arrBeamKirbyRightFlyDown[] = { 0,1,2,3 };
	int arrBeamKirbyLeftFlyDown[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_RIGHT_FLY_DOWN", "ºöÄ¿ºñ_FLY_DOWN", arrBeamKirbyRightFlyDown, 4, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("ºöÄ¿ºñ_LEFT_FLY_DOWN", "ºöÄ¿ºñ_FLY_DOWN", arrBeamKirbyLeftFlyDown, 4, 9, true);



}


void beamKirby::attack()
{
	
	//Ä¿ºñ Áß½ÉÁÂÇ¥°ª
	float cx = _kirby->getCenterX();
	float cy = _kirby->getCenterY();


	_angle = PI/2;


	//ºö ÃÊ±âÈ­
	for (int i = 0; i < 6; i++)
	{
		//¼¼·Î·Î ¼¼¿ò
		_beam[i].x = cx-15;
		_beam[i].y = cy - i * 20-15;
		_beam[i].r = i * 15 +25;

		//·ºÆ® ¸¸µéÀÚ
		_beam[i].rc = RectMakeCenter(_kirby->getCenterX()+cosf(_angle)*_beam[i].r, _kirby->getCenterY() - sinf(_angle)*_beam[i].r, 30, 30);

		//ºö
		_beam[i].image = IMAGEMANAGER->addFrameImage("BEAM", "image\\characters\\kirby\\ºöÄ¿ºñ\\ºö.bmp", 168, 26, 6, 1, true, RGB(255, 0, 255));
		
	}


	
}



void beamKirby::beamMove()
{
	//isAttack ÀÏ¶§¸¸ render / move
	//update ¿¡ move ³Ö¾î³õÀÚ!




	//¿À¸¥ÂÊ °ø°Ý
	if (_kirby->getIsRight())
	{
		//¾Þ±Û¿òÁ÷ÀÌ°Ô
		_angle -= 0.06f;
		//if (_angle <= 0) _angle += PI2;

		//135µµ ¿òÁ÷ÀÌ¸é ±×¸¸
		if ((START_ANGLE - _angle) > PI4*3)
		{
			//·ºÆ®²¨Á®
			for (int i = 0; i < 6; i++)
			{
				_beam[i].rc = RectMake( 0, 0, 0, 0 );					
			}
			_kirby->setIsAttack(false);
			_kirby->setState(RIGHT_STOP);
		}
	}
	//¿ÞÂÊ
	else
	{
		//¾Þ±Û¿òÁ÷ÀÌ°Ô
		_angle += 0.06f;

		//if (_angle >= PI2) _angle -= PI2;

		//135µµ ¿òÁ÷ÀÌ¸é ±×¸¸
		if (_angle - START_ANGLE > PI4 * 3)
		{
			//·ºÆ®²¨Á®
			for (int i = 0; i < 6; i++)
			{
				_beam[i].rc = RectMake( 0, 0, 0, 0 );
			}
			_kirby->setIsAttack(false);
			_kirby->setState(LEFT_STOP);

		}

	}


	for (int i = 0; i < 6; i++)
	{
		
		_beam[i].x = _kirby->getCenterX() + cosf(_angle)*_beam[i].r;
		_beam[i].y = _kirby->getCenterY() + -sinf(_angle) *_beam[i].r;
		_beam[i].rc = RectMake(_beam[i].x,_beam[i].y,30,30);
	}

}
