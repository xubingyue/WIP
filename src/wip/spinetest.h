#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "SkeletonDrawable.h"
void callback (spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount) {
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
spSkeleton* skeletonNode;
spAnimationState* state;
SkeletonDrawable* drawable;

void spine_init()
{
	spAtlas* atlas = spAtlas_createFromFile("../Resources/spineboy/export/dragon.atlas", 0);
	spSkeletonJson* json = spSkeletonJson_create(atlas);
	json->scale = 0.4f;
	spSkeletonData *skeletonData = spSkeletonJson_readSkeletonDataFile(json, "../Resources/spineboy/export/dragon.json");
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

	drawable = new SkeletonDrawable(skeletonData,stateData);
	drawable->time_scale = 10.6;

	spSkeleton* skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	//spSkeleton_setSkinByName(skeleton, "goblin");
	spSkeleton_setToSetupPose(skeleton);

	skeleton->x = 0;
	skeleton->y = 0;
	spSkeleton_updateWorldTransform(skeleton);

	spSlot* headSlot = spSkeleton_findSlot(skeleton, "head");

	drawable->state->listener = callback;
	if (false) {
		spAnimationState_setAnimationByName(drawable->state, 0, "test", true);
	} else {
		
		spAnimationState_setAnimationByName(drawable->state, 0, "flying", true);
		/*
		spAnimationState_addAnimationByName(drawable->state, 0, "jump", false, 3);
		spAnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
		spAnimationState_addAnimationByName(drawable->state,0,"shoot",true,3);
		spAnimationState_addAnimationByName(drawable->state, 0, "walk", true,3);
		*/
	}
	//spAnimationState_setAnimation(drawable->state, 0, walkAnimation, false);
	drawable->x = 160;
	drawable->y = 290;
	drawable->bounds = bounds;
}

void init()
{
	spine_init();
}

void update()
{

}