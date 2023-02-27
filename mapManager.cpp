#include "stdafx.h"
#include "mapManager.h"
#include "Door.h"
#include "enemyManager.h"
#include "kirby.h"
#include "frosty.h"


mapManager::mapManager(){}
mapManager::~mapManager(){}

HRESULT mapManager::init()
{
	StageDoorTimeBool = false;
	StageDoorTime = 0.0f;
	earthquakeCount = 0.0f;
	Offsetx = 0;
	Offsety = 0;
	JumpEart = false;
	//Hub
	IMAGEMANAGER->addImage("Hub", "mapImage/Hub.bmp", WINSIZEX * 2, WINSIZEY * 1.5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HubBack", "mapImage/HubBack.bmp", WINSIZEX * 2, WINSIZEY * 1.5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HubPix", "mapImage/HubPix.bmp", WINSIZEX * 2, WINSIZEY * 1.5, true, RGB(255, 0, 255));
	//Stage1
	IMAGEMANAGER->addImage("Stage0", "mapImage/Stage1.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackStage0", "mapImage/Stage1Back.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PixStage0", "mapImage/Stage1Pix.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	//Stage2
	IMAGEMANAGER->addImage("Stage1", "mapImage/Stage2.bmp", WINSIZEX * 5, WINSIZEY * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackStage1", "mapImage/Stage2Back.bmp", WINSIZEX * 5, WINSIZEY * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PixStage1", "mapImage/Stage2Pix.bmp", WINSIZEX * 5, WINSIZEY * 2, true, RGB(255, 0, 255));
	//Stage3
	IMAGEMANAGER->addImage("Stage2", "mapImage/Stage3.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackStage2", "mapImage/Stage3Back.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PixStage2", "mapImage/Stage3Pix.bmp", WINSIZEX * 4, WINSIZEY, true, RGB(255, 0, 255));
	//Stage4
	IMAGEMANAGER->addImage("Stage3", "mapImage/Stage4.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackStage3", "mapImage/Stage4Back.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PixStage3", "mapImage/Stage4Pix.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	//문이미지
	IMAGEMANAGER->addImage("NODOOR", "mapImage/NODOOR.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));

	//노동작
	IMAGEMANAGER->addImage("DoorNo", "mapImage/DoorClose.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door1No", "mapImage/DoorClose.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door2No", "mapImage/DoorClose.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door3No", "mapImage/BoosRoomClose.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));


	//문동작
	IMAGEMANAGER->addFrameImage("Door", "mapImage/Door4f.bmp", 224 * 1.5, 24 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door1", "mapImage/Door4f.bmp", 224 * 1.5, 24 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door2", "mapImage/Door4f.bmp", 224 * 1.5, 24 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door3", "mapImage/BossRoom.bmp", 224 * 1.5, 24 * 2, 4, 1, true, RGB(255, 0, 255));
	//닫힌동작
	IMAGEMANAGER->addImage("DoorClose", "mapImage/CloseDoor.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door1Close", "mapImage/CloseDoor.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door2Close", "mapImage/CloseDoor.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door3Close", "mapImage/CloseBossDoor.bmp", 56 * 1.5, 24 * 2, true, RGB(255, 0, 255));
	//문스테이지
	IMAGEMANAGER->addImage("DoorNumber", "mapImage/Number1.bmp", 11 * 2, 16 * 1.5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door1Number", "mapImage/Number2.bmp", 11 * 2, 16 * 1.5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Door2Number", "mapImage/Number3.bmp", 11 * 2, 16 * 1.5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door3Number", "mapImage/BoosRoom.bmp", 144 * 2, 24 * 1.5, 6, 1, true, RGB(255, 0, 255));
	//클리어 깃발
	IMAGEMANAGER->addFrameImage("Doorclear", "mapImage/Clear.bmp", 76 * 2, 19 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door1clear", "mapImage/Clear.bmp", 76 * 2, 19 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door2clear", "mapImage/Clear.bmp", 76 * 2, 19 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Door3clear", "mapImage/Clear.bmp", 76 * 2, 19 * 2, 4, 1, true, RGB(255, 0, 255));

	currentStage = new image;
	currentBackGround = new image;
	currentPixStage = new image;
	
	_focusRect = NULL;
	_drawRect = RectMake(0, 0, WINSIZEX, WINSIZEY);
	//커비랑 문 확인
	kubyTrue = true;
	//테스트용

	//Stage 초기화
	for (int i = 0; i < DOORMAX; i++)
	{
		stage[i] = false;
		stageClear[i] = false;
	}
	//문위치	
	/*_door[0]->Doorinit(415, 360, "Door");
	_door[1]->Doorinit(565,	250, "Door1");
	_door[2]->Doorinit(1035, 200, "Door2");
	_door[3]->Doorinit(1050, 90, "Door3");*/
	//HUBDOOR
	
	//StageDoorNumber
	earthquake = false;
	_Stage = 1;
	
	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_testRect = RectMake(0, 0, 50, 50);
		changeStage(1);
		
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_testRect = RectMake(0, 0, 50, 50);
		//_em->addEnemy(200, 100, 5, 400, 0, true);
		changeStage(2);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_testRect = RectMake(0, 0, 50, 50);
		changeStage(3);
		
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_testRect = RectMake(0, 0, 50, 50);

		changeStage(4);
	}
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		
		_testRect = RectMake(0, 0, 50, 50);
		changeStage(0);
	}

	if (_focusRect != NULL)
	{
		_drawRect.left = _focusRect->left - ((WINSIZEX / 2) - (_focusRect->right - _focusRect->left) / 2);
		_drawRect.top = _focusRect->top - ((WINSIZEY / 2) - (_focusRect->bottom - _focusRect->top) / 2);
		_drawRect.right = _drawRect.left + WINSIZEX;
		_drawRect.bottom = _drawRect.top + WINSIZEY;

		if (_drawRect.left < 0)
		{
			_drawRect.left -= _drawRect.left;
			_drawRect.right = _drawRect.left + WINSIZEX;
		}

		if (_drawRect.right > currentStage->getWidth())
		{
			_drawRect.right -= _drawRect.right - currentStage->getWidth();
			_drawRect.left = _drawRect.right - WINSIZEX;
		}

		if (_drawRect.top < 0)
		{
			_drawRect.top -= _drawRect.top;
			_drawRect.bottom = _drawRect.top + WINSIZEY;
		}

		if (_drawRect.bottom > currentStage->getHeight())
		{
			_drawRect.bottom -= _drawRect.bottom - currentStage->getHeight();
			_drawRect.top = _drawRect.bottom - WINSIZEY;
		}
	}
	else
	{
		_drawRect.left = 0;
		_drawRect.top = 0;
		_drawRect.right = WINSIZEX;
		_drawRect.bottom = WINSIZEY;
	}
	if (DOOR.size() > 1)
	{
		for (int i = 0; i < DOOR.size(); i++)
		{
			DOOR[i]->update();
			if (DOOR[i]->getStageDoor())
			{
				if (DOOR[i]->getStageStart())
				{
					changeStage(i + 1);
					break;
				}
			}
			
		}
	}
	if (StageDoorTimeBool)
	{
		StageDoorTime += TIMEMANAGER->getElapsedTime();
		if (StageDoorTime > 0.3f)
		{
			changeStage(0);
			StageDoorTime = 0.0f;
			StageDoorTimeBool = false;
		}
	}

	if (StageRoomNum == 4)
	{
		earthquakeCount += TIMEMANAGER->getElapsedTime();
		if (((Frosty*)_em->getVEnemy()[0])->getDrop())
		{
			JumpEart = true;
		}
		else
		{
			JumpEart = false;
		}
	}
	//RECT TEMPE;
	//for (int i = 0; i < _em->getVEnemy().size(); i++)
	//{
	//	if (IntersectRect(&TEMPE, &_drawRect, &_em->getVEnemy()[i]->getRC()))
	//	{
	//		_em->Spawn(i);
	//	}
	//	else
	//	{

	//	}

	//}
}

void mapManager::render()
{
	currentBackGround->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _drawRect.left, _drawRect.top);
	if (!_debug)
	{
		if (currentStage == IMAGEMANAGER->findImage("Stage3"))
		{
			if (JumpEart)
			{
				if (earthquakeCount > 0.05f)
				{
					if (earthquake)
					{
						Offsetx -= 15;
						Offsety -= 15;
						earthquake = false;
						earthquakeCount = 0.0f;

					}
					else if (!earthquake)
					{
						Offsetx += 15;
						Offsety += 15;
						earthquake = true;
						earthquakeCount = 0.0f;

					}
				}
			}
			else
			{
				Offsetx = 0;
				Offsety = 0;
			}
			currentStage->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), Offsetx, Offsety);

		}
		else
		{
			RECT temp;
		
			currentStage->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _drawRect.left, _drawRect.top);
			
		}
		if (currentStage == IMAGEMANAGER->findImage("Hub"))
		{
			for (int i = 0; i < DOOR.size(); i++)
			{
				DOOR[i]->draw(_drawRect, stage[i], stageClear[i]);
			}
		}
		
	}
	else
	{
		currentPixStage->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _drawRect.left, _drawRect.top);
		for (int i = 0; i < DOOR.size(); i++)
		{
			DOOR[i]->DoorRectMake(_drawRect);
		}
	}
}

void mapManager::changeStage(int Stage)
{
	SCENEMANAGER->fadeIn(NULL);
	DOORReLease();
	_em->removeAll();
	for (int i = 0; i < _Stage; i++)
	{
		stage[i] = true;
	}
	switch (Stage)
	{
	case HUB:
	{
		if (kubyTrue)
		{
			_kirby->setCenterX(140.0f);
			_kirby->setCenterY((float)WINSIZEY - 250.0f);
		}
		else
		{
			_kirby->setCenterX(Cx);
			_kirby->setCenterY(Cy);
		}
		

		currentStage = IMAGEMANAGER->findImage("Hub");
		currentBackGround = IMAGEMANAGER->findImage("HubBack");
		currentPixStage = IMAGEMANAGER->findImage("HubPix");
		DOORINIT(415, 360, "Door");
		DOORINIT(565, 250, "Door1");
		DOORINIT(1035, 200, "Door2");
		DOORINIT(1050, 90, "Door3");

		for (int i = 0; i < DOOR.size(); i++)
		{
			DOOR[i]->setDoorTrue(true);
			DOOR[i]->setStageDoor(stage[i]);//->문을 열어라
		}

	}break;
		
	case STAGE1:
	{

		kubyTrue = false;
		if (_Stage < STAGE2)
		{
			_Stage = STAGE2;
		}
		StageRoomNum = 1;

		stageClear[0] = true;

		_kirby->setCenterX(120.0f);
		_kirby->setCenterY((float)WINSIZEY - 170.0f);
		currentStage = IMAGEMANAGER->findImage("Stage0");
		currentBackGround = IMAGEMANAGER->findImage("BackStage0");
		currentPixStage = IMAGEMANAGER->findImage("PixStage0");
		DOORINIT(IMAGEMANAGER->findImage("Stage0")->getWidth()-90, WINSIZEY / 2 + 30, "NODOOR");
		DOOR[0]->setDoorTrue(true);
	
		//문을 열어라
		Cx = 415.0f;
		Cy = 360.0f;
		//적 추가
		_em->addEnemy(WINSIZEX / 2 + 250, WINSIZEY / 2 - 50, 40, 100, 12, false);
		_em->addEnemy(WINSIZEX / 2 + 500, WINSIZEY / 2 + 50, 60, 200, 7, true);
		_em->addEnemy(WINSIZEX / 2 + 900, WINSIZEY / 2, 20, 200, 2, false);

		_em->addEnemy(WINSIZEX / 2 + 1100, WINSIZEY / 2 + 100, 40, 200, 1, false);
		_em->addEnemy(WINSIZEX / 2 + 1270, WINSIZEY / 2 + +20, 300, 300, 8, true);
		_em->addEnemy(IMAGEMANAGER->findImage("Stage0")->getWidth() - 100, WINSIZEY / 2, 40, 200, 2, true);


	}break;

	case STAGE2:
	{
		
		kubyTrue = false;
		if (_Stage < STAGE3)
		{
			_Stage = STAGE3;
		}
		stageClear[1] = true;
		StageRoomNum = 2;
		_kirby->setCenterX(120.0f);
		_kirby->setCenterY((float)WINSIZEY + 310);
		currentStage = IMAGEMANAGER->findImage("Stage1");
		currentBackGround = IMAGEMANAGER->findImage("BackStage1");
		currentPixStage = IMAGEMANAGER->findImage("PixStage1");
		DOORINIT(IMAGEMANAGER->findImage("Stage1")->getWidth() - 90, WINSIZEY / 2 + 200, "NODOOR");
		DOOR[0]->setDoorTrue(true);
		//문을 열어라
		Cx = 565.0f;
		Cy = 250.0f;
		//적 추가
		_em->addEnemy(WINSIZEX / 2 + 500, WINSIZEY + 160, 100, 200, 7, false);
		_em->addEnemy(WINSIZEX / 2 + 700, WINSIZEY, 100, 400, 1, true);
		_em->addEnemy(WINSIZEX / 2 + 1100, WINSIZEY, 100, 400, 1, false);
		_em->addEnemy(WINSIZEX / 2 + 1500, WINSIZEY, 100, 400, 1, true);

		_em->addEnemy(WINSIZEX / 2 + 700, WINSIZEY, 100, 200, 1, true);

		_em->addEnemy(WINSIZEX / 2 + 900, WINSIZEY, 20, 200, 2, true);

		_em->addEnemy(WINSIZEX / 2 + 1100, WINSIZEY , 160, 400, 11, true);
		_em->addEnemy(WINSIZEX / 2 + 1300, WINSIZEY + 400, 40, 200, 10, false);
		_em->addEnemy(WINSIZEX / 2 + 1700, WINSIZEY, 20, 200, 12, true);
		_em->addEnemy(WINSIZEX / 2 + 2100, WINSIZEY + 80, 100, 200, 11, true);
		_em->addEnemy(WINSIZEX / 2 + 2100, WINSIZEY - 50, 20, 200, 4, false);
		_em->addEnemy(WINSIZEX / 2 + 1770, WINSIZEY - 260, 200, 500, 8, true);

		_em->addEnemy(WINSIZEX / 2 + 2200, WINSIZEY - 260, 100, 300, 2, true);

	}break;

	case STAGE3:
	{
		
		kubyTrue = false;
		if (_Stage < STAGE4)
		{
			_Stage = STAGE4;
		}
		stageClear[2] = true;
		StageRoomNum = 3;
		_kirby->setCenterX(120.0f);
		_kirby->setCenterY((float)WINSIZEY - 130.0f);
		currentStage = IMAGEMANAGER->findImage("Stage2");
		currentBackGround = IMAGEMANAGER->findImage("BackStage2");
		currentPixStage = IMAGEMANAGER->findImage("PixStage2");
		DOORINIT(IMAGEMANAGER->findImage("Stage2")->getWidth() - 90, WINSIZEY / 2 + 80, "NODOOR");
		DOOR[0]->setDoorTrue(true);
		//문을 열어라
		Cx = 1035.0f;
		Cy = 200.0f;
		//적 추가
		_em->addEnemy(WINSIZEX / 2 + 250, WINSIZEY / 2 - 100, 500, 500, 8, false);

		_em->addEnemy(WINSIZEX / 2 + 500, WINSIZEY/2 -200, 40, 200, 12, false);
		_em->addEnemy(WINSIZEX / 2 + 700, WINSIZEY / 2, 20, 200, 2, true);
		_em->addEnemy(WINSIZEX / 2 + 900, WINSIZEY / 2, 20, 200, 0, true);

		_em->addEnemy(WINSIZEX / 2 + 1100, WINSIZEY / 2 + 100, 40, 200, 1, false);
		_em->addEnemy(WINSIZEX / 2 + 1300, WINSIZEY / 2 + 100, 40, 200, 1, true);
		_em->addEnemy(IMAGEMANAGER->findImage("Stage0")->getWidth() - 100, WINSIZEY / 2, 40, 200, 2, true);
	}break;

	case STAGE4:
	{
		stageClear[3] = true;
		StageRoomNum = 4;
		kubyTrue = false;
		_kirby->setCenterX(120.0f);
		_kirby->setCenterY((float)WINSIZEY - 180.0f);
		currentStage = IMAGEMANAGER->findImage("Stage3");
		currentBackGround = IMAGEMANAGER->findImage("BackStage3");
		currentPixStage = IMAGEMANAGER->findImage("PixStage3");
		DOORINIT(IMAGEMANAGER->findImage("Stage3")->getWidth() - 100, WINSIZEY / 2, "NODOOR");
		DOOR[0]->setDoorTrue(true);
		//문을 열어라
		Cx = 1050.0f;
		Cy = 90.0f;

		_em->addEnemy(WINSIZEX - 100, WINSIZEY / 2, 40, 150, 13, true);
	}break;

	}
	//_em->InactiveEnemy();

}

//문 초기화
void mapManager::DOORINIT(int x, int y, string _string)
{
	_door = new Door;
	_door->Doorinit(x, y, _string);
	DOOR.push_back(_door);
}
//문 릴리즈
void mapManager::DOORReLease()
{
	//++i 하면 사이즈가 0이 아닌데도 나가므로 
	for (int i = 0; i < DOOR.size();)
	{
		DOOR[0]->release();
		SAFE_DELETE(DOOR[0]);
		DOOR.erase(DOOR.begin());
	}
}





//커비 체크
bool mapManager::getDoorCheck(RECT* _Kuby)
{

	RECT temp;
	for (int i = 0; i < DOOR.size(); i++)
	{
		if (IntersectRect(&temp, _Kuby, &DOOR[i]->getRect()))
		{
			if (DOOR.size() > 1)
			{
				DOOR[i]->setCountBool(true);
			}
			else
			{
				DOOR[0]->setStageStart(true);
				StageDoorTimeBool = true;
				SCENEMANAGER->fadeOut(NULL, 17);
				return true;
			}
			if (DOOR[i]->getStageDoor())
			{
				SCENEMANAGER->fadeOut(NULL, 17);
				return true;
			}
			else
			{
				return false;
			}
		}

	}
	return false;
}