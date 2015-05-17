#include "RenderQuad.h"
#include "SkeletonDrawable.h"
#include "Texture.h"
#include "Renderer.h"


SkeletonDrawable::SkeletonDrawable(spSkeletonData* skeletonData, spAnimationStateData* stateData)
		:time_scale(1)
	{
		//设置Y轴方向
		spBone_setYDown(true);
		//world_vertices = (float*)malloc(1000);
		skeleton = spSkeleton_create(skeletonData);
		state = spAnimationState_create(stateData);
		//动画状态机更新用，每帧消耗的时间
		//delta_time = 0.001;


		s = 0;
		bmove = true;
	}
	SkeletonDrawable::~SkeletonDrawable()
	{
		//释放资源
		spAnimationState_dispose(state);
		spSkeleton_dispose(skeleton);
	}
	void SkeletonDrawable::UpdateLogic()
	{

		//只有一种动画才需要更新这个
		if(bounds)
			spSkeletonBounds_update(bounds, skeleton, true);
		//if(x==300&&state->data)
			//spAnimationState_addAnimationByName(state,0,"jump",true,0);
		//所有的动画都需要更新这个
		float t = 0.001;
		spSkeleton_update(skeleton, t);
		spAnimationState_update(state, t * time_scale);
		spAnimationState_apply(state, skeleton);
		spSkeleton_updateWorldTransform(skeleton);
	}
	void SkeletonDrawable::draw()
	{
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
				spRegionAttachment_computeWorldVertices(regionAttachment,  slot->skeleton->x, slot->skeleton->y,slot->bone, world_vertices);
				//上述语句执行之后，图片资源的坐标会与骨骼坐标形成对应，最外层的for循环中的skeleton->slotCount是多少，
				//那么png图片就可以被拆解成多少个部件
				//每个部件都是一个旋转的矩形，world_vertices中就储存着这个矩形的四个顶点

			}
			else if (attachment->type == SP_ATTACHMENT_MESH) 
			{
				spMeshAttachment* mesh = (spMeshAttachment*)attachment;
				if (mesh->verticesCount > 1000) continue;
				p = (WIPTexture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject;
				spMeshAttachment_computeWorldVertices(mesh, /*slot->skeleton->x, slot->skeleton->y, */x,y,slot, world_vertices);

				for (int i = 0; i < mesh->trianglesCount; ++i)
				{

				}
			}
			else if (attachment->type == SP_ATTACHMENT_SKINNED_MESH) 
			{
				spSkinnedMeshAttachment* mesh = (spSkinnedMeshAttachment*)attachment;
				if (mesh->uvsCount > 1000) continue;
				p = (WIPTexture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject;
				spSkinnedMeshAttachment_computeWorldVertices(mesh, /*slot->skeleton->x, slot->skeleton->y, */x,y,slot, world_vertices);

				for (int i = 0; i < mesh->trianglesCount; ++i) 
				{

				}
			}

			if (p) 
			{
				//RECT rect = {world_vertices[SP_VERTEX_X1]+x,world_vertices[SP_VERTEX_Y1]+world_vertices[SP_VERTEX_X4]+y,world_vertices[SP_VERTEX_Y4]+1024+x,256+y};
				//RECT rectclip = {0+x,0+y,256+x,256+y};
				
				//p->Draw(hdc,rect,&rectclip);
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

				int x1 = world_vertices[SP_VERTEX_X1];
				int y1 = world_vertices[SP_VERTEX_Y1];
				int x2 = world_vertices[SP_VERTEX_X2];
				int y2 = world_vertices[SP_VERTEX_Y2];
				int x4 = world_vertices[SP_VERTEX_X3];
				int y4 = world_vertices[SP_VERTEX_Y3];
				int x3 = world_vertices[SP_VERTEX_X4];
				int y3 = world_vertices[SP_VERTEX_Y4];

				RenderQuad q;
				q.lb.x = x1+x;
				q.lb.y = y1+y;
				q.lt.x = x2+x;
				q.lt.y = y2+y;
				q.rb.x = x3+x;
				q.rb.y = y3+y;
				q.rt.x = x4+x;
				q.rt.y = y4+y;
				//
				/*
				set_point(hdc,x1+x,y1+y);
				set_point(hdc,x2+x,y2+y);
				set_point(hdc,x3+x,y3+y);
				set_point(hdc,x4+x,y4+y);
				*/
				g_renderer->render(p,&q,&uv_q);
				//g_renderer->draw_box(&q);
				//g_renderer->render(p,&uv_q);

				if(bmove)
				{
					s++;
					if(0==s%12)
					{
						x++;
						if(x>720)
							x = -200;
					}
				}
				
				
			}
		}

	}

