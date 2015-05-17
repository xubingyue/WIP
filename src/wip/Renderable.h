#pragma once
#include "OpenGL.h"
#include "Mesh.h"
#include "RBMath/Inc/Platform/RBBasedata.h"
class WIPMesh;
class WIPFrameBox;
class WIPRenderBatch;
class WIPRenderable
{


protected:
	friend WIPRenderBatch;
	class _WIPRenderPack
	{
		
	public:
		//camera change it when culling
		//actually it is not mesh!
		WIPMesh mesh;
		WIPFrameBox* framebox;
		GLuint tex_id;
		i32 z_order;
		_WIPRenderPack();
	
		
		void update(GLuint tex_id,i32 z_order);
		bool operator < (const _WIPRenderPack& n);
		bool operator > (const _WIPRenderPack& n);

	};

protected:
	_WIPRenderPack _pak;

};