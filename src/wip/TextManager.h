#pragma once
//此类，用于管理纹理申请和释放，同一张纹理会返回相同的纹理id
#include "OpenGL.h"
#include "Utilities/WPMap.h"
#include "ResourceManager.h"

class TextureManager
{
public:
	static TextureManager* instance();
	~TextureManager();
	//TODO:Add const
	GLuint generate_texture(ResHandler* res,GLint gl_internalformat,GLenum gl_format,GLenum gl_type);
	//with data
	GLuint generate_texture(void *data,int w, int h ,GLint gl_internalformat,GLenum gl_format,GLenum gl_type);
	void delete_texture(ResHandler* res);

protected:
	TextureManager();
private:
	static TextureManager* _instance;

	struct _TextureCounter 
	{
		GLuint _tex_id;
		unsigned int _ref;
		_TextureCounter()
		{
			_tex_id = 0;
			_ref = 0;
		}
	};

	typedef Map<void*,_TextureCounter*> _TextureMap;
	_TextureMap _texture_map;

};

extern TextureManager* g_texture_manager;