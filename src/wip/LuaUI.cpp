#include "LuaUI.h"
#include "Logger.h"
#include <string>
#include "flyUI/BasePanel.h"
#include "flyUI/BaseWidget.h"
#include "flyUI/ButtonWidget.h"
#include "flyUI/PictureWidget.h"
#include "flyUI/ScrollerWidget.h"
#include "flyUI/SwitchWidget.h"
#include "flyUI/TouchWidget.h"



/////////////////////////////////////////////////////////////////////////
//NOTICE :need gc
/////////////////////////////////////////////////////////////////////////
int L_ui_set_draw(lua_State* L)
{
	_check_parameters(L,2);
	ActiveDrawableRect* rec = (ActiveDrawableRect*)lua_touserdata(L,1);
	rec->bdraw = lua_toboolean(L,-1);
	return 0;
}

int L_ui_get_draw(lua_State* L)
{
	_check_parameters(L,1);
	ActiveDrawableRect* rec = (ActiveDrawableRect*)lua_touserdata(L,1);
	lua_pushboolean(L,rec->bdraw);
	return 1;

}
/////////////////////////////////////////////////////////////////////////
//BasePanel
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg base_panel_dtor[] =
{
	{"__gc",L_base_panel_delete},
	{NULL,NULL}
};

int L_base_panel_create(lua_State* L)
{
	_check_parameters(L,4);
	int x = lua_tointeger(L,1);
	int y = lua_tointeger(L,2);
	int w = lua_tointeger(L,3);
	int h = lua_tointeger(L,4);
	luaL_newmetatable(L, "wip.ui.base_panel");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, base_panel_dtor, 0);
	int tsize = sizeof(BasePanel*);
	BasePanel **q = (BasePanel**)lua_newuserdata(L,tsize);
	*q = new BasePanel(x,y,w,h);
	luaL_getmetatable(L,"wip.ui.base_panel");
	lua_setmetatable(L,-2);
	return 1;
}

int L_base_panel_delete(lua_State* L)
{
	_check_parameters(L,1);
	BasePanel **q = (BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"BasePanel %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_base_panel_set_background(lua_State* L)
{
	_check_parameters(L,2);
	BasePanel *q = *(BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	std::string path = lua_tostring(L,-1);

	q->set_background(path.c_str());

	return 0;
}

int L_base_panel_set_font(lua_State* L)
{
	_check_parameters(L,2);
	BasePanel *q = *(BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	std::string path = lua_tostring(L,-1);

	q->set_font(path.c_str());

	return 0;
}

int L_base_panel_add_panel(lua_State* L)
{
	_check_parameters(L,2);
	BasePanel *q = *(BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	BasePanel *p = *(BasePanel**)luaL_checkudata(L,-1,"wip.ui.base_panel");

	q->add_panel(p);
	return 0;
}

int L_base_panel_add_widget(lua_State* L)
{
	_check_parameters(L,2);
	BasePanel *q = *(BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	BaseWidget *p = *(BaseWidget**)luaL_checkudata(L,-1,"wip.ui.widget");
	q->add_widget(p);
	return 0;
}

int L_base_panel_update(lua_State* L)
{
	_check_parameters(L,2);
	BasePanel *q = *(BasePanel**)luaL_checkudata(L,1,"wip.ui.base_panel");
	float dt = lua_tonumber(L,-1);
	q->update(dt);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//ButtonWidget
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg button_dtor[] =
{
	{"__gc",L_button_delete},
	{NULL,NULL}
};

int L_button_create(lua_State* L)
{
	_check_parameters(L,0);
	luaL_newmetatable(L, "wip.ui.buttonwidget");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, button_dtor, 0);
	int tsize = sizeof(ButtonWidget*);
	ButtonWidget **q = (ButtonWidget**)lua_newuserdata(L,tsize);
	*q = new ButtonWidget();
	luaL_getmetatable(L,"wip.ui.buttonwidget");
	lua_setmetatable(L,-2);
	printf("button:%d\n",*q);
	return 1;
}

int L_button_delete(lua_State* L)
{
	_check_parameters(L,1);
	ButtonWidget **q = (ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"ButtonWidget %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

//the last parameter set to null,because callback has been moved to Lua for data driven
int L_button_init_button(lua_State* L)
{
	_check_parameters(L,5);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	std::string normal = lua_tostring(L,-2);
	std::string move = lua_tostring(L,-3);
	std::string down = lua_tostring(L,-4);
	q->init_button(down,move,normal,NULL);
	return 0;
}

int L_button_update_button(lua_State* L)
{
	_check_parameters(L,3);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	q->update_button(x,y);
	return 0;
}

int L_button_set_position(lua_State* L)
{
	_check_parameters(L,3);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	q->set_position(x,y);
	return 0;
}

int L_button_set_mouse_state(lua_State* L)
{
	_check_parameters(L,4);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	int y = lua_tointeger(L,-2);
	int x = lua_tointeger(L,-3);
	int state = lua_tointeger(L,-1);
	q->set_mouse_state(x,y,state);
	return 0;
}

int L_button_update(lua_State* L)
{
	_check_parameters(L,2);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	float dt = lua_tonumber(L,-1);
	q->update(dt);
	return 0;
}

int L_button_set_size(lua_State* L)
{
	_check_parameters(L,3);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	int h = lua_tointeger(L,-1);
	int w = lua_tointeger(L,-2);
	q->set_size(w,h);
	return 0;
}

//set if the callback should be called
int L_button_set_callback_state(lua_State* L)
{
	_check_parameters(L,2);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	bool b = lua_toboolean(L,-1);
	q->call = b;
	return 0;
}

int L_button_get_callback_state(lua_State* L)
{
	_check_parameters(L,1);
	ButtonWidget *q = *(ButtonWidget**)luaL_checkudata(L,1,"wip.ui.buttonwidget");
	lua_pushboolean(L,q->call);
	return 1;
}

/////////////////////////////////////////////////////////////////////////
//PictureWidget
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg picture_dtor[] =
{
	{"__gc",L_picture_delete},
	{NULL,NULL}
};

int L_picture_create(lua_State* L)
{
	_check_parameters(L,4);
	int x = lua_tointeger(L,1);
	int y = lua_tointeger(L,2);
	int w = lua_tointeger(L,3);
	int h = lua_tointeger(L,4);
	luaL_newmetatable(L, "wip.ui.picturewidget");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, picture_dtor, 0);
	int tsize = sizeof(PictureWidget*);
	PictureWidget **q = (PictureWidget**)lua_newuserdata(L,tsize);
	*q = new PictureWidget(x,y,w,h);
	luaL_getmetatable(L,"wip.ui.picturewidget");
	lua_setmetatable(L,-2);
	printf("picture:%d\n",*q);
	return 1;
}

int L_picture_delete(lua_State* L)
{
	_check_parameters(L,1);
	PictureWidget **q = (PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"PictureWidget %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_picture_static_init(lua_State* L)
{
	_check_parameters(L,2);
	PictureWidget *q = *(PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	std::string path = lua_tostring(L,-1);

	q->static_init(path);

	return 0;
}

int L_picture_update(lua_State* L)
{
	_check_parameters(L,2);

	PictureWidget *q = *(PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	float dt = lua_tonumber(L,-1);

	q->update(dt);

	return 0;
}

int L_picture_reset_picture(lua_State* L)
{
	_check_parameters(L,2);

	PictureWidget *q = *(PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	std::string path = lua_tostring(L,-1);

	q->reset_pic(path.c_str());

	return 0;
}

int L_picture_set_position(lua_State* L)
{
	_check_parameters(L,3);

	PictureWidget *q = *(PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);

	q->set_position(x,y);

	return 0;
}

int L_picture_reshape(lua_State* L)
{
	_check_parameters(L,5);

	PictureWidget *q = *(PictureWidget**)luaL_checkudata(L,1,"wip.ui.picturewidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	int h = lua_tointeger(L,-3);
	int w = lua_tointeger(L,-4);

	if(x==-1||y==-1)
		q->reshape(w,h);
	else
		q->reshape(w,h,x,y);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//ScrollerWidget
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg scroller_dtor[] =
{
	{"__gc",L_scroller_delete},
	{NULL,NULL}
};

int L_scroller_create(lua_State* L)
{
	_check_parameters(L,0);
	luaL_newmetatable(L, "wip.ui.scrollerwidget");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, scroller_dtor, 0);
	int tsize = sizeof(ScrollerWidget*);
	ScrollerWidget **q = (ScrollerWidget**)lua_newuserdata(L,tsize);
	*q = new ScrollerWidget();
	luaL_getmetatable(L,"wip.ui.scrollerwidget");
	lua_setmetatable(L,-2);

	printf("scroller:%d\n",*q);

	return 1;
}

int L_scroller_delete(lua_State* L)
{
 	_check_parameters(L,1);
	ScrollerWidget **q = (ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"ScrollerWidget %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_scroller_update_button(lua_State* L)
{
	_check_parameters(L,3);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	q->update_button(x,y);
	return 0;
}

int L_scroller_update(lua_State* L)
{
	_check_parameters(L,2);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	float dt = lua_tonumber(L,-1);

	q->update(dt);
	return 0;
}

int L_scroller_set_position(lua_State* L)
{
	_check_parameters(L,3);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);

	q->set_position(x,y);
	return 0;
}

//there is two default parameters,if set them to "",they will be default
//return if this function has been succeed
int L_scroller_init(lua_State* L)
{

	_check_parameters(L,3);
	bool ret = false;
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	std::string con = lua_tostring(L,-1);
	std::string bar = lua_tostring(L,-2);
	if(con==""||bar=="")
		ret = q->init();
	else
		ret = q->init(bar.c_str(),con.c_str());
	lua_pushboolean(L,ret);
	return 1;
}

int L_scroller_set_mouse_state(lua_State* L)
{
	_check_parameters(L,4);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	int y = lua_tointeger(L,-2);
	int x = lua_tointeger(L,-3);
	int state = lua_tointeger(L,-1);
	q->set_mouse_state(x,y,state);
	return 0;
}

int L_scroller_reshape(lua_State* L)
{
	_check_parameters(L,5);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	int h = lua_tointeger(L,-3);
	int w = lua_tointeger(L,-4);

	if(x==-1||y==-1)
		q->reshape(w,h,-1,-1);
	else
		q->reshape(w,h,x,y);
	return 0;
}

int L_scroller_set_current_val(lua_State* L)
{
	_check_parameters(L,2);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	float v = lua_tonumber(L,-1);

	q->set_current_val(v);

	return 0;
}

int L_scroller_set_controll(lua_State* L)
{
	_check_parameters(L,2);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	bool b = lua_toboolean(L,-1);

	q->set_controll(b);

	return 0;
}

int L_scroller_get_current_val(lua_State* L)
{
	_check_parameters(L,1);
	ScrollerWidget *q = *(ScrollerWidget**)luaL_checkudata(L,1,"wip.ui.scrollerwidget");
	
	lua_pushnumber(L,q->get_current_val());

	return 1;
}

/////////////////////////////////////////////////////////////////////////
//StaticText
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//SwitchWidget
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg switch_dtor[] =
{
	{"__gc",L_switch_delete},
	{NULL,NULL}
};

int L_switch_create(lua_State* L)
{
	_check_parameters(L,0);
	luaL_newmetatable(L, "wip.ui.switchwidget");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, switch_dtor, 0);
	int tsize = sizeof(SwitchWidget*);
	SwitchWidget **q = (SwitchWidget**)lua_newuserdata(L,tsize);
	*q = new SwitchWidget();
	luaL_getmetatable(L,"wip.ui.switchwidget");
	lua_setmetatable(L,-2);
	return 1;
}

int L_switch_delete(lua_State* L)
{
	_check_parameters(L,1);
	SwitchWidget **q = (SwitchWidget**)luaL_checkudata(L,1,"wip.ui.switchwidget");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"SwitchWidget %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_switch_init_button(lua_State* L)
{
	_check_parameters(L,4);
	SwitchWidget *q = *(SwitchWidget**)luaL_checkudata(L,1,"wip.ui.switchwidget");
	std::string normal = lua_tostring(L,-1);
	std::string move = lua_tostring(L,-2);
	std::string down = lua_tostring(L,-3);
	q->init_button(down,move,normal,NULL);
	return 0;
}

int L_switch_update_button(lua_State* L)
{
	_check_parameters(L,3);
	SwitchWidget *q = *(SwitchWidget**)luaL_checkudata(L,1,"wip.ui.switchwidget");
	int y = lua_tointeger(L,-1);
	int x = lua_tointeger(L,-2);
	q->update_button(x,y);
	return 0;
}

int L_switch_set_switch_state(lua_State* L)
{
	_check_parameters(L,2);
	SwitchWidget *q = *(SwitchWidget**)luaL_checkudata(L,1,"wip.ui.switchwidget");
	bool b = lua_toboolean(L,-1);
	q->set_switch_state(b);
	return 0;
}

int L_switch_get_switch_state(lua_State* L)
{
	_check_parameters(L,1);
	SwitchWidget *q = *(SwitchWidget**)luaL_checkudata(L,1,"wip.ui.switchwidget");

	lua_pushboolean(L,q->get_switch_state());

	return 1;
}

/////////////////////////////////////////////////////////////////////////
//TouchWidget
/////////////////////////////////////////////////////////////////////////
static const luaL_Reg touch_dtor[] =
{
	{"__gc",L_touch_delete},
	{NULL,NULL}
};

int L_touch_create(lua_State* L)
{
	_check_parameters(L,4);
	
	int x = lua_tointeger(L,1);
	int y = lua_tointeger(L,2);
	int w = lua_tointeger(L,3);
	int h = lua_tointeger(L,4);
	luaL_newmetatable(L, "wip.ui.touchwidget");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, touch_dtor, 0);
	int tsize = sizeof(TouchWidget*);
	TouchWidget **q = (TouchWidget**)lua_newuserdata(L,tsize);
	*q = new TouchWidget(x,y,w,h);
	luaL_getmetatable(L,"wip.ui.touchwidget");
	lua_setmetatable(L,-2);
	return 1;
}

int L_touch_delete(lua_State* L)
{
	_check_parameters(L,1);
	TouchWidget **q = (TouchWidget**)luaL_checkudata(L,1,"wip.ui.touchwidget");
	if(q&&*q)
	{
		
#ifdef _DEBUG
		g_logger->debug_print(WIP_INFO,"TouchWidget %d has been deleted",(*q));
#endif
		delete *q;
	}
	return 0;
}

int L_touch_update(lua_State* L)
{
	_check_parameters(L,2);
	TouchWidget *q = *(TouchWidget**)luaL_checkudata(L,1,"wip.ui.touchwidget");
	float dt = lua_tonumber(L,-1);
	q->update(dt);
	return 0;
}

int L_touch_add_widget(lua_State* L)
{
	_check_parameters(L,2);
	TouchWidget *q = *(TouchWidget**)luaL_checkudata(L,1,"wip.ui.touchwidget");
	BaseWidget *p = *(BaseWidget**)lua_touserdata(L,-1);
	q->add_widget(p);
	return 0;
}

int L_touch_get_widget_by_name(lua_State* L)
{
	_check_parameters(L,2);
	TouchWidget *q = *(TouchWidget**)luaL_checkudata(L,1,"wip.ui.touchwidget");
	std::string name = lua_tostring(L,-1);
	lua_pushlightuserdata(L,q->get_widget_by_name(name));
	return 1;
}

