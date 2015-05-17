#include "RenderQuad.h"
#include "ResourceManager.h"
#include "AppManager.h"
#include "KeyDefinetions.h"
#include "InputManager.h"
#include "Input.h"
#include "Sprite.h"
#include "Logger.h"

#include "LuaAPI.h"
#include "LuaUI.h"


void _check_parameters(lua_State* L,int n)
{
	int s = lua_gettop(L);
	if(s<n)
	{
		printf("function need %d,there is %d\n",n,s);
		getchar();
		exit(0);
	}
}

/*LuaAPI
 *note LuaAPI only support the function like this:
 *int function(lua_state*);
 *called by generate_api()
 *
 */
int L_load_lib(lua_State* L)
{
	luaL_Reg lib[] = 
	{
		{"init",L_init},
		{"create_window",L_create_window},
		{"run",L_run},
		{"create_internal_rect",L_create_internal_rect},
		{"delete_internal_rect",L_delete_internal_rect},
		{"resize_internal_rect",L_resize_internal_rect},
		{"get_key",L_get_key},
		{"get_sys_key",L_get_sys_key},
		{"get_mouse_position",L_get_mouse_position},
		{"is_mouse_move",L_mouse_move},
		{"generate_id",L_generate_id},
		{"create_sprite",L_create_sprite},
		{"delete_sprite",L_delete_sprite},
		{"sprite_get_position",L_sprite_get_position},
		{"sprite_set_position",L_sprite_set_position},
		{"sprite_get_rotation",L_sprite_get_rotation},
		{"sprite_rotate",L_sprite_rotate},
		{"sprite_rotate_by",L_sprite_rotate_by},
		{"sprite_rotate2",L_sprite_rotate2},
		{"sprite_rotate2_by",L_sprite_rotate2_by},
		{"sprite_translate",L_sprite_translate},
		{"sprite_scale",L_sprite_scale},
		{"sprite_scale_to",L_sprite_scale_to},
		{"sprite_get_forward",L_sprite_get_forward},
		{"sprite_get_local_position",L_sprite_get_local_position},
		{"sprite_get_scale",L_sprite_get_scale},
		{"sprite_get_anchor",L_sprite_get_anchor},
		{"sprite_set_anchor",L_sprite_set_anchor},
		{"sprite_get_zorder",L_sprite_get_zorder},
		{"sprite_set_zorder",L_sprite_set_zorder},
		{"scene_delete",L_scene_delete},
		{"scene_create",L_scene_create},
		{"scene_add_object",L_scene_add_object},
		{"scene_unload",L_scene_unload},
		{"scene_add_ui",L_scene_add_ui},
		{"sprite_set_sataic_texture",L_sprite_set_sataic_texture},
		{"sprite_attach_mesh",L_sprite_attach_mesh},
		{"sprite_attach_animation",L_sprite_attach_animation},
		{"sprite_attach_collider",L_sprite_attach_collider},
		{"mesh_create",L_mesh_create},
		{"mesh_delete",L_mesh_delete},
		{"mesh_set_anchor",L_mesh_set_anchor},
		{"mesh_get_anchor",L_mesh_get_anchor},
		{"mesh_set_size",L_mesh_set_size},
		{"mesh_get_size",L_mesh_get_size},
		{"camera_create",L_camera_create},
		{"camera_delete",L_camera_delete},
		{"camera_move_world",L_camera_move_world},
		{"camera_move_world_to",L_camera_move_world_to},
		{"camera_get_world_x",L_camera_get_world_x},
		{"camera_get_world_y",L_camera_get_world_y},
		{"camera_get_world",L_camera_get_world},
		{"camera_get_world_width",L_camera_get_world_width},
		{"camera_get_world_height",L_camera_get_world_height},
		{"camera_move_screen",L_camera_move_screen},
		{"camera_get_screen_x",L_camera_get_screen_x},
		{"camera_get_screen_y",L_camera_get_screen_y},
		{"camera_get_screen_width",L_camera_get_screen_width},
		{"camera_get_screen_height",L_camera_get_screen_height},
		{"camera_move_screen_to",L_camera_move_screen_to},
		{"camera_copy_from",L_camera_copy_from},
		{"camera_set_active",L_camera_set_active},
		{"camera_get_active",L_camera_get_active},
		{"camera_set_screen_size",L_camera_set_screen_size},
		{"camera_set_world_size",L_camera_set_world_size},
		{"system_get_dt",L_system_get_dt},
		{"system_draw_rect",L_system_draw_rect},
		{"app_add_camera",L_app_add_camera},
		{"texture_create",L_texture_create},
		{"texture_delete",L_texture_delete},
		{"texture_resize",L_texture_resize},
		{"texture_size",L_texture_size},
		{"animation_create",L_animation_create},
		{"animation_delete",L_animation_delete},
		{"animation_play",L_animation_play},
		{"animation_stop",L_animation_stop},
		{"animation_rewind",L_animation_rewind},
		{"animation_add_clip",L_animation_add_clip},
		{"clip_create",L_clip_create},
		{"clip_delete",L_clip_delete},
		{"collider_create",L_collider_create},
		{"collider_delete",L_collider_delete},
		{"collider_set_active",L_collider_set_active},
		{"collider_add_force",L_collider_add_force},
		{"collider_reset_body_type",L_collider_reset_body_type},
		{"collider_is_collision_empty",L_collider_is_collision_empty},
		{"collider_get_collision_list_size",L_collider_get_collision_list_size},
		{"collider_set_density",L_collider_set_density},
		{"collider_get_speed",L_collider_get_speed},
		{"text_draw",L_text_draw},
		{"text_flush",L_text_flush},
		{"text_clear",L_text_clear},
		{"sound_create",L_sound_create},
		{"sound_delete",L_sound_delete},
		{"sound_stream_delete",L_sound_stream_delete},
		{"sound_turn",L_sound_turn},
		{"sound_set_loop",L_sound_set_loop},
		{"sound_pause",L_sound_pause},
		{"sound_stop",L_sound_stop},
		{"sound_stopforever",L_sound_stopforever},
		{"sound_rewind",L_sound_rewind},
		{"sound_remove",L_sound_remove},
		{"sound_clear_all",L_sound_clear_all},
		{"sound_stream_play",L_sound_stream_play},
		{"sound_stream_turn",L_sound_stream_turn},
		{"sound_stream_pause",L_sound_stream_pause},
		{"sound_stream_resume",L_sound_stream_resume},
		{"sound_play",L_sound_play
		},

		//////
		//UI
		/////
		{"ui_set_draw",L_ui_set_draw},
		{"ui_get_draw",L_ui_get_draw},
		{"base_panel_create",L_base_panel_create},
		{"base_panel_delete",L_base_panel_delete},
		{"base_panel_set_background",L_base_panel_set_background},
		{"base_panel_set_font",L_base_panel_set_font},
		{"base_panel_add_panel",L_base_panel_add_panel},
		{"base_panel_add_widget",L_base_panel_add_widget},
		{"base_panel_update",L_base_panel_update},
		{"button_create",L_button_create},
		{"button_delete",L_button_delete},
		{"button_init_button",L_button_init_button},
		{"button_update_button",L_button_update_button},
		{"button_set_position",L_button_set_position},
		{"button_set_mouse_state",L_button_set_mouse_state},
		{"button_update",L_button_update},
		{"button_set_size",L_button_set_size},
		{"button_set_callback_state",L_button_set_callback_state},
		{"button_get_callback_state",L_button_get_callback_state},
		{"picture_create",L_picture_create},
		{"picture_delete",L_picture_delete},
		{"picture_static_init",L_picture_static_init},
		{"picture_update",L_picture_update},
		{"picture_reset_picture",L_picture_reset_picture},
		{"picture_set_position",L_picture_set_position},
		{"picture_reshape",L_picture_reshape},
		{"scroller_create",L_scroller_create},
		{"scroller_delete",L_scroller_delete},
		{"scroller_update_button",L_scroller_update_button},
		{"scroller_update",L_scroller_update},
		{"scroller_set_position",L_scroller_set_position},
		{"scroller_init",L_scroller_init},
		{"scroller_set_mouse_state",L_scroller_set_mouse_state},
		{"scroller_reshape",L_scroller_reshape},
		{"scroller_set_current_val",L_scroller_set_current_val},
		{"scroller_set_controll",L_scroller_set_controll},
		{"scroller_get_current_val",L_scroller_get_current_val},
		{"touch_get_widget_by_name",L_touch_get_widget_by_name},
		{"switch_create",L_switch_create},
		{"switch_delete",L_switch_delete},
		{"switch_init_button",L_switch_init_button},
		{"switch_update_button",L_switch_update_button},
		{"switch_set_switch_state",L_switch_set_switch_state},
		{"switch_get_switch_state",L_switch_get_switch_state},
		{"touch_create",L_touch_create},
		{"touch_delete",L_touch_delete},
		{"touch_update",L_touch_update},
		{"touch_add_widget",L_touch_add_widget},
		{"touch_get_widget_by_name",L_touch_get_widget_by_name},


		//
		{"transform4x4",L_transform4X4},
		{"generate_atlas",L_generate_atlas},

		{NULL,NULL}
	};
	luaL_newlib(L, lib);
	return 1;
}

int L_init(lua_State* L)
{
	/*
	bool ret = false;
	if(g_res_manager->startup())
	{
	ret = true;
	}
	else
	{
		ret = false;
	}
	lua_pushboolean(L,1);
	*/
	return 1;
}

int L_create_window(lua_State* L)
{
	int n = lua_gettop(L);
	if(n<3)
	{
		printf("function need 3,there is %d\n",n);
		getchar();
		exit(0);
	}
	const char* name = lua_tostring(L,1);
	int width = (int)lua_tonumber(L,2);
	int height = (int)lua_tonumber(L,3);
	bool ret = g_app_manager->create_window(name,width,height);
	lua_pushboolean(L,ret);
	//return the number you want to return
	return 1;
}

int L_run(lua_State* L)
{
	g_app_manager->run();
	return 0;
}

static int L_XXX(lua_State* L)
{
	return 0;
}

/*
the __gc implementation only in c++
*/
static const luaL_Reg rect_dtor[] =
{
	{"__gc",L_delete_internal_rect},
	{NULL,NULL}
};

int L_create_internal_rect(lua_State* L)
{
	int n = lua_gettop(L);
	if(n<4)
	{
		printf("function need 4,there is %d\n",n);
		getchar();
		exit(0);
	}
	float x = lua_tonumber(L,1);
	float y = lua_tonumber(L,2);
	float w = lua_tonumber(L,3);
	float h = lua_tonumber(L,4);
	luaL_newmetatable(L, "wip.camera");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, rect_dtor, 0);
	int tsize = sizeof(RenderQuad*);
	RenderQuad **q = (RenderQuad**)lua_newuserdata(L,tsize);
	*q = new RenderQuad();
	(*q)->set_quickly(x,y,x,y+h,x+w,y+h,x+w,y);
	luaL_getmetatable(L,"wip.camera");
	lua_setmetatable(L,-2);
	//lua_pushlightuserdata(L,q);
	return 1;

}

int L_delete_internal_rect(lua_State* L)
{
	int n = lua_gettop(L);
	if(n<1)
	{
		printf("function need 1,there is %d\n",n);
		getchar();
		exit(0);
	}
	RenderQuad **q = (RenderQuad**)luaL_checkudata(L,1,"wip.camera1");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Rect %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_resize_internal_rect(lua_State* L)
{
	int n = lua_gettop(L);
	if(n<5)
	{
		printf("function need 4,there is %d\n",n);
		getchar();
		exit(0);
	}

	RenderQuad **q = (RenderQuad**)luaL_checkudata(L,1,"wip.camera1");
	float h = lua_tonumber(L,-1);
	float w = lua_tonumber(L,-2);
	float y = lua_tonumber(L,-3);
	float x = lua_tonumber(L,-4);
	(*q)->set_quickly(x,y,x,y+h,x+w,y+h,x+w,y);
	return 0;
}

int L_get_key(lua_State* L)
{
	_check_parameters(L,2);
	bool ret = false;
	std::string key = lua_tostring(L,1);
	int key_state = lua_tointeger(L,2);
	int _key = g_input_manager->input_map[key];
	//0 for pressed,1 for pressing,2 for released
	switch (key_state)
	{
	case 0:
		ret = Input::get_key_down(_key);
		break;
	case 1:
		ret = Input::get_key_pressed(_key);
		break;
	case 2:
		ret = Input::get_key_up(_key);
		break;
	default:
		printf("Wrong key state!\n");
		break;
	}
	lua_pushboolean(L,ret);
	return 1;
}

int L_get_sys_key(lua_State* L)
{
	_check_parameters(L,2);
	bool ret = false;
	std::string key = lua_tostring(L,1);
	int key_state = lua_tointeger(L,2);
	int _key = g_input_manager->input_map[key];
	//0 for pressed,1 for pressing,2 for released
	switch (key_state)
	{
	case 0:
		ret = Input::get_sys_key_down(_key);
		break;
	case 1:
		ret = Input::get_sys_key_pressed(_key);
		break;
	case 2:
		ret = Input::get_sys_key_up(_key);
		break;
	default:
		printf("Wrong key state!\n");
		break;
	}
	lua_pushboolean(L,ret);
	return 1;
}

int L_get_mouse_position(lua_State* L)
{
	_check_parameters(L,0);
	int x = Input::get_mouse_x();
	int y = Input::get_mouse_y();
	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	return 2;
}

int L_mouse_move(lua_State* L)
{
	bool ret = Input::is_move();
	lua_pushboolean(L,ret);
	return 1;
}

int L_generate_id(lua_State* L)
{
	_check_parameters(L,1);
	long ret = lua_tonumber(L,1);
	lua_pushnumber(L,ret);
	return 1;
}

static const luaL_Reg sprite_dtor[] =
{
	{"__gc",L_delete_sprite},
	{NULL,NULL}
};



int L_create_sprite(lua_State* L)
{
	_check_parameters(L,2);
	float w = lua_tonumber(L,1);
	float h = lua_tonumber(L,2);
	luaL_newmetatable(L, "wip.sprite");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	//luaL_setfuncs(L, sprite_dtor, 0);
	int tsize = sizeof(WIPSprite*);
	WIPSprite **q = (WIPSprite**)lua_newuserdata(L,tsize);
	*q = WIPSprite::create(w,h);
	//(*q)->anchor_x = 1.23532;
	luaL_getmetatable(L,"wip.sprite");
	lua_setmetatable(L,-2);
	return 1;

}



int L_delete_sprite(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Sprite %x has been deleted",(*q)->get_tag());
#endif
		delete *q;
	}
	return 0;
}

int L_sprite_get_position(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	lua_pushnumber(L,(*q)->world_x);
	lua_pushnumber(L,(*q)->world_y);
	return 2;

}

int L_sprite_set_position(lua_State* L)
{
	_check_parameters(L,3);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->world_y = lua_tonumber(L,-1);
	(*q)->world_x = lua_tonumber(L,-2);
	return 0;
}

int L_sprite_get_rotation(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	lua_pushnumber(L,(*q)->rotation);
	return 1;
}

int L_sprite_rotate(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->rotation += lua_tonumber(L,-1);
	return 0;
}

int L_sprite_rotate_by(lua_State* L)
{
	g_logger->debug_print(WIP_WARNING,"L_sprite_rotate_by is not in use!");
	return 0;
}

int L_sprite_rotate2(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->rotation = lua_tonumber(L,-1);
	return 0;
}

int L_sprite_rotate2_by(lua_State* L)
{
	g_logger->debug_print(WIP_WARNING,"L_sprite_rotate2_by is not in use!");
	return 0;
}

int L_sprite_translate(lua_State* L)
{
	_check_parameters(L,3);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	f32 a =  lua_tonumber(L,-1);
	f32 b =  lua_tonumber(L,-2);
	(*q)->world_y += a;
	(*q)->world_x += b;
	return 0;
}

int L_sprite_scale(lua_State* L)
{
	_check_parameters(L,3);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->scale_y *= lua_tonumber(L,-1);
	(*q)->scale_x *= lua_tonumber(L,-2);
	return 0;
}

int L_sprite_scale_to(lua_State* L)
{
	_check_parameters(L,3);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->scale_y = lua_tonumber(L,-1);
	(*q)->scale_x = lua_tonumber(L,-2);
	return 0;
}

int L_sprite_get_forward(lua_State* L)
{
	g_logger->debug_print(WIP_WARNING,"L_sprite_get_forward is not in use!");
	return 0;
}

int L_sprite_get_local_position(lua_State* L)
{
	g_logger->debug_print(WIP_WARNING,"L_sprite_get_local_position is not in use!");
	return 0;
}

int L_sprite_get_scale(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	lua_pushnumber(L,(*q)->scale_x);
	lua_pushnumber(L,(*q)->scale_y);
	return 2;
}

int L_sprite_get_anchor(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	lua_pushnumber(L,(*q)->get_copy_mesh()->anchor.x);
	lua_pushnumber(L,(*q)->get_copy_mesh()->anchor.y);
	return 2;
}

int L_sprite_set_anchor(lua_State* L)
{
	_check_parameters(L,3);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	f32 y = lua_tonumber(L,-1);
	f32 x = lua_tonumber(L,-2);
	(*q)->set_anchor(x,y);
	return 0;
}

int L_sprite_get_zorder(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	lua_pushnumber(L,(*q)->z_order);
	return 1;
}

int L_sprite_set_zorder(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite **q = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	(*q)->z_order = lua_tonumber(L,-1);
	return 0;
}
/////////////////////////////////////////////////////////////////////////
//Scene
/////////////////////////////////////////////////////////////////////////
#include "Scene.h"
static const luaL_Reg scene_dtor[] =
{
	{"__gc",L_scene_delete},
	{NULL,NULL}
};
//param scene_ptr
int L_scene_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPScene **q = (WIPScene**)luaL_checkudata(L,1,"wip.scene");

	//L_scene_unload(L);
	//unload
	//(*q)->delete_all_object();
	//we don't need to call the dctor because the lua __gc will call automatically

	g_app_manager->remove_scene(*q);
	
	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Scene %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

//return scene_ptr
int L_scene_create(lua_State* L)
{
	_check_parameters(L,0);
	luaL_newmetatable(L, "wip.scene");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, scene_dtor, 0);
	int tsize = sizeof(WIPScene*);
	WIPScene **q = (WIPScene**)lua_newuserdata(L,tsize);
	*q = new WIPScene();
	luaL_getmetatable(L,"wip.scene");
	lua_setmetatable(L,-2);

	g_app_manager->add_scene(*q);

	return 1;
}

//add go to cpp scene object layer list
int L_scene_add_object(lua_State* L)
{
	_check_parameters(L,2);
	WIPScene** scene = (WIPScene**)luaL_checkudata(L,-2,"wip.scene");
	WIPSprite** sprite = (WIPSprite**)luaL_checkudata(L,-1,"wip.sprite");
	if(*scene&&*sprite)
	{
		(*scene)->add_object(*sprite);
	}
	return 0;
}

//param scene_ptr unload the scene resources
//this function will noly explicit call in lua,never call it when delete its container.
int L_scene_unload(lua_State* L)
{
	_check_parameters(L,1);
	WIPScene** scene = (WIPScene**)luaL_checkudata(L,1,"wip.scene");
	(*scene)->delete_all_object();
	return 0;
}

#include "./flyUI/ActiveDrawableRect.h"
#include "./flyUI/ButtonWidget.h"
#include "UILayer.h"
int L_scene_add_ui(lua_State* L)
{
	_check_parameters(L,2);
	WIPScene* scene = *(WIPScene**)luaL_checkudata(L,1,"wip.scene");
	//(ButtonWidget*)luaL_checkudata(L,1,"wip.ui.widget");
	ActiveDrawableRect* ui = *(ActiveDrawableRect**)lua_touserdata(L,-1);
	scene->get_ui_layer()->add_ui(ui);
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//Sprite
/////////////////////////////////////////////////////////////////////////
#include "Animation.h"
//param LuaTexture return bool 
int L_sprite_set_sataic_texture(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite** s = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	WIPTexture** t = (WIPTexture**)luaL_checkudata(L,-1,"wip.texture");
	(*s)->set_texture((*t));
	return 1;
}

int L_sprite_attach_mesh(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite* s = *(WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	WIPMesh* t = *(WIPMesh**)luaL_checkudata(L,-1,"wip.mesh");
	s->reset_origin_mesh(t);
	return 0;
}

int L_sprite_attach_animation(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite* s = *(WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	WIPAnimation* t = *(WIPAnimation**)luaL_checkudata(L,-1,"wip.animation");
	s->reset_animaton(t);
	return 0;
}

#include "Collider.h"
int L_sprite_attach_collider(lua_State* L)
{
	_check_parameters(L,2);
	WIPSprite* s = *(WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	WIPCollider* t = *(WIPCollider**)luaL_checkudata(L,-1,"wip.collider");
	s->reset_collider(t);
	return 0;
}
/////////////////////////////////////////////////////////////////////////
//Mesh
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg mesh_dtor[]=
{
	{"__gc",L_mesh_delete},
	{0,0}
};

//param w,h return mesh_ptr
int L_mesh_create(lua_State* L)
{
	_check_parameters(L,2);
	f32 h = lua_tonumber(L,-1);
	f32 w = lua_tonumber(L,-2);
	luaL_newmetatable(L, "wip.mesh");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, scene_dtor, 0);
	int tsize = sizeof(WIPMesh*);
	WIPMesh **q = (WIPMesh**)lua_newuserdata(L,tsize);
	*q = new WIPMesh(w,h);
	luaL_getmetatable(L,"wip.mesh");
	lua_setmetatable(L,-2);


	return 1;
}

int L_mesh_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPMesh **q = (WIPMesh**)luaL_checkudata(L,1,"wip.mesh");
	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Mesh %x has been deleted",(*q));
#endif
		delete (*q);
	}
	return 0;
}

//param percent cx cy
int L_mesh_set_anchor(lua_State* L)
{
	_check_parameters(L,3);
	f32 py = lua_tonumber(L,-1);
	f32 px = lua_tonumber(L,-2);
	WIPMesh **q = (WIPMesh**)luaL_checkudata(L,1,"wip.mesh");
	//something wrong ,be sure to check cx,cy 0,0
	(*q)->set_anchor(px,py);
	return 0;
}

//return ax,ay
int L_mesh_get_anchor(lua_State* L)
{
	_check_parameters(L,1);

	return 2;
}

int L_mesh_set_size(lua_State* L)
{
	_check_parameters(L,3);

	return 0;
}

int L_mesh_get_size(lua_State* L)
{
	_check_parameters(L,1);
	WIPMesh **q = (WIPMesh**)luaL_checkudata(L,1,"wip.mesh");
	//lua_pushnumber(L,(*q)->

	return 2;
}

/////////////////////////////////////////////////////////////////////////
//Camera
/////////////////////////////////////////////////////////////////////////
#include "Camera.h"
static const luaL_Reg camera_dtor[] =
{
	{"__gc",L_camera_delete},
	{NULL,NULL}
};
//create a cpp camera and return its pointer
//param world_w,world_h
int L_camera_create(lua_State* L)
{
	_check_parameters(L,2);
	luaL_newmetatable(L, "wip.camera");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, camera_dtor, 0);
	int tsize = sizeof(WIPScene*);
	WIPCamera **q = (WIPCamera**)lua_newuserdata(L,tsize);
	float w = lua_tonumber(L,1);
	float h = lua_tonumber(L,2);
	*q = new WIPCamera(w,h);
	luaL_getmetatable(L,"wip.camera");
	lua_setmetatable(L,-2);

	//g_app_manager->add_camera(*q);
	return 1;
}

int L_camera_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");

	g_app_manager->remove_camera(*q);

	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Camera %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_camera_move_world(lua_State* L)
{
	_check_parameters(L,3);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->world_x += x;
	(*q)->world_y += y;
	return 0;
}

int L_camera_move_world_to(lua_State* L)
{
	_check_parameters(L,3);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->world_x = x;
	(*q)->world_y = y;
	return 0;
}

int L_camera_get_world(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	f32 x = (*q)->world_x;
	f32 y = (*q)->world_y;
	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	return 2;
}

int L_camera_get_world_x(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	f32 x = (*q)->world_x;
	lua_pushnumber(L,x);
	return 1;
}

int L_camera_get_world_y(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	f32 y = (*q)->world_y;
	lua_pushnumber(L,y);
	return 1;
}

int L_camera_get_world_width(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	f32 y = (*q)->world_w;
	lua_pushnumber(L,y);
	return 1;
}

int L_camera_get_world_height(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	f32 y = (*q)->world_h;
	lua_pushnumber(L,y);
	return 1;
}

int L_camera_move_screen(lua_State* L)
{
	_check_parameters(L,3);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->screen_x += x;
	(*q)->screen_y += y;
	return 0;
}

int L_camera_get_screen_x(lua_State* L)
{
	_check_parameters(L,1);

	return 1;
}

int L_camera_get_screen_y(lua_State* L)
{
	_check_parameters(L,1);

	return 1;
}

int L_camera_get_screen_width(lua_State* L)
{
	_check_parameters(L,1);

	return 1;
}

int L_camera_get_screen_height(lua_State* L)
{
	_check_parameters(L,1);

	return 1;
}

int L_camera_move_screen_to(lua_State* L)
{
	_check_parameters(L,2);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->screen_x = x;
	(*q)->screen_y = y;
	return 0;
}

int L_camera_copy_from(lua_State* L)
{
	_check_parameters(L,2);

	return 0;
}

int L_camera_set_active(lua_State* L)
{
	_check_parameters(L,2);

	return 0;
}

int L_camera_get_active(lua_State* L)
{
	_check_parameters(L,1);

	return 1;
}

int L_camera_set_screen_size(lua_State* L)
{
	_check_parameters(L,3);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->screen_w = x;
	(*q)->screen_h = y;
	return 0;
}

int L_camera_set_world_size(lua_State* L)
{
	_check_parameters(L,3);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	i32 y = lua_tointeger(L,-1);
	i32 x = lua_tointeger(L,-2);
	(*q)->world_w = x;
	(*q)->world_h = y;
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//System
/////////////////////////////////////////////////////////////////////////

int L_system_get_dt(lua_State* L)
{
	_check_parameters(L,0);
	lua_pushnumber(L,g_app_manager->get_dt());
	return 1;
}

#include "Renderer.h"
int L_system_draw_rect( lua_State* L )
{
	_check_parameters(L,5);
	i32 x = lua_tointeger(L,1);
	i32 y = lua_tointeger(L,2);
	i32 w = lua_tointeger(L,3);
	i32 h = lua_tointeger(L,4);
	bool b = lua_toboolean(L,5);
	RenderQuad q;
	q.set_quickly(
		x,y,
		x,y+h,
		x+w,y+h,
		x+w,y
		);
	g_renderer->draw_box(q,b);

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//App
/////////////////////////////////////////////////////////////////////////
int L_app_add_camera(lua_State* L)
{
	_check_parameters(L,1);
	WIPCamera **q = (WIPCamera**)luaL_checkudata(L,1,"wip.camera");
	
	g_app_manager->add_camera(*q);
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//Texture
//Texture don't manage memory self you must delete it manually either in c++ or lua
/////////////////////////////////////////////////////////////////////////
#include "Texture.h"
#include "TextManager.h"
static const luaL_Reg texture_dtor[] =
{
	//{"__gc",L_texture_delete},
	{NULL,NULL},
};
int L_texture_create(lua_State* L)
{
	_check_parameters(L,3);
	string path = lua_tostring(L,-3);
	luaL_newmetatable(L, "wip.texture");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, texture_dtor, 0);
	int tsize = sizeof(WIPTexture*);
	WIPTexture **q = (WIPTexture**)lua_newuserdata(L,tsize);

	*q = new WIPTexture(path.c_str());
	luaL_getmetatable(L,"wip.texture");
	lua_setmetatable(L,-2);
	return 1;
}

int L_texture_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPTexture **q = (WIPTexture**)luaL_checkudata(L,1,"wip.texture");

	
	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"Texture %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_texture_resize(lua_State* L)
{
	_check_parameters(L,3);

	return 0;
}

int L_texture_size(lua_State* L)
{
	_check_parameters(L,1);

	return 2;
}

/////////////////////////////////////////////////////////////////////////
//Animation
/////////////////////////////////////////////////////////////////////////
#include "Animation.h"
#include "AnimationClip.h"
int L_animation_create(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **s = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	luaL_newmetatable(L, "wip.animation");
	lua_pushvalue(L, -1);
	int tsize = sizeof(WIPAnimation*);
	WIPAnimation **q = (WIPAnimation**)lua_newuserdata(L,tsize);
	*q = new WIPAnimation((*s)->get_sprite_frame());
	luaL_getmetatable(L,"wip.animation");
	lua_setmetatable(L,-2);
	return 1;
}

int L_animation_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPAnimation **q = (WIPAnimation**)luaL_checkudata(L,1,"wip.animation");


	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"animation %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_animation_play(lua_State* L)
{
	_check_parameters(L,2);
	WIPAnimation* s = *(WIPAnimation**)luaL_checkudata(L,1,"wip.animation");
	WIPAnimationClip* t = *(WIPAnimationClip**)luaL_checkudata(L,-1,"wip.animaiton_clip");
	s->play(t);
	return 0;
}

int L_animation_stop(lua_State* L)
{
	_check_parameters(L,2);

	return 0;
}

int L_animation_rewind(lua_State* L)
{
	_check_parameters(L,2);

	return 0;
}

int L_animation_add_clip(lua_State* L)
{
	_check_parameters(L,3);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//Animation Clip
/////////////////////////////////////////////////////////////////////////
//not use
static const luaL_Reg clip_dtor[] =
{
	{"__gc",L_clip_delete},
	{NULL,NULL},
};
//param clip name/atlas file name/texture (Texture) if nil call create_with_atlas(const char* name,const char* atlas_file)
int L_clip_create(lua_State* L)
{
	_check_parameters(L,3);
	string name = lua_tostring(L,1);
	string path = lua_tostring(L,2);
	WIPAnimationClip* ret;
	if(lua_isnil(L,3))
		ret = WIPAnimationClip::create_with_atlas(name.c_str(),path.c_str());
	else
	{
		WIPTexture* t = *(WIPTexture**)luaL_checkudata(L,-1,"wip.texture");
		ret = WIPAnimationClip::create_with_atlas(name.c_str(),path.c_str(),t);
	}
	luaL_newmetatable(L, "wip.animaiton_clip");
	lua_pushvalue(L, -1);
	int tsize = sizeof(WIPAnimationClip*);
	WIPAnimationClip **q = (WIPAnimationClip**)lua_newuserdata(L,tsize);
	*q = ret;
	luaL_getmetatable(L,"wip.animaiton_clip");
	lua_setmetatable(L,-2);
	return 1;
}

int L_clip_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPAnimationClip **q = (WIPAnimationClip**)luaL_checkudata(L,1,"wip.animation_clip");


	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"animationClip %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//Collider
//NO GC NOW!!!
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg collider_dtor[] =
{
	{"__gc",L_collider_delete},
	{NULL,NULL}
};
//param sprite_ptr
int L_collider_create(lua_State* L)
{
	_check_parameters(L,1);
	WIPSprite **s = (WIPSprite**)luaL_checkudata(L,1,"wip.sprite");
	luaL_newmetatable(L, "wip.collider");
	lua_pushvalue(L, -1);
	//lua_setfield(L, -2, "__index");
	//luaL_setfuncs(L, collider_dtor, 0);
	int tsize = sizeof(WIPCollider*);
	WIPCollider **q = (WIPCollider**)lua_newuserdata(L,tsize);
	*q = WIPCollider::create_collider((*s)->get_copy_mesh());
	luaL_getmetatable(L,"wip.collider");
	lua_setmetatable(L,-2);
	return 1;
}

int L_collider_delete(lua_State* L)
{
	_check_parameters(L,1);
	WIPCollider **q = (WIPCollider**)luaL_checkudata(L,1,"wip.collider");


	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"collider %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_collider_set_active(lua_State* L)
{
	_check_parameters(L,2);
	WIPCollider **q = (WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	bool b = lua_toboolean(L,-1);

	(*q)->set_active(b);

	return 0;
}

int L_collider_add_force(lua_State* L)
{
	_check_parameters(L,3);
	WIPCollider **q = (WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	f32 y = lua_tonumber(L,-1);
	f32 x = lua_tonumber(L,-2);
#ifdef _DEBUG
		//g_logger->debug_print(WIP_INFO,"collider %x added a force:%0.2f,%0.2f",(*q),x,y);
#endif
	(*q)->add_force(x,y);

	return 0;
}

int L_collider_reset_body_type(lua_State* L)
{
	_check_parameters(L,2);
	WIPCollider *q = *(WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	int c = (int)lua_tonumber(L,-1);

	q->reset_body_type((WIPCollider::_CollisionTypes)c);

	return 0;
}

int L_collider_is_collision_empty(lua_State* L)
{
	_check_parameters(L,1);
	WIPCollider *q = *(WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	bool l = q->is_collision_list_empty();
	lua_pushboolean(L,l);
	return 1;
}

int L_collider_get_collision_list_size(lua_State* L)
{
	_check_parameters(L,1);
	WIPCollider *q = *(WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	int i = q->get_collision_list_size();
	lua_pushnumber(L,i);
	return 1;
}

int L_collider_set_density(lua_State* L)
{
	_check_parameters(L,2);
	WIPCollider *q = *(WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	f32 f = lua_tonumber(L,-1);

	q->set_density(f);

	return 0;
}

//return x,y
int L_collider_get_speed(lua_State* L)
{
	_check_parameters(L,1);
	WIPCollider *q = *(WIPCollider**)luaL_checkudata(L,1,"wip.collider");
	lua_pushnumber(L,q->get_speed_x());
	lua_pushnumber(L,q->get_speed_y());
	return 2;
}
//////////////////////////////////////////////////////////////////////////////////
//Frame Animation Tools
//////////////////////////////////////////////////////////////////////////////////
#include "Renderer.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "../Utilities/WIPIniHelper.h"
#include "ExtraTool.h"

int L_transform4X4(lua_State* L)
{
	_check_parameters(L,1);
	RenderQuad pos;
	RenderQuad uv;

	std::string content1 = "[head]\ntexture = ";//+name
	std::string content2 = "\ntotal_frame = 4\n\n[1]\n\
lb_x = 0 \n\
lb_y = 0 \n\
lt_x = 0 \n\
lt_y = 1 \n\
rt_x = 0.25 \n\
rt_y = 1 \n\
rb_x = 0.25 \n\
rb_y = 0 \n\
\n\
[2]\n\
lb_x = 0.25\n\
lb_y = 0\n\
lt_x = 0.25\n\
lt_y = 1\n\
rt_x = 0.5\n\
rt_y = 1\n\
rb_x = 0.5\n\
rb_y = 0\n\
\n\
[3]\n\
lb_x = 0.5\n\
lb_y = 0\n\
lt_x = 0.5\n\
lt_y = 1\n\
rt_x = 0.75\n\
rt_y = 1\n\
rb_x = 0.75\n\
rb_y = 0\n\
\n\
[4]\n\
lb_x = 0.75\n\
lb_y = 0\n\
lt_x = 0.75\n\
lt_y = 1\n\
rt_x = 1\n\
rt_y = 1\n\
rb_x = 1\n\
rb_y = 0\n";

	std::string c = "";

	std::string  path = lua_tostring(L,-1);
	WIPTexture* tex = new WIPTexture(path.c_str());
	
	i32 w = tex->get_width();i32 sw = w/4;
	i32 h = tex->get_height();i32 sh = h/4;

	pos.set_quickly(0,sh,0,0,w,0,w,sh);
	uv.set_quickly(0,0,0,0.25,1,0.25,1,0);

	WIPRenderTexture* rt = WIPRenderTexture::create(w,sh);
	
	rt->begin();
	rt->clear();

	g_renderer->render(tex,&pos,&uv);


	rt->end();
	uv.set_quickly(0,0.25,0,0.5,1,0.5,1,0.25);
	WIPExtraTool::save_png(rt,"../Resources/out1.png");
	c = content1+"out1.png"+content2;
	WIPExtraTool::save_ini(c.c_str(),"../Resources/out1.clip");

	rt->begin();
	rt->clear();

	g_renderer->render(tex,&pos,&uv);


	rt->end();
	uv.set_quickly(0,0.5,0,0.75,1,0.75,1,0.5);
	WIPExtraTool::save_png(rt,"../Resources/out2.png");
	c = content1+"out2.png"+content2;
	WIPExtraTool::save_ini(c.c_str(),"../Resources/out2.clip");
	rt->begin();
	rt->clear();

	g_renderer->render(tex,&pos,&uv);


	rt->end();
	uv.set_quickly(0,0.75,0,1,1,1,1,0.75);
	WIPExtraTool::save_png(rt,"../Resources/out3.png");
	c = content1+"out3.png"+content2;
	WIPExtraTool::save_ini(c.c_str(),"../Resources/out3.clip");
	rt->begin();
	rt->clear();

	g_renderer->render(tex,&pos,&uv);


	rt->end();

	WIPExtraTool::save_png(rt,"../Resources/out4.png");
	c = content1+"out4.png"+content2;
	WIPExtraTool::save_ini(c.c_str(),"../Resources/out4.clip");

	delete rt;
	delete tex;
	return 0;
}

int L_generate_atlas(lua_State* L)
{
	std::string  path = lua_tostring(L,-1);

	return 0;
}

#include "TextCanvas.h"
//#include "AppManager.h"
#include "ft3.h"
//////////////////////////////////////////////////////////////////////////
//Text
//////////////////////////////////////////////////////////////////////////
int L_text_draw(lua_State* L)
{
	_check_parameters(L,3);
	int y = lua_tonumber(L,-1);
	int x = lua_tonumber(L,-2);
	string t = lua_tostring(L,-3);
	//std::cout<<t<<std::endl;
	g_app_manager->text_cav->draw_text(t,x,y);
	return 0;
}

int L_text_flush(lua_State* L)
{
	g_app_manager->text_cav->update();
	return 0;
}

int L_text_clear(lua_State* L)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//sound
//////////////////////////////////////////////////////////////////////////
#include "Sound.h"
#include "SoundPlayer.h"
#include "OggStream.h"

static luaL_Reg sound_dtor[] = 
{
	{"__gc",L_sound_delete},
	{NULL,NULL},
};


int L_sound_create(lua_State* L)
{
	_check_parameters(L,2);
	string type = lua_tostring(L,-1);
	string path = lua_tostring(L,-2);
	string luastring = "";
	int tsize;
	if(type=="stream")
	{
		sound_dtor[0].func = L_sound_stream_delete;
		luastring = "wip.stream";
		tsize = sizeof(WIPSound*); 
	}
	else
	{
		sound_dtor[0].func = L_sound_delete;
		luastring = "wip.sound";
		tsize = sizeof(OggStream*);
	}
	luaL_newmetatable(L,luastring.data());
	lua_pushvalue(L,-1);
	lua_setfield(L,-2,"__index");
	luaL_setfuncs(L,sound_dtor,0);
	if (type=="stream")
	{
		OggStream **q = (OggStream**)lua_newuserdata(L,tsize);
		*q = new OggStream();
		(*q)->open(path);
		luaL_getmetatable(L,"wip.stream");
		lua_setmetatable(L,-2);
	}
	else
	{
		WIPSound **q = (WIPSound**)lua_newuserdata(L,tsize);
		*q = new WIPSound(path.data(),SoundInGameTypes::WIP_SE);
		luaL_getmetatable(L,"wip.sound");
		lua_setmetatable(L,-2);
	}
	return 1;
}

int L_sound_delete(lua_State* L)
{
	WIPSound **q = (WIPSound**)luaL_checkudata(L,1,"wip.sound");


	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"WIPSound %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_sound_stream_delete(lua_State* L)
{
	OggStream **q = (OggStream**)luaL_checkudata(L,1,"wip.stream");

	(*q)->release();
	if(q&&*q)
	{
#ifdef _DEBUG
		g_logger->debug_log(WIP_INFO,"OggStream %x has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_sound_turn(lua_State* L)
{
	_check_parameters(L,2);
	int v = lua_tonumber(L,-1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->set_volume(q,v);
	return 0;
}


int L_sound_set_loop(lua_State* L)
{
	_check_parameters(L,2);
	bool v = lua_toboolean(L,-1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->set_loop(q,v);
	return 0;
}

int L_sound_play(lua_State* L)
{
	_check_parameters(L,2);
	int v = lua_tointeger(L,-1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->set_volume(q,v);
	g_sound_palyer->play(q);
	return 0;
}

int L_sound_stream_play(lua_State* L)
{
	_check_parameters(L,2);
	bool v = lua_toboolean(L,-1);
	OggStream *q = *(OggStream**)luaL_checkudata(L,1,"wip.stream");
	g_sound_palyer->play_stream(q,v);
	return 0;
}

int L_sound_pause(lua_State* L)
{
	_check_parameters(L,1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->pause(q);
	return 0;
}

int L_sound_stop(lua_State* L)
{
	_check_parameters(L,1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->stop(q);
	return 0;
}

int L_sound_stopforever(lua_State* L)
{
	_check_parameters(L,1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->stop_forever(q);
	return 0;
}

int L_sound_rewind(lua_State* L)
{
	_check_parameters(L,1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->rewind(q);
	return 0;
}

int L_sound_remove(lua_State* L)
{
	_check_parameters(L,1);
	WIPSound *q = *(WIPSound**)luaL_checkudata(L,1,"wip.sound");
	g_sound_palyer->delete_sound(q);
	return 0;
}

int L_sound_clear_all(lua_State* L)
{
	_check_parameters(L,0);
	g_sound_palyer->clear_all_sounds();
	return 0;
}

int L_sound_stream_turn(lua_State* L)
{
	_check_parameters(L,2);
	float v = lua_tonumber(L,-1);
	OggStream *q = *(OggStream**)luaL_checkudata(L,1,"wip.stream");
	q->setGain(v);
	return 0;
}

int L_sound_stream_pause(lua_State* L)
{
	_check_parameters(L,1);
	OggStream *q = *(OggStream**)luaL_checkudata(L,1,"wip.stream");
	q->pause();
	return 0;
}

int L_sound_stream_resume(lua_State* L)
{
	_check_parameters(L,1);
	OggStream *q = *(OggStream**)luaL_checkudata(L,1,"wip.stream");
	q->resume();
	return 0;
}