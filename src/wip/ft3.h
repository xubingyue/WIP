#pragma once
#include "RenderQuad.h"
#include "windows.h"
#include "OpenGL.h"

//#include "gl\glu.h"
#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include "Utilities\WPMap.h"
#include "ResourceManager.h"

#include "Renderer.h"

extern int zga;
extern int zzg ;
extern int n;

int get_by_power_2(int i);

#define MAX_NO_TEXTURES 1
#define CUBE_TEXTURE 0

struct xCharTexture
{
	GLuint  m_texID;
	wchar_t m_chaID;
	int     m_Width;
	int     m_Height;
	int     m_adv_x;
	int     m_adv_y;
	int     m_delta_x;
	int     m_delta_y;
public:
	xCharTexture()
	{
		m_texID  = 0;
		m_chaID  = 0;
		m_Width  = 0;
		m_Height = 0;
	}
} ;
typedef Hash_Map<wchar_t,xCharTexture*> TextMap;
extern TextMap text_map;
class xFreeTypeLib
{
	FT_Library m_FT2Lib;
	FT_Face    m_FT_Face;
public:
	int   m_w;
	int   m_h;
	void load(const char* font_file , int _w , int _h);
	GLuint loadChar(wchar_t ch);
	void free()
	{
		FT_Done_Face(m_FT_Face);
		FT_Done_FreeType(m_FT2Lib);
	}
};



extern xFreeTypeLib g_FreeTypeLib;
extern float ratio;
xCharTexture* getTextChar(wchar_t ch);
void AnsiToUnicode(LPCSTR lpcstr,LPWSTR outstr) ;  //参数lpcstr类型也可是char*

//wchar_t g_UnicodeString[]=L"aaabb\x4E2D\x6587\x0031\x0032\x0033";  


void drawText(wchar_t* _strText,int x , int y, int maxW , int h,bool isfbo);