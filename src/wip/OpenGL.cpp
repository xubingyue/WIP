#include "OpenGL.h"
GLuint ESUTIL_API esLoadShader ( GLenum type, const char *shaderSrc )
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader ( type );

	if ( shader == 0 )
	{
		return 0;
	}

	// Load the shader source
	glShaderSource ( shader, 1, &shaderSrc, NULL );

	// Compile the shader
	glCompileShader ( shader );

	// Check the compile status
	glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

	if ( !compiled )
	{
		GLint infoLen = 0;

		glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

			glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
			printf( "Error compiling shader:\n%s\n", infoLog );

			free ( infoLog );
		}

		glDeleteShader ( shader );
		return 0;
	}

	return shader;

}


//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint ESUTIL_API esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = esLoadShader ( GL_VERTEX_SHADER, vertShaderSrc );

	if ( vertexShader == 0 )
	{
		return 0;
	}

	fragmentShader = esLoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );

	if ( fragmentShader == 0 )
	{
		glDeleteShader ( vertexShader );
		return 0;
	}

	// Create the program object
	programObject = glCreateProgram ( );

	if ( programObject == 0 )
	{
		return 0;
	}

	glAttachShader ( programObject, vertexShader );
	glAttachShader ( programObject, fragmentShader );

	// Link the program
	glLinkProgram ( programObject );

	// Check the link status
	glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

	if ( !linked )
	{
		GLint infoLen = 0;

		glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

			glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
			printf( "Error linking program:\n%s\n", infoLog );

			free ( infoLog );
		}

		glDeleteProgram ( programObject );
		return 0;
	}

	// Free up no longer needed shader resources
	glDeleteShader ( vertexShader );
	glDeleteShader ( fragmentShader );

	return programObject;
}


bool init_gl(GLFWwindow** window,const char* title,int width,int height)
{
	

	if(!glfwInit())
	{
		printf("glfwInit() failed!\n");
		getchar();
		exit(0);
	}

	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	*window = glfwCreateWindow(width,height,title,NULL,NULL);
	glfwMakeContextCurrent(*window);
	//set all callbacks
	
	glewInit();

	return true;
}