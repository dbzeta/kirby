#pragma once
#include "kirbyBase.h"

#define START_ANGLE float(PI/2.0f) 


struct sBeam
{
	float x;//������ǥ
	float y;
	float r;//������
	image* image;
	RECT rc;

};

class enemyManeger;

class beamKirby : public kirbyBase
{
private:
	sBeam _beam[6];
	float _angle;

	enemyManager* _em;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(RECT rcFocus);

	virtual void setMotion();
	virtual void initImage();
	virtual void attack();

	void checkCollision();

	void beamMove();

	inline animation* getMotion() { return _motion; }
	inline image* getImage() { return _image; }


	beamKirby();
	~beamKirby();
};

