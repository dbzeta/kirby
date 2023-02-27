#include "stdafx.h"
#include "settingScene.h"


settingScene::settingScene()
{
}


settingScene::~settingScene()
{
}

HRESULT settingScene::init()
{
	_backVolume = atof(DATABASE->getElementData("backVolume").c_str());
	_effectVolume = atof(DATABASE->getElementData("effectVolume").c_str());

	IMAGEMANAGER->addFrameImage("setting", "image\\setting.bmp", WINSIZEX * 2, WINSIZEY * 2, 2, 2, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "image\\number.bmp", 610, 41, 10, 1, true, RGB(255, 0, 255));

	_selectIndex = 0;
	_alpha = 100;

	_backNumber = getNumber(_backVolume);
	_effectNumber = getNumber(_effectVolume);
	_canKey = true;

	SCENEMANAGER->fadeIn(NULL);

	return S_OK;
}

void settingScene::release()
{
	IMAGEMANAGER->deleteImage("setting");
	IMAGEMANAGER->deleteImage("number");
	char str[128];
	sprintf(str, "%2.1f", _backVolume);
	DATABASE->setElementData("backVolume", str);
	sprintf(str, "%2.1f", _effectVolume);
	DATABASE->setElementData("effectVolume", str);
}

void settingScene::update()
{
	if (_canKey)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_selectIndex == 0)
			{
				_backVolume -= 0.1f;
				if (_backVolume < 0.0f)
					_backVolume = 0.0f;

				SOUNDMANAGER->setVolume("background", _backVolume);
				_backNumber = getNumber(_backVolume);
			}
			else
			{
				_effectVolume -= 0.1f;
				if (_effectVolume < 0.0f)
					_effectVolume = 0.0f;

				SOUNDMANAGER->play("fly", _effectVolume);
				_effectNumber = getNumber(_effectVolume);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_selectIndex == 0)
			{
				_backVolume += 0.1f;
				if (_backVolume > 1.0f)
					_backVolume = 1.0f;

				SOUNDMANAGER->setVolume("background", _backVolume);
				_backNumber = getNumber(_backVolume);
			}
			else
			{
				_effectVolume += 0.1f;
				if (_effectVolume > 1.0f)
					_effectVolume = 1.0f;

				SOUNDMANAGER->play("fly", _effectVolume);
				_effectNumber = getNumber(_effectVolume);
			}
		}


		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_selectIndex -= 1;
			if (_selectIndex < 0)
				_selectIndex = 1;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_selectIndex += 1;
			if (_selectIndex > 1)
				_selectIndex = 0;
		}
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

void settingScene::render()
{
	IMAGEMANAGER->findImage("setting")->frameRender(getMemDC(), 0, 0, _selectIndex, 0);
	IMAGEMANAGER->findImage("setting")->alphaFrameRender(getMemDC(), 0, 0, _selectIndex, 1,_alpha);

	if(_backNumber > 9)
		IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 172, 320, _backNumber/10, 0);
	IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 225, 320, _backNumber%10, 0);
	if(_effectNumber > 9)
		IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 315, 320, _effectNumber /10, 0);
	IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 367, 320, _effectNumber %10, 0);
}

int settingScene::getNumber(float volume)
{
	if (volume == 0.0f)
		return 0;
	else if (volume > 0 && volume < 0.11f)
		return 1;
	else if (volume > 0.1 && volume < 0.21f)
		return 2;	
	else if (volume > 0.2 && volume < 0.31f)
		return 3;			
	else if (volume > 0.3 && volume < 0.41f)
		return 4;			
	else if (volume > 0.4 && volume < 0.51f)
		return 5;			
	else if (volume > 0.5 && volume < 0.61f)
		return 6;			
	else if (volume > 0.6 && volume < 0.71f)
		return 7;			
	else if (volume > 0.7 && volume < 0.81f)
		return 8;			
	else if (volume > 0.8 && volume < 0.91f)
		return 9;
	else if (volume == 1.0f)
		return 10;
}

void settingScene::changeScene()
{
	SCENEMANAGER->changeScene("menuScene");
}
