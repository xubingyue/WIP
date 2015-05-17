#include "Mesh.h"
#include "RBMath/Inc/Matrix.h"

void WIPMesh::set_quickly( float x1,float y1, float x2,float y2, float x3,float y3, float x4,float y4 )
{
	lt.x = x1;
	lt.y = y1;
	lb.x = x2;
	lb.y = y2;
	rb.x = x3;
	rb.y = y3;
	rt.x = x4;
	rt.y = y4;
	anchor.x = 0.f;
	anchor.y = 0.f;
}

WIPMesh::WIPMesh(f32 w,f32 h)
{
	if(w<=0||h<=0)
	{
		lt = RBVector2::zero_vector;
		lb = RBVector2::zero_vector;
		rt = RBVector2::zero_vector;
		rb = RBVector2::zero_vector;
		anchor = RBVector2::zero_vector;
		return;
	}
	f32 hw = w*.5f;
	f32 hh = h*.5f;
	lt = RBVector2(-hw,hh);
	lb = RBVector2(-hw,-hh);
	rt = RBVector2(hw,hh);
	rb = RBVector2(hw,-hh);
	anchor = RBVector2(0.f,0.f);
}

WIPMesh::WIPMesh()
{
	lt = RBVector2::zero_vector;
	lb = RBVector2::zero_vector;
	rt = RBVector2::zero_vector;
	rb = RBVector2::zero_vector;
	anchor = RBVector2::zero_vector;
}

WIPMesh::WIPMesh(const WIPMesh& mesh)
{
	lt = mesh.lt;
	lb = mesh.lb;
	rt = mesh.rt;
	rb = mesh.rb;
	anchor = mesh.anchor;
}

void WIPMesh::set_anchor(f32 x,f32 y)
{
	anchor.x = x;
	anchor.y = y;
}

void WIPMesh::apply_scale_to(f32 sx,f32 sy)
{

	lt.x *= sx;
	lb.x *= sx;
	rb.x *= sx;
	rt.x *= sx;
	lt.y *= sy;
	lb.y *= sy;
	rb.y *= sy;
	rt.y *= sy;

}

WIPMesh WIPMesh::scale_to(f32 sx,f32 sy)
{
	WIPMesh ret(*this);
	ret.apply_scale_to(sx,sy);
	/*
	WIPMesh ret;
	ret.set_quickly(lt.x *= sx,
	lb.x *= sx,
	rb.x *= sx,
	rt.x *= sx,
	lt.y *= sy,
	lb.y *= sy,
	rb.y *= sy,
	rt.y *= sy);
	*/
	return ret;
}

void WIPMesh::apply_rotation_to(f32 rad)
{
#define _cos RBMath::cos
#define _sin RBMath::sin
	//CCW is positive
	f32 xx = lt.x*_cos(rad) - lt.y*_sin(rad);
	lt.y = lt.x*_sin(rad) + lt.y*_cos(rad);
	lt.x = xx;
	xx = lb.x*_cos(rad) - lb.y*_sin(rad);
	lb.y = lb.x*_sin(rad) + lb.y*_cos(rad);
	lb.x = xx;
	xx = rt.x*_cos(rad) - rt.y*_sin(rad);
	rt.y = rt.x*_sin(rad) + rt.y*_cos(rad);
	rt.x = xx;
	xx = rb.x*_cos(rad) - rb.y*_sin(rad);
	rb.y = rb.x*_sin(rad) + rb.y*_cos(rad);
	rb.x = xx;
#undef _cos
#undef _sin
}

WIPMesh WIPMesh::rotate_to(f32 rad)
{
	WIPMesh ret(*this);
	ret.apply_rotation_to(rad);
	return ret;
}

void WIPMesh::apply_translation_offset(f32 x,f32 y)
{
	lt.x += x;
	lt.y += y;
	lb.x += x;
	lb.y += y;
	rt.x += x;
	rt.y += y;
	rb.x += x;
	rb.y += y;

}

WIPMesh WIPMesh::translate_offset(f32 x,f32 y)
{
	WIPMesh ret(*this);
	ret.apply_translation_offset(x,y);
	return ret;
}


