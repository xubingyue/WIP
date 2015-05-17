#pragma once
#include "OpenGL.h"
#include "BaseTexture.h"
#include "ResourceManager.h"

struct WIPQuad
{
	int width,height;
	WIPQuad()
	{
		memset(this,0,sizeof(WIPQuad));
	}
	//control memory by MemoryPools.
};

//Read-only texture
class WIPTexture :public WIPBaseTexture
{
public:
	WIPTexture(const char* file_path,int width = -1,int height = -1);
	//create a empty texture,not use,because the empty texture is always NOT a read-only texture.reference to RenderTexture
	WIPTexture(int width,int height);
	//with data defualt float
	WIPTexture(void *data,int width,int height,int format = GL_FLOAT);
	~WIPTexture();


	inline int get_width()
	{
		return _quad->width;
	}

	inline int get_height()
	{
		return _quad->height;
	}

	inline WIPQuad* get_quad()
	{
		return _quad;
	}

	inline GLuint get_texture_id()
	{
		return tex_id;
	}
	inline ResHandler* get_resource_reference()
	{
		return _handler;
	}

protected:

private:
	bool load_source(const char* file_path);
	void free_source();
	//generate texture and get the id
	bool generate_texture(void* data = 0);
	//useless
	void release_texture();
	GLint _gl_internalformat; 
	GLenum _gl_format;
	GLenum _gl_type;
	ResHandler* _handler;
	WIPQuad *_quad;
	static WIPResourceManager* _manager;
};