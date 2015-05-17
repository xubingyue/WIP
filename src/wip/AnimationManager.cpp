#include "AnimationManager.h"
#include "AnimationClip.h"
#include "SpriteFrame.h"
#include "FrameBox.h"
#include "RBMath/Inc/RBMath.h"

#ifdef _DEBUG
#include "Assertion.h"
#endif


WIPAnimationManager* WIPAnimationManager::_instance = 0;

WIPAnimationManager* WIPAnimationManager::instance()
{
	if(!_instance)
		_instance = new WIPAnimationManager();
	return _instance;
}

bool WIPAnimationManager::startup(f32 delta/* = 1/24*/)
{
	_delta_t = delta;
	return true;
}

void WIPAnimationManager::shutdown()
{

}

void WIPAnimationManager::update(f32 dt)
{
	/*
	_cur_dt+=dt;
	if(dt<_delta_t)
		return;
		*/
	WIPAnimationClip* clip;
	i32 step = 1;
	WIPFrameBox* frame;
	i32 index = 0;
	i32 n = 0;
	i32 copy_size = _queue_szie;
	//_queue_szie = 0;
	int i = 0;
	//clip = _clip_queue.front();
	//while(i<_clip_queue.size())
	if(_clip_queue.size()!=0)
	{

		clip = _clip_queue.begin()->value;
		_ClipQueue::iterator it = _clip_queue.getHead();
		for(;it!=_clip_queue.end();it = it->next)
		{
			
			clip = it->next->value;
			if(clip->_will_stop)
			{
				clip->bplaying = false;
				--_queue_szie;
				_clip_queue.pre_remove(clip);
				clip->_will_stop = false;
			}
			clip->_cur_dt += dt * clip->_speed;
			//printf("\n\n%d",clip);
			if(RBMath::abs(clip->_cur_dt)>=_delta_t + 0.001)
			{

				step = clip->_cur_dt>0 ? 1 : -1;

				//printf("\n\n%d\n%f\n%f",clip,clip->_cur_dt-dt,clip->_cur_dt);
				frame = clip->_framebox_ref;
				index = (clip->_cur_frame-1)*8;
				frame->lt.x = clip->_uvs[index];
				frame->lt.y = clip->_uvs[index+1];
				frame->lb.x = clip->_uvs[index+2];
				frame->lb.y = clip->_uvs[index+3];
				frame->rb.x = clip->_uvs[index+4];
				frame->rb.y = clip->_uvs[index+5];
				frame->rt.x = clip->_uvs[index+6];
				frame->rt.y = clip->_uvs[index+7];
				clip->_cur_frame+=step;

				if(clip->_cur_frame>clip->_total_frame)
				{

					clip->_cur_frame = 1;
					if(!clip->bloop)
					{
						clip->bplaying = false;
						//_clip_queue.pre_pop_front();
						_clip_queue.pre_remove(clip);
						--_queue_szie;
					}
					/*
					if(clip->bloop)
					{
					//add_clip_back(clip);
					_clip_queue.push_back(clip);
					}
					*/

				}
				else if(clip->_cur_frame<1)
				{
					//once set the speed to negtive be sure to set the frame to the last
					//and be sure that set the speed only when the clip is stop
					clip->_cur_frame = clip->_total_frame;
					if(!clip->bloop)
					{
						clip->bplaying = false;

						//_clip_queue.pre_pop_front();
						_clip_queue.pre_remove(clip);
					}
					--_queue_szie;
					/*
					if(clip->bloop)
					{
					add_clip_back(clip);
					}
					*/

				}
				clip->_cur_dt = 0;
			}
			++n;
			++i;
		}
		//Mark recycling to prevent the iterator to be invalid
		_clip_queue.recycle();
	}

#ifdef _DEBUG
//	CHECK(_queue_szie==_clip_queue.size());
#endif
}

void WIPAnimationManager::add_clip(WIPAnimationClip* clip)
{
	/*
	if(!clip)
		return;
	*/
	clip->bplaying = true;
	_clip_queue.push_back(clip);
	++_queue_szie;
}

void WIPAnimationManager::add_clip_back(WIPAnimationClip* clip)
{
	clip->bplaying = true;
	_clip_queue.push_back(clip);
	++_queue_szie;
}

void WIPAnimationManager::add_clip_front(WIPAnimationClip* clip)
{
	clip->bplaying = true;
	_clip_queue.push_front(clip);
	++_queue_szie;
}

WIPAnimationManager::WIPAnimationManager()
{
	_queue_szie = 0;
	//_cur_dt = 0.f;
	_delta_t = 1/24;
}

WIPAnimationManager::~WIPAnimationManager()
{

}


WIPAnimationManager* g_animation_manager = WIPAnimationManager::instance();

