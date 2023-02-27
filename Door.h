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
	bool stageDoor;//->���� ������
	bool CountTrue;//ī���Ͱ� �����δ�
	bool StageStart;//���������� �����Ѵ�
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
	virtual void DoorRectMake(RECT rcFocus);//���Ʈ����
	virtual void draw(RECT rcFocus, bool Kuby, bool clear);
	//������ ��
	inline void setStageDoor(bool _stageDoor) { stageDoor = _stageDoor; }
	inline bool getStageDoor() { return stageDoor; }

	//���Ʈ ��
	inline RECT getRect() { return _DoorRect; }
	//�������� ���� ��
	inline bool getStageStart() { return StageStart; }
	//�������� ���� �� ��
	inline void setStageStart(bool _StageStart) { StageStart = _StageStart; }
	//���Ʈ
	inline void setDoorTrue(bool _DoorTrue) { DoorTrue = _DoorTrue; }
	inline bool getDoorTrue() { return DoorTrue; }
	//ī���� ����
	inline void setCountBool(bool _CountTrue) { CountTrue = _CountTrue; }
	//�������� ��ȯ

	void DoorCount();//���� ������ ������ ī����
	void NumberCount();
	void ClearCount();

};


