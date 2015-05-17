#pragma once
#include "RBMath/Inc/Vector2.h"
struct RenderQuad
{
	RBVector2 lt;
	RBVector2 lb;
	RBVector2 rb;
	RBVector2 rt;
	void set_quickly
		(
		float lt_x1,float lt_y1,
		float lb_x2,float lb_y2,
		float rb_x3,float rb_y3,
		float rt_x4,float rt_y4
		);

};

template <> struct TIsPODType<RenderQuad> { enum { v = true }; };