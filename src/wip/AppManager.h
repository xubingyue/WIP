#pragma once
#include "Utilities\NoCopy.h"
#include "OpenGL.h"
#include <vector>

class Win32TimeSource;
class RBTimerBase;
class RBClock;
class WIPCamera;
class WIPScene;
class WIPTextCanvas;
class OggStream;

class WIPAppManager : private WIPNoCopy
{
public:
	static WIPAppManager* instance();

	WIPAppManager::WIPAppManager();
	WIPAppManager::~WIPAppManager();
	bool startup();
	void shutdown();

	bool create_window(const char* title,int width,int height);
	void run();

	inline GLFWContext* get_glfw_context()
	{
		return &context;
	}
	inline int get_window_height()
	{
		return _es_context->height;
	}
	inline int get_window_width()
	{
		return _es_context->width;
	}
	void add_camera(WIPCamera* camera);
	void remove_camera(WIPCamera* camera);
	void clear_cameras();
	void add_scene(WIPScene* scene);
	void remove_scene(WIPScene* scene);
	void clear_scene();
	double get_dt();

	WIPTextCanvas* text_cav;
	OggStream* ogg_stream;
protected:

private:
	static WIPAppManager* _instance;

	ESContext *_es_context;
	GLFWContext context;
	Win32TimeSource* times;
	RBClock* clock;
	RBTimerBase *timer;
	double lastTime;
	double curTime;
	float _frame;

	typedef std::vector<WIPCamera*> _CameraList;
	_CameraList _cameras;
	_CameraList::iterator _it_camera;

	typedef std::vector<WIPScene*> _SceneList;
	_SceneList _scenes;
	_SceneList::iterator _it_scene;

	
};

extern WIPAppManager* g_app_manager;