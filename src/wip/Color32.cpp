#include "Color32.h"
#include "Colorf.h"

WIPColor32::WIPColor32(int color)
{
	r = color>>24;
	g = (color&0xff0000)>>16;
	b = (color&0xff00)>>8;
	a = color&0xff;
}

WIPColor32::WIPColor32(u8 r,u8 g,u8 b,u8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

WIPColor32::WIPColor32(u8 r,u8 g,u8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

WIPColor32::WIPColor32(const WIPColorf& colorf)
{
	r = colorf.r*255;
	g = colorf.g*255;
	b = colorf.b*255;
	a = colorf.a*255;
}