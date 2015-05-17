#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "OpenGL.h"
#include "vmath.h"

class WIPShader
{
public:
	bool load(const char* vs,const char* fs ,const char* gs);
	FORCEINLINE void begin()
	{
		glUseProgram(_program);
	}
	FORCEINLINE void end()
	{
		glUseProgram(0);
	}
	void set_uniform_matrix(const char* name,vmath::mat4 m);
	void set_uniform_vec4();
	void set_uniform_i(const char* name,int i);
	void set_uniform_texture(const char* name,int id,int loc);
private:
	GLuint _program;

};
