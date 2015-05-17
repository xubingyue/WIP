#include "Scene.h"
#include "BackGroundLayer.h"
#include "UILayer.h"
#include "TextCanvas.h"
#include "Sprite.h"
#include "Camera.h"
#include "ObjectsLayer.h"
#include "RenderBatch.h"
#include "Assertion.h"
#include "Logger.h"

void WIPScene::update_logic(f32 dt)
{
#ifdef _DEBUG
	WIPObjectsLayer::_ObjectList::iterator it;
	for(it = _obj_layer->_objects.begin();it!=_obj_layer->_objects.end();++it)
	{
		//This is moved to Lua.Reference to Lua::main_script() method

	}
	g_logger->debug_print(WIP_ERROR,"You have called c++ update_logic but it is not in use!");
#endif
}

void WIPScene::cull_scene(WIPCamera* camera)
{
	camera->culling(_obj_layer);



	
}

WIPScene::WIPScene()
{
	_bg_layer = new WIPBackgroundLayer();
	_obj_layer = new WIPObjectsLayer();
	_ui_layer = new WIPUILayer();
	_text_canvas = new WIPTextCanvas(800,600);
}

WIPScene::~WIPScene()
{
	delete _bg_layer;
	delete _obj_layer;
	delete _ui_layer;
	delete _text_canvas;
}

void WIPScene::add_object(WIPSprite* s)
{
	_obj_layer->add_object(s);
}

void WIPScene::delete_all_object()
{
	_obj_layer->delete_all();
	_obj_layer->clear();
}