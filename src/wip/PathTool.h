#pragma once
#include <string>

using std::string;

class WIPPathTool
{
public:
	//only to '/'
	static string get_file_directory(string file_path);
	static string get_file_name(string file_path);
	static string get_file_extension(string file_path);
	static string get_separator();
	//TODO!!!!
	static bool check_path_available(string file_path);
	static bool create_directory(string path);
	static bool delete_directory(string path);


	static string char2string(char* tstring);
	static const char* string2char(string tstring);
	//contain a and b
	static string get_n1_to_n2(string tstring,int n1,int n2);

};