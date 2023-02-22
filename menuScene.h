#pragma once
#include "gameNode.h"
class menuScene : public gameNode
{
protected:
	int _selectIndex;
	int _alpha;
	bool _canKey;
public:
	menuScene();
	virtual ~menuScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	inline int getSelectIndex() { return _selectIndex; }
	static void changeScene(void* obj);
	static void changeScene();
};

