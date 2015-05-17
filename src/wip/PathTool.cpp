#include "PathTool.h"

string WIPPathTool::char2string(char* tstring)
{
	return string(tstring);
}

string WIPPathTool::get_file_directory(string file_path)
{
	int len = file_path.size();
	const char* chars = file_path.c_str();
	int sep = 0;
	for (int i=0;i<len;++i)
	{
		if(file_path[i]=='/')
		{
			sep = i;
		}
	}

	return get_n1_to_n2(file_path,0,sep);
}

string WIPPathTool::get_file_extension(string file_path)
{

	int pos = file_path.rfind('.');
	string res = file_path.substr(pos+1);
	return res;
}

string WIPPathTool::get_file_name(string file_path0)
{
	int len = file_path0.size();
	const char* chars = file_path0.c_str();
	int sep = 0;
	int point = 0;
	for (int i=0;i<len;++i)
	{
		if(file_path0[i]=='/')
		{
			sep = i;
		}
		if(file_path0[i]=='.')
		{
			point = i;
		}

	}

	return get_n1_to_n2(file_path0,sep+1,point-1);
}

string WIPPathTool::get_separator()
{
	string separator;
#ifdef _WIN32
	separator = "\\";	
#else
	separator = "/";
#endif

	return separator;
}

const char* WIPPathTool::string2char(string tstring)
{
	return tstring.c_str();
}

string WIPPathTool::get_n1_to_n2(string tstring,int n1,int n2)
{
	if (n1>n2)
	{
		return "\0";
	}
	string ret;
	char temp = tstring[n1];
	int i=0;
	do 
	{
		ret.push_back(temp);
		temp = tstring[n1+(++i)];
	}
	while(i<=n2-n1);
	return ret;
}


//TODO!!!
bool WIPPathTool::check_path_available(string file_path)
{
	return true;
}

bool WIPPathTool::create_directory(string path)
{
	return true;
}

bool WIPPathTool::delete_directory(string path)
{
	return true;
}