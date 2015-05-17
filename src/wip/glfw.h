#include "Opengl.h"
#include "RenderQuad.h"
#include <stdlib.h>
#include <stdio.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"
#include "OpenGL.h"
#include <stdlib.h>
#include "stdio.h"
#include "vmath.h"
#include "InputManager.h"
#include "Input.h"
#include "ft3.h"
#include "Win32TimeSource.h"
#include "Clock.h"
#include "Timer.h"
#include "callbacks.h"

//////////////////////////////////////////////////////////////////////////
#include "TextCanvas.h"
WIPTexture* tex,*tex1;



GLuint          program1;
GLuint          program2;
GLuint          vao;
GLuint          position_buffer;
GLuint          index_buffer;
GLuint          fbo;
GLuint          color_texture;
GLuint          depth_texture;
GLint           mv_location;
GLint           proj_location;
GLuint          mv_location2;
GLuint          proj_location2;
GLuint fs,vs;

GLuint framebuffer,framebuffer1,texturel;
GLuint renderbuffer[2],depthbuffer;

WIPTextCanvas *text_canvas;
WIPTextCanvas *cav;
int Init ( ESContext *esContext )
{
	if(!g_res_manager->startup())
	{
		printf("ResManager failed!\n");
		getchar();
	}
	if(!g_renderer->startup(esContext))
	{
		printf("create shader failed!\n");
		getchar();
		exit(0);
	}
	g_input_manager->startup("");
	tex = new WIPTexture("../Resources/2.jpg",640,640);
	tex1 = new WIPTexture("../Resources/2.png",-1,-1);

	glGenFramebuffers(1,&framebuffer);

	glGenTextures(1,&texturel);
	glBindTexture(GL_TEXTURE_2D,texturel);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,esContext->width,esContext->height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texturel,0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);


	g_FreeTypeLib.load("../Resources/simkai.ttf",12,12);
	text_canvas = new WIPTextCanvas(-1,-1);
	cav = new WIPTextCanvas(-1,-1);
	return 0;
}

void Draw ( ESContext *esContext )
{
	/*
	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
	ratio = esContext->width / (float) esContext->height;
	
	glViewport(0,0,esContext->width,esContext->height);
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);//|GL_DEPTH_BUFFER_BIT);
	//glOrtho(ratio, -ratio, 1.f, 1.f,1.0f,-1.0f);
	//We need translate the y from left top to left button.
	int x = 0;
	int y = 0;
	int width = 80;
	int height = 60;
	int rheight = -height;
	int ry = esContext->height - y;
	g_renderer->render(tex->get_texture_id(),x,ry,width,rheight);
	g_renderer->render(tex1->get_texture_id(),100,100,200,200);
	//g_renderer->render(tex,0,0);

	//drawText(L"先诛", 50, esContext->height-50, 900,10,false);
	//drawText(L"先诛少林再灭武当，宝刀屠龙唯我独尊，哈哈哈哈哈答复我发\n1234567890\nqwertyuiop[]asdfghjkl;'zxcvbnm,./\nQAZWSXEDCRFVTGBYHNUJMIK,LOP;\"\\:?<>", 50, esContext->height-50, 900,10,true);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	*/




	glViewport(0, 0, esContext->width, esContext->height);
	glClearColor(0.85,0.85,0.85,1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearBufferfv(GL_COLOR, 0, green);

	static bool first = true;
	if (first)
	{
		text_canvas->draw_text("hddasdsjdaodj酵素分解\nsda1242",23,23);
		text_canvas->update();
		first = !first;
	}
	//printf("%d\n",g_input_manager->get_last_key_info()[1].key_bit);
	if (Input::get_sys_key_down(WIP_MOUSE_LBUTTON))
	{
		printf("L pressed\n");
	}
	if (Input::get_sys_key_pressed(WIP_MOUSE_LBUTTON))
	{
		text_canvas->draw_text("我长大了要娶韩小野",Input::get_mouse_x(),Input::get_mouse_y());
		text_canvas->update();
	}
	
	if (Input::get_sys_key_pressed(WIP_MOUSE_LBUTTON))
	{
		printf("L pressing\n");
	}
	if(Input::get_sys_key_up(WIP_MOUSE_LBUTTON))
	{
		printf("L up\n");
	}
	if (Input::get_sys_key_down(WIP_MOUSE_RBUTTON))
	{
		printf("R pressed\n");
	}
	if (Input::get_sys_key_pressed(WIP_MOUSE_RBUTTON))
	{
		printf("R pressing\n");
		
	}
	if(Input::get_sys_key_up(WIP_MOUSE_RBUTTON))
	{
		printf("R up\n");
	}
	if (Input::get_sys_key_down(WIP_MOUSE_RBUTTON))
	{
		text_canvas->update();
	}
	if (Input::get_sys_key_down(WIP_MOUSE_MBUTTON))
	{
		printf("M pressed\n");
	}
	if (Input::get_sys_key_pressed(WIP_MOUSE_MBUTTON))
	{
		printf("M pressing\n");

	}
	if(Input::get_sys_key_up(WIP_MOUSE_MBUTTON))
	{
		printf("M up\n");
	}
	
	//printf("%d\n",Input::get_mouse_scroller());
	//g_renderer->render(tex,0,0);
	text_canvas->draw_buffer(0,0,800,600);
	
			
	//g_renderer->draw_point(50,50);
	//drawText(L"a", 50,50, 900,10,false);
	//drawText(L"先诛少林再灭武当，宝刀屠龙唯我独尊，哈哈哈哈哈答复我发\n1234567890\nqwertyuiop[]asdfghjkl;'zxcvbnm,./\nQAZWSXEDCRFVTGBYHNUJMIK,LOP;\"\\:?<>", 50, esContext->height-50, 900,10,false);
}

int main(void)
{

	glfwSetErrorCallback(glfw_error_callback);
	GLFWContext context;
	init_gl(&context.window);

	glfwSetCursorPosCallback(context.window,glfw_mouse_pos_callback);
	glfwSetMouseButtonCallback(context.window,glfw_mouse_button_callback);
	glfwSetKeyCallback(context.window,glfw_key_callback);
	glfwSetScrollCallback(context.window,glfw_scroll_callback);
	//just for convinience
	ESContext escontext;
	glfwGetWindowSize(context.window,&escontext.width,&escontext.height);


	Init(&escontext);

	
	Win32TimeSource times;
	RBClock::init(&times);
	RBClock* clock = RBClock::Instance();
	RBTimerBase timer(*clock);
	clock->set_filtering(10,0.1666666666666f);

	double lastTime = timer.get_time();
	clock->update();
	while (!glfwWindowShouldClose(context.window))
	{
		//////////////////////////////////////////////////////////////////////////
		//only this order!!!!!
		{
			
			int bits = g_input_manager->get_last_key_info()->key_bit;
			int bits_c = g_input_manager->get_last_key_info()[1].key_bit;

			if(lmouse_keep_going)
			{
				bits |= WIP_MOUSE_LBUTTON;
			}
			if(rmouse_keep_going) 
				bits |= WIP_MOUSE_RBUTTON;
			if(mmouse_keep_going) 
				bits |= WIP_MOUSE_MBUTTON;
			g_input_manager->update(bits_c,bits);
			
		}

		glfwPollEvents();
		//////////////////////////////////////////////////////////////////////////
		double curTime = times.get_time();
		float frame = 0.16666666666666666;
		if(curTime-lastTime>=frame)
		{

			//draw can't be placed in it but because of the mass achitecture
			Draw(&escontext);
			

			lastTime = curTime;
			clock->update();

			char s[20];
			sprintf_s(s,"%0.3f ",clock->get_frame_rate());
			cav->draw_text(s,Input::get_mouse_x(),Input::get_mouse_y());
			cav->update();
			cav->draw_buffer(0,0,800,600);
			glfwSwapBuffers(context.window);
		}
		else
		{
			Sleep(0);
		}

		
		g_input_manager->clear_states();
		//for glfw
		g_input_manager->clear_scroller();

	}


	glfwDestroyWindow(context.window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
