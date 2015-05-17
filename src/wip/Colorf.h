#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"

class WIPColor32;

class WIPColorf
{
public:
	//0.0f-1.0f
	f32 r,g,b,a;
	WIPColorf(f32 r,f32 g,f32 b,f32 a);
	WIPColorf(f32 r,f32 g,f32 b);
	bool equal(const WIPColorf& other);
	f32 get_grayscale();
	//[Kinds of operators(+,-,*,/)] 

	WIPColorf(const WIPColor32& color32);

	static const WIPColorf 
		red,
		green,
		blue,
		white,
		black,
		yellow,
		cyan,
		magenta,
		gray,
		grey,
		blank;

};

template <> struct TIsPODType<WIPColorf> { enum { v = true }; };