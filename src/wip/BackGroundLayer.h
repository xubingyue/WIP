#pragma once
#include "Layer.h"

class WIPSprite;

class WIPBackgroundLayer:public WIPLayer
{
public:

private:
	friend WIPScene;
	typedef std::list<WIPSprite*> _ObjectList;
	_ObjectList _objects;
};