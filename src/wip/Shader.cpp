#include "Shader.h"
#include "Utilities/Utilities.h"
#include "Logger.h"

bool WIPShader::load( const char* vs,const char* fs ,const char* gs)
{
	std::string fss;
	if (!read_text_file(fs,fss))
	{
		printf("fs read failed!");
		return false;
	}
	std::string vss;
	if (!read_text_file(vs,vss))
	{
		printf("vs read failed!");
		return false;
	}
	const char* fssc = fss.data();
	const char* vssc = vss.data();
	
	GLint compiled;
	GLint linked;

	_program = glCreateProgram();
	GLuint fsc = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fsc,1,&fssc,NULL);

	glCompileShader(fsc);

	glGetShaderiv ( fsc, GL_COMPILE_STATUS, &compiled );
	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv ( fsc, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

			glGetShaderInfoLog ( fsc, infoLen, NULL, infoLog );
			printf( "Error compiling shader:\n%s\n", infoLog );

			free ( infoLog );
		}

		glDeleteShader ( fsc );
		printf("fs_source failed!\n");
		return false;
	}


	GLuint vsc = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vsc,1,&vssc,NULL);

	glCompileShader(vsc);


	glGetShaderiv ( vsc, GL_COMPILE_STATUS, &compiled );
	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv ( vsc, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

			glGetShaderInfoLog ( vsc, infoLen, NULL, infoLog );
			printf( "Error compiling shader:\n%s\n", infoLog );

			free ( infoLog );
		}

		glDeleteShader ( vsc );
		printf("vs_source failed!\n");
		return false;
	}

	glAttachShader(_program,vsc);

	glAttachShader(_program,fsc);
	GLuint gsc = 0;
	if (gs)
	{
		std::string gss;
		if (!read_text_file(gs,gss))
		{
			printf("gs read failed!");
			return false;
		}

		const char* gssc = gss.data();


		gsc = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gsc,1,&gssc,NULL);

		glCompileShader(gsc);

		glGetShaderiv ( gsc, GL_COMPILE_STATUS, &compiled );
		if (!compiled)
		{
			GLint infoLen = 0;

			glGetShaderiv ( gsc, GL_INFO_LOG_LENGTH, &infoLen );

			if ( infoLen > 1 )
			{
				char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

				glGetShaderInfoLog ( gsc, infoLen, NULL, infoLog );
				printf( "Error compiling shader:\n%s\n", infoLog );

				free ( infoLog );
			}

			glDeleteShader ( gsc );
			printf("fs_source failed!\n");
			return false;
		}

		glAttachShader(_program,gsc);
	}


	glLinkProgram(_program);
	glGetProgramiv ( _program, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLint infoLen = 0;

		glGetProgramiv ( _program, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char *infoLog = (char*)malloc ( sizeof ( char ) * infoLen );

			glGetProgramInfoLog ( _program, infoLen, NULL, infoLog );
			printf( "Error linking program:\n%s\n", infoLog );

			free ( infoLog );
		}

		glDeleteProgram ( _program );
		return 0;
	}
	glDeleteShader ( vsc );
	glDeleteShader ( fsc );

	if(gsc)
	{
		glDeleteShader(gsc);
	}

	return true;
}

void WIPShader::set_uniform_matrix(const char* name,vmath::mat4 m)
{
	GLint loc = glGetUniformLocation(_program,name);
	glUniformMatrix4fv(loc,1,GL_FALSE,m);
}

void WIPShader::set_uniform_vec4()
{

}

void WIPShader::set_uniform_i(const char* name,int i)
{
	GLint loc = glGetUniformLocation(_program,name);
	glUniform1i(loc,i);
}

void WIPShader::set_uniform_texture(const char* name,int id,int loc)
{
	GLint locc = glGetUniformLocation(_program,name);
	glUniform1i(locc,loc);
	glActiveTexture(GL_TEXTURE0+loc);
	glBindTexture(GL_TEXTURE_2D,id);
}