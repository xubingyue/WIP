#include "Colorf.h"
#include "RBMath/Inc/RBMath.h"
#include "Color32.h"

WIPColorf::WIPColorf(f32 r,f32 g,f32 b,f32 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

WIPColorf::WIPColorf(f32 r,f32 g,f32 b)
{
	this->r = r;
	this->b = b;
	this->g = g;
	this->a = 1.0;
}

WIPColorf::WIPColorf(const WIPColor32& color32)
{
	f32 f = 1.f/255.f;
	r = color32.r*f;
	g = color32.g*f;
	b = color32.b*f;
	a = color32.a*f;
}

bool WIPColorf::equal(const WIPColorf& other)
{
	return RBMath::is_nearly_equal(r,other.r)&&RBMath::is_nearly_equal(g,other.g)&&RBMath::is_nearly_equal(b,other.b)&&RBMath::is_nearly_equal(a,other.a);
}

f32 WIPColorf::get_grayscale()
{
	return (((0.299f * r) + (0.587f * g)) + (0.114f * b));
}


const WIPColorf 
	WIPColorf::red(1.f,0.f,0.f,1.f),
	WIPColorf::green(0.f,1.f,0.f,1.f),
	WIPColorf::blue(0.f,0.f,1.f,1.f),
	WIPColorf::white(1.f,1.f,1.f,1.f),
	WIPColorf::black(0.f,0.f,0.f,1.f),
	WIPColorf::yellow(1.f,0.9215686f,0.01568628f,1.f),
	//Çà
	WIPColorf::cyan(0.f,1.f,1.f,1.f),
	//Ñóºì
	WIPColorf::magenta(1.f,0.f,1.f,1.f),
	//»Ò
	WIPColorf::grey(0.5f,0.5f,0.5f,1.f),
	//»Ò
	WIPColorf::gray(0.5f,0.5f,0.5f,1.f),
	//clear
	WIPColorf::blank(0.f,0.f,0.f,0.f);