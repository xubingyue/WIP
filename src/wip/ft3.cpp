#include "ft3.h"

int zga=0;
int zzg = 0;
int n = 1;
float ratio;
xCharTexture g_TexID[65535];
int get_by_power_2(int i)
{
	int s = 1;
	while (s<i)
		s<<=2;
	return s;
}
GLuint texture_id[MAX_NO_TEXTURES];
wchar_t g_UnicodeString[]=L"" ;
void xFreeTypeLib::load(const char* font_file , int _w , int _h)
{
	FT_Error e;
	FT_Library library;
	if (FT_Init_FreeType( &library) ) 
		exit(0);
	//加载一个字体,取默认的Face,一般为Regualer
	if (FT_New_Face( library, font_file, 0, &m_FT_Face )) 
		exit(0);
	e = FT_Select_Charmap(m_FT_Face, FT_ENCODING_UNICODE);
	if (e)
	{
		printf("load ttf failed!");
		exit(0);
	}
	m_w = _w ; m_h = _h;
	m_FT_Face->num_fixed_sizes;
	//大小要乘64
	//FT_Set_Char_Size( m_FT_Face , 0 , m_w << 6, 96, 96);
	e = FT_Set_Pixel_Sizes(m_FT_Face,m_w, m_h);
	if(e)
	{
		exit(0);
	}
	loadChar(97);

}

GLuint xFreeTypeLib::loadChar(wchar_t ch)
{
	/*
	TextMap::iterator it = text_map.find(ch);
	if (it!=text_map.end())
	{
		return it->second->m_texID;
	}
	*/
	
	if(g_TexID[ch].m_texID)
		return g_TexID[ch].m_texID;
		
		
	if(FT_Load_Char(m_FT_Face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT|
		(true ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO) )   )
	{
		return 0;
	}


	/*if(FT_Load_Glyph( m_FT_Face, FT_Get_Char_Index( m_FT_Face, ch ), FT_LOAD_FORCE_AUTOHINT ))
	throw std::runtime_error("FT_Load_Glyph failed");*/
	xCharTexture& charTex = g_TexID[ch];
	/*
	xCharTexture& charTex = *(new xCharTexture());//g_TexID[ch];
	text_map[ch] = &charTex;
	*/
	

	//得到字模
	FT_Glyph glyph;
	if(FT_Get_Glyph( m_FT_Face->glyph, &glyph ))
		return 0;
	//转化成位图
	FT_Render_Glyph( m_FT_Face->glyph,   FT_RENDER_MODE_LCD );//FT_RENDER_MODE_NORMAL  ); 
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	//取道位图数据
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	//把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。
	int width  =  bitmap.width;
	int height =  bitmap.rows;
	
	zzg += height;
	zga = zzg/n++;
	width = get_by_power_2( bitmap.width); 
	height = get_by_power_2( bitmap.rows);
	m_FT_Face->size->metrics.y_ppem;
	m_FT_Face->glyph->metrics.horiAdvance;

	charTex.m_Width = width;
	charTex.m_Height = height;
	charTex.m_adv_x = m_FT_Face->glyph->advance.x / 64.0f;
	charTex.m_adv_y = m_FT_Face->size->metrics.y_ppem; //m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex.m_delta_x = (float)bitmap_glyph->left;
	//64 is hard code
	charTex.m_delta_y = (float)bitmap_glyph->top - 64;
	
	
	//char* pBuf = new char[width * height * 4];
		unsigned char* expanded_data = new unsigned char[  width * height];
	for(int j=0; j  < height ; j++)
	{
		for(int i=0; i < width; i++)
		{
			expanded_data[(i+(j)*width)]=  

				(i>=bitmap.width || j>=bitmap.rows) ? 
				0 : bitmap.buffer[i + bitmap.width*j];
			/*
			unsigned char _vl =  (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
			pBuf[(4*i + (height - j - 1) * width * 4)  ] = 0xFF;
			pBuf[(4*i + (height - j - 1) * width * 4)+1] = 0xFF;
			pBuf[(4*i + (height - j - 1) * width * 4)+2] = 0xFF;
			pBuf[(4*i + (height - j - 1) * width * 4)+3] = _vl;
			*/
		}
		
	}
	glGetError();
	GLenum s;
	glGenTextures(1,&charTex.m_texID);
	glBindTexture(GL_TEXTURE_2D,charTex.m_texID);
	s = glGetError();
	if(s!=GL_NO_ERROR)
	{
		printf("%d\n",s);
	}
	//glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,width, height,0,GL_RGBA,GL_UNSIGNED_BYTE,pBuf);
	

	//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ((TextureData*)r->extra)->width, ((TextureData*)r->extra)->height, 0,GL_ALPHA, GL_UNSIGNED_BYTE,r->ptr);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_ALPHA, GL_UNSIGNED_BYTE,expanded_data);
	s = glGetError();
	if(s!=GL_NO_ERROR)
	{
		printf("%d\n",s);
	}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	//glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	/*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);*/
	//delete[] pBuf;
	 delete [] expanded_data;
	return charTex.m_chaID;
}

xCharTexture* getTextChar(wchar_t ch)
{
	g_FreeTypeLib.loadChar(ch);
	//return text_map[ch];
	return &g_TexID[ch];
}
void AnsiToUnicode(LPCSTR lpcstr,LPWSTR outstr)   //参数lpcstr类型也可是char*
{ 
	int  i;
	i=MultiByteToWideChar(CP_ACP,0,lpcstr,-1,NULL,0);
	MultiByteToWideChar(CP_ACP,0,lpcstr,-1,outstr,i);
}

void drawText(wchar_t* _strText,int x , int y, int maxW , int h,bool isfbo)
{
	int sx = x;
	int sy = y;
	int maxH = h;
	//bool first = true;
	int wordh = zga;
	size_t nLen = wcslen(_strText);
	int p = 0;

	for(int i = 0 ; i <nLen ; i ++)
	{
		if(_strText[i] =='\n')
		{
			if(!isfbo)
			{	sx = x ; sy += maxH + wordh;
			}
			else
			{
				sx = x;
				sy += maxH+wordh;
				p++;
			}
			continue;
		}
		xCharTexture* pCharTex = getTextChar(_strText[i]);

		int w ;
		int h ;
		int ch_x ;
		int ch_y ;
		if(!isfbo)
		{
			w = pCharTex->m_Width;
			h = pCharTex->m_Height;
			ch_x = sx + pCharTex->m_delta_x;
			ch_y = sy - h - pCharTex->m_delta_y;
		}
		else
		{
			w = pCharTex->m_Width;
			h = pCharTex->m_Height;
			ch_x = sx + pCharTex->m_delta_x;
			ch_y = sy +h - pCharTex->m_delta_y;
		}
		//;
		//if(maxH < h) maxH = h;
		RenderQuad q;
		if(isfbo)
			q.set_quickly(ch_x,ch_y,ch_x,ch_y-h,ch_x+w,ch_y-h,ch_x+w,ch_y);
		else
			q.set_quickly(ch_x,ch_y,ch_x,ch_y+h,ch_x+w,ch_y+h,ch_x+w,ch_y);

		g_renderer->render(pCharTex->m_texID,&q);


		sx += pCharTex->m_adv_x;
		if(sx > x + maxW)
		{
			sx = x ; 
			if(!isfbo)
				sy += maxH + wordh;
			else
			{
				sy += maxH + wordh;
				p++;
			}
		}
	}
}

xFreeTypeLib g_FreeTypeLib;



TextMap text_map;