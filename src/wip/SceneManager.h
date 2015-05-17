#pragma once
#include "RBMath\Inc\Platform\RBBasedata.h"
#include <vector>

class WIPScene;

class WIPSceneManager
{
public:
	static WIPSceneManager* instance();

	bool startup();
	void shutdown();

	void update();
	void push();
	void pop();

	

protected:
	WIPSceneManager();
	~WIPSceneManager();

private:
	static WIPSceneManager* _instance;

	WIPScene* current_scene;

	typedef std::vector<WIPScene*> _SceneStack;
	_SceneStack _scene_stack;
};

extern WIPSceneManager* g_scene_manager;