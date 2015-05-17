#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"

class WIPColorf;

class WIPColor32
{
public:
	u8 r,g,b,a;
	WIPColor32(int color);
	WIPColor32(u8 r,u8 g,u8 b,u8 a);
	WIPColor32(u8 r,u8 g,u8 b);
	WIPColor32(const WIPColorf& colorf);
};

template <> struct TIsPODType<WIPColor32> { enum { v = true }; };