#include "SceneManager.h"

WIPSceneManager* WIPSceneManager::_instance = 0;

WIPSceneManager* WIPSceneManager::instance()
{
	if(!_instance)
		_instance = new WIPSceneManager();
	return _instance;
}

WIPSceneManager::WIPSceneManager()
{

}

WIPSceneManager::~WIPSceneManager()
{

}

bool WIPSceneManager::startup()
{
	return true;
}

void WIPSceneManager::shutdown()
{

}

WIPSceneManager* g_scene_manager = WIPSceneManager::instance();