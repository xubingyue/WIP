#include "Camera.h"
#include "callbacks.h"
#include "user.h"
#include "AppManager.h"
#include "KeyDefinetions.h"
#include "InputManager.h"
#include "Input.h"
#include "ResourceManager.h"
#include "ScriptManager.h"
#include "Renderer.h"
#include "Clock.h"
#include "Timer.h"
#include "Utilities/WIPIniHelper.h"
#include "synchapi.h "
#include "Scene.h"
#include "ObjectsLayer.h"
#include "AnimationManager.h"
#include "Animator.h"
#include "Sprite.h"
#include "PhysicsManager.h"
#include "Logger.h"
#include "flyUI/ActiveDrawableRect.h"
#include "UILayer.h"
#include "TextCanvas.h"
#include "OggStream.h"
#include "SoundPlayer.h"


WIPAppManager* WIPAppManager::_instance = 0;

WIPAppManager::WIPAppManager()
{
	_es_context = NULL;
}

WIPAppManager::~WIPAppManager()
{

}

WIPAppManager* WIPAppManager::instance()
{
	if(!_instance)
		_instance = new WIPAppManager();
	return _instance;
}

bool WIPAppManager::create_window(const char* title,int width,int height)
{
	//just for convinience
	_es_context = new ESContext();
	memset ( _es_context, 0, sizeof ( ESContext ) );

	glfwSetErrorCallback(glfw_error_callback);
	if(!init_gl(&context.window,title,width,height))
	{
		printf("init_gl failed!\n");
		getchar();
	}
	glfwSetCursorPosCallback(context.window,glfw_mouse_pos_callback);
	glfwSetMouseButtonCallback(context.window,glfw_mouse_button_callback);
	glfwSetKeyCallback(context.window,glfw_key_callback);
	glfwSetScrollCallback(context.window,glfw_scroll_callback);
	glfwGetWindowSize(context.window,&_es_context->width,&_es_context->height);
	g_renderer->startup(_es_context);
	if (!Init(_es_context))
	{
		printf("Big Init failed!");
		return false;
	}
	times = new Win32TimeSource();
	RBClock::init(times);
	clock = RBClock::Instance();

	timer = new RBTimerBase(*clock);
	clock->set_filtering(10,0.1666666666666f);
	lastTime = timer->get_time();
	clock->update();
	glViewport(0, 0, _es_context->width, _es_context->height);
	glClearColor(0.85,0.85,0.85,1);
	glClear(GL_COLOR_BUFFER_BIT);

	text_cav = new WIPTextCanvas();
	ogg_stream = new OggStream();
	g_sound_palyer->startup();
	return true;
}

void WIPAppManager::run()
{
	while (!glfwWindowShouldClose(context.window))
	{

		curTime = times->get_time();
		if(curTime-lastTime>=_frame)
		{
			//////////////////////////////////////////////////////////////////////////
			//only this order!!!!!
			//only to put input handle here to keep everything right
			{

				int bits = g_input_manager->get_last_key_info()->key_bit;
				int bits_c = g_input_manager->get_last_key_info()[1].key_bit;

				if(lmouse_keep_going)
				{
					bits |= WIP_MOUSE_LBUTTON;
				}
				if(rmouse_keep_going) 
					bits |= WIP_MOUSE_RBUTTON;
				if(mmouse_keep_going) 
					bits |= WIP_MOUSE_MBUTTON;
				g_input_manager->update(bits_c,bits);

			}

			glfwPollEvents();
			//////////////////////////////////////////////////////////////////////////
			g_animation_manager->update(clock->get_frame_time());

			//物理卡顿
			//快速拖动鼠标导致物理穿透

			_it_scene = _scenes.begin();
			for(;_it_scene!=_scenes.end();++_it_scene)
			{
				g_physics_manager->update(*_it_scene);
			}

			
			g_script_manager->call("main_logic");
			

			
			_it_scene = _scenes.begin();
			for(;_it_scene!=_scenes.end();++_it_scene)
			{
				WIPScene* scene = *_it_scene;
				WIPSprite* s;
				WIPObjectsLayer* layer = scene->_obj_layer;
				WIPObjectsLayer::_ObjectList::iterator it;
				for(it = ((WIPObjectsLayer*)layer)->_objects.begin();it!=((WIPObjectsLayer*)layer)->_objects.end();++it)
				{
					//write
					s = *it;
					if(s->_animator&&s->_animator->active())
						s->_animator->update(clock->get_frame_time());
				}
			}
			

			_it_camera = _cameras.begin();
			for(;_it_camera!=_cameras.end();++_it_camera)
			{
				_it_scene = _scenes.begin();
				for(;_it_scene!=_scenes.end();++_it_scene)
				{
					(*_it_camera)->culling((*_it_scene)->_obj_layer);

					//for test
					/*
					(*_it_camera)->begin();
					glClearColor(0.85,0,0,0.1);
					glClear(GL_COLOR_BUFFER_BIT);

					(*_it_camera)->end();
					*/
					g_renderer->render_to_camera(*_it_camera,(*_it_scene)->_obj_layer->_batch);
				}
			}

			glViewport(0, 0, _es_context->width, _es_context->height);
			glClearColor(0.85,0.85,0.85,1);
			glClear(GL_COLOR_BUFFER_BIT);
			g_script_manager->call("debug_draw");

			_it_camera = _cameras.begin();
			for(;_it_camera!=_cameras.end();++_it_camera)
			{
				(*_it_camera)->render();
			}

			
			_it_scene = _scenes.begin();
			for(;_it_scene!=_scenes.end();++_it_scene)
			{
				WIPScene* scene = *_it_scene;
				ActiveDrawableRect* s;
				WIPUILayer* layer = scene->_ui_layer;
				WIPUILayer::_ObjectList::iterator it;
				for(it = ((WIPUILayer*)layer)->_objects.begin();it!=((WIPUILayer*)layer)->_objects.end();++it)
				{
					//write
					s = *it;
					s->draw();
				}
			}
			//text_cav->update();
			text_cav->draw_buffer(0,0,_es_context->width,_es_context->height);
			//draw can't be placed in it but because of the mass achitecture
			Draw(_es_context,clock->get_frame_rate());
			lastTime = curTime;
			clock->update();
			g_sound_palyer->update();
			
			glfwSwapBuffers(context.window);
			g_input_manager->clear_states();
			//for glfw
			g_input_manager->clear_scroller();
		}
		else
		{
			Sleep(0);
		}

	}

}
#include "Texture.h"
bool WIPAppManager::startup()
{
	float fps;
	std::string path = "WIPCFG.ini";
	std::string log_path;
	if(WIPIniHelper::reset_ini_file(path.data()))
	{
		WIPIniHelper::get_float("Common","fps",fps);
		_frame = 1.0f/fps;
		WIPIniHelper::get_string("Common","log",log_path);
	}
	else
	{
		printf("Read ini failed!\n");
		getchar();
		exit(0);
	}
	WIPIniHelper::close();

	g_logger->startup(log_path.c_str());
	
	g_physics_manager->startup();
	g_input_manager->startup("");
	g_res_manager->startup();
	g_script_manager->startup();
	//g_renderer->startup(_es_context);
	g_animation_manager->startup(0.15);

	return true;
}

void WIPAppManager::shutdown()
{

	delete text_cav;

	glfwDestroyWindow(context.window);

	glfwTerminate();

	g_renderer->shutdown();
	g_animation_manager->shutdown();
	g_script_manager->shutdown();
	g_input_manager->shutdown();
	g_res_manager->shutdown();
	g_physics_manager->shutdown();
	delete _es_context;
	
	delete timer;
	delete clock;
	delete times;

	delete _instance;

	g_logger->shutdown();
}

void WIPAppManager::add_camera(WIPCamera* camera)
{
	_cameras.push_back(camera);
}

void WIPAppManager::remove_camera(WIPCamera* camera)
{
	_CameraList::iterator it;
	for(it = _cameras.begin();it!=_cameras.end();++it)
	{
		if((*it)==camera)
		{
			_cameras.erase(it);
			break;
		}
	}
	
}

void WIPAppManager::clear_cameras()
{
	_cameras.clear();
}

void WIPAppManager::add_scene(WIPScene* scene)
{
	_scenes.push_back(scene);
}

void WIPAppManager::remove_scene(WIPScene* scene)
{
	_SceneList::iterator it;
	for(it = _scenes.begin();it!=_scenes.end();++it)
	{
		if((*it)==scene)
		{
			_scenes.erase(it);
			break;
		}
	}
	
}

void WIPAppManager::clear_scene()
{
	_scenes.clear();
}

f64 WIPAppManager::get_dt()
{
	return timer->get_frame_time();
}

WIPAppManager* g_app_manager = WIPAppManager::instance();