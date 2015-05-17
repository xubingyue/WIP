#include "RenderTexture.h"
#include "Assertion.h"
#include "AppManager.h"
#include "Renderer.h"


i32 WIPRenderTexture::_total = 0;

WIPRenderTexture*
	WIPRenderTexture::create(i32 w,i32 h,uint type/*=GL_UNSIGNED_BYTE*/,uint format/*=GL_RGBA*/,uint internal_format/*=GL_RGBA*/)
{
	_total++;
	return new WIPRenderTexture(w,h,type,format,internal_format);


}

WIPRenderTexture::WIPRenderTexture(i32 w,i32 h,uint type,uint format,uint internal_format)
{
	_gl_internalformat = internal_format;
	_gl_format = format;
	_gl_type = type;
	_width = w;
	_height = h;
	generate_texture();
}

void WIPRenderTexture::begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER,_frame_buffer);
	glViewport(0,0,_width,_height);
	glClearColor(1.0,0.0,0.0,0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	
	//prepare matrix
	/*
	f32 m[] = {1.f,0.f,0.f,0.f,0.f,-1.f,g_app_manager->get_window_height(),0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f};
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m);
	*/
	g_renderer->reset_iv_h(_height);
	g_renderer->reset_iv_w(_width);
}

void WIPRenderTexture::end()
{
	g_renderer->reset_iv_h(g_app_manager->get_window_height());
	g_renderer->reset_iv_w(g_app_manager->get_window_width());
	//pop gl matrix
	//glPopMatrix();
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void WIPRenderTexture::set_data(void* data,int w,int h)
{
	_width = w;
	_height = h;
	glDeleteTextures(1,&tex_id);
	glDeleteFramebuffers(1,&_frame_buffer);
	generate_texture(data);

}

void WIPRenderTexture::generate_texture(void *data)
{
	glGenFramebuffers(1,&_frame_buffer);
	glGenTextures(1,&tex_id);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glTexImage2D(GL_TEXTURE_2D,0,_gl_internalformat,_width,_height,0,_gl_format,_gl_type,data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindFramebuffer(GL_FRAMEBUFFER,_frame_buffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex_id,0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

WIPRenderTexture::~WIPRenderTexture()
{

	_total--;
	CHECK(_total>=0);
	glDeleteTextures(1,&tex_id);
	glDeleteFramebuffers(1,&_frame_buffer);
}

void WIPRenderTexture::resize(i32 w,i32 h)
{
	_width = w;
	_height = h;
	glDeleteTextures(1,&tex_id);
	glDeleteFramebuffers(1,&_frame_buffer);

	generate_texture();
}