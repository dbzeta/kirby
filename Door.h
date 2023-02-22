#pragma once
#include "gameNode.h"
class mapManager;
class Door : public gameNode
{
private:
	float _DoorCount, _NumberCount, _ClearCount;
	int _DoorX;
	int _DoorY;
	string _DoorKeyName;
	bool stageDoor;//->문이 열린다
	bool CountTrue;//카운터가 움직인다
	bool StageStart;//스테이지가 시작한다
	RECT _DoorRect;
	RECT _DoorRectDraw;
	bool DoorTrue;
	int Stage;
public:
	Door();
	~Door();
	virtual HRESULT Doorinit(int X, int Y, string KeyName);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void DoorRectMake(RECT rcFocus);//도어렉트생성
	virtual void draw(RECT rcFocus, bool Kuby, bool clear);
	//문여는 불
	inline void setStageDoor(bool _stageDoor) { stageDoor = _stageDoor; }
	inline bool getStageDoor() { return stageDoor; }

	//도어랙트 줌
	inline RECT getRect() { return _DoorRect; }
	//스테이지 시작 불
	inline bool getStageStart() { return StageStart; }
	//스테이지 시작 불 쎗
	inline void setStageStart(bool _StageStart) { StageStart = _StageStart; }
	//도어렉트
	inline void setDoorTrue(bool _DoorTrue) { DoorTrue = _DoorTrue; }
	inline bool getDoorTrue() { return DoorTrue; }
	//카운터 시작
	inline void setCountBool(bool _CountTrue) { CountTrue = _CountTrue; }
	//스테이지 변환

	void DoorCount();//도어 프레임 돌리는 카운터
	void NumberCount();
	void ClearCount();

};


