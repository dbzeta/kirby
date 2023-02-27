#pragma once
#include <vector>

class enemyManager;
class mapManager;

class kirbyBase;

// �Դ°�


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

	// ������ ���� ��

	// ����
	LEFT_STOP,
	RIGHT_STOP,
	// ���� ����
	LEFT_LOW_STOP_UP,
	RIGHT_LOW_STOP_UP,
	LEFT_LOW_STOP_DOWN,
	RIGHT_LOW_STOP_DOWN,
	// ���� ����
	LEFT_HIGH_STOP_UP,
	RIGHT_HIGH_STOP_UP,
	LEFT_HIGH_STOP_DOWN,
	RIGHT_HIGH_STOP_DOWN,

	// �ɾ��� ��

	// ����
	LEFT_SIT,
	RIGHT_SIT,
	// ���� ����
	LEFT_LOW_SIT_DOWN,
	RIGHT_LOW_SIT_DOWN,
	LEFT_LOW_SIT_UP,
	RIGHT_LOW_SIT_UP,
	// ���� ����
	LEFT_HIGH_SIT_DOWN,
	RIGHT_HIGH_SIT_DOWN,
	LEFT_HIGH_SIT_UP,
	RIGHT_HIGH_SIT_UP,


	// �̵�

	// ����
	LEFT_MOVE,
	RIGHT_MOVE,
	// ���� ����
	LEFT_LOW_MOVE,
	RIGHT_LOW_MOVE,
	// ���� ����
	LEFT_HIGH_MOVE,
	RIGHT_HIGH_MOVE,

	// �޸���
	LEFT_DASH,
	RIGHT_DASH,

	// ���� ( ��¥�� ���� �����϶� �ö󰡰ų� �������� �����̹Ƿ� �¿�� ������ ���� �Ǵ����� STATE�� �߰� )

	// ���� ���Ƶ��� ��
	LEFT_FLY_EAT,
	RIGHT_FLY_EAT,
	// �ö󰥶�
	LEFT_FLY_UP,
	RIGHT_FLY_UP,
	// ��������
	LEFT_FLY_DOWN,
	RIGHT_FLY_DOWN,
	// ���� ������ ���� ��
	LEFT_FLY,
	RIGHT_FLY,
	// ���� ������ �����϶� ( �¿� �̵��� state �����Ҷ��� �Ⱦ� )
	LEFT_FLY_MOVE,
	RIGHT_FLY_MOVE,


	// ����

	// ���� �ö󰥶� 
	LEFT_JUMP_UP,
	RIGHT_JUMP_UP,
	// ���� �߰�����
	LEFT_JUMP_TURN,
	RIGHT_JUMP_TURN,
	// ���� �������� 
	LEFT_JUMP_DOWN,
	RIGHT_JUMP_DOWN,

	// ��Ŭ
	LEFT_KICK,
	RIGHT_KICK,

	// ��Ű�� ����
	LEFT_EAT,
	RIGHT_EAT,
	// ��� ��Ű�� ��
	LEFT_EATING,
	RIGHT_EATING,

	// �����
	LEFT_THROW,
	RIGHT_THROW,

	// �߶�
	LEFT_FALL,
	RIGHT_FALL,

	// ������ ��
	LEFT_ATTACK,
	RIGHT_ATTACK,

	// ���� ����
	LEFT_RETURN,
	RIGHT_RETURN,

	// �浹
	LEFT_CRASH,
	RIGHT_CRASH,

	// ����
	LEFT_SWIM,
	RIGHT_SWIM,

	// ������ȯ�Ҷ�
	LEFT_TURN,
	RIGHT_TURN,

	// ���� ����
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

	// Ŀ�� �����Ѵ�. ( ���� Ŀ�� ����Ű�� �� )
	kirbyBase* _currentKirby;

	// �÷��̾� �̹��� ���� ��ǥ
	float _cx, _cy;
	float _startCx, _startCy;

	// �÷��̾� ��Ʈ, �浹�� ��Ʈ
	RECT _rc, _collisionRC;

	// ���� ��ų�� ���� ��Ʈ
	RECT _eatRc;

	// �÷��̾� state
	STATE _state;
	STATE _preState;

	// ���� ���� Ŀ�񼼿�? �Ǵ��� mode
	MODE _mode;

	// fly, jump�� �Ҷ� ���� dir
	DIRECTION _dir;

	// Ű �Է¿� ���� state��ȭ�� �����ϰ� ���� �ð��� ����ؾ��ϴ� ��� count�� ����Ͽ� state�� �����Ѵ�.
	int _count;
	float _timer;

	// �뽬 �Ǻ��� ���� count
	bool _isDashReady;

	bool _isPixelCollision;
	bool _isRectCollision;

	bool _isPixelCollisionUp;

	bool _isGameEnd;

	// hp , life
	int _hp, _life;

	// LEFT RIGHT �Ǵ�
	bool _isRight;

	bool _isPushButton;

	// ���� �Ծ���? 
	bool _isFull;

	// �� ���ȴ�?
	bool _isOnTheDoor;

	RECT _tempRect;

	// �����̴�?
	bool _isAttack;


public:
	kirby();
	virtual ~kirby();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void keyControl();		// Ű�� ������ state�� ��ȭ
	void checkState();		// ���� state�� ���� state, x/y, rect�� ��ȭ (_count �� ����Ͽ� state�� ��ȭ��Ų��.)

	void checkPixelCollision();
	bool checkDoorPixel();
	void checkRectCollision();

	void changeMode(MODE mode);

	void attack();
	//��Ű��
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

