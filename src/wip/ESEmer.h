

#include "RenderQuad.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"
#include "OpenGL.h"
#include <stdlib.h>
#include "stdio.h"
#include "vmath.h"
#include "InputManager.h"
#include "Input.h"

/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8


/*
#ifndef __APPLE__
#pragma pack(pop,x1)
#endif
*/
#ifndef __APPLE__

///
// GetContextRenderableType()
//
//    Check whether EGL_KHR_create_context extension is supported.  If so,
//    return EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT
//
EGLint GetContextRenderableType ( EGLDisplay eglDisplay )
{
#ifdef EGL_KHR_create_context
	const char *extensions = eglQueryString ( eglDisplay, EGL_EXTENSIONS );

	// check whether EGL_KHR_create_context is in the extension string
	if ( extensions != NULL && strstr( extensions, "EGL_KHR_create_context" ) )
	{
		// extension is supported
		return EGL_OPENGL_ES3_BIT_KHR;
	}
#endif
	// extension is not supported
	return EGL_OPENGL_ES2_BIT;
}
#endif

int Init ( ESContext *esContext );
void Draw ( ESContext *esContext );

int window_x,window_y;
LRESULT WINAPI ESWindowProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT  lRet = 1;

	switch ( uMsg )
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		{

			ESContext *esContext = ( ESContext * ) ( LONG_PTR ) GetWindowLongPtr ( hWnd, GWL_USERDATA );





			ValidateRect ( esContext->eglNativeWindow, NULL );

		}
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			int bits = g_input_manager->get_last_key_info()->key_bit;
			int bits_c = g_input_manager->get_last_key_info()[1].key_bit;
			switch (wParam)
			{
			case VK_F1:
				bits |= WIP_F1;break;
			case VK_F2:
				bits |= WIP_F2;break;
			case VK_F3:
				bits |= WIP_F3;break;
			case VK_F4:
				bits |= WIP_F4;break;
			case VK_F5:
				bits |= WIP_F5;break;
			case VK_F6:
				bits |= WIP_F6;break;
			case VK_F7:
				bits |= WIP_F7;break;
			case VK_F8:
				bits |= WIP_F8;break;
			case VK_F9:
				bits |= WIP_F9;break;
			case VK_F10:
				bits |= WIP_F10;break;
			case VK_F11:
				bits |= WIP_F11;break;
			case VK_F12:
				bits |= WIP_F12;break;
			case VK_ESCAPE:
				bits |= WIP_ESC;break;
			case VK_BACK:
				bits |= WIP_BACKSPACE;break;
			case VK_RETURN:
				bits |= WIP_ENTER;break;
			case VK_RSHIFT:
				bits |= WIP_RSHIFT;break;
			case VK_LSHIFT:
				bits |= WIP_LSHIFT;break;
			case VK_LCONTROL:
				bits |= WIP_LCTRL;break;
			case VK_RCONTROL:
				bits |= WIP_RCTRL;break;
			case VK_LMENU:
				bits |= WIP_LALT;break;
			case VK_RMENU:
				bits |= WIP_RALT;break;
			case VK_TAB:
				bits |= WIP_TAB;break;
			case VK_UP:
				bits |= WIP_UP;break;
			case VK_DOWN:
				bits |= WIP_DOWN;break;
			case VK_LEFT:
				bits |= WIP_LEFT;break;
			case VK_RIGHT:
				bits |= WIP_RIGHT;break;
			case VK_SPACE:
				bits |= WIP_SPACE;break;

			case 65:
				bits_c |= WIP_A;break;
			case 66:
				bits_c |= WIP_B;break;
			case 67:
				bits_c |= WIP_C;break;
			case 68:
				bits_c |= WIP_D;break;
			case 69:
				bits_c |= WIP_E;break;
			case 70:
				bits_c |= WIP_F;break;
			case 71:bits_c |= WIP_G;break;
			case 72:bits_c |= WIP_H;break;
			case 73:bits_c |= WIP_I;break;
			case 74:bits_c |= WIP_J;break;
			case 75:bits_c |= WIP_K;break;
			case 76:bits_c |= WIP_L;break;
			case 77:bits_c |= WIP_M;break;
			case 78:bits_c |= WIP_N;break;
			case 79:bits_c |= WIP_O;break;
			case 80:bits_c |= WIP_P;break;
			case 81:bits_c |= WIP_Q;break;
			case 82:bits_c |= WIP_R;break;
			case 83:bits_c |= WIP_S;break;
			case 84:bits_c |= WIP_T;break;
			case 85:bits_c |= WIP_U;break;
			case 86:bits_c |= WIP_V;break;
			case 87:bits_c |= WIP_W;break;
			case 88:bits_c |= WIP_X;break;
			case 89:bits_c |= WIP_Y;break;
			case 90:bits_c |= WIP_Z;break;

			case VK_LBUTTON:
				bits_c |= WIP_MOUSE_LBUTTON;break;
			case VK_RBUTTON:
				bits_c |= WIP_MOUSE_RBUTTON;break;
			case VK_MBUTTON:
				bits_c |= WIP_MOUSE_MBUTTON;break;
			default:
				break;
			}
			g_input_manager->update(bits_c,bits);
			break;
		}
	case WM_KEYUP:
	case WM_SYSKEYUP:
		{
			int bits_c = g_input_manager->get_last_key_info()[1].key_bit;
			int bits = g_input_manager->get_last_key_info()->key_bit;
			switch (wParam)
			{
			case VK_F1:
				bits &= ~WIP_F1;break;
			case VK_F2:
				bits &= ~WIP_F2;break;
			case VK_F3:
				bits &= ~WIP_F3;break;
			case VK_F4:
				bits &= ~WIP_F4;break;
			case VK_F5:
				bits &= ~WIP_F5;break;
			case VK_F6:
				bits &= ~WIP_F6;break;
			case VK_F7:
				bits &= ~WIP_F7;break;
			case VK_F8:
				bits &= ~WIP_F8;break;
			case VK_F9:
				bits &= ~WIP_F9;break;
			case VK_F10:
				bits &= ~WIP_F10;break;
			case VK_F11:
				bits &= ~WIP_F11;break;
			case VK_F12:
				bits &= ~WIP_F12;break;
			case VK_ESCAPE:
				bits &= ~WIP_ESC;break;
			case VK_BACK:
				bits &= ~WIP_BACKSPACE;break;
			case VK_RETURN:
				bits &= ~WIP_ENTER;break;
			case VK_RSHIFT:
				bits &= ~WIP_RSHIFT;break;
			case VK_LSHIFT:
				bits &= ~WIP_LSHIFT;break;
			case VK_LCONTROL:
				bits &= ~WIP_LCTRL;break;
			case VK_RCONTROL:
				bits &= ~WIP_RCTRL;break;
			case VK_LMENU:
				bits &= ~WIP_LALT;break;
			case VK_RMENU:
				bits &= ~WIP_RALT;break;
			case VK_TAB:
				bits &= ~WIP_TAB;break;
			case VK_UP:
				bits &= ~WIP_UP;break;
			case VK_DOWN:
				bits &= ~WIP_DOWN;break;
			case VK_LEFT:
				bits &= ~WIP_LEFT;break;
			case VK_RIGHT:
				bits &= ~WIP_RIGHT;break;
			case VK_SPACE:
				bits &= ~WIP_SPACE;break;

			case 65:
				bits_c &= ~WIP_A;break;
			case 66:
				bits_c &= ~WIP_B;break;
			case 67:
				bits_c &= ~WIP_C;break;
			case 68:
				bits_c &= ~WIP_D;break;
			case 69:
				bits_c &= ~WIP_E;break;
			case 70:
				bits_c &= ~WIP_F;break;
			case 71:bits_c &= ~WIP_G;break;
			case 72:bits_c &= ~WIP_H;break;
			case 73:bits_c &= ~WIP_I;break;
			case 74:bits_c &= ~WIP_J;break;
			case 75:bits_c &= ~WIP_K;break;
			case 76:bits_c &= ~WIP_L;break;
			case 77:bits_c &= ~WIP_M;break;
			case 78:bits_c &= ~WIP_N;break;
			case 79:bits_c &= ~WIP_O;break;
			case 80:bits_c &= ~WIP_P;break;
			case 81:bits_c &= ~WIP_Q;break;
			case 82:bits_c &= ~WIP_R;break;
			case 83:bits_c &= ~WIP_S;break;
			case 84:bits_c &= ~WIP_T;break;
			case 85:bits_c &= ~WIP_U;break;
			case 86:bits_c &= ~WIP_V;break;
			case 87:bits_c &= ~WIP_W;break;
			case 88:bits_c &= ~WIP_X;break;
			case 89:bits_c &= ~WIP_Y;break;
			case 90:bits_c &= ~WIP_Z;break;



			case VK_LBUTTON:
				bits_c &= ~WIP_MOUSE_LBUTTON;break;
			case VK_RBUTTON:
				bits_c &= ~WIP_MOUSE_RBUTTON;break;
			case VK_MBUTTON:
				bits_c &= ~WIP_MOUSE_MBUTTON;break;
			default:
				break;
			}
			g_input_manager->update(bits_c,bits);

			break;

		}
	case WM_MOUSEMOVE:
		{
			//if there are so many message of key pressing,this will be blocked.
			//g_input_manager->update_mouse((int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam));

		}
		break;

	case WM_DESTROY:
		PostQuitMessage ( 0 );
		break;
		//case WM_WINDOWPOSCHANGED:
		//{
		//	WINDOWPOS* pos = (WINDOWPOS*)lParam;

		//window_x = pos->x;
		//window_y = pos->y;

		//	}
		//	break;
	case WM_MOVE:
		window_x = (int)(short)LOWORD(lParam);
		window_y = (int)(short)HIWORD(lParam);
		break;
	case WM_CHAR:
		{
			POINT      point;
			ESContext *esContext = ( ESContext * ) ( LONG_PTR ) GetWindowLongPtr ( hWnd, GWL_USERDATA );

			GetCursorPos ( &point );
			//g_input_manager->update_mouse((int)point.x,(int)point.y);
			if ( esContext && esContext->keyFunc )
				esContext->keyFunc ( esContext, ( unsigned char ) wParam,
				( int ) point.x, ( int ) point.y );
		}
		break;

	default:
		lRet = DefWindowProc ( hWnd, uMsg, wParam, lParam );
		break;
	}

	return lRet;
}


GLboolean WinCreate ( ESContext *esContext, const char *title )
{
	WNDCLASS wndclass = {0};
	DWORD    wStyle   = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle ( NULL );


	wndclass.style         = CS_OWNDC;
	wndclass.lpfnWndProc   = ( WNDPROC ) ESWindowProc;
	wndclass.hInstance     = hInstance;
	wndclass.hbrBackground = ( HBRUSH ) GetStockObject ( BLACK_BRUSH );
	wndclass.lpszClassName = "opengles3.0";

	if ( !RegisterClass ( &wndclass ) )
	{
		return FALSE;
	}

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = esContext->width;
	windowRect.bottom = esContext->height;

	AdjustWindowRect ( &windowRect, wStyle, FALSE );



	esContext->eglNativeWindow = CreateWindow (
		"opengles3.0",
		title,
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL );

	// Set the ESContext* to the GWL_USERDATA so that it is available to the
	// ESWindowProc
	SetWindowLongPtr (  esContext->eglNativeWindow, GWL_USERDATA, ( LONG ) ( LONG_PTR ) esContext );


	if ( esContext->eglNativeWindow == NULL )
	{
		return GL_FALSE;
	}

	ShowWindow ( esContext->eglNativeWindow, TRUE );

	return GL_TRUE;
}

void WinLoop ( ESContext *esContext )
{



	MSG msg = { 0 };
	int done = 0;





	while ( !done )
	{

		//clock->update();
		int gotMsg = ( PeekMessage ( &msg, NULL, 0, 0, PM_REMOVE ) != 0 );

		//float deltaTime = ( float ) ( curTime - lastTime ) / 1000.0f;


		if ( gotMsg )
		{
			if ( msg.message == WM_QUIT )
			{
				done = 1;
			}
			else
			{
				TranslateMessage ( &msg );
				DispatchMessage ( &msg );
			}
		}
		else
		{

			//SendMessage ( esContext->eglNativeWindow, WM_PAINT, 0, 0 );
		}

		//update here to make mouse right but it is screen x,y
		POINT point;
		GetCursorPos ( &point );
		g_input_manager->update_mouse((int)(short)point.x - window_x,(int)(short)point.y - window_y);


		Draw(esContext);
		eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );

		g_input_manager->clear_states();




	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include "ft3.h"
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


	g_FreeTypeLib.load("../Resources/simkai.ttf",24,24);

	return TRUE;
}



void Draw ( ESContext *esContext )
{
	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);

	glViewport(0,0,esContext->width,esContext->height);
	glClearColor(1.0,0.0,0.0,0.2);
	glClear(GL_COLOR_BUFFER_BIT);//|GL_DEPTH_BUFFER_BIT);
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

	//drawText(L"先诛", 50, esContext->height-50, 900,10);
	glBindFramebuffer(GL_FRAMEBUFFER,0);





	glViewport(0, 0, esContext->width, esContext->height);
	glClearColor(0.85,0.85,0.85,1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearBufferfv(GL_COLOR, 0, green);

	g_renderer->render(texturel,Input::get_mouse_x(),Input::get_mouse_y(),800,600);
	//g_renderer->draw_point(50,50);
	drawText(L"a", 50,50, 900,10);
	drawText(L"先诛少林再灭武当，宝刀屠龙唯我独尊，哈哈哈哈哈答复我发\n1234567890\nqwertyuiop[]asdfghjkl;'zxcvbnm,./\nQAZWSXEDCRFVTGBYHNUJMIK,LOP;\"\\:?<>", 50, esContext->height-50, 900,10);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


ESContext* _es_context;
int main()
{
	_es_context = new ESContext();
	memset ( _es_context, 0, sizeof ( ESContext ) );

	int width = 800;
	int height = 600;
	const char* title = "I am your father!";
	GLuint flags = ES_WINDOW_RGB|ES_WINDOW_ALPHA ;
	//create window
#ifndef __APPLE__

	EGLConfig config;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

	if ( _es_context == NULL )
	{
		printf("_es_context:NULL\n");
		getchar();
	}

#ifdef ANDROID
	// For Android, get the width/height from the window rather than what the
	// application requested.
	_es_context->width = ANativeWindow_getWidth ( _es_context->eglNativeWindow );
	_es_context->height = ANativeWindow_getHeight ( _es_context->eglNativeWindow );

#else

	_es_context->width = width;
	_es_context->height = height;
#endif

	if ( !WinCreate ( _es_context, title ) )
	{
		printf("Win32 window failed!\n");
		getchar();
	}

	_es_context->eglDisplay = eglGetDisplay( _es_context->eglNativeDisplay );
	if ( _es_context->eglDisplay == EGL_NO_DISPLAY )
	{
		printf("_es_context->eglDisplay == EGL_NO_DISPLAY \n");
		getchar();
	}

	// Initialize EGL
	if ( !eglInitialize ( _es_context->eglDisplay, &majorVersion, &minorVersion ) )
	{
		printf("eglInitialize failed!\n");
		getchar();
	}

	{
		EGLint numConfigs = 0;
		EGLint attribList[] =
		{
			EGL_RED_SIZE,       5,
			EGL_GREEN_SIZE,     6,
			EGL_BLUE_SIZE,      5,
			EGL_ALPHA_SIZE,     ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
			EGL_DEPTH_SIZE,     ( flags & ES_WINDOW_DEPTH ) ? 8 : EGL_DONT_CARE,
			EGL_STENCIL_SIZE,   ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
			// if EGL_KHR_create_context extension is supported, then we will use
			// EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
			EGL_RENDERABLE_TYPE, GetContextRenderableType ( _es_context->eglDisplay ),
			EGL_NONE
		};

		// Choose config
		if ( !eglChooseConfig ( _es_context->eglDisplay, attribList, &config, 1, &numConfigs ) )
		{
			printf("eglChooseConfig failed!\n");
			getchar();
		}

		if ( numConfigs < 1 )
		{
			printf("numConfigs < 1 \n");
			getchar();
		}
	}


#ifdef ANDROID
	// For Android, need to get the EGL_NATIVE_VISUAL_ID and set it using ANativeWindow_setBuffersGeometry
	{
		EGLint format = 0;
		eglGetConfigAttrib ( _es_context->eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format );
		ANativeWindow_setBuffersGeometry ( _es_context->eglNativeWindow, 0, 0, format );
	}
#endif // ANDROID

	// Create a surface
	_es_context->eglSurface = eglCreateWindowSurface ( _es_context->eglDisplay, config, 
		_es_context->eglNativeWindow, NULL );

	if ( _es_context->eglSurface == EGL_NO_SURFACE )
	{
		printf("EGL_NO_SURFACE\n");
		getchar();
	}

	// Create a GL context
	_es_context->eglContext = eglCreateContext ( _es_context->eglDisplay, config, 
		EGL_NO_CONTEXT, contextAttribs );

	if ( _es_context->eglContext == EGL_NO_CONTEXT )
	{
		printf("EGL_NO_CONTEXT\n");
		getchar();
	}


	// Make the context current
	if ( !eglMakeCurrent ( _es_context->eglDisplay, _es_context->eglSurface, 
		_es_context->eglSurface, _es_context->eglContext ) )
	{
		printf("eglMakeCurrent failed!\n");
		getchar();
	}


#endif // #ifndef __APPLE__

	if (!Init(_es_context))
	{
		printf("Custom init failed!\n");
		getchar();
	}
	WinLoop(_es_context);

	return 0;
}