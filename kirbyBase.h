#pragma once
#include "gameNode.h"

class kirby;
class enemyManager;

struct bullet
{
	// 공격용 이미지, rect
	image* image;
	RECT rc;
	animation* bulletMotion;
	float startCX, startCY;
	float cx, cy;
	bool isFire;	
	bool isAttackRight;
	bool isCollision;
};

class kirbyBase : public gameNode
{
protected:
	animation* _motion;
	kirby* _kirby;
	enemyManager* _em;

	image* _image;
	RECT _rc;

	image* _changeEffect;
	image* _attackEffect;

	bullet _bullet;

	float _defaultX, _defaultY;


public:
	kirbyBase();
	virtual ~kirbyBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(RECT rcFocus);

	virtual void setMotion();
	virtual void initImage();

	void createBullet();
	void moveBullet();
	void renderBullet(RECT rcFocus);

	void checkCollision();
	
	inline animation* getMotion() { return _motion; }
	inline image* getImage() { return _image; }

	inline void setKirbyMemoryLink(kirby* kirby) { _kirby = kirby; }


};

