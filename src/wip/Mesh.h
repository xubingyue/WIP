#pragma once
#include "RBMath/Inc/Vector2.h"

//object coordinates
//Anchor is on geometric center
class WIPMesh
{
public:
	WIPMesh(f32 w,f32 h);
	WIPMesh();
	WIPMesh(const WIPMesh&);
	RBVector2 lt,lb,rb,rt;
	RBVector2 anchor;

	//copy
	//these will be remove
	/*
	RBVector2 ltc,lbc,rbc,rtc;
	RBVector2 anchorc;
	*/
	void set_quickly
		(
		float lt_x1,float lt_y1,
		float lb_x2,float lb_y2,
		float rb_x3,float rb_y3,
		float rt_x4,float rt_y4
		);
	//model view
	void set_anchor(f32 x,f32 y);
	//void apply_scale(f32 sx,f32 sy);
	void apply_scale_to(f32 sx,f32 sy);
	//WIPMesh scale(f32 sx,f32 sy);
	WIPMesh scale_to(f32 sx,f32 sy);
	//CCW
	//void apply_rotation(f32 rad);
	void apply_rotation_to(f32 rad);
	//WIPMesh rotate(f32 rad);
	WIPMesh rotate_to(f32 rad);
	//void apply_translation(f32 x,f32 y);
	void apply_translation_offset(f32 x,f32 y);
	//WIPMesh translate(f32 x,f32 y);
	WIPMesh translate_offset(f32 x,f32 y);

private:
	
};

template <> struct TIsPODType<WIPMesh> { enum { v = true }; };