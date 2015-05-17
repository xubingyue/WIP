#pragma once
#include "Layer.h"


class WIPSprite;
class WIPCamera;
class WIPPhysicsManager;
class WIPAppManager;

class WIPObjectsLayer : public WIPLayer
{
public:
	WIPObjectsLayer();
	~WIPObjectsLayer();
	void add_object(WIPSprite* s);
	void delete_all();
	void clear();
protected:

private:
	friend WIPCamera;
	friend WIPScene;
	friend WIPPhysicsManager;
	friend WIPAppManager;
	typedef std::list<WIPSprite*> _ObjectList;
	_ObjectList _objects;


};