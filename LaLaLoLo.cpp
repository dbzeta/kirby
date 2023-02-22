#include "stdafx.h"
#include "LaLaLoLo.h"


LaLaLoLo::LaLaLoLo()
{
}


LaLaLoLo::~LaLaLoLo()
{
}

HRESULT LaLaLoLo::init()
{
	_lala._bossImage = IMAGEMANAGER->addFrameImage("LalalaBack", "image//Enemy//boss//boss1//Lalala//LalalaBack.bmp", 240, 29, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LalalaFront", "image//Enemy//boss//boss1//Lalala//LalalaFront.bmp", 60, 29, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LalalaWalk", "image//Enemy//boss//boss1//Lalala//LalalaWalk.bmp", 150, 29, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LalalaWalk2", "image//Enemy//boss//boss1//Lalala//LalalaWalk2.bmp", 150, 29, 5, 2, true, RGB(255, 0, 255));

	_lolo._bossImage = IMAGEMANAGER->addFrameImage("LololoBack", "image//Enemy//boss//boss1//Lololo//LololoBack.bmp", 240, 29, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LololoFront", "image//Enemy//boss//boss1//Lololo//LololoFront.bmp", 60, 29, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LololoWalk", "image//Enemy//boss//boss1//Lololo//LololoWalk.bmp", 150, 29, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LololoWalk2", "image//Enemy//boss//boss1//Lololo//LololoWalk2.bmp", 150, 29, 5, 2, true, RGB(255, 0, 255));

	_lolo._block._BlockImage = IMAGEMANAGER->addFrameImage("LoloBlock", "image//Enemy//boss//boss1//Rect.bmp", 171, 29, 6, 1, true, RGB(255, 0, 255));
	_lala._block._BlockImage = IMAGEMANAGER->addFrameImage("LalaBlock", "image//Enemy//boss//boss1//Rect.bmp", 171, 29, 6, 1, true, RGB(255, 0, 255));



	return S_OK;
}

void LaLaLoLo::release()
{

}

void LaLaLoLo::update()
{


}

void LaLaLoLo::render()
{

}

void LaLaLoLo::draw(RECT rcFocus)
{
	/*int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("BBWalk")->getFrameWidth(), IMAGEMANAGER->findImage("BBWalk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;*/

	IMAGEMANAGER->findImage("www")->render(getMemDC());
}
