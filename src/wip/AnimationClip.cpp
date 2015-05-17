#include "AnimationClip.h"
#include "Texture.h"
#include "FrameBox.h"
#include "Utilities/Utilities.h"
#include "PathTool.h"

WIPAnimationClip::WIPAnimationClip(const char* name,bool loop)
{
	bloop = loop;
	bplaying = false;
	this->name = name;
	_textures = 0;
	_total_frame = 0;
	_uvs = 0;
	_speed = 1.f;
	_framebox_ref = 0;
	_cur_dt = 0.f;
	_cur_frame = 1;
	_will_stop = false;
	_delete_texture = false;
}

WIPAnimationClip* WIPAnimationClip::create_with_atlas(const char* name,const char* atlas_file)
{
	std::string texture_name;
	WIPAnimationClip* ret= new WIPAnimationClip(name,false);
	if(!read_animation_atlas_file(atlas_file,ret->_total_frame,&ret->_uvs,texture_name))
	{
		delete ret;
		return 0;
	}
	std::string p =  WIPPathTool::get_file_directory(std::string(atlas_file));
	WIPTexture* tex = new WIPTexture((p+texture_name).c_str());
	ret->_textures = tex;
	ret->texture_type = ATLAS;
	ret->_delete_texture = true;
	return ret;
}

WIPAnimationClip* WIPAnimationClip::create_with_atlas(const char* name,const char* atlas_file,WIPTexture* texture)
{
	std::string texture_name;
	WIPAnimationClip* ret= new WIPAnimationClip(name,false);
	ret->_textures = texture;
	if(!read_animation_atlas_file(atlas_file,ret->_total_frame,&ret->_uvs,texture_name))
	{
		delete ret;
		return 0;
	}
	ret->texture_type = ATLAS;
	return ret;
}

WIPAnimationClip::~WIPAnimationClip()
{
	delete[] _uvs;
	if(_delete_texture)
		delete _textures;
}