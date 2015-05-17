#pragma once

enum WIPModelType 
{
	E_OBJ,
	E_FBX,
	E_1,
};

class WIPModelLoader
{
public:
	static bool load_model(WIPModelType model_type,const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int& c_vt, unsigned short** index,int& c_i);

protected:

private:

public:
	static bool load_obj(const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int& c_vt, unsigned short** index,int& c_i);
	static bool load_fbx();
	static bool load_1(const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int& c_vt, unsigned short** index,int& c_i);
};