#include "user.h"
#include "RenderQuad.h"
#include <stdlib.h>
#include <stdio.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"
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
#include "OggStream.h"
#include "Sound.h"
#include "SoundPlayer.h"
#include "RenderTexture.h"
#include "AppManager.h"
#include "Input.h"
//////////////////////////////////////////////////////////////////////////
#include "TextCanvas.h"
#include "Utilities/Utilities.h"
#include "gpu_fft.h"
//#include "boxman.h"

WIPTexture* tex,*tex1;
WIPSound* sound;

WIPTextCanvas *text_canvas;
WIPTextCanvas *cav;
WIPRenderTexture* rt;
OggStream steam;
//////////////////////////////////////////////////////////////////////////
//此处定义摄像机变量
//////////////////////////////////////////////////////////////////////////
float fovy = 50;
float near_clip = 0.1f;
float far_clip = 1000.f;
float tx = 0.f;
float ty = 0.f;
float tz = -200.f;
float ax = 0.f;
float ay = 0.f;
float az = 0.f;
float degreex = 0.f;
float degreey = 0.f;
float degreez = 0.f;

float transform_speed_x = 1.0f;
float transform_speed_y = 1.0f;
//////////////////////////////////////////////////////////////////////////
/*
		y
		^
		|    
		|   
		|  
		|  
		|_____________>x
	   /
	  /
	 /
	V
	z
	注意：vmath数学库的矩阵请左乘。
*/
vmath::mat4 gproj_matrix;
vmath::mat4 gmv_matrix;

void input()
{
		if(Input::get_key_pressed(WIP_W))
	{
		ty += transform_speed_y;
	}
	if (Input::get_key_pressed(WIP_S))
	{
		ty -= transform_speed_y;
	}
	if(Input::get_key_pressed(WIP_A))
	{
		tx -= transform_speed_x;
	}
	if(Input::get_key_pressed(WIP_D))
	{
		tx += transform_speed_x;
	}
	if (Input::get_sys_key_pressed(WIP_MOUSE_SCROLLER_DOWN))
	{
		tz -= 5.f; 
	}
	if (Input::get_sys_key_pressed(WIP_MOUSE_SCROLLER_UP))
	{
		tz += 5.f;
	}
	if(Input::get_key_pressed(WIP_J))
	{

		degreex += 2.f;
	}


	if(Input::get_key_pressed(WIP_K))
	{

		degreey += 2.f;
	}
	if(Input::get_key_pressed(WIP_I))
	{
		degreez += 2.f;
	}
	if(Input::get_key_pressed(WIP_U))
	{

		degreex -= 2.f;
	}

	if(Input::get_key_pressed(WIP_I))
	{
		
		degreey -= 2.f;
	}
	if(Input::get_key_pressed(WIP_O))
	{

		degreez -= 2.f;
	}
}

int Init ( ESContext *esContext )
{
	g_FreeTypeLib.load("engine/simkai.ttf",24,24);
	text_canvas = new WIPTextCanvas(-1,-1);
	cav = new WIPTextCanvas(-1,-1);
	//	g_sound_palyer->startup();
	//steam.open("../Resources/test.ogg");
	//steam.play(true);
	//sound = new WIPSound("../Resources/test.ogg",WIP_BGM);
	//g_sound_palyer->play(sound,100);
	rt = WIPRenderTexture::create(esContext->width,esContext->height);

	init();
	return 1;
}

void Draw ( ESContext *esContext,double dt )
{
	input();
	glViewport(0, 0, g_app_manager->get_window_width(), g_app_manager->get_window_height());
	gproj_matrix = vmath::perspective
		(
		fovy,
		(float)g_app_manager->get_window_width() / (float)g_app_manager->get_window_height(),
		near_clip,
		far_clip
		);
	static int i = -200;
	float f = 0.3f;
	gmv_matrix = 
		vmath::translate(tx, ty, tz) *
		vmath::rotate(degreex, 1.f, 0.f, 0.f)*
		vmath::rotate(degreey, 0.f, 1.f, 0.f)*
		vmath::rotate(degreez,0.f, 0.f, 1.f);


	update();
	draw(gmv_matrix,gproj_matrix);

	char s[20];
	sprintf_s(s,"%0.3f ",dt);
	cav->draw_text(s,55,-10);
	cav->update();
	cav->draw_buffer(0,0,esContext->width,esContext->height);
}

