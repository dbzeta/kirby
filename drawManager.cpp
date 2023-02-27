#include "stdafx.h"
#include "drawManager.h"
#include "gameNode.h"


drawManager::drawManager()
{
}


drawManager::~drawManager()
{
}

HRESULT drawManager::init()
{
	_focus = NULL;
	return S_OK;
}

void drawManager::release()
{
}

void drawManager::update()
{

}

void drawManager::render()
{
	sort();
	for (int i = 0; i < _vDraw.size(); ++i)
	{
		_vDraw[i]->render();
	}
}

void drawManager::sort()
{

}
