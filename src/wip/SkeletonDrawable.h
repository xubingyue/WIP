#pragma once

#include "spine.h"
#include "extension.h"


class SkeletonDrawable
{
public:
	int x,y;
	bool bmove;
	int s;
	spSkeleton* skeleton;
	spAnimationState* state;
	//时间缩放因子
	float time_scale;
	//一种动画需要的bounds，外部初始化spine时输入
	spSkeletonBounds* bounds;

	SkeletonDrawable(spSkeletonData* skeletonData, spAnimationStateData* stateData=0);
	~SkeletonDrawable();
	void UpdateLogic();
	void draw();

	
protected:

private:
	float world_vertices[100];
};
