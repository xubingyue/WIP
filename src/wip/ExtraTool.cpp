#include "ExtraTool.h"
#include "FreeImage.h"
#include "Texture.h"
#include "RenderTexture.h"
#include <fstream>

bool WIPExtraTool::save_png(WIPRenderTexture* texture,const char* path)
{
	if(!texture)
		return false;
	int w = texture->get_width();
	int h = texture->get_height();
	unsigned char *mpixels =new unsigned char[w*h*4];
	glBindTexture(GL_TEXTURE_2D,texture->get_texture_id());
	glGetTexImage(GL_TEXTURE_2D,0,GL_BGRA,GL_UNSIGNED_BYTE,mpixels);  
	glDisable(GL_TEXTURE_2D);
	/*
    for(int i=0; i<(int)w*h*4; i+=4)
    {
        //exchange R&B
        mpixels[i] ^= mpixels[i+2] ^= mpixels[i] ^= mpixels[i+2];
    }
	*/
    FIBITMAP* bitmap =FreeImage_Allocate(w,h,32,8,8,8);

    for(int y =0 ;y<FreeImage_GetHeight(bitmap);y++)
    {
        BYTE *bits =FreeImage_GetScanLine(bitmap,y);
        for(int x =0 ;x<FreeImage_GetWidth(bitmap);x++)
        {
            bits[0] =mpixels[(y*w+x)*4+0];
            bits[1] =mpixels[(y*w+x)*4+1];
            bits[2] =mpixels[(y*w+x)*4+2];
            bits[3] =mpixels[(y*w+x)*4+3];
            bits+=4;

        }

    }
    bool bSuccess = FreeImage_Save(FIF_PNG, bitmap,path, PNG_DEFAULT);
     FreeImage_Unload(bitmap);
	 delete [] mpixels;
    return bSuccess;
}

bool WIPExtraTool::save_ini(const char* content,const char* path)
{
    std::ofstream fout(path);
    if (fout)
    {
		fout<<content<< std::endl;
        fout.close();
    }
	return true;
}