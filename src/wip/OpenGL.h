#pragma once
#include <stdlib.h>
#include "stdio.h"

//#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"


#ifdef _WIN32
#define ESUTIL_API  __cdecl
#define ESCALLBACK  __cdecl
#else
#define ESUTIL_API
#define ESCALLBACK
#endif


typedef struct ESContext ESContext;

struct ESContext
{
	/// Put platform specific data here
	void       *platformData;

	/// Put your user data here...
	void       *userData;

	/// Window width
	GLint       width;

	/// Window height
	GLint       height;

	/// Callbacks
	void ( ESCALLBACK *drawFunc ) ( ESContext * );
	void ( ESCALLBACK *shutdownFunc ) ( ESContext * );
	void ( ESCALLBACK *keyFunc ) ( ESContext *, unsigned char, int, int );
	void ( ESCALLBACK *updateFunc ) ( ESContext *, float deltaTime );
};



struct GLFWContext
{
	GLFWwindow* window; 

};

bool init_gl(GLFWwindow** window,const char* title,int width,int height);


GLuint ESUTIL_API esLoadShader ( GLenum type, const char *shaderSrc );

//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint ESUTIL_API esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );

