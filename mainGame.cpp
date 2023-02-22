#include "stdafx.h"
#include "mainGame.h"

#include "titleScene.h"
#include "gameScene.h"
#include "settingScene.h"
#include "menuScene.h"
#include "endScene.h"

BOOL _debug = false;

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
////////////////////////////////////
//생성자 소멸자 빠이빠이
////////////////////////////////////

//초기화 해주는 함수
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	_winSizeX = WINSIZEX;
	_winSizeY = WINSIZEY;

	SCENEMANAGER->addScene("titleScene", new titleScene);
	SCENEMANAGER->addScene("menuScene", new menuScene);
	SCENEMANAGER->addScene("settingScene", new settingScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);
	SCENEMANAGER->addScene("endScene", new endScene);

	SCENEMANAGER->changeScene("titleScene");
	
	return S_OK;
}

//메모리 해제함수
void mainGame::release(void)
{
	gameNode::release();

}

//연산 하는 곳
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();	

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_debug = !_debug;
	}

	RECT temp;
	GetClientRect(_hWnd, &temp);

	_winSizeX = (temp.right - temp.left);
	_winSizeY = (temp.bottom - temp.top);

}

//그려주는 곳
void mainGame::render()
{
	//흰색 도화지 한장이 필요함
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();

	if(_debug)
		TIMEMANAGER->render(getMemDC());


	//백버퍼에 옮겨 그려줄 애 건들지마라 얘는
	this->getBackBuffer()->render(getHDC(), 0, 0,_winSizeX,_winSizeY);

}
