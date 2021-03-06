#pragma once
#include "lua.hpp"

class WIPScriptManager
{
public:
	static WIPScriptManager* instance();

	WIPScriptManager();
	~WIPScriptManager();

	bool startup();
	void shutdown();
	bool load_file(const char* file);
	void call(const char* function);
	void call(const char* function,const char* param_types,...);

protected:

private:
	void generate_api();
	static WIPScriptManager* _instance;
	
	lua_State *_L;
};

extern WIPScriptManager* g_script_manager;