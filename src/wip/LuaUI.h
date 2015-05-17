#pragma once
#include "LuaAPI.h"

/////////////////////////////////////////////////////////////////////////
//NOTICE :need gc
/////////////////////////////////////////////////////////////////////////
int L_ui_set_draw(lua_State* L);
int L_ui_get_draw(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//BasePanel
/////////////////////////////////////////////////////////////////////////
int L_base_panel_create(lua_State* L);
int L_base_panel_delete(lua_State* L);
int L_base_panel_set_background(lua_State* L);
int L_base_panel_set_font(lua_State* L);
int L_base_panel_add_panel(lua_State* L);
int L_base_panel_add_widget(lua_State* L);
int L_base_panel_update(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//ButtonWidget
/////////////////////////////////////////////////////////////////////////
int L_button_create(lua_State* L);
int L_button_delete(lua_State* L);
//the last parameter set to null,because callback has been moved to Lua for data driven
int L_button_init_button(lua_State* L);
int L_button_update_button(lua_State* L);
int L_button_set_position(lua_State* L);
int L_button_set_mouse_state(lua_State* L);
int L_button_update(lua_State* L);
int L_button_set_size(lua_State* L);
//set if the callback should be called
int L_button_set_callback_state(lua_State* L);
int L_button_get_callback_state(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//PictureWidget
/////////////////////////////////////////////////////////////////////////
int L_picture_create(lua_State* L);
int L_picture_delete(lua_State* L);
int L_picture_static_init(lua_State* L);
int L_picture_update(lua_State* L);
int L_picture_reset_picture(lua_State* L);
int L_picture_set_position(lua_State* L);
int L_picture_reshape(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//ScrollerWidget
/////////////////////////////////////////////////////////////////////////
int L_scroller_create(lua_State* L);
int L_scroller_delete(lua_State* L);
int L_scroller_update_button(lua_State* L);
int L_scroller_update(lua_State* L);
int L_scroller_set_position(lua_State* L);
//there is two default parameters,if set them to "",they will be default
//return if this function has been succeed
int L_scroller_init(lua_State* L);
int L_scroller_set_mouse_state(lua_State* L);
int L_scroller_reshape(lua_State* L);
int L_scroller_set_current_val(lua_State* L);
int L_scroller_set_controll(lua_State* L);
int L_scroller_get_current_val(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//StaticText
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//SwitchWidget
/////////////////////////////////////////////////////////////////////////
int L_switch_create(lua_State* L);
int L_switch_delete(lua_State* L);
int L_switch_init_button(lua_State* L);
int L_switch_update_button(lua_State* L);
int L_switch_set_switch_state(lua_State* L);
int L_switch_get_switch_state(lua_State* L);
/////////////////////////////////////////////////////////////////////////
//TouchWidget
/////////////////////////////////////////////////////////////////////////
int L_touch_create(lua_State* L);
int L_touch_delete(lua_State* L);
int L_touch_update(lua_State* L);
int L_touch_add_widget(lua_State* L);
int L_touch_get_widget_by_name(lua_State* L);
