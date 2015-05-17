#pragma once
#include "RBMath\Inc\Platform\RBBasedata.h"

class WIPObjectsLayer;
class WIPBackgroundLayer;
class WIPUILayer;
class WIPTextCanvas;
class WIPSceneManager;
class WIPCamera;
class WIPMesh;
class WIPSprite;
class WIPAppManager;
class WIPPhysicsManager;

class WIPScene
{
public:
	WIPScene();
	~WIPScene();

	bool load();
	//not in use
	void update_logic(f32 dt);
	void cull_scene(WIPCamera* camera);
	void add_object(WIPSprite* sprite);
	void delete_all_object();

	FORCEINLINE WIPUILayer* get_ui_layer()
	{
		return _ui_layer;
	}

private:
	friend WIPAppManager;
	friend WIPSceneManager;
	friend WIPPhysicsManager;
	WIPBackgroundLayer* _bg_layer;
	WIPObjectsLayer* _obj_layer;
	WIPUILayer* _ui_layer;
	WIPTextCanvas* _text_canvas;

	
};