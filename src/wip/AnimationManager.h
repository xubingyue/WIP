#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include <list>
#include "LinkList.h"

#define WIP_ANIMATION_DELTA_T 1/24

class WIPAnimationClip;

class WIPAnimationManager
{
public:
	static WIPAnimationManager* instance();

	bool startup(f32 delta = 1/24);
	void shutdown();
	void update(f32 dt);

	void add_clip(WIPAnimationClip* clip);
	void add_clip_back(WIPAnimationClip* clip);
	void add_clip_front(WIPAnimationClip* clip);
protected:
	WIPAnimationManager();
	~WIPAnimationManager();

private:

	static WIPAnimationManager* _instance;

	typedef LinkList<WIPAnimationClip*> _ClipQueue;
	_ClipQueue _clip_queue;
	i32 _queue_szie;

	//f32 _cur_dt;
	f32 _delta_t;
};

extern WIPAnimationManager* g_animation_manager;