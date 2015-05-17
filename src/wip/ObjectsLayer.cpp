#include "ObjectsLayer.h"
#include "Sprite.h"

WIPObjectsLayer::WIPObjectsLayer()
	: WIPLayer()
{

}

WIPObjectsLayer::~WIPObjectsLayer()
{

}

void WIPObjectsLayer::delete_all()
{
	_ObjectList::iterator it;
	for(it=_objects.begin();it!=_objects.end();++it)
	{
		delete (*it);
	}
}

void WIPObjectsLayer::add_object(WIPSprite* s)
{
	_objects.push_back(s);
}

void WIPObjectsLayer::clear()
{
	_objects.clear();
}