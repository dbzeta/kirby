#pragma once
#include "gameNode.h"
class settingScene : public gameNode
{
protected:
	float _backVolume;
	float _effectVolume;
	int _selectIndex;
	int _alpha;
	int _backNumber;
	int _effectNumber;
	bool _canKey;
public:
	settingScene();
	virtual ~settingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	int getNumber(float volume);

	static void changeScene();
};

