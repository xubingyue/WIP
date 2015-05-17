#include "ObjectsLayer.h"
#include "Scene.h"
#include "Sprite.h"
#include "Collider.h"
#include "PhysicsManager.h"

WIPPhysicsManager* WIPPhysicsManager::_instance = 0;
Floekr2d::f2Space* WIPPhysicsManager::_phy_space = 0;

WIPPhysicsManager* WIPPhysicsManager::instance()
{
	if(!_instance)
		_instance = new WIPPhysicsManager();
	return _instance;
}

WIPPhysicsManager::WIPPhysicsManager()
{

}

WIPPhysicsManager::~WIPPhysicsManager()
{

}

void WIPPhysicsManager::delete_body(Floekr2d::f2Body* b)
{
	if(b)
		_phy_space->deleteBody(b);
}

Floekr2d::f2PolygonShape* WIPPhysicsManager::create_polygon()
{
	if(_phy_space)
		return (Floekr2d::f2PolygonShape*)_phy_space->createShape(Floekr2d::f2Shape::e_polygon);
	return NULL;
}

Floekr2d::f2Body* WIPPhysicsManager::create_body()
{
	if(_phy_space)
		return (Floekr2d::f2Body*)_phy_space->createBody();
	return NULL;
}

bool WIPPhysicsManager::startup()
{
	if(_phy_space)
		delete _phy_space;
	_phy_space = new Floekr2d::f2Space();

	//for test
	_phy_space->setGravity(0,-200);

	_phy_space->setIteration(8);

	return true;
}

void WIPPhysicsManager::shutdown()
{
	delete _phy_space;
}

void  WIPPhysicsManager::update(WIPScene* scene)
{
	WIPSprite* s;
	WIPObjectsLayer* layer = scene->_obj_layer;
	WIPObjectsLayer::_ObjectList::iterator it;
	for(it = ((WIPObjectsLayer*)layer)->_objects.begin();it!=((WIPObjectsLayer*)layer)->_objects.end();++it)
	{
		//write
		s = *it;
		if(s->_collider)
			s->_collider->update_in(s->_copy_mesh,s->rotation,s->world_x,s->world_y);
	}

	_phy_space->step();

	for(it = ((WIPObjectsLayer*)layer)->_objects.begin();it!=((WIPObjectsLayer*)layer)->_objects.end();++it)
	{
		//read
		s = *it;
		if(s->_collider)
			s->_collider->update_out(*s->_copy_mesh,s->rotation,s->world_x,s->world_y);
	}
}

WIPPhysicsManager* g_physics_manager = WIPPhysicsManager::instance();
