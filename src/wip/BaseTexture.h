#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "OpenGL.h"

class WIPBaseTexture
{
public:
	virtual i32 get_width(){return 0;};
	virtual i32 get_height(){return 0;};
	virtual GLuint get_texture_id(){return 0;};

protected:
	GLuint tex_id;			

};