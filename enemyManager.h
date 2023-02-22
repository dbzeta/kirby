#pragma once
#include "Beem.h"
#include "BroomHatter.h"
#include "BrontoBurt.h"
#include "Cappy.h"
#include "Fire.h"
#include "Gordo.h"
#include "Grizzo.h"
#include "Scarfy.h"
#include "Shotzo.h"
#include "Stone.h"
#include "Tooky.h"
#include "Twizzy.h"
#include "WaddleDee.h"
#include "Frosty.h"
#include "LaLaLoLo.h"

#include <vector>

class enemyBase;
class mapManager;
class kirby;


enum Enemy
{
	BEEM,
	BRONTO_BURT,
	BROOM_HATTER,
	CAPPY,
	FIRE,
	GORDO,
	GRIZZO,
	SCARFY,
	SHOTZO,
	STONE,
	TOOKY,
	TWIZZY,
	WADDLE_DEE,
	BOSS_Frosty,
	BOSS_LALALOLO,

};


class enemyManager
{
protected:
	vector<enemyBase*> _vEnemy;
	mapManager* _mm;
	kirby* _kirby;

public:
	enemyManager();
	virtual ~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void removeEnemy(int index);
	void removeAll();
	void Spawn(int arr);
	void InactiveEnemy();
	void addEnemy(float x, float y, float speed, int moveRange, int enemyNumber, bool type);

	kirby* getKirby() { return _kirby; }
	vector<enemyBase*>& getVEnemy() { return _vEnemy; }
	mapManager* getMapManager() { return _mm; }

	void setEmMemoryLink(mapManager* mm) { _mm = mm; }
	void setKBMemoryLink(kirby* kb) { _kirby = kb; }
};

