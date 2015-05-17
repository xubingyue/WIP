#pragma once
#include "Renderable.h"
//#include "./RBMathEx/Inc/Platform/RBBasedata.h"
#include <string>

class WIPSpriteFrame;
class WIPMesh;
class WIPAnimation;
class WIPTexture;
class WIPRenderable;
class WIPScene;
class WIPCamera;
class WIPCollider;
class WIPPhysicsManager;
class WIPAnimator;
class WIPAppManager;

class WIPSprite : private WIPRenderable
{
public:
	static WIPSprite* create(f32 width,f32 height);
	//use for lua
	static WIPSprite* create();
	WIPSprite();
	~WIPSprite();
	f32 world_x,world_y;
	i32 z_order;
	//CCW is positive
	f32 rotation;


	f32 scale_x,scale_y;

	void set_z_order(i32 z);
	void set_anchor(f32 percentx,f32 percenty);
	//force set a texture to _frame and at the same time set the full texture as the render result
	void set_texture(WIPTexture* texture);

	FORCEINLINE WIPMesh* get_copy_mesh()
	{
		return _copy_mesh;
	}
	//the anchor position is also the world 


	//Transform functions
	void rotate(f32 drad);
	void rotate_to(f32 rad);
	void translate(f32 dx,f32 dy);
	void translate_to(f32 x,f32 y);
	//scale with anchor
	void scale(f32 dsx,f32 dsy);
	void scale_to(f32 sx,f32 sy);
	//reset to the origin mesh
	void reset_mesh();

	void reset_origin_mesh(WIPMesh* mesh);
	void reset_animaton(WIPAnimation* ani);
	void reset_collider(WIPCollider* c);

	void set_tag(std::string s);
	std::string get_tag();

	INLINE WIPSpriteFrame* get_sprite_frame()
	{
		return _frame;
	}

	
private:


	friend WIPScene;
	friend WIPCamera;
	friend WIPPhysicsManager;
	friend WIPAppManager;

	void fill_static_texture_uv();

	WIPTexture* _default_texture;

	WIPSpriteFrame* _frame;
	WIPMesh* _origin_mesh;
	WIPMesh* _copy_mesh;
	WIPAnimation* _animation_controller;
	WIPCollider* _collider;
	WIPAnimator* _animator;

	std::string _tag;

};
