#pragma once
#include "OpenGL.h"
#include <cstring>
#include <list>
#include "Renderable.h"
#include "LinkList.h"


/*
TODO:
This class is used to cache all the things need be rendered and
will render them in total at the end of the main loop
*/
extern const i32 WARNING_NUM_LEVEL;

class WIPMesh;
class WIPFrameBox;
class Renderer;


class WIPRenderBatch
{
public:

	WIPRenderBatch();
	~WIPRenderBatch();
	uint _size;
	void add_pack(WIPRenderable::_WIPRenderPack* pak);
	void delete_pack(WIPRenderable::_WIPRenderPack* pack);
	//sort only when we need
	void sort();
	void unpack(f32* out_vertices,GLuint &tex_id,f32 vh,f32 vw);
	bool bsort;
	void clear();

#ifdef _DEBUG
	//Debug
	void set_name(const char* name);
	//output the pack number
	void pack_number_info();
	void pack_number_warning();
#endif

private:
	//test
	friend Renderer;

	//typedef std::list<WIPRenderable::_WIPRenderPack*> _PackList;
	typedef LinkList<WIPRenderable::_WIPRenderPack*> _PackList;
	_PackList _packages;
	
#ifdef _DEBUG
	std::string _name;
#endif
};

