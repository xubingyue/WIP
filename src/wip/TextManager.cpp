#include "TextManager.h"
#include "Assertion.h"


TextureManager* TextureManager::_instance = 0;

TextureManager* TextureManager::instance()
{
	if (!_instance)
	{
		_instance = new TextureManager();
	}

	return _instance;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	delete _instance;
}

GLuint TextureManager::generate_texture(ResHandler* res,GLint gl_internalformat,GLenum gl_format,GLenum gl_type)
{
	if (!res)
	{
		return 0;
	}

	//be sure to delete this value in map when delete the reshandler
	_TextureMap::iterator it = _texture_map.find(res->ptr);
	if (it!=_texture_map.end())
	{
		++it->second->_ref;
		return it->second->_tex_id;
	}

	if (!res->ptr)
	{
		//be sure to do nothing.
		return 0;
	}

	_TextureCounter *tex = new _TextureCounter();
	GLuint res_back;
	glGenTextures ( 1, &res_back );
	glBindTexture ( GL_TEXTURE_2D, res_back );

	glTexImage2D ( GL_TEXTURE_2D, 0, gl_internalformat,
		((TextureData*)(res->extra))->width, ((TextureData*)(res->extra))->height, 
		0, gl_format , gl_type, res->ptr);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	tex->_ref = 1;
	tex->_tex_id = res_back;
	_texture_map[res->ptr] = tex;
	return res_back;
}

GLuint TextureManager::generate_texture(void *data,int w, int h ,GLint gl_internalformat,GLenum gl_format,GLenum gl_type)
{
	if (!data)
	{
		return 0;
	}

	//be sure to delete this value in map when delete the reshandler
	_TextureMap::iterator it = _texture_map.find(data);
	if (it!=_texture_map.end())
	{
		++it->second->_ref;
		return it->second->_tex_id;
	}

	_TextureCounter *tex = new _TextureCounter();
	GLuint res_back;
	glGenTextures ( 1, &res_back );
	glBindTexture ( GL_TEXTURE_2D, res_back );

	glTexImage2D ( GL_TEXTURE_2D, 0, gl_internalformat,w, h, 0, gl_format , gl_type, data);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	tex->_ref = 1;
	tex->_tex_id = res_back;
	_texture_map[data] = tex;
	return res_back;
}

void TextureManager::delete_texture(ResHandler* res)
{
	_TextureMap::iterator it = _texture_map.find(res->ptr);
	if (it==_texture_map.end())
	{
		//log
		printf("Delete nothing...\n");
		return;
	}
	--it->second->_ref;
	if (it->second->_ref<=0)
	{
		glDeleteTextures(1,&it->second->_tex_id);
		CHECK(it->second->_ref<=0);
		delete it->second;
		g_res_manager->free(res,res->size);
		_texture_map.erase(it->first);
	}
	

}

TextureManager* g_texture_manager = TextureManager::instance();

