#pragma once
#include "lua.hpp"

void _check_parameters(lua_State* L,int n);

int L_load_lib(lua_State* L);


int L_init(lua_State* L);
int L_create_window(lua_State* L);
int L_run(lua_State* L);
int L_create_internal_rect(lua_State* L);
int L_delete_internal_rect(lua_State* L);
int L_resize_internal_rect(lua_State* L);
//////////////////////////////////////////////////////////////////////////
//Input
//////////////////////////////////////////////////////////////////////////
int L_get_key(lua_State* L);
int L_get_sys_key(lua_State* L);
int L_get_mouse_position(lua_State* L);
int L_mouse_move(lua_State* L);
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//Sprite
/////////////////////////////////////////////////////////////////////////
int L_generate_id(lua_State* L);
int L_create_sprite(lua_State* L);
int L_delete_sprite(lua_State* L);
int L_sprite_get_position(lua_State* L);
int L_sprite_set_position(lua_State* L);
int L_sprite_get_rotation(lua_State* L);
int L_sprite_rotate(lua_State* L);
int L_sprite_rotate_by(lua_State* L);
int L_sprite_rotate2(lua_State* L);
int L_sprite_rotate2_by(lua_State* L);
int L_sprite_translate(lua_State* L);
int L_sprite_scale(lua_State* L);
int L_sprite_get_forward(lua_State* L);
int L_sprite_get_local_position(lua_State* L);
int L_sprite_get_scale(lua_State* L);
int L_sprite_get_anchor(lua_State* L);
int L_sprite_set_anchor(lua_State* L);
int L_sprite_get_zorder(lua_State* L);
int L_sprite_set_zorder(lua_State* L);

static int L_XXX(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Scene
/////////////////////////////////////////////////////////////////////////
//param scene_ptr
int L_scene_delete(lua_State* L);
//return scene_ptr
int L_scene_create(lua_State* L);
//add go to cpp scene object layer list
int L_scene_add_object(lua_State* L);
//param scene_ptr unload the scene resources
int L_scene_unload(lua_State* L);
int L_scene_add_ui(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Sprite
/////////////////////////////////////////////////////////////////////////
//param path return bool 
int L_sprite_set_sataic_texture(lua_State* L);
int L_sprite_attach_mesh(lua_State* L);
int L_sprite_attach_animation(lua_State* L);
int L_sprite_attach_collider(lua_State* L);
int L_sprite_scale_to(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Mesh
/////////////////////////////////////////////////////////////////////////
//param w,h return mesh_ptr
int L_mesh_create(lua_State* L);
int L_mesh_delete(lua_State* L);
//param percent cx cy
int L_mesh_set_anchor(lua_State* L);
//return ax,ay
int L_mesh_get_anchor(lua_State* L);
int L_mesh_set_size(lua_State* L);
int L_mesh_get_size(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Camera
/////////////////////////////////////////////////////////////////////////
//create a cpp camera and return its pointer
//param world_w,world_h
int L_camera_create(lua_State* L);
int L_camera_delete(lua_State* L);
int L_camera_move_world(lua_State* L);
int L_camera_move_world_to(lua_State* L);
int L_camera_get_world_x(lua_State* L);
int L_camera_get_world_y(lua_State* L);
int L_camera_get_world_width(lua_State* L);
int L_camera_get_world_height(lua_State* L);
int L_camera_move_screen(lua_State* L);
int L_camera_get_screen_x(lua_State* L);
int L_camera_get_screen_y(lua_State* L);
int L_camera_get_screen_width(lua_State* L);
int L_camera_get_screen_height(lua_State* L);
int L_camera_move_screen_to(lua_State* L);
int L_camera_copy_from(lua_State* L);
int L_camera_set_active(lua_State* L);
int L_camera_get_active(lua_State* L);
int L_camera_set_screen_size(lua_State* L);
int L_camera_set_world_size(lua_State* L);
int L_camera_get_world(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//System
/////////////////////////////////////////////////////////////////////////
int L_system_get_dt(lua_State* L);
int L_system_draw_rect(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//App
/////////////////////////////////////////////////////////////////////////
int L_app_add_camera(lua_State* L);

/////////////////////////////////////////////////////////////////////////
//Texture
/////////////////////////////////////////////////////////////////////////
int L_texture_create(lua_State* L);
int L_texture_delete(lua_State* L);
int L_texture_resize(lua_State* L);
int L_texture_size(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Animation
/////////////////////////////////////////////////////////////////////////
int L_animation_create(lua_State* L);
int L_animation_delete(lua_State* L);
int L_animation_play(lua_State* L);
int L_animation_stop(lua_State* L);
int L_animation_rewind(lua_State* L);
int L_animation_add_clip(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Animation Clip
/////////////////////////////////////////////////////////////////////////
//param clip nama/atlas file name/texture (Texture) if nil call create_with_atlas(const char* name,const char* atlas_file)
int L_clip_create(lua_State* L);
int L_clip_delete(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Collider
/////////////////////////////////////////////////////////////////////////
//param sprite_ptr
int L_collider_create(lua_State* L);
int L_collider_delete(lua_State* L);
int L_collider_set_active(lua_State* L);
int L_collider_add_force(lua_State* L);
int L_collider_reset_body_type(lua_State* L);
int L_collider_is_collision_empty(lua_State* L);
int L_collider_get_collision_list_size(lua_State* L);
int L_collider_set_density(lua_State* L);
//return x,y
int L_collider_get_speed(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Frame Animation Tools
/////////////////////////////////////////////////////////////////////////
int L_transform4X4(lua_State* L);
int L_generate_atlas(lua_State* L);
//////////////////////////////////////////////////////////////////////////
//Text
//////////////////////////////////////////////////////////////////////////
int L_text_draw(lua_State* L);
int L_text_flush(lua_State* L);
int L_text_clear(lua_State* L);
//////////////////////////////////////////////////////////////////////////
//sound
//////////////////////////////////////////////////////////////////////////
int L_sound_create(lua_State* L);
int L_sound_delete(lua_State* L);
int L_sound_stream_delete(lua_State* £Ì);
int L_sound_turn(lua_State* L);
int L_sound_set_loop(lua_State* L);
int L_sound_pause(lua_State* L);
int L_sound_stop(lua_State* L);
int L_sound_stopforever(lua_State* L);
int L_sound_rewind(lua_State* L);
int L_sound_remove(lua_State* L);
int L_sound_clear_all(lua_State* L);
int L_sound_play(lua_State* L);

int L_sound_stream_turn(lua_State* L);
int L_sound_stream_pause(lua_State* L);
int L_sound_stream_resume(lua_State* L);
int L_sound_stream_play(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//Shader
/////////////////////////////////////////////////////////////////////////
int L_shader_create(lua_State* L);
int L_shader_begin(lua_State* L);
int L_shader_end(lua_State* L);
int L_shader_set_uniform(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//3DModel
/////////////////////////////////////////////////////////////////////////
