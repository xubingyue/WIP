#include "UILayer.h"
#include "Sprite.h"


void WIPUILayer::delete_all()
{
	_ObjectList::iterator it;
	for(it=_objects.begin();it!=_objects.end();++it)
	{
		delete (*it);
	}
}

void WIPUILayer::add_ui(ActiveDrawableRect* s)
{
	_objects.push_back(s);
}

void WIPUILayer::clear()
{
	_objects.clear();
}