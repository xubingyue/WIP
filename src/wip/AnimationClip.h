#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include <string>

#define ATLAS			1
#define PICTURES		2

class WIPTexture;
class WIPFrameBox;
class WIPSpriteFrame;
class WIPAnimation;
class WIPAnimationManager;

class WIPAnimationClip
{
public:
	bool bplaying;
	bool bloop;
	std::string name;
	//ATLAS or PICTURE
	i32 texture_type;

	~WIPAnimationClip();

	//find texture from atlas files.TODO:dtor
	static WIPAnimationClip* create_with_atlas(const char* name,const char* atlas_file);
	static WIPAnimationClip* create_with_atlas(const char* name,const char* atlas_file,WIPTexture* texture);

	WIPAnimationClip(const char* name,bool loop);

	INLINE WIPTexture* get_texture()
	{
		return _textures;
	}


private:
	friend WIPAnimation;
	friend WIPAnimationManager;
	//dynamic arraym,maybe
	WIPTexture* _textures;
	//lt,lb,rb,rt->next::size=_tatal_frameX8
	f32* _uvs;
	i32 _total_frame;

	f32 _speed;
	WIPFrameBox* _framebox_ref;
	f32 _cur_dt;
	//begin with 1
	i32 _cur_frame;
	
	bool _will_stop;

	bool _delete_texture;

};