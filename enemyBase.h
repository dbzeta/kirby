#pragma once
#include "gameNode.h"

#define RATE 1.5
#define RATE2 2

enum ENEMY_STATE
{
	ENEMY_RIGHT_STOP,
	ENEMY_RIGHT_MOVE,
	ENEMY_RIGHT_FLY,
	ENEMY_RIGHT_DASH,
	ENEMY_RIGHT_DIE,
	ENEMY_RIGHT_HIT,
	ENEMY_RIGHT_ATTACK,
	ENEMY_RIGHT_DROPJUMP,
	ENEMY_RIGHT_JUMP,

	ENEMY_LEFT_STOP,
	ENEMY_LEFT_MOVE,
	ENEMY_LEFT_FLY,
	ENEMY_LEFT_DASH,
	ENEMY_LEFT_DIE,
	ENEMY_LEFT_HIT,
	ENEMY_LEFT_ATTACK,
	ENEMY_LEFT_DROPJUMP,
	ENEMY_LEFT_JUMP,

	ENEMY_UP_MOVE,
	ENEMY_UP_FLY,
	ENEMY_UP_JUMP,

	ENEMY_RIGHT_READY,
	ENEMY_LEFT_READY,

	ENEMY_END,
};

class enemyManager;
class enemyBase : public gameNode
{
protected:
	enemyManager* _em;

	// 기본 변수들
	int _nEnemyHP;
	int _moveRange;
	float _fSpeed;
	float _x, _y;
	float _startX, _startY;
	float _angle;
	float _gravity;
	float _mapGravity;
	float _jumpPower;
	RECT _rc;
	float _motionCount;
	float _InvincibilityCount;

	bool _isJump;
	bool _attack;
	bool _isUpFly;
	bool _isHit;
	bool _isMove;
	bool _bDie;
	bool _patternPlay;
	bool _bEat;
	bool _boss;

	float _reSetSpeed;
	float _reSetX, _reSetY;
	float _reSetMoveRange;
	bool  _reSetType;

	ENEMY_STATE _state;
	ENEMY_STATE _resetState;

	//프레임으로 이미지 돌리기 위한 변수들
	image* _imageEnemy;
	int _currentFrameX;
	int _currentFrameY;
	float _count;

public:
	enemyBase();
	virtual ~enemyBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw(RECT rcFocus);
	virtual void move();
	virtual void move(ENEMY_STATE nextMotion);
	virtual void Followmove();
	virtual void jump();
	virtual void Followjump();
	virtual void Fly();
	virtual void FollowFly();
	virtual void Dash(float dashRange, float dashSpeed, ENEMY_STATE nextMotion);
	virtual void Gravity();

	virtual void setSpawn(bool activation) { _bDie = activation; }
	virtual RECT getRC() { return _rc; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }
	virtual bool getDie() { return _bDie; }
	virtual bool getHit() { return _isHit; }

	virtual bool getEat() { return _bEat; }

	virtual void hitDamage(int damage);

	void PixelCollision();


	void setEmMemoryLink(enemyManager* em) { _em = em; }
};

