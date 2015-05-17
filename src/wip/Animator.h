#pragma once
#include "spine.h"
#include "RBMath/Inc/Platform/RBBasedata.h"

class WIPTexture;
class WIPRenderTexture;
class WIPAnimationManager;
class WIPSpriteFrame;

/*
This class defines the animator ccomponent.With this component,we can use skeleton animation
Note:Once a gameobject has contained a Animator,the Animation componenet which defined frame animation will
not take effect.
*/
class WIPAnimator
{
public:
	static WIPAnimator* create(const char* atlas_path,const char* json_path,i32 w=200,i32 h=200);

	static void callback (spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount);

	WIPAnimator(const char* atlas_path,const char* json_path,i32 w,i32 h);
	~WIPAnimator();
	//contaoin update and draw(to _out_buffer)
	void update(f32 dt);

	void set_frame_ref(WIPSpriteFrame* frame_ref);
	INLINE WIPRenderTexture* get_buffer()
	{
		return _out_buffer;
	}

	INLINE void set_active(bool v)
	{
		_active = v;
	}

	FORCEINLINE bool active()
	{
		return _active;
	}
	float time_scale;
	spSkeleton* skeleton;
	spAnimationState* state;
private:
	friend WIPAnimationManager;
	WIPRenderTexture* _out_buffer;
	WIPSpriteFrame* _frame_ref;

	bool _active;

	float _world_vertices[100];
};