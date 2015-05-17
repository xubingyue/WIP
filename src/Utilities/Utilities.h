#pragma once
#include <string>
#include <fstream>
#include <iostream>

//std::string up_down(const std::string& s);
std::string to_str(float f);
std::string to_str(int i);
bool read_text_file(const char* file_name,std::string& outstr);
bool read_animation_atlas_file(const char* file_name,int& total_frame,float **out_uvs,std::string& texture_name);

typedef struct 
{
	unsigned long size;
	unsigned short res1;
	unsigned short res2;
	unsigned long offset_bits;
} BmpFileHeader;

typedef struct
{
	unsigned long header_size;
	long width;
	long height;
	unsigned short planes;
	unsigned short bit_count;
	unsigned long  compression;
    unsigned long  size_image;
	long xpm;   
    long ypm;
    unsigned long clr_used;
    unsigned long clr_important;
} BmpContentHeader;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char res;
} RGB;
bool load_bmp(const char* file_name,int& out_w,int& out_h,int& channels,unsigned char** data);
