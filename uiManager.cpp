#include "stdafx.h"
#include "uiManager.h"
#include "kirby.h"
#include "enemyManager.h"


uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}

HRESULT uiManager::init()
{
	IMAGEMANAGER->addImage("hp", "image\\hp.bmp", 16, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp1", "image\\hp1.bmp", 16, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("life", "image\\life.bmp", 44, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "image\\gamenumber.bmp", 240, 33,10,1 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bosshp_top", "image\\bosshp_up.bmp", 160, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bosshp_bottom", "image\\bosshp_down.bmp", 160, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mode", "image\\mode.bmp", 480, 33, 4, 1, true, RGB(255, 0, 255));

	_kirbyHP = 0;
	_kirbyLife = 0;
	_score = 0;
	_visibleBossHP = false;
	_bossHP = NULL;

	return S_OK;
}

void uiManager::release()
{
	IMAGEMANAGER->deleteImage("hp");
	IMAGEMANAGER->deleteImage("hp1");
	IMAGEMANAGER->deleteImage("life");
	IMAGEMANAGER->deleteImage("number");
	IMAGEMANAGER->deleteImage("bosshp_top");
	IMAGEMANAGER->deleteImage("hosshp_bottom");
	IMAGEMANAGER->deleteImage("mode");
}

void uiManager::update()
{
	_kirbyHP = _kirby->getHp();
	_kirbyLife = _kirby->getLife();
}

void uiManager::render()
{

	IMAGEMANAGER->findImage("mode")->frameRender(getMemDC(), 20, WINSIZEY - 40, _kirby->getMode(), 0);

	IMAGEMANAGER->findImage("life")->render(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY - 30);
	IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), WINSIZEX / 2 - 102, WINSIZEY - 40, _kirbyLife / 10, 0);
	IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), WINSIZEX / 2 - 78, WINSIZEY - 40, _kirbyLife % 10, 0);

	for (int i = 0; i < 6; ++i)
	{
		if(_kirbyHP > i)
			IMAGEMANAGER->findImage("hp")->render(getMemDC(), WINSIZEX / 2 +(i*16), WINSIZEY - 35);
		else
			IMAGEMANAGER->findImage("hp1")->render(getMemDC(), WINSIZEX / 2 + (i * 16), WINSIZEY - 35);
	}

	if (_visibleBossHP)
	{
		IMAGEMANAGER->findImage("bosshp_bottom")->render(getMemDC(), WINSIZEX - 160, WINSIZEY - 40);
		//MIN 15 ~ MAX 145 (130)
		IMAGEMANAGER->findImage("bosshp_top")->render(getMemDC(), WINSIZEX - 160, WINSIZEY - 40, 0, 0, 145, 32);
	}
	else
	{
		for (int i = 0; i < 7; ++i)
		{
			if(i < 6)
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), WINSIZEX - 180 + (i*24), WINSIZEY - 40, (_score % (int)pow(10,7-i) )/ pow(10,6-i), 0);
			else
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), WINSIZEX - 180 + (i * 24), WINSIZEY - 40, _score % 10, 0);
		}
	}
}
