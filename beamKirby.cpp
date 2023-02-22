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
	_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_STOP");
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
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_STOP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_STOP");
		_motion->start();
		break;
	case RIGHT_STOP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_STOP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_STOP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_LOW_STOP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_UP");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_UP");
		_motion->start();
		break;
	case LEFT_LOW_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_LOW_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_STOP_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_HIGH_STOP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_UP");
		_motion->start();
		break;
	case LEFT_HIGH_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_HIGH_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_STOP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_STOP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_STOP_DOWN");
		break;
	case LEFT_SIT:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_SIT");
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion->start();
		break;
	case RIGHT_SIT:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_SIT");
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion->start();
		break;
	case LEFT_LOW_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_LOW_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_SIT_DOWN");
		_motion->start();
		break;
	case RIGHT_LOW_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_SIT_DOWN");
		_motion->start();
		break;
	case LEFT_LOW_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_LOW_SIT_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_SIT_UP");
		_motion->start();
		break;
	case RIGHT_LOW_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_LOW_SIT_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_LOW_SIT_UP");
		break;
	case LEFT_HIGH_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_HIGH_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_SIT_DOWN");
		_motion->start();
		break;
	case RIGHT_HIGH_SIT_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_SIT_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_SIT_DOWN");
		_motion->start();
		break;
	case LEFT_HIGH_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_HIGH_SIT_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_SIT_UP");
		_motion->start();
		break;
	case RIGHT_HIGH_SIT_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_HIGH_SIT_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_HIGH_SIT_UP");
		_motion->start();
		break;
	case LEFT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_MOVE");
		_image = IMAGEMANAGER->findImage("��Ŀ��_MOVE");
		_motion->start();
		break;
	case RIGHT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_MOVE");
		_image = IMAGEMANAGER->findImage("��Ŀ��_MOVE");
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
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_DASH");
		_image = IMAGEMANAGER->findImage("��Ŀ��_DASH");
		_motion->start();
		break;
	case RIGHT_DASH:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_DASH");
		_image = IMAGEMANAGER->findImage("��Ŀ��_DASH");
		_motion->start();
		break;
	case LEFT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_EAT");
		_motion->start();
		break;
	case RIGHT_FLY_EAT:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_EAT");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_EAT");
		_motion->start();
		break;
	case LEFT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_UP");
		_motion->start();
		break;
	case RIGHT_FLY_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_UP");
		_motion->start();
		break;
	case LEFT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_DOWN");
		_motion->start();
		break;
	case RIGHT_FLY_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY_DOWN");
		_motion->start();
		break;
	case LEFT_FLY:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_FLY");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY");
		_motion->start();
		break;
	case RIGHT_FLY:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_FLY");
		_image = IMAGEMANAGER->findImage("��Ŀ��_FLY");
		_motion->start();
		break;
	case LEFT_JUMP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case RIGHT_JUMP_UP:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_UP");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case LEFT_JUMP_TURN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case RIGHT_JUMP_TURN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case LEFT_JUMP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion->start();
		break;
	case RIGHT_JUMP_DOWN:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_DOWN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_SIT");
		_motion->start();
		break;
	case LEFT_KICK:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_KICK");
		_image = IMAGEMANAGER->findImage("��Ŀ��_KICK");
		_motion->start();
		break;
	case RIGHT_KICK:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_KICK");
		_image = IMAGEMANAGER->findImage("��Ŀ��_KICK");
		_motion->start();
		break;
	case LEFT_THROW:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_THROW");
		_image = IMAGEMANAGER->findImage("��Ŀ��_THROW");
		_motion->start();
		break;
	case RIGHT_THROW:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_THROW");
		_image = IMAGEMANAGER->findImage("��Ŀ��_THROW");
		_motion->start();
		break;
	case LEFT_FALL:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case RIGHT_FALL:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_JUMP_TURN");
		_image = IMAGEMANAGER->findImage("��Ŀ��_JUMP");
		_motion->start();
		break;
	case LEFT_ATTACK:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_ATTACK");
		_image = IMAGEMANAGER->findImage("��Ŀ��_ATTACK");
		_motion->start();
		attack();
		_kirby->setIsAttack(true);
		break;
	case RIGHT_ATTACK:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_ATTACK");
		_image = IMAGEMANAGER->findImage("��Ŀ��_ATTACK");
		_motion->start();
		attack();
		_kirby->setIsAttack(true);
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
	case LEFT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_LEFT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("��Ŀ��_OPENDOOR");
		_motion->start();
		break;
	case RIGHT_OPEN_DOOR:
		_motion = KEYANIMANAGER->findAnimation("��Ŀ��_RIGHT_OPENDOOR");
		_image = IMAGEMANAGER->findImage("��Ŀ��_OPENDOOR");
		_motion->start();
		break;
	default:
		break;
	}
}


void  beamKirby::initImage()
{
	///////////////////// �� Ŀ�� //////////////////////////////
	//�̹��� �߰�

	//STOP
	_image = IMAGEMANAGER->addFrameImage("��Ŀ��_STOP", "image\\characters\\kirby\\��Ŀ��\\BEAM_STOP.bmp", 64 * 2, 64 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\BEAM_HIGH_STOP_UP.bmp", 58 * 2, 66 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\BEAM_HIGH_STOP_DOWN.bmp", 60 * 2, 66 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_UP", "image\\characters\\kirby\\��Ŀ��\\BEAM_LOW_STOP_UP.bmp", 62 * 2, 62 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_STOP_DOWN", "image\\characters\\kirby\\��Ŀ��\\BEAM_LOW_STOP_DOWN.bmp", 58 * 2, 64 * 2, 2, 2, true, RGB(255, 0, 255));

	//SIT
	IMAGEMANAGER->addFrameImage("��Ŀ��_SIT", "image\\characters\\kirby\\��Ŀ��\\BEAM_SIT.bmp", 60 * 2, 50 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_SIT_UP", "image\\characters\\kirby\\��Ŀ��\\BEAM_HIGH_SIT_UP.bmp", 62 * 2, 52 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_HIGH_SIT_DOWN", "image\\characters\\kirby\\��Ŀ��\\BEAM_HIGH_SIT_DOWN.bmp", 60 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_SIT_UP", "image\\characters\\kirby\\��Ŀ��\\BEAM_LOW_SIT_UP.bmp", 62 * 2, 56 * 2, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_LOW_SIT_DOWN", "image\\characters\\kirby\\��Ŀ��\\BEAM_LOW_SIT_DOWN.bmp", 60 * 2, 54 * 2, 2, 2, true, RGB(255, 0, 255));

	//MOVE
	IMAGEMANAGER->addFrameImage("��Ŀ��_MOVE", "image\\characters\\kirby\\��Ŀ��\\BEAM_MOVE.bmp", 360 * 2, 60 * 2, 12, 2, true, RGB(255, 0, 255));


	//FLY	
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_EAT", "image\\characters\\kirby\\��Ŀ��\\BEAM_FLY_EAT.bmp", 165 * 2, 62 * 2, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_UP", "image\\characters\\kirby\\��Ŀ��\\BEAM_FLY_UP.bmp", 204 * 2, 76 * 2, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY_DOWN", "image\\characters\\kirby\\��Ŀ��\\BEAM_FLY_DOWN.bmp", 136 * 2, 76 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��_FLY", "image\\characters\\kirby\\��Ŀ��\\BEAM_FLY.bmp", 288 * 2, 80 * 2, 8, 2, true, RGB(255, 0, 255));


	//������
	IMAGEMANAGER->addFrameImage("��Ŀ��_OPENDOOR", "image\\characters\\kirby\\��Ŀ��\\BEAM_OPENDOOR.bmp", 160 * 2, 60 * 2, 5, 2, true, RGB(255, 0, 255));


	//�뽬
	IMAGEMANAGER->addFrameImage("��Ŀ��_DASH", "image\\characters\\kirby\\��Ŀ��\\BEAM_DASH.bmp", 264 * 2, 60 * 2, 8, 2, true, RGB(255, 0, 255));


	//JUMP
	IMAGEMANAGER->addFrameImage("��Ŀ��_JUMP", "image\\characters\\kirby\\��Ŀ��\\BEAM_JUMP.bmp", 702 * 2, 88 * 2, 18, 2, true, RGB(255, 0, 255));


	//TACKLE
	IMAGEMANAGER->addFrameImage("��Ŀ��_KICK", "image\\characters\\kirby\\��Ŀ��\\BEAM_TACKLE.bmp", 144 * 2, 60 * 2, 3, 2, true, RGB(255, 0, 255));


	//����
	IMAGEMANAGER->addFrameImage("��Ŀ��_ATTACK", "image\\characters\\kirby\\��Ŀ��\\BEAM_ATTACK.bmp", 570 * 2, 58 * 2, 15, 2, true, RGB(255, 0, 255));

	//�߶�

	//��
	IMAGEMANAGER->addFrameImage("BEAM", "image\\characters\\kirby\\��Ŀ��\\��.bmp", 168 * 2, 26 * 2, 6, 1, true, RGB(255, 0, 255));

	//����ũ
	IMAGEMANAGER->addFrameImage("SPARK", "image\\characters\\kirby\\��Ŀ��\\����ũ.bmp", 72 * 2, 22 * 2, 3, 1, true, RGB(255, 0, 255));


	//Ű�� �߰�
	// �� Ŀ�� STOP ( LEFT / RIGHT ) 
	int arrBeamKirbyRightStop[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int arrBeamKirbyLeftStop[] = { 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_STOP", "��Ŀ��_STOP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_STOP", "��Ŀ��_STOP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_STOP_UP", "��Ŀ��_HIGH_STOP_UP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_STOP_UP", "��Ŀ��_HIGH_STOP_UP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_STOP_DOWN", "��Ŀ��_HIGH_STOP_DOWN", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_STOP_DOWN", "��Ŀ��_HIGH_STOP_DOWN", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_STOP_UP", "��Ŀ��_LOW_STOP_UP", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_STOP_UP", "��Ŀ��_LOW_STOP_UP", arrBeamKirbyLeftStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_STOP_DOWN", "��Ŀ��_LOW_STOP_DOWN", arrBeamKirbyRightStop, 13, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_STOP_DOWN", "��Ŀ��_LOW_STOP_DOWN", arrBeamKirbyLeftStop, 13, 6, true);

	// �� Ŀ�� SIT ( LEFT / RIGHT ) 
	int arrBeamKirbyRightSit[] = { 0, 1 };
	int arrBeamKirbyLeftSit[] = { 3, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_SIT", "��Ŀ��_SIT", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_SIT", "��Ŀ��_SIT", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_SIT_UP", "��Ŀ��_HIGH_SIT_UP", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_SIT_UP", "��Ŀ��_HIGH_SIT_UP", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_HIGH_SIT_DOWN", "��Ŀ��_HIGH_SIT_DOWN", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_HIGH_SIT_DOWN", "��Ŀ��_HIGH_SIT_DOWN", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_SIT_UP", "��Ŀ��_LOW_SIT_UP", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_SIT_UP", "��Ŀ��_LOW_SIT_UP", arrBeamKirbyLeftSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_LOW_SIT_DOWN", "��Ŀ��_LOW_SIT_DOWN", arrBeamKirbyRightSit, 2, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_LOW_SIT_DOWN", "��Ŀ��_LOW_SIT_DOWN", arrBeamKirbyLeftSit, 2, 6, true);



	// �� Ŀ�� MOVE ( LEFT / RIGHT )
	int arrBeamKirbyRightMove[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	int arrBeamKirbyLeftMove[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_MOVE", "��Ŀ��_MOVE", arrBeamKirbyRightMove, 12, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_MOVE", "��Ŀ��_MOVE", arrBeamKirbyLeftMove, 12, 9, true);


	// �� Ŀ�� ������
	int arrBeamKirbyRightOpenDoor[] = { 9,8,7,6,5 };
	int arrBeamKirbyLeftOpenDoor[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_OPENDOOR", "��Ŀ��_OPENDOOR", arrBeamKirbyRightOpenDoor, 5, 12, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_OPENDOOR", "��Ŀ��_OPENDOOR", arrBeamKirbyLeftOpenDoor, 5, 12, false);


	// �� Ŀ�� �뽬
	int arrBeamKirbyRightDash[] = { 0,1,2,3,4,5,6,7 };
	int arrBeamKirbyLeftDash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_DASH", "��Ŀ��_DASH", arrBeamKirbyRightDash, 8, 12, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_DASH", "��Ŀ��_DASH", arrBeamKirbyLeftDash, 8, 12, true);


	// �� Ŀ�� JUMP UP
	int arrBeamKirbyRightJumpUp[] = { 1,0 };
	int arrBeamKirbyLeftJumpUp[] = { 34,35 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_UP", "��Ŀ��_JUMP", arrBeamKirbyRightJumpUp, 2, 22, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_UP", "��Ŀ��_JUMP", arrBeamKirbyLeftJumpUp, 2, 22, false);


	// �� Ŀ�� JUMP TURN
	int arrBeamKirbyRightJumpTurn[] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	int arrBeamKirbyLeftJumpTurn[] = { 33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_TURN", "��Ŀ��_JUMP", arrBeamKirbyRightJumpTurn, 14, 33, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_TURN", "��Ŀ��_JUMP", arrBeamKirbyLeftJumpTurn, 14, 33, false);

	// �� Ŀ�� JUMP DOWN
	int arrBeamKirbyRightJumpDown[] = { 0,0 };
	int arrBeamKirbyLeftJumpDown[] = { 3,3 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_JUMP_DOWN", "��Ŀ��_SIT", arrBeamKirbyRightJumpDown, 2, 9, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_JUMP_DOWN", "��Ŀ��_SIT", arrBeamKirbyLeftJumpDown, 2, 9, false);


	// �� Ŀ�� ��Ŭ( KICK )
	int arrBeamKirbyRightKick[] = { 0,1,1,1,1,1,1,2 };
	int arrBeamKirbyLeftKick[] = { 5,4,4,4,4,4,4,3 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_KICK", "��Ŀ��_KICK", arrBeamKirbyRightKick, 8, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_KICK", "��Ŀ��_KICK", arrBeamKirbyLeftKick, 8, 6, true);


	// �� Ŀ�� ���� ATTACK
	int arrBeamKirbyRightAttack[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int arrBeamKirbyLeftAttack[] = { 29,28,27,26,25,24,23,22,21,20,19,18,17,16,15 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_ATTACK", "��Ŀ��_ATTACK", arrBeamKirbyRightAttack, 15, 15, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_ATTACK", "��Ŀ��_ATTACK", arrBeamKirbyLeftAttack, 15, 15, false);

	// �� Ŀ�� FLY_EAT
	int arrBeamKirbyRightFlyEat[] = { 0,1,2,3,4 };
	int arrBeamKirbyLeftFlyEat[] = { 9,8,7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_EAT", "��Ŀ��_FLY_EAT", arrBeamKirbyRightFlyEat, 5, 9, false);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_EAT", "��Ŀ��_FLY_EAT", arrBeamKirbyLeftFlyEat, 5, 9, false);


	// �� Ŀ�� FLY (L / R)
	int arrBeamKirbyRightFly[] = { 0,1,2,3,4,5,6,7 };
	int arrBeamKirbyLeftFly[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY", "��Ŀ��_FLY", arrBeamKirbyRightFly, 8, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY", "��Ŀ��_FLY", arrBeamKirbyLeftFly, 8, 9, true);


	// �� Ŀ�� FlY UP (L / R)
	int arrBeamKirbyRightFlyUp[] = { 0,1,2,3,4,5 };
	int arrBeamKirbyLeftFlyUp[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_UP", "��Ŀ��_FLY_UP", arrBeamKirbyRightFlyUp, 6, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_UP", "��Ŀ��_FLY_UP", arrBeamKirbyLeftFlyUp, 6, 9, true);

	// �� Ŀ�� FLY DOWN (L / R)
	int arrBeamKirbyRightFlyDown[] = { 0,1,2,3 };
	int arrBeamKirbyLeftFlyDown[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_RIGHT_FLY_DOWN", "��Ŀ��_FLY_DOWN", arrBeamKirbyRightFlyDown, 4, 9, true);
	KEYANIMANAGER->addArrayFrameAnimation("��Ŀ��_LEFT_FLY_DOWN", "��Ŀ��_FLY_DOWN", arrBeamKirbyLeftFlyDown, 4, 9, true);



}


void beamKirby::attack()
{
	
	//Ŀ�� �߽���ǥ��
	float cx = _kirby->getCenterX();
	float cy = _kirby->getCenterY();


	_angle = PI/2;


	//�� �ʱ�ȭ
	for (int i = 0; i < 6; i++)
	{
		//���η� ����
		_beam[i].x = cx-15;
		_beam[i].y = cy - i * 20-15;
		_beam[i].r = i * 15 +25;

		//��Ʈ ������
		_beam[i].rc = RectMakeCenter(_kirby->getCenterX()+cosf(_angle)*_beam[i].r, _kirby->getCenterY() - sinf(_angle)*_beam[i].r, 30, 30);

		//��
		_beam[i].image = IMAGEMANAGER->addFrameImage("BEAM", "image\\characters\\kirby\\��Ŀ��\\��.bmp", 168, 26, 6, 1, true, RGB(255, 0, 255));
		
	}


	
}



void beamKirby::beamMove()
{
	//isAttack �϶��� render / move
	//update �� move �־����!




	//������ ����
	if (_kirby->getIsRight())
	{
		//�ޱۿ����̰�
		_angle -= 0.06f;
		//if (_angle <= 0) _angle += PI2;

		//135�� �����̸� �׸�
		if ((START_ANGLE - _angle) > PI4*3)
		{
			//��Ʈ����
			for (int i = 0; i < 6; i++)
			{
				_beam[i].rc = RectMake( 0, 0, 0, 0 );					
			}
			_kirby->setIsAttack(false);
			_kirby->setState(RIGHT_STOP);
		}
	}
	//����
	else
	{
		//�ޱۿ����̰�
		_angle += 0.06f;

		//if (_angle >= PI2) _angle -= PI2;

		//135�� �����̸� �׸�
		if (_angle - START_ANGLE > PI4 * 3)
		{
			//��Ʈ����
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
