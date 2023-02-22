#include "stdafx.h"
#include "endScene.h"


endScene::endScene()
{
}


endScene::~endScene()
{
}

HRESULT endScene::init()
{
	_selectIndex = 0;

	IMAGEMANAGER->addFrameImage("end", "image\\end.bmp", WINSIZEX * 2, WINSIZEY,2,1,false,RGB(255,0,255));
	_hand = IMAGEMANAGER->addFrameImage("hand", "image\\hand.bmp", 290, 56, 5, 1, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("end1", "sound\\end1.wav", true, false);
	_handX = WINSIZEX / 2 - 20;
	_handY = WINSIZEY / 2 - 20;
	_handFrameX = 0;
	_canKey = true;
	_select = false;
	_count = 0;
	return S_OK;
}

void endScene::release()
{
	IMAGEMANAGER->deleteImage("end");
	IMAGEMANAGER->deleteImage("hand");
}

void endScene::update()
{
	if(_canKey)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_selectIndex -= 1;
			if (_selectIndex < 0)
				_selectIndex = 1;
			_handY = WINSIZEY / 2 - 20 + _selectIndex*60;
			SOUNDMANAGER->play("end1", atof(DATABASE->getElementData("effectVolume").c_str()));
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_selectIndex += 1;
			if (_selectIndex > 1)
				_selectIndex = 0;
			_handY = WINSIZEY / 2 - 20 + _selectIndex * 60;
			SOUNDMANAGER->play("end1", atof(DATABASE->getElementData("effectVolume").c_str()));
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_canKey = false;
		_select = true;
		SOUNDMANAGER->play("end1", atof(DATABASE->getElementData("effectVolume").c_str()));
	}

	if (_select)
	{
		if (_handFrameX == _hand->getMaxFrameX())
		{
			SCENEMANAGER->fadeOut(changeScene, this);
			_select = false;
		}
		_count += TIMEMANAGER->getElapsedTime();
		if (_count > 0.1)
		{
			_count = 0;
			_handFrameX += 1;
		}
	}
}

void endScene::render()
{
	IMAGEMANAGER->findImage("end")->frameRender(getMemDC(), 0, 0, _selectIndex, 0);
	_hand->frameRender(getMemDC(), _handX,_handY,_handFrameX,0);
}

void endScene::changeScene(void * obj)
{
	endScene* es = (endScene*)obj;
	switch (es->getSelectIndex())
	{
	case 0: {
		SCENEMANAGER->changeScene("gameScene");
	}break;
	case 1: {
		SCENEMANAGER->changeScene("titleScene");
	}break;
	}
}
