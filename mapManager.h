#pragma once
#include "gameNode.h"
#include <map>
#include <vector>
#define DOORMAX 4
enum STAGE
{
	HUB = 0,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4
};
class kirby;
class enemyManager;
class uiManager;
class Door;
class mapManager : public gameNode
{
protected:
	kirby* _kirby;
	enemyManager* _em;
	uiManager* _uim;
	Door* _door;

	RECT* _focusRect;
	RECT _drawRect;
	RECT _testRect;
private:
	//mapImage
	image* currentStage;
	image* currentPixStage;
	image* currentBackGround;

	int _Stage;
	vector<Door*> DOOR;
	vector<Door*>::iterator iDOOR;
	void DOORINIT(int x, int y, string _string);
	void DOORReLease();
	
	//스테이지 문 타임
	float StageDoorTime;
	bool StageDoorTimeBool;
	bool kubyTrue;//처음커비 위치
	bool StageClearCheak;
	float Cx, Cy;
	bool stage[DOORMAX];
	bool stageClear[DOORMAX];
	//
	bool earthquake;
	float earthquakeCount;
	int Offsetx, Offsety;
	bool JumpEart;
	int StageRoomNum;
public:
	mapManager();
	virtual ~mapManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void changeStage(int Stage);
	

	inline image* getPixalCrushImage() { return currentPixStage; }
	inline void setFocus(RECT* rcFocus) { _focusRect = rcFocus; }

	inline RECT getFocus() { return _drawRect; }
	bool getDoorCheck(RECT* _Kuby);

	void setKirbyMemoryLink(kirby* kirby) { _kirby = kirby; }
	void setEmMemoryLink(enemyManager* em) { _em = em; }
	void setUimMemoryLink(uiManager* uim) { _uim = _uim; }
};

