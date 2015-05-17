#include "AppManager.h"
#include "ScriptManager.h"
#include "PathTool.h"
#include "Utilities/WIPIniHelper.h"

#include "ModelLoader.h"

int main()
{

	/*
	//use c++
	g_app_manager->startup();
	if(g_app_manager->create_window("WIP",720,480))
		g_app_manager->run();
	else
	{
		printf("window init failed!\n");
		getchar();
		return 1;
	}
	
	g_app_manager->shutdown();
	*/

	//use lua
	g_app_manager->startup();


	string file_path = "../LuaSyatem/OG/main.lua";

	std::string path = "WIPCFG.ini";
	if(WIPIniHelper::reset_ini_file(path.data()))
	{
		WIPIniHelper::get_string("Common","project",file_path);
	}
	else
	{
		printf("Read ini failed!\n");
		getchar();
		exit(0);
	}
	WIPIniHelper::close();

	g_script_manager->load_file(file_path.c_str());
	//g_script_manager->call("init");
	
	g_script_manager->call("main");

	g_app_manager->shutdown();
	

	return 0;

}