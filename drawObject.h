#pragma once
#include "gameNode.h"
class drawObject : public gameNode
{
	int _zOrder;
public:
	drawObject();
	virtual ~drawObject();
};

