#include "stdafx.h"
#include "gameScene.h"

#include "kirby.h"
#include "enemyManager.h"
#include "mapManager.h"
#include "uiManager.h"

gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	SOUNDMANAGER->addSound("jump", "sound\\jump.wav", false, false);
	SOUNDMANAGER->addSound("eat", "sound\\eat.wav", false, false);
	SOUNDMANAGER->addSound("damage", "sound\\damage.wav", false, false);
	SOUNDMANAGER->addSound("change", "sound\\change.wav", false, false);
	SOUNDMANAGER->addSound("fire", "sound\\fire.wav", false, false);
	SOUNDMANAGER->addSound("beam", "sound\\beam.wav", false, false);

	SOUNDMANAGER->stop("background");

	SOUNDMANAGER->addSound("background", "sound\\game1.mp3", true, true);
	SOUNDMANAGER->play("background", atof(DATABASE->getElementData("backVolume").c_str()));

	SOUNDMANAGER->addSound("background", "sound\\game2.mp3", true, true);
	SOUNDMANAGER->play("background", atof(DATABASE->getElementData("backVolume").c_str()));

	IMAGEMANAGER->addFrameImage("effect1", "image\\effect1.bmp", 651, 90, 7, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("effect1", "effect1", 651, 90, 93, 90, 15, TIMEMANAGER->getElapsedTime(), 5);



	if (DATABASE->getElementData("kirbyLife") == "")
	{
		DATABASE->addElementData("kirbyLife", "3");
	}
	else
	{
		DATABASE->setElementData("kirbyLife", "3");
	}

	if (DATABASE->getElementData("kirbyHp") == "")
	{
		DATABASE->addElementData("kirbyHp", "6");
	}
	else
	{
		DATABASE->setElementData("kirbyHp", "3");
	}




	_kirby = new kirby;
	_kirby->init();

	_em = new enemyManager;
	_em->init();

	_mm = new mapManager;
	_mm->init();

	_uim = new uiManager;
	_uim->init();

	_kirby->setEmMemoryLink(_em);
	_kirby->setMmMemoryLink(_mm);

	_em->setEmMemoryLink(_mm);
	_em->setKBMemoryLink(_kirby);

	_mm->setEmMemoryLink(_em);
	_mm->setKirbyMemoryLink(_kirby);
	_mm->setUimMemoryLink(_uim);

	_uim->setKirbyMemoryLink(_kirby);
	_uim->setEmMemoryLink(_em);

	_mm->setFocus(&_kirby->getRect());

	_mm->changeStage(0);


	return S_OK;
}

void gameScene::release()
{
	_kirby->release();
	_em->release();
	_mm->release();
	_uim->release();

	SAFE_DELETE(_kirby);
	SAFE_DELETE(_em);
	SAFE_DELETE(_mm);
	SAFE_DELETE(_uim);
}

void gameScene::update()
{
	_kirby->update();
	_em->update();
	_mm->update();
	_uim->update();
	EFFECTMANAGER->update();

	if(_kirby->getGameEnd())
		SCENEMANAGER->changeScene("endScene");
}

void gameScene::render()
{
	_mm->render();
	EFFECTMANAGER->render();
	_em->render();
	_kirby->render();
	_uim->render();
}
