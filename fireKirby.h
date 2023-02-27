#pragma once
#include "kirbyBase.h"

class enemyManager;

class fireKirby : public kirbyBase
{
private:

	enemyManager* _em;

public:
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


	fireKirby();
	virtual ~fireKirby();
};