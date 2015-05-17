#include "Camera.h"
#include "Layer.h"
#include "RenderBatch.h"
#include "Sprite.h"
#include "ObjectsLayer.h"
#include "Renderable.h"
#include "RenderTexture.h"
#include "Logger.h"
#include "Renderer.h"
#include "AppManager.h"
#include "SpriteFrame.h"
#include "Texture.h"
#include "RBMath/Inc/RBMath.h"

WIPCamera::WIPCamera(f32 w,f32 h)
{
	world_x = world_y = 0.f;
	screen_x = screen_y = 0;
	world_h = h;
	world_w = w;
	screen_w = g_app_manager->get_window_width();
	screen_h = g_app_manager->get_window_height();
	_active = true;
	_target = WIPRenderTexture::create(screen_w,screen_h);
}

WIPCamera::~WIPCamera()
{
	delete _target;
}


void WIPCamera::culling(WIPLayer* layer)
{
	culling(layer,((WIPObjectsLayer*)layer)->_batch);
}

void WIPCamera::culling(WIPLayer* layer,WIPRenderBatch* rbatch)
{
	WIPMesh mesh;
	WIPMesh* copy_mesh;
	WIPSprite* s;
	WIPObjectsLayer::_ObjectList::iterator it;
	for(it = ((WIPObjectsLayer*)layer)->_objects.begin();it!=((WIPObjectsLayer*)layer)->_objects.end();++it)
	{
		s = *it;
		s->_pak.z_order = s->z_order;
		//trnsform copy_mesh
		f32 scale_x = s->scale_x;
		f32 scale_y = s->scale_y;
		copy_mesh = s->_copy_mesh;
		f32 tworld_x = s->world_x -  copy_mesh->anchor.x;
		f32 tworld_y = s->world_y -  copy_mesh->anchor.y;
		f32 rotation = s->rotation;
		
		//(*s->_copy_mesh);
#define _cos RBMath::cos
#define _sin RBMath::sin
		//CCW is positive
		mesh.lt.y = (copy_mesh->lt.x - copy_mesh->anchor.x) * _sin(rotation) + (copy_mesh->lt.y - copy_mesh->anchor.y) * _cos(rotation);
		mesh.lt.x = (copy_mesh->lt.x - copy_mesh->anchor.x) * _cos(rotation) - (copy_mesh->lt.y - copy_mesh->anchor.y) * _sin(rotation);

		mesh.lb.y = (copy_mesh->lb.x - copy_mesh->anchor.x) * _sin(rotation) + (copy_mesh->lb.y - copy_mesh->anchor.y) * _cos(rotation);
		mesh.lb.x = (copy_mesh->lb.x - copy_mesh->anchor.x) * _cos(rotation) - (copy_mesh->lb.y - copy_mesh->anchor.y) * _sin(rotation);

		mesh.rt.y = (copy_mesh->rt.x - copy_mesh->anchor.x) * _sin(rotation) + (copy_mesh->rt.y - copy_mesh->anchor.y) * _cos(rotation);
		mesh.rt.x = (copy_mesh->rt.x - copy_mesh->anchor.x) * _cos(rotation) - (copy_mesh->rt.y - copy_mesh->anchor.y) * _sin(rotation);

		mesh.rb.y = (copy_mesh->rb.x - copy_mesh->anchor.x) * _sin(rotation) + (copy_mesh->rb.y - copy_mesh->anchor.y) * _cos(rotation);
		mesh.rb.x = (copy_mesh->rb.x - copy_mesh->anchor.x) * _cos(rotation) - (copy_mesh->rb.y - copy_mesh->anchor.y) * _sin(rotation);

		mesh.lt += copy_mesh->anchor;
		mesh.lb += copy_mesh->anchor;
		mesh.rt += copy_mesh->anchor;
		mesh.rb += copy_mesh->anchor;

#undef _cos
#undef _sin

		mesh.lt.x = (mesh.lt.x - copy_mesh->anchor.x) * scale_x + copy_mesh->anchor.x;
		mesh.lt.y = (mesh.lt.y - copy_mesh->anchor.y) * scale_y + copy_mesh->anchor.y;
		mesh.lb.x = (mesh.lb.x - copy_mesh->anchor.x) * scale_x + copy_mesh->anchor.x;
		mesh.lb.y = (mesh.lb.y - copy_mesh->anchor.y) * scale_y + copy_mesh->anchor.y;
		mesh.rt.x = (mesh.rt.x - copy_mesh->anchor.x) * scale_x + copy_mesh->anchor.x;
		mesh.rt.y = (mesh.rt.y - copy_mesh->anchor.y) * scale_y + copy_mesh->anchor.y;
		mesh.rb.x = (mesh.rb.x - copy_mesh->anchor.x) * scale_x + copy_mesh->anchor.x;
		mesh.rb.y = (mesh.rb.y - copy_mesh->anchor.y) * scale_y + copy_mesh->anchor.y;

		mesh.lt.x += tworld_x;
		mesh.lb.x += tworld_x;
		mesh.rt.x += tworld_x;
		mesh.rb.x += tworld_x;
		mesh.lt.y += tworld_y;
		mesh.lb.y += tworld_y;
		mesh.rt.y += tworld_y;
		mesh.rb.y += tworld_y;

		if(is_in_camera(&mesh))
		{
			s->_pak.mesh.lb.x = mesh.lt.x - world_x;
			s->_pak.mesh.lb.y = mesh.lt.y - world_y;
			s->_pak.mesh.lt.x = mesh.lb.x - world_x;
			s->_pak.mesh.lt.y = mesh.lb.y - world_y;
			s->_pak.mesh.rb.x = mesh.rt.x - world_x;
			s->_pak.mesh.rb.y = mesh.rt.y - world_y;
			s->_pak.mesh.rt.x = mesh.rb.x - world_x;
			s->_pak.mesh.rt.y = mesh.rb.y - world_y;
			s->_pak.tex_id = s->get_sprite_frame()->texture->get_texture_id();
			//flipY to set origin to left top in order to render
			//the next stage:renderer::render_to_camera
			/*
			s->_pak.mesh.lt.y = world_h - s->_pak.mesh.lt.y;
			s->_pak.mesh.lb.y = world_h - s->_pak.mesh.lb.y;
			s->_pak.mesh.rt.y = world_h - s->_pak.mesh.rt.y;
			s->_pak.mesh.rb.y = world_h - s->_pak.mesh.rb.y;
			*/
			rbatch->add_pack(&s->_pak);
		}
		else
		{
			g_logger->debug_print(WIP_NOTE,"Object has been culled!!");
		}
	}
}

bool WIPCamera::is_in_camera(WIPMesh* mesh1)
{
	WIPMesh mesh;
	generate_aabb(*mesh1,mesh);
	/*
	if (mesh.lt.x > world_x + world_w || mesh.rb.x < world_x) return false;
	if (mesh.rb.y > world_y + world_h || mesh.lt.y < world_y) return false;
	

	return true;
	*/
	return !(mesh.lt.x > world_x + world_w || mesh.rb.x < world_x||mesh.rb.y > world_y + world_h || mesh.lt.y < world_y);
}

void WIPCamera::copy_from(WIPCamera* other)
{
	_target->begin();
	other->render();
	_target->end();
}

void WIPCamera::render_to_texture(WIPRenderTexture* target)
{
	if(!target)
		return;
	target->begin();
	render();
	target->end();
}

void WIPCamera::render_with_shader(WIPShader* shader)
{
	g_logger->debug_print(WIP_NOTE,"Function render_with_shader is not in use!");
}

void WIPCamera::reset_ratio(f32 ratio)
{
	f32 new_height = screen_w * ratio;
	i32 height = static_cast<i32>(new_height);
	screen_h = height;
}

RBVector2 WIPCamera::camera_to_world(const RBVector2& camera_pos)
{
	return RBVector2(world_x+camera_pos.x,world_y+camera_pos.y);
}

RBVector2 WIPCamera::world_to_camera(const RBVector2& world_pos)
{
	return RBVector2(world_pos.x-world_x,world_pos.y-world_y);
}

void WIPCamera::set_background_color(const WIPColorf& color)
{

}

void WIPCamera::move(f32 dx,f32 dy)
{
	world_x += dx;
	world_y += dy;
}

void WIPCamera::move_to(f32 x,f32 y)
{
	world_x = x;
	world_y = y;
}

void WIPCamera::render(u32 flag)
{
	if(flag==AFTER_EFFECT)
	{
		g_renderer->render(_target->get_texture_id(),screen_x,screen_y,screen_w,screen_h);
	}
	else
	{
		//Things are almost the same now.
		g_renderer->render(_target->get_texture_id(),screen_x,screen_y,screen_w,screen_h);
	}
}

void WIPCamera::set_active(bool val)
{
	_active = val;
}

bool WIPCamera::get_active()
{
	return _active;
}

void WIPCamera::begin()
{
	_target->begin();
}

void WIPCamera::end()
{
	_target->end();
}

void WIPCamera::generate_aabb(const WIPMesh& ref,WIPMesh& m)
{
	f32 max_x = RBMath::max(RBMath::max3(ref.lt.x,ref.lb.x,ref.rb.x),ref.rt.x);
	f32 max_y = RBMath::max(RBMath::max3(ref.lt.y,ref.lb.y,ref.rb.y),ref.rt.y);
	f32 min_x = RBMath::min(RBMath::min3(ref.lt.x,ref.lb.x,ref.rb.x),ref.rt.x);
	f32 min_y = RBMath::min(RBMath::min3(ref.lt.y,ref.lb.y,ref.rb.y),ref.rt.y);

	m.lt.x = min_x;
	m.lt.y = max_y;
	m.lb.x = min_x;
	m.lb.y = min_y;
	m.rb.x = max_x;
	m.rb.y = min_y;
	m.rt.x = max_x;
	m.rt.y = max_y;


}