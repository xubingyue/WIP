#include "ft3.h"
#include "TextCanvas.h"
#include "Renderer.h"
#include "AppManager.h"

//NOTE:this can't be init when gl has not been set.
//TODO:Move it to init() method
WIPTextCanvas::WIPTextCanvas(int width /* = -1 */,int height /* = -1 */)
{
	
	if (width==-1||height==-1)
	{
		glfwGetWindowSize(g_app_manager->get_glfw_context()->window,&_buffer_width,&_buffer_height);
	}
	else
	{
		_buffer_width = width;
		_buffer_height = height;
	}
	glGenFramebuffers(1,&_frame_buffer);

	glGenTextures(1,&_out_buffer);
	glBindTexture(GL_TEXTURE_2D,_out_buffer);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_buffer_width,_buffer_height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER,_frame_buffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_out_buffer,0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	//g_FreeTypeLib.load("../Resources/simkai.ttf",24,24);
}

WIPTextCanvas::~WIPTextCanvas()
{
	//g_FreeTypeLib.free();
	glDeleteTextures(1,&_out_buffer);
	glDeleteFramebuffers(1,&_frame_buffer);
}

void WIPTextCanvas::draw_text(const char* text,int x,int y)
{

	WIPCanvasObject* t = new WIPCanvasObject(text,x,y);
	_object_list.push_back(t);
}

void WIPTextCanvas::draw_text(const std::string text,int x,int y)
{
	WIPCanvasObject* t = new WIPCanvasObject(text,x,y);
	_object_list.push_back(t);
}

void WIPTextCanvas::update()
{
	glBindFramebuffer(GL_FRAMEBUFFER,_frame_buffer);
	glViewport(0,0,_buffer_width,_buffer_height);
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (_ObjectList::iterator it=_object_list.begin();it!=_object_list.end();++it)
	{
		std::string s = (*it)->words;
		int len = s.size();
		wchar_t*  str = new wchar_t[len+1];
		AnsiToUnicode(s.c_str(),str);
		drawText(str, (*it)->x, (*it)->y, _buffer_width,10,true);
		delete []str;
		//delete object one by one
		delete (*it);
	}

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	//Finished just delete all
	_object_list.clear();
}

void WIPTextCanvas::draw_buffer(int x,int y,int w,int h)
{
	g_renderer->render(_out_buffer,x,y,w,h);
}