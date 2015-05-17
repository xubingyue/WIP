#include "Animator.h"
#include "RenderQuad.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "SpriteFrame.h"
#include "FrameBox.h"
#include "Renderer.h"
#include "AppManager.h"
#include "Input.h"

void WIPAnimator::callback (spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount) {
	spTrackEntry* entry = spAnimationState_getCurrent(state, trackIndex);
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
	char outstr[64];
	switch (type) {
	case SP_ANIMATION_START:
		sprintf(outstr,"%d start: %s\n", trackIndex, animationName);

		break;
	case SP_ANIMATION_END:
		sprintf(outstr,"%d end: %s\n", trackIndex, animationName);
		break;
	case SP_ANIMATION_COMPLETE:
		sprintf(outstr,"%d complete: %s, %d\n", trackIndex, animationName, loopCount);
		break;
	case SP_ANIMATION_EVENT:
		sprintf(outstr,"%d event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
			event->stringValue);
		break;
	}
	//printf(outstr);
	//fflush(stdout);
}

WIPAnimator* WIPAnimator::create(const char* atlas_path,const char* json_path,i32 w,i32 h)
{
	WIPAnimator* ret;
	ret = new WIPAnimator(atlas_path,json_path,w,h);
	ret->set_active(false);
	return ret;
}

void WIPAnimator::set_frame_ref(WIPSpriteFrame* frame)
{
	_frame_ref = frame;
}

WIPAnimator::WIPAnimator(const char* atlas_path,const char* json_path,i32 w,i32 h):time_scale(1)
{
	_out_buffer = WIPRenderTexture::create(w,h);
	_frame_ref = 0;

	spAtlas* atlas = spAtlas_createFromFile(atlas_path, 0);
	spSkeletonJson* json = spSkeletonJson_create(atlas);
	json->scale = 0.8f;
	spSkeletonData *skeletonData = spSkeletonJson_readSkeletonDataFile(json, json_path);
	if (!skeletonData) {
		printf("Error: %s\n", json->error);
		getchar();
		exit(0);
	}
	//spAnimation* walkAnimation = spSkeletonData_findAnimation(skeletonData, "walk");
	spSkeletonJson_dispose(json);
	spSkeletonBounds* bounds = spSkeletonBounds_create();

	spAnimationStateData* stateData = spAnimationStateData_create(skeletonData);
	//spAnimationStateData_setMixByName(stateData, "walk", "jump", 0.2f);
	//spAnimationStateData_setMixByName(stateData, "jump", "run", 0.2f);
	//spAnimationStateData_setMixByName(stateData, "shoot", "walk", 0.2f);

	//drawable = new SkeletonDrawable(skeletonData,stateData);
	spBone_setYDown(true);
	skeleton = spSkeleton_create(skeletonData);
	state = spAnimationState_create(stateData);
	time_scale = 1;

	//spSkeleton* skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	//spSkeleton_setSkinByName(skeleton, "goblin");
	spSkeleton_setToSetupPose(skeleton);

	skeleton->x = 0;
	skeleton->y = 0;
	spSkeleton_updateWorldTransform(skeleton);

	spSlot* headSlot = spSkeleton_findSlot(skeleton, "head");

	state->listener = callback;
	if (false) {
		spAnimationState_setAnimationByName(state, 0, "test", true);
	} else {

		spAnimationState_setAnimationByName(state, 0, "flying", true);
		/*
		spAnimationState_addAnimationByName(drawable->state, 0, "jump", false, 3);
		spAnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
		spAnimationState_addAnimationByName(drawable->state,0,"shoot",true,3);
		spAnimationState_addAnimationByName(drawable->state, 0, "walk", true,3);
		*/
	}
	//spAnimationState_setAnimation(drawable->state, 0, walkAnimation, false);
	//drawable->bounds = bounds;
}

WIPAnimator::~WIPAnimator()
{
	spAnimationState_dispose(state);
	spSkeleton_dispose(skeleton);
	delete _out_buffer;
}



void WIPAnimator::update(f32 dt)
{
	if(!_frame_ref)
		return;

	f32 iww = 1.f/g_app_manager->get_window_width();
	f32 iwh = 1.f/g_app_manager->get_window_height();

	f32 sw = _out_buffer->get_width()*iww;
	f32 sh = _out_buffer->get_height()*iwh;

	f32 hw =g_app_manager->get_window_width()*0.5f;
	f32 hh = g_app_manager->get_window_height()*0.65f;


	_out_buffer->begin();
	glClear(GL_COLOR_BUFFER_BIT);
	_out_buffer->end();
	spSkeleton_update(skeleton, dt);
	spAnimationState_update(state, dt * time_scale);
	spAnimationState_apply(state, skeleton);
	spSkeleton_updateWorldTransform(skeleton);
	_out_buffer->begin();
	for(int i=0;i<skeleton->slotCount; ++i)
	{
		spSlot* slot = skeleton->drawOrder[i];
		spAttachment* attachment = slot->attachment;
		if (!attachment) continue;
		WIPTexture* p = 0;
		if (attachment->type == SP_ATTACHMENT_REGION) 
		{
			//available
			spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;
			p = (WIPTexture*)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
			spRegionAttachment_computeWorldVertices(regionAttachment,  slot->skeleton->x, slot->skeleton->y,slot->bone, _world_vertices);
		}

		if(p)
		{
			spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;
			int tex_x = p->get_width();
			int tex_y = p->get_height();

			RenderQuad uv_q;
			uv_q.lt.x = regionAttachment->uvs[SP_VERTEX_X1];
			uv_q.lt.y =regionAttachment->uvs[SP_VERTEX_Y1];
			uv_q.lb.x = regionAttachment->uvs[SP_VERTEX_X2];
			uv_q.lb.y =regionAttachment->uvs[SP_VERTEX_Y2];
			uv_q.rt.x = regionAttachment->uvs[SP_VERTEX_X4];
			uv_q.rt.y =regionAttachment->uvs[SP_VERTEX_Y4];
			uv_q.rb.x = regionAttachment->uvs[SP_VERTEX_X3];
			uv_q.rb.y =regionAttachment->uvs[SP_VERTEX_Y3];

			int x1 = _world_vertices[SP_VERTEX_X1];
			int y1 = _world_vertices[SP_VERTEX_Y1];
			int x2 = _world_vertices[SP_VERTEX_X2];
			int y2 = _world_vertices[SP_VERTEX_Y2];
			int x4 = _world_vertices[SP_VERTEX_X3];
			int y4 = _world_vertices[SP_VERTEX_Y3];
			int x3 = _world_vertices[SP_VERTEX_X4];
			int y3 = _world_vertices[SP_VERTEX_Y4];

			

			RenderQuad q;
			q.lb.x = x1+hw;
			q.lb.y = y1+hh;
			q.lt.x = x2+hw;
			q.lt.y = y2+hh;
			q.rb.x = x3+hw;
			q.rb.y = y3+hh;
			q.rt.x = x4+hw;
			q.rt.y = y4+hh;

			
			
			g_renderer->render(p,&q,&uv_q);
			

		}
		
	}
	_out_buffer->end();
	_frame_ref->texture = _out_buffer;
	_frame_ref->framebox->set_quickly(0,0,0,1,1,1,1,0,0,0);

	
}

