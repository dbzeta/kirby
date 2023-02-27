#pragma once
#include "enemyBase.h"

struct Block
{
	RECT _rcBlock;
	bool _bEat;
	image* _BlockImage;
};

struct BossInfo
{
	Block _block;
	RECT _rc;
	float _speed;
	bool _die;
	bool _inOut;
	int _hp;
	image* _bossImage;
};

class LaLaLoLo :
	public enemyBase
{
private:
	BossInfo _lala;
	BossInfo _lolo;
	
public:
	LaLaLoLo();
	~LaLaLoLo();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void draw(RECT rcFocus);
};

