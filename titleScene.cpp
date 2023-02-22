#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	if (DATABASE->getElementData("backVolume") == "")
	{
		DATABASE->addElementData("backVolume", "1.0");
	}

	if (DATABASE->getElementData("effectVolume") == "")
	{
		DATABASE->addElementData("effectVolume", "1.0");
	}

	SOUNDMANAGER->addSound("fly", "sound\\fly.wav", false, false);
	SOUNDMANAGER->addSound("background", "sound\\title.mp3", true, true);
	SOUNDMANAGER->play("background", atof(DATABASE->getElementData("backVolume").c_str()));

	IMAGEMANAGER->addFrameImage("title", "image\\title.bmp",WINSIZEX, WINSIZEY*2,1,2,false,RGB(255,0,255));

	_alpha = 0;
	_canKey = true;

	return S_OK;
}

void titleScene::release()
{
	IMAGEMANAGER->deleteImage("title");
}

void titleScene::update()
{
	if (_canKey)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_canKey = false;
			SCENEMANAGER->fadeOut(changeScene);
		}
	}

	_alpha -= 500*TIMEMANAGER->getElapsedTime();
	if (_alpha < 0)
		_alpha = 150;
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("title")->frameRender(getMemDC(), 0, 0, 0, 0);
	IMAGEMANAGER->findImage("title")->alphaFrameRender(getMemDC(), 0, 0, 0, 1,_alpha);
}

void titleScene::changeScene()
{
	SCENEMANAGER->changeScene("menuScene");
}
