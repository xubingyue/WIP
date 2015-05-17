#include "RenderBatch.h"
#include "Assertion.h"
#include "FrameBox.h"
#include "Renderer.h"
#include "Logger.h"
#include <functional>

const i32 WARNING_NUM_LEVEL = 50;

WIPRenderBatch::WIPRenderBatch()
{

	bsort = true;
	_size = 0;
	_name = "";
}

WIPRenderBatch::~WIPRenderBatch()
{

}

void WIPRenderBatch::add_pack(WIPRenderable::_WIPRenderPack* pak)
{
#ifdef _DEBUG
	if(!pak)
		g_logger->debug_print(WIP_WARNING,"add a empty pack!");
#endif

	/*
	if(!pack->framebox||!pack->mesh||pack->z_order<0||!pack->tex_id)
		return;
	*/
	_packages.push_front(pak);
	_size++;
	CHECK(_size==_packages.size());
}

void WIPRenderBatch::delete_pack(WIPRenderable::_WIPRenderPack* pack)
{
	/*
	_PackList::iterator it;
	for(it = _packages.begin();it!=_packages.end();++it)
	{
		if((*it)==pack)
		{
			_packages.erase(it);
			_size--;
			break;
		}
	}

	CHECK(_size==_packages.size());
#ifdef _DEBUG
	if(it==_packages.end())
	{
		g_logger->debug_print(WIP_NOTE,"There is no package:%d",pack);
	}
#endif
	*/
}

void WIPRenderBatch::sort()
{
	//_packages.sort(greater<WIPRenderable::_WIPRenderPack>());
	//_packages.sort();
	_packages.sort_pointer(1);
}

void WIPRenderBatch::unpack(GLfloat* out_vertices,GLuint &tex_id,f32 vh,f32 vw)
{
	WIPRenderable::_WIPRenderPack* pack = _packages.front();

	/*
	out_vertices[0] = pack->mesh.lt.x*vw-1.f;
	out_vertices[1] = 1.f-pack->mesh.lt.y*vh;
	out_vertices[2] = 0.f;
	out_vertices[3] = pack->framebox->lt.x;
	out_vertices[4] = pack->framebox->lt.y;
	out_vertices[5] = pack->mesh.lb.x*vw-1.f;
	out_vertices[6] = 1.f-pack->mesh.lb.y*vh;
	out_vertices[7] = 0.f;
	out_vertices[8] = pack->framebox->lb.x;
	out_vertices[9] = pack->framebox->lb.y;
	out_vertices[10] = pack->mesh.rb.x*vw-1.f;
	out_vertices[11] = 1.f-pack->mesh.rb.y*vh;
	out_vertices[12] = 0.f;
	out_vertices[13] = pack->framebox->rb.x;
	out_vertices[14] = pack->framebox->rb.y;
	out_vertices[15] = pack->mesh.rt.x*vw-1.f;
	out_vertices[16] = 1.f-pack->mesh.rt.y*vh;
	out_vertices[17] = 0.f;
	out_vertices[18] = pack->framebox->rt.x;
	out_vertices[19] = pack->framebox->rt.y;
	*/

	out_vertices[0] = pack->mesh.lt.x*vw-1.f;
	out_vertices[1] = -1.f+pack->mesh.lt.y*vh;
	out_vertices[2] = 0.f;
	out_vertices[3] = pack->framebox->lt.x;
	out_vertices[4] = pack->framebox->lt.y;
	out_vertices[5] = pack->mesh.lb.x*vw-1.f;
	out_vertices[6] = -1.f+pack->mesh.lb.y*vh;
	out_vertices[7] = 0.f;
	out_vertices[8] = pack->framebox->lb.x;
	out_vertices[9] = pack->framebox->lb.y;
	out_vertices[10] = pack->mesh.rb.x*vw-1.f;
	out_vertices[11] = -1.f+pack->mesh.rb.y*vh;
	out_vertices[12] = 0.f;
	out_vertices[13] = pack->framebox->rb.x;
	out_vertices[14] = pack->framebox->rb.y;
	out_vertices[15] = pack->mesh.rt.x*vw-1.f;
	out_vertices[16] = -1.f+pack->mesh.rt.y*vh;
	out_vertices[17] = 0.f;
	out_vertices[18] = pack->framebox->rt.x;
	out_vertices[19] = pack->framebox->rt.y;

	tex_id = pack->tex_id;

	_packages.pop_front();
	_size--;

	CHECK(_size==_packages.size());
}

void WIPRenderBatch::clear()
{
	_packages.clear();
	bsort = false;
	_size = 0;
	CHECK(_size==_packages.size());
}

#ifdef _DEBUG
void WIPRenderBatch::pack_number_info()
{
	g_logger->debug_print(WIP_INFO,"%d",_size);
}

void WIPRenderBatch::pack_number_warning()
{
	if(_size%WARNING_NUM_LEVEL==0)
		g_logger->debug_print(WIP_WARNING,"The pak %s is already %d packages!",_name.c_str(),_size);

}

void WIPRenderBatch::set_name(const char* name)
{
	_name = name;
}
#endif