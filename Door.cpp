#include "stdafx.h"
#include "Door.h"
#include "mapManager.h"


Door::Door()
{
}


Door::~Door()
{
}

HRESULT Door::Doorinit(int X, int Y, string KeyName)
{

	//HubDoor
	_DoorCount = 0.0f;
	_NumberCount = 0.0f;
	_ClearCount = 0.0f;
	_DoorX = X;
	_DoorY = Y;
	_DoorKeyName = KeyName;
	CountTrue = false;
	StageStart = false;
	stageDoor = false;//스테이지 클리어불
					   //stageDoor-> 안씀 렉트크기 땜시 
	//StageDoorOpen = false;
	DoorTrue = false;
	
	_DoorRect = RectMakeCenter(_DoorX, _DoorY, 56 * 1.5, 24 * 2);
	IMAGEMANAGER->findImage(_DoorKeyName)->setFrameX(0);

	return S_OK;
}



void Door::release()
{
}

void Door::update()
{
	if (CountTrue && stageDoor)
	{
		DoorCount();
	}
	if (IMAGEMANAGER->findImage(_DoorKeyName + "Number") == IMAGEMANAGER->findImage("Door3Number"))
	{
		NumberCount();
	}
	ClearCount();
	
}

void Door::render()
{
	
}
void Door::DoorRectMake(RECT rcFocus)
{
	//문 상자 만듬
	int x, y;
	RECT rc = RectMakeCenter(_DoorX, _DoorY, IMAGEMANAGER->findImage(_DoorKeyName)->getFrameWidth(), IMAGEMANAGER->findImage(_DoorKeyName)->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;
	_DoorRectDraw = RectMakeCenter(x + (IMAGEMANAGER->findImage(_DoorKeyName)->getFrameWidth()/2),
									y + IMAGEMANAGER->findImage(_DoorKeyName)->getFrameHeight()/2, 
									IMAGEMANAGER->findImage(_DoorKeyName)->getFrameWidth(), 
									IMAGEMANAGER->findImage(_DoorKeyName)->getFrameHeight());
	Rectangle(getMemDC(), _DoorRectDraw.left, _DoorRectDraw.top, _DoorRectDraw.right, _DoorRectDraw.bottom);
}
void Door::draw(RECT rcFocus, bool Kuby, bool clear/*<-커비 렉트첵*/)
{
	int x, y;
	RECT rc = RectMakeCenter(_DoorX, _DoorY, IMAGEMANAGER->findImage(_DoorKeyName)->getFrameWidth(), IMAGEMANAGER->findImage(_DoorKeyName)->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;
	RECT temp;
	if (stageDoor)
	{	
		IMAGEMANAGER->findImage(_DoorKeyName)->frameRender(getMemDC(), x, y);
		
	}
	else
	{
		IMAGEMANAGER->findImage(_DoorKeyName + "Close")->render(getMemDC(), x, y);

	}
	if (IMAGEMANAGER->findImage(_DoorKeyName + "Number") != IMAGEMANAGER->findImage("Door3Number"))
	{
		IMAGEMANAGER->findImage(_DoorKeyName + "Number")->render(getMemDC(), x + 30, y - 25);
	}
	else
	{
		IMAGEMANAGER->findImage(_DoorKeyName + "Number")->frameRender(getMemDC(), x + 21, y - 35);
	}
	if (clear)
	{
		IMAGEMANAGER->findImage(_DoorKeyName + "clear")->frameRender(getMemDC(), x + 80, y + 10);

	}
	
}



void Door::DoorCount()
{
	_DoorCount += TIMEMANAGER->getElapsedTime();
	if (_DoorCount > 0.06f)
	{
		if (IMAGEMANAGER->findImage(_DoorKeyName)->getFrameX() > IMAGEMANAGER->findImage(_DoorKeyName)->getMaxFrameX()-1)
		{
			IMAGEMANAGER->findImage(_DoorKeyName)->setFrameX(0);
			StageStart = true;
		}
		else
		{
			IMAGEMANAGER->findImage(_DoorKeyName)->setFrameX(IMAGEMANAGER->findImage(_DoorKeyName)->getFrameX() + 1);
		}
		_DoorCount = 0.0f;
	}
}

void Door::NumberCount()
{
	_NumberCount += TIMEMANAGER->getElapsedTime();
	if (_NumberCount > 0.06f)
	{

		if (IMAGEMANAGER->findImage(_DoorKeyName + "Number")->getFrameX() > IMAGEMANAGER->findImage(_DoorKeyName + "Number")->getMaxFrameX() - 1)
		{
			IMAGEMANAGER->findImage(_DoorKeyName + "Number")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage(_DoorKeyName + "Number")->setFrameX(IMAGEMANAGER->findImage(_DoorKeyName + "Number")->getFrameX() + 1);
		}
		_NumberCount = 0.0f;
	}
}

void Door::ClearCount()
{
	_ClearCount += TIMEMANAGER->getElapsedTime();
	if (_ClearCount > 0.06f)
	{

		if (IMAGEMANAGER->findImage(_DoorKeyName + "clear")->getFrameX() > IMAGEMANAGER->findImage(_DoorKeyName + "clear")->getMaxFrameX() - 1)
		{
			IMAGEMANAGER->findImage(_DoorKeyName + "clear")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage(_DoorKeyName + "clear")->setFrameX(IMAGEMANAGER->findImage(_DoorKeyName + "clear")->getFrameX() + 1);
		}
		_ClearCount = 0.0f;
	}
}
