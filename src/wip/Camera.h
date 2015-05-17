#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "RBMath/Inc/Vector2.h"

class WIPRenderTexture;
class WIPLayer;
class WIPRenderBatch;
class WIPShader;
class WIPColorf;
class WIPMesh;

#define ORIGIN_EFFECT	1
#define AFTER_EFFECT		2

class WIPCamera
{
public:
	WIPCamera(f32 w,f32 h);
	~WIPCamera();
	//left button
	f32 world_x,world_y;
	f32 world_w,world_h;
	//left top
	i32 screen_x,screen_y;
	i32 screen_w,screen_h;

	
	
	void culling(WIPLayer* layer);
	void culling(WIPLayer* layer,WIPRenderBatch* rbatch);
	
	void copy_from(WIPCamera* other);
	void clear();
	//render to screen.AE for with affter effects,OR for otherwise.
	void render(u32 flag = AFTER_EFFECT);
	void render_to_texture(WIPRenderTexture* target);
	void render_with_shader(WIPShader* shader);
	//keep width fixed
	void reset_ratio(f32 ratio);
	RBVector2 camera_to_world(const RBVector2& camera_pos);
	RBVector2 world_to_camera(const RBVector2& world_pos);
	void set_background_color(const WIPColorf& color);
	void move(f32 x,f32 y);
	void move_to(f32 x,f32 y);
	void set_active(bool val);
	bool get_active();

	void begin();
	void end();
private:
	void generate_aabb(const WIPMesh& ref,WIPMesh& m);
	bool is_in_camera(WIPMesh* mesh);

	WIPRenderTexture* _target;
	bool _active;
};