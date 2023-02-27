#pragma once
#include <vector>

class enemyManager;
class mapManager;

class kirbyBase;

// 먹는거


enum DIRECTION
{
	DIRECTION_STOP,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
};

enum STATE
{

	// 가만히 있을 때

	// 평지
	LEFT_STOP,
	RIGHT_STOP,
	// 낮은 평지
	LEFT_LOW_STOP_UP,
	RIGHT_LOW_STOP_UP,
	LEFT_LOW_STOP_DOWN,
	RIGHT_LOW_STOP_DOWN,
	// 높은 평지
	LEFT_HIGH_STOP_UP,
	RIGHT_HIGH_STOP_UP,
	LEFT_HIGH_STOP_DOWN,
	RIGHT_HIGH_STOP_DOWN,

	// 앉았을 때

	// 평지
	LEFT_SIT,
	RIGHT_SIT,
	// 낮은 평지
	LEFT_LOW_SIT_DOWN,
	RIGHT_LOW_SIT_DOWN,
	LEFT_LOW_SIT_UP,
	RIGHT_LOW_SIT_UP,
	// 높은 평지
	LEFT_HIGH_SIT_DOWN,
	RIGHT_HIGH_SIT_DOWN,
	LEFT_HIGH_SIT_UP,
	RIGHT_HIGH_SIT_UP,


	// 이동

	// 평지
	LEFT_MOVE,
	RIGHT_MOVE,
	// 낮은 평지
	LEFT_LOW_MOVE,
	RIGHT_LOW_MOVE,
	// 높은 평지
	LEFT_HIGH_MOVE,
	RIGHT_HIGH_MOVE,

	// 달리기
	LEFT_DASH,
	RIGHT_DASH,

	// 날기 ( 어짜피 나는 상태일땐 올라가거나 내려가는 상태이므로 좌우로 움직일 지만 판단해줄 STATE를 추가 )

	// 공기 빨아들일 떄
	LEFT_FLY_EAT,
	RIGHT_FLY_EAT,
	// 올라갈때
	LEFT_FLY_UP,
	RIGHT_FLY_UP,
	// 내려갈때
	LEFT_FLY_DOWN,
	RIGHT_FLY_DOWN,
	// 땅에 가만히 있을 때
	LEFT_FLY,
	RIGHT_FLY,
	// 왼쪽 오른쪽 움직일때 ( 좌우 이동의 state 랜더할때는 안씀 )
	LEFT_FLY_MOVE,
	RIGHT_FLY_MOVE,


	// 점프

	// 점프 올라갈때 
	LEFT_JUMP_UP,
	RIGHT_JUMP_UP,
	// 점프 중간지점
	LEFT_JUMP_TURN,
	RIGHT_JUMP_TURN,
	// 점프 내려갈때 
	LEFT_JUMP_DOWN,
	RIGHT_JUMP_DOWN,

	// 태클
	LEFT_KICK,
	RIGHT_KICK,

	// 삼키기 시전
	LEFT_EAT,
	RIGHT_EAT,
	// 계속 삼키는 중
	LEFT_EATING,
	RIGHT_EATING,

	// 내뱉기
	LEFT_THROW,
	RIGHT_THROW,

	// 추락
	LEFT_FALL,
	RIGHT_FALL,

	// 공격할 때
	LEFT_ATTACK,
	RIGHT_ATTACK,

	// 변신 해제
	LEFT_RETURN,
	RIGHT_RETURN,

	// 충돌
	LEFT_CRASH,
	RIGHT_CRASH,

	// 수영
	LEFT_SWIM,
	RIGHT_SWIM,

	// 방향전환할때
	LEFT_TURN,
	RIGHT_TURN,

	// 문을 연다
	LEFT_OPEN_DOOR,
	RIGHT_OPEN_DOOR,


};

enum MODE
{
	MODE_NORMAL,
	MODE_FIRE,
	MODE_CUPID,
	MODE_BEAM,
};

class kirby
{
protected:
	enemyManager* _em;
	mapManager* _mm;

	// 커비를 선택한다. ( 현재 커비를 가리키는 것 )
	kirbyBase* _currentKirby;

	// 플레이어 이미지 센터 좌표
	float _cx, _cy;
	float _startCx, _startCy;

	// 플레이어 렉트, 충돌용 렉트
	RECT _rc, _collisionRC;

	// 몬스터 삼킬때 쓰는 렉트
	RECT _eatRc;

	// 플레이어 state
	STATE _state;
	STATE _preState;

	// 지금 무슨 커비세요? 판단한 mode
	MODE _mode;

	// fly, jump를 할때 사용될 dir
	DIRECTION _dir;

	// 키 입력에 의한 state변화를 제외하고 일정 시간이 경과해야하는 경우 count를 사용하여 state를 변경한다.
	int _count;
	float _timer;

	// 대쉬 판별을 위한 count
	bool _isDashReady;

	bool _isPixelCollision;
	bool _isRectCollision;

	bool _isPixelCollisionUp;

	bool _isGameEnd;

	// hp , life
	int _hp, _life;

	// LEFT RIGHT 판단
	bool _isRight;

	bool _isPushButton;

	// 몬스터 먹었니? 
	bool _isFull;

	// 문 열렸니?
	bool _isOnTheDoor;

	RECT _tempRect;

	// 공격이니?
	bool _isAttack;


public:
	kirby();
	virtual ~kirby();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void keyControl();		// 키를 누르면 state가 변화
	void checkState();		// 현재 state에 따른 state, x/y, rect값 변화 (_count 를 사용하여 state를 변화시킨다.)

	void checkPixelCollision();
	bool checkDoorPixel();
	void checkRectCollision();

	void changeMode(MODE mode);

	void attack();
	//삼키기
	void eat();

	void hitDamage(int damage, RECT enemyRect);

	inline STATE getState() { return _state; }

	inline MODE getMode() { return _mode; }
	inline void setState(STATE state) { _state = state; }

	inline RECT& getRect() { return _rc; }
	inline RECT& getEatRect() { return _eatRc; }
	inline RECT& getCollisionRect() { return _collisionRC; }

	inline RECT& getEnemyRect() { return _tempRect; }


	inline float getCenterX() { return _cx; }
	inline float getCenterY() { return _cy; }
	inline void setCenterX(float cx) { _cx = cx; }
	inline void setCenterY(float cy) { _cy = cy; }

	inline int getHp() { return _hp; }
	inline int getLife() { return _life; }
	inline int setHp(int hp) { _hp = hp; }
	inline int setLifp(int life) { _life = life; }

	inline bool getIsFull() { return _isFull; }
	inline bool getIsRight() { return _isRight; }
	inline bool getIsAttack() { return _isAttack; }
	inline void setIsAttack(bool isAttack) { _isAttack = isAttack; }

	inline bool getGameEnd() { return _isGameEnd; }

	inline void setEmMemoryLink(enemyManager* em) { _em = em; }
	inline void setMmMemoryLink(mapManager* mm) { _mm = mm; }

	inline enemyManager* getEnemyManager() { return _em; }
	
};

