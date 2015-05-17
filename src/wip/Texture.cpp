#include "Texture.h"
#include "TextManager.h"
//#include "MemoryleakDec.h"

WIPResourceManager* WIPTexture::_manager = g_res_manager;

WIPTexture::WIPTexture(const char* file_path,int width/*=-1*/,int height/*=-1*/)
{
	_gl_internalformat = GL_RGBA;
	_gl_format = GL_RGBA;
	_gl_type = GL_UNSIGNED_BYTE;
	tex_id = 0;
	_handler = NULL;
	_quad = new WIPQuad();
	//can't return!
	load_source(file_path);
	_quad->width = width;
	_quad->height = height;
	if (-1==width)
	{
		_quad->width = ((TextureData*)_handler->extra)->width;
	}
	if(-1==height)
	{
		_quad->height = ((TextureData*)_handler->extra)->height;
	}

}

WIPTexture::WIPTexture(void *data,int width,int height,int format /*= GL_FLOAT*/)
{
	_gl_internalformat = GL_RGBA16F;
	_gl_format = GL_RGBA;
	_gl_type = format;
	tex_id = 0;
	_handler = NULL;
	_quad = new WIPQuad();
	_quad->width = width;
	_quad->height = height;
	generate_texture(data);
}

WIPTexture::WIPTexture(int width,int height)
{
	printf("This constructor is not used.Create texture failed!\n");
	getchar();
	exit(0);

}


WIPTexture::~WIPTexture()
{
	free_source();
	delete _quad;
}

bool WIPTexture::load_source(const char* file_path)
{
	_handler = _manager->load_resource(file_path,TEXTURE);
	if(!_handler)
		return false;
	generate_texture();
	return true;
}


void WIPTexture::free_source()
{
	g_texture_manager->delete_texture(_handler);
	
	/*
	release_texture();
	_manager->free(_handler,_handler->size);
	*/
	

}

bool WIPTexture::generate_texture(void* data)
{
	
	/*
	if (!_handler->ptr)
	{
		return false;
	}
	glGenTextures ( 1, &_gl_texid );
	glBindTexture ( GL_TEXTURE_2D, _gl_texid );

	glTexImage2D ( GL_TEXTURE_2D, 0, _gl_internalformat,
		((TextureData*)(_handler->extra))->width, ((TextureData*)(_handler->extra))->height, 
		0, _gl_format , _gl_type, _handler->ptr);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	*/
	
	
	GLuint ret = 0; 
	if(data)
		ret = g_texture_manager->generate_texture(data,_quad->width,_quad->height, _gl_internalformat,_gl_format,_gl_type);
	else
		ret = g_texture_manager->generate_texture(_handler,_gl_internalformat,_gl_format,_gl_type);
	if (0==ret)
	{
		return false;
	}
	tex_id = ret;
	
	
	return true;
	
}

//useless
void WIPTexture::release_texture()
{
	//glDeleteTextures(1,&_gl_texid);
}