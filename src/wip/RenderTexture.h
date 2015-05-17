#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "OpenGL.h"
#include "BaseTexture.h"

class WIPRenderTexture:public WIPBaseTexture
{
public:
	
	static WIPRenderTexture* create(i32 w,i32 h,uint type=GL_UNSIGNED_BYTE,uint format=GL_RGBA,uint internal_format=GL_RGBA);

	void set_data(void* data,int w,int h);

	void begin();
	void end();

	INLINE i32 get_width()
	{
		return _width;
	}

	INLINE i32 get_height()
	{
		return _height;
	}
	INLINE GLuint get_texture_id()
	{
		return tex_id;
	}
	INLINE void clear()
	{
		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void resize(i32 w,i32 h);
	~WIPRenderTexture();
protected:
	WIPRenderTexture(i32 w,i32 h,uint type,uint format,uint internal_format);
private:
	i32 _width,_height;
	void generate_texture(void* data=0);
	//GLuint _tex_id;
	GLint _gl_internalformat; 
	GLenum _gl_format;
	GLenum _gl_type;
	GLuint _frame_buffer;

	static i32 _total;
};