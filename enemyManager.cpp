#include "stdafx.h"
#include "enemyManager.h"
#include "BroomHatter.h"
#include "mapManager.h"
#include "kirby.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	//addEnemy(0, 0, 40, 300, BOSS_LALALOLO, true);

	//// BEEM
	//addEnemy(WINSIZEX / 3, 50, 30, 100, BEEM, false);
	//addEnemy(WINSIZEX / 3, 100, 30, 100, BEEM, true);
	
	//// CAPPY
	//addEnemy(WINSIZEX / 3, 150, 30, 100, CAPPY, false);
	//addEnemy(WINSIZEX / 3, 200, 30, 100, CAPPY, true);

	//boss
	//addEnemy(WINSIZEX - 100, WINSIZEY - 100, 40, 150, BOSS_Frosty, false);
	//Grizzo
	addEnemy(WINSIZEX - 100, WINSIZEY / 2, 40, 150, GRIZZO, false);
	
	//----------------------------테스트 완료--------------------------------
	// //BRONTO_BURT
	//addEnemy(WINSIZEX - 50, WINSIZEY / 2, 50, 200, BRONTO_BURT, false);
	//addEnemy(WINSIZEX - 50, WINSIZEY / 2, 50, 200, BRONTO_BURT, true);

	//BROOM_HATTER
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 40, 200, BROOM_HATTER, true);
	//addEnemy(WINSIZEX / 2 - 50, WINSIZEY - 200, 40, 200, BROOM_HATTER, false);

	//SCARFY
	//addEnemy(50, WINSIZEY - 100, 40, 200, SCARFY, false);
	//addEnemy(WINSIZEX - 50, WINSIZEY - 100, 40, 200, SCARFY, false);

	//SHOTZO
	//addEnemy(WINSIZEX / 3, WINSIZEY - 100, 150, 400, SHOTZO, false);

	// STONE
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 50, 200, STONE, false);
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 20, 200, STONE, true);

	//// Tooky
	//addEnemy(WINSIZEX /2, WINSIZEY - 50, 50, 200, TOOKY, false);
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 50, 200, TOOKY, true);
	
	//// TWIZZY
	//addEnemy(WINSIZEX / 2 , WINSIZEY - 50, 50, 200, TWIZZY, false);
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 50, 200, TWIZZY, true);

	//WADDLE_DEE
	//addEnemy(WINSIZEX / 2, WINSIZEY - 200, 50, 200, WADDLE_DEE, true);
	//addEnemy(WINSIZEX, WINSIZEY - 100, 50, 200, WADDLE_DEE, false);
	

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size();)
	{
		_vEnemy[i]->update();
		//if (_vEnemy[i])	//enemy 죽어있으면
		//{
		//	removeEnemy(i);
		//}
		//else
		//{
			++i;
		//}
	}

}

void enemyManager::render()
{
	
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->draw(_mm->getFocus());
	}
}

void enemyManager::removeEnemy(int index)
{
	_vEnemy[index]->release();
	SAFE_DELETE(_vEnemy[index]);
	_vEnemy.erase(_vEnemy.begin() + index);
}

void enemyManager::removeAll()
{
	for (int i = 0; i < _vEnemy.size();)
	{
		removeEnemy(i);
	}
}

void enemyManager::Spawn(int arr)
{
	_vEnemy[arr]->setSpawn(false);
}

void enemyManager::InactiveEnemy()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->setSpawn(true);
	}
}

// 적을 세팅한다~ type 에따라 패턴이 바뀐다 true or false
void enemyManager::addEnemy(float x, float y, float speed, int moveRange, int enemyNumber, bool type) 
{
	switch (enemyNumber)
	{
	case BEEM:
		Beem* _beem;
		_beem = new Beem;
		_beem->init(x, y, speed, moveRange);
		_beem->setEmMemoryLink(this);
		_vEnemy.push_back(_beem);
		break;

	case BRONTO_BURT:
		BrontoBurt* _brontoBurt;
		_brontoBurt = new BrontoBurt;
		_brontoBurt->init(x, y, speed, moveRange, type);
		_brontoBurt->setEmMemoryLink(this);
		_vEnemy.push_back(_brontoBurt);
		break;

	case BROOM_HATTER:
		BroomHatter* _broomHatter;
		_broomHatter = new BroomHatter;
		_broomHatter->init(x, y, speed, moveRange, type);
		_broomHatter->setEmMemoryLink(this);
		_vEnemy.push_back(_broomHatter);
		break;

	case CAPPY:
		Cappy* _cappy;
		_cappy = new Cappy;
		_cappy->init(x, y, speed, moveRange, type);
		_cappy->setEmMemoryLink(this);
		_vEnemy.push_back(_cappy);
		break;

	case FIRE:
		Fire* _fire;
		_fire = new Fire;
		_fire->init(x, y, speed, moveRange);
		_fire->setEmMemoryLink(this);
		_vEnemy.push_back(_fire);
		break;

	case GORDO:
		Gordo* _gordo;
		_gordo = new Gordo;
		_gordo->init(x, y, speed, moveRange, type);
		_gordo->setEmMemoryLink(this);
		_vEnemy.push_back(_gordo);
		break;

	case GRIZZO:
		Grizzo* _grizzo;
		_grizzo = new Grizzo;
		_grizzo->init(x, y, speed, moveRange, type);
		_grizzo->setEmMemoryLink(this);
		_vEnemy.push_back(_grizzo);
		break;

	case SCARFY:
		Scarfy* _scarfy;
		_scarfy = new Scarfy;
		_scarfy->init(x, y, speed, moveRange, type);
		_scarfy->setEmMemoryLink(this);
		_vEnemy.push_back(_scarfy);
		break;

	case SHOTZO:
		Shotzo* _shotzo;
		_shotzo = new Shotzo;
		_shotzo->init(x, y, speed, moveRange);
		_shotzo->setEmMemoryLink(this);
		_vEnemy.push_back(_shotzo);
		break;

	case STONE:
		Stone* _stone;
		_stone = new Stone;
		_stone->init(x, y, speed, moveRange, type);
		_stone->setEmMemoryLink(this);
		_vEnemy.push_back(_stone);
		break;

	case TOOKY:
		Tooky* _tooky;
		_tooky = new Tooky;
		_tooky->init(x, y, speed, moveRange, type);
		_tooky->setEmMemoryLink(this);
		_vEnemy.push_back(_tooky);
		break;

	case TWIZZY:
		Twizzy* _twizzy;
		_twizzy = new Twizzy;
		_twizzy->init(x, y, speed, moveRange, type);
		_twizzy->setEmMemoryLink(this);
		_vEnemy.push_back(_twizzy);
		break;

	case WADDLE_DEE:
		WaddleDee* _waddelDee;
		_waddelDee = new WaddleDee;
		_waddelDee->init(x, y, speed, moveRange, type);
		_waddelDee->setEmMemoryLink(this);
		_vEnemy.push_back(_waddelDee);
		break;

	case BOSS_Frosty:
		Frosty* _Frosty;
		_Frosty = new Frosty;
		_Frosty->init(x, y, speed, moveRange);
		_Frosty->setEmMemoryLink(this);

		_vEnemy.push_back(_Frosty);
		break;

	case BOSS_LALALOLO:
		LaLaLoLo* _LaLaLoLo;
		_LaLaLoLo = new LaLaLoLo;
		_LaLaLoLo->init();
		_LaLaLoLo->setEmMemoryLink(this);

		_vEnemy.push_back(_LaLaLoLo);
		break;
	}
}
