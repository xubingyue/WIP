#include "../wip/Logger.h"
#include "Utilities.h"
#include "WIPIniHelper.h"
#include <sstream>
/*
std::string up_down(const std::string& s)
{
	std::string ts;
	ts.
}
*/
std::string to_str(float f)
{
	return "";
}

std::string to_str(int i)
{
	std::ostringstream out;
	out<<i;
	return out.str();
	/*
	std::string ret;
	
	while(i>0)
	{
		
		ret += (i - i/10*10 + 48);
		i = i/10;
	}

	

	return ret;
	*/
}

bool read_text_file(const char* file_name,std::string& outstr)
{
	std::fstream f;
	f.open(file_name,std::ios::in);
	if(!f)
	{
		return false;
	}
	outstr.clear();
	std::string temp;
	while (getline(f,temp))
	{
		temp+='\n';
		outstr+=temp;
	}
	return true;
}

bool read_animation_atlas_file(const char* file_name,int& total_frame,float **out_uvs,std::string& texture_name)
{
	bool ret = true;
	WIPIniHelper::reset_ini_file(file_name);
	if(!WIPIniHelper::get_int("head","total_frame",total_frame))
	{
		g_logger->debug_print(WIP_NOTE,"load clip total_frame failed!");
		return false;
	}
	if(!WIPIniHelper::get_string("head","texture",texture_name))
	{
		g_logger->debug_print(WIP_INFO,"read clip texture infomation failed!");
		return false;
	}

	*out_uvs = new float[total_frame*8];

	
	for(int i=0;i<total_frame;++i)
	{
		char s[32];
		sprintf(s,"%d",i+1);
		WIPIniHelper::get_float(s,"lt_x",(*out_uvs)[i*8+0]);
		WIPIniHelper::get_float(s,"lt_y",(*out_uvs)[i*8+1]);
		WIPIniHelper::get_float(s,"lb_x",(*out_uvs)[i*8+2]);
		WIPIniHelper::get_float(s,"lb_y",(*out_uvs)[i*8+3]);
		WIPIniHelper::get_float(s,"rb_x",(*out_uvs)[i*8+4]);
		WIPIniHelper::get_float(s,"rb_y",(*out_uvs)[i*8+5]);
		WIPIniHelper::get_float(s,"rt_x",(*out_uvs)[i*8+6]);
		WIPIniHelper::get_float(s,"rt_y",(*out_uvs)[i*8+7]);
	}
	
	WIPIniHelper::close();
	return ret;
}



bool load_bmp(const char* file_name,int& out_w,int& out_h,int& channels,unsigned char** data)
{
	FILE* file;
	file = fopen(file_name,"rb");
	if(!file)
	{
		g_logger->debug_print(WIP_WARNING,"No file:%s",file_name);
		return false;
	}
	 unsigned short type; 
	 fread(&type,sizeof(unsigned short),1,file);
	 if(type!=0x4d42)
	 {
		 g_logger->debug_print(WIP_WARNING,"NOT A BMP file:%s",file_name);
		 fclose(file);
		 return false;
	 }

	 BmpFileHeader file_header;
	 BmpContentHeader content_header;

	 fread(&file_header,sizeof(BmpFileHeader),1,file);
	 fread(&content_header,sizeof(BmpContentHeader),1,file);

	  out_w = content_header.width;
	  out_h = content_header.height;

	  
	  g_logger->debug_log(WIP_NOTE,"header size:%d\n", content_header.header_size);
	  g_logger->debug_log(WIP_NOTE,"width:%d\n", content_header.width);
	  g_logger->debug_log(WIP_NOTE,"height:%d\n", content_header.height);
	  g_logger->debug_log(WIP_NOTE,"planes:%d\n", content_header.planes);
	  g_logger->debug_log(WIP_NOTE,"bits:%d\n", content_header.bit_count);
	  g_logger->debug_log(WIP_NOTE,"image size:%d\n", content_header.size_image);
	  g_logger->debug_log(WIP_NOTE,"compression:%d\n", content_header.compression);

	 if(content_header.bit_count==8)
	 {
		  g_logger->debug_print(WIP_WARNING,"A 8bit BMP file:%s",file_name);
		 /*
		channels = 1;
		 *data = (unsigned char*)malloc(sizeof(unsigned char)*out_w*out_h);

		 RGB* q = (RGB*)malloc(sizeof(RGB)*256);
		 fread(q,sizeof(RGB),256,file);
		 free(q);

		 //size_t c = sizeof(unsigned char)*4*256*256;
		 size_t off = out_w%4;
		 if(off!=0)
		 {
			 off = 4 - off;
		 }
		 //fseek(file,c,SEEK_CUR);
		 unsigned char pix;
		 for(int i = 0;i<out_h;i++)
		 {

			 for(int j=0;j<out_w;j++)
			 {
				 fread(&pix,sizeof(unsigned char),1,file);
				 (*data)[(out_h-1-i)*out_w+j] = pix;
			 }
			 if(off!=0)
			 {
				 for(int k=0;k<off;k++)
				 {
					 fseek(file,sizeof(unsigned char),SEEK_CUR);
				 }
			 }
		 }
		 */

	 }
	 else if(content_header.bit_count==24)
	 {
		 channels = 4;
		 *data = (unsigned char*)malloc(sizeof(unsigned char)*out_w*4*out_h);
		 int c = channels*out_w;

		 int off = c%4;
		 if(off!=0)
		 {
			 off = 4 - off;
		 }
		 unsigned char pix;
		 for(int i=0;i<out_h;i++)
		 {
			 for(int j=0;j<out_w;j++)
			 {
				 /*
				 for(int k=0;k<3;k++)
				 {
					 fread(&pix,sizeof(unsigned char),1,file);
					 (*data)[(out_h-1-i)*c+j*3+k] = pix;
				 }
				 */
				 /*
				 fread(&pix,sizeof(unsigned char),1,file);
				 (*data)[(out_h-1-i)*c+j*3+2] = pix;
				 fread(&pix,sizeof(unsigned char),1,file);
					 (*data)[(out_h-1-i)*c+j*3+1] = pix;
					 fread(&pix,sizeof(unsigned char),1,file);
					 (*data)[(out_h-1-i)*c+j*3+0] = pix;
					 */
				  fread(&pix,sizeof(unsigned char),1,file);
					(*data)[(i)*c+j*4+2] = pix;
				 fread(&pix,sizeof(unsigned char),1,file);
					 (*data)[(i)*c+j*4+1] = pix;
					 fread(&pix,sizeof(unsigned char),1,file);
					 (*data)[(i)*c+j*4+0] = pix;
					 //Óë°×É«Òì»ò
					 if((*data)[(i)*c+j*4+2]==255&&(*data)[(i)*c+j*4+0]==255&&(*data)[(i)*c+j*4+1]==255)
						(*data)[(i)*c+j*4+3] = 0;
					 
			 }
			 if(off!=0)
			 {
				 for(int k=0;k<off;k++)
				 {
					  fseek(file,sizeof(unsigned char),SEEK_CUR);
				 }
			 }
		 }
	 }

	return true;
}