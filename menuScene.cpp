#include "stdafx.h"
#include "menuScene.h"


menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}

HRESULT menuScene::init()
{
	SOUNDMANAGER->addSound("background", "sound\\menu.mp3", true, true);
	SOUNDMANAGER->play("background", atof(DATABASE->getElementData("backVolume").c_str()));

	IMAGEMANAGER->addFrameImage("menu", "image\\menu.bmp", WINSIZEX * 2, WINSIZEY * 2, 2, 2, false, RGB(255, 0, 255));

	_selectIndex = 0;
	_alpha = 100;
	SCENEMANAGER->fadeIn(NULL);
	_canKey = true;
	return S_OK;
}

void menuScene::release()
{
	IMAGEMANAGER->deleteImage("menu");
}

void menuScene::update()
{
	if (_canKey)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_selectIndex -= 1;
			if (_selectIndex < 0)
				_selectIndex = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_selectIndex += 1;
			if (_selectIndex > 1)
				_selectIndex = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_canKey = false;
		SCENEMANAGER->fadeOut(changeScene,this);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_canKey = false;
		SCENEMANAGER->fadeOut(changeScene);
	}

	_alpha -= 300 * TIMEMANAGER->getElapsedTime();
	if (_alpha < 0)
		_alpha = 100;
}

void menuScene::render()
{
	IMAGEMANAGER->findImage("menu")->frameRender(getMemDC(), 0, 0, _selectIndex, 0);
	IMAGEMANAGER->findImage("menu")->alphaFrameRender(getMemDC(), 0, 0, _selectIndex, 1,_alpha);
}

void menuScene::changeScene(void* obj)
{
	menuScene* ms = (menuScene*)obj;
	switch (ms->getSelectIndex())
	{
	case 0: {
		SCENEMANAGER->changeScene("gameScene");
		if (DATABASE->getElementData("stage") == "")
		{
			DATABASE->addElementData("stage", "1");
		}
		else
		{
			DATABASE->setElementData("stage", "1");
		}
	}break;
	case 1: {
		SCENEMANAGER->changeScene("settingScene");
	}break;
	}
}

void menuScene::changeScene()
{
	SCENEMANAGER->changeScene("titleScene");
}
