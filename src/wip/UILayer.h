#pragma once
#include "Layer.h"
#include "flyUI/ActiveDrawableRect.h"

class WIPSprite;
class WIPAppManager;

class WIPUILayer:public WIPLayer
{
public:
	void add_ui(ActiveDrawableRect* w);
	void delete_all();
	void clear();
private:
	friend WIPScene;
	friend WIPAppManager;
	typedef std::list<ActiveDrawableRect*> _ObjectList;
	_ObjectList _objects;
};