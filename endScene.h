#pragma once
#include "gameNode.h"
class endScene : public gameNode
{
private:
	int _selectIndex;
	image* _hand;
	int _handX;
	int _handY;
	int _handFrameX;
	bool _canKey;
	bool _select;
	float _count;
public:
	endScene();
	virtual ~endScene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	static void changeScene(void* obj);
	inline int getSelectIndex() { return _selectIndex; }
};

