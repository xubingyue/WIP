#include "RenderQuad.h"

void RenderQuad::set_quickly( float x1,float y1, float x2,float y2, float x3,float y3, float x4,float y4 )
{
	lt.x = x1;
	lt.y = y1;
	lb.x = x2;
	lb.y = y2;
	rb.x = x3;
	rb.y = y3;
	rt.x = x4;
	rt.y = y4;
}
