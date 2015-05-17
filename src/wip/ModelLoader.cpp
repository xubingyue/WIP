#include "ModelLoader.h"
#include "Logger.h"
#include "Assertion.h"
#include <fstream>
#include <string>


bool WIPModelLoader::load_model( WIPModelType model_type,const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int& c_vt, unsigned short** index,int& c_i )
{
	switch (model_type)
	{
	case WIPModelType::E_OBJ:
		return load_obj(model_path,vert,c_v,normal,c_vn,uv,c_vt,index,c_i);
		break;
	case WIPModelType::E_FBX:
		return load_fbx();
		break;
	case WIPModelType::E_1:
		return load_1(model_path,vert,c_v,normal,c_vn,uv,c_vt,index,c_i);
		break;
	default:
		/*
		g_logger->debug_print(WIP_ERROR,"No MODEL TYPE CALLED %d",model_type);
		g_logger->debug_log(WIP_ERROR,"No MODEL TYPE CALLED %d",model_type);
		*/
		g_logger->debug(WIP_ERROR,"No MODEL TYPE CALLED %d",model_type);
		return false;
		break;
	}
}





bool WIPModelLoader::load_obj( const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int& c_vt, unsigned short** index,int &c_i )
{
	std::fstream f;
	std::string s;
	int k = 0;
	unsigned int len_vert;
	unsigned int len_normal;
	unsigned int len_uv;
	unsigned int len_index;

	bool check = false;

	f.open(model_path,std::ios::in);
	if (!f)
	{
		g_logger->debug_log(WIP_ERROR,"Open model file %s failed!",model_path);
		return false;
	}

	int temp_n;
	char temp_s[25];
	while (getline(f,s))
	{
		if(s[0]=='@')
			continue;
		if (!check&&s[0]=='v')
		{
			check = true;
		}
		if (check&&s[0]=='#')
		{
			
			sscanf(s.data(),"# %d %s",&temp_n,&temp_s);
			if(strcmp(temp_s,"vertices")==0)
			{
				len_vert = temp_n*3; 
				c_v = len_vert;
			}
			else if (strcmp(temp_s,"vertex")==0)
			{
				len_normal = temp_n*3; 
				c_vn = len_normal;
			}
			else if (strcmp(temp_s,"texture")==0)
			{
				len_uv = temp_n*2;
				c_vt = len_uv;
			}
			else if (strcmp(temp_s,"faces")==0)
			{
				len_index = temp_n*9;
				c_i = len_index;
			}
			else 
			{
				g_logger->debug(WIP_WARNING,"MODEL READ ARRAY SIZE CHECK:NO THIS TYPE DATA CALLED %s",temp_s);
				return false;
			}
		}
	}

	 float* tvert = *vert = new float[len_vert*sizeof(float)];
	 float* tnormal = *normal = new float[len_normal*sizeof(float)];
	 float* tuv = *uv = new float[len_uv*sizeof(float)];
	 unsigned short* tindex = *index = new unsigned short[len_index*sizeof(unsigned short)];

	//clear bad state
	f.clear();
	f.seekg(0,std::ios::beg);

	unsigned int count_v(0),count_vt(0),count_vn(0),count_f(0);
	while (getline(f,s))
	{
		sscanf(s.data(),"%s ",&temp_s);
		if (strcmp(temp_s,"v")==0)
		{
			sscanf(s.data(),"%s %f %f %f",&temp_s,&tvert[count_v],&tvert[count_v+1],&tvert[count_v+2]);
			count_v += 3;
		}
		else if(strcmp(temp_s,"vn")==0)
		{
			sscanf(s.data(),"%s %f %f %f",&temp_s,&tnormal[count_vn],&tnormal[count_vn+1],&tnormal[count_vn+2]);
			count_vn += 3;
		}
		else if(strcmp(temp_s,"vt")==0)
		{
			sscanf(s.data(),"%s %f %f ",&temp_s,&tuv[count_vt],&tuv[count_vt+1]);
			count_vt += 2;
		}
		else if(strcmp(temp_s,"f")==0)
		{
			sscanf(s.data(),"%s %d/%d/%d %d/%d/%d %d/%d/%d",&temp_s,
				&tindex[count_f],&tindex[count_f+1],&tindex[count_f+2],
				&tindex[count_f+3],&tindex[count_f+4],&tindex[count_f+5],
				&tindex[count_f+6],&tindex[count_f+7],&tindex[count_f+8]);
			count_f += 9;
		}
		




	}

#ifdef _DEBUG
	CHECK(count_f==len_index);
	CHECK(count_v==len_vert);
	CHECK(count_vn==len_normal);
	CHECK(count_vt==len_uv);
	
#endif

		float *out_uv = new float[len_vert*sizeof(float)];
		float *out_normal = new float[len_vert*sizeof(float)];
		unsigned short *out_index = new unsigned short[len_index*sizeof(unsigned short)];

		for(unsigned int i=0;i<len_index;i+=3)
		{
			unsigned int vi = tindex[i]-1;
			unsigned int ti = tindex[i+1]-1;
			unsigned int ni = tindex[i+2]-1;

			out_uv[vi*2] = tuv[ti*2];
			out_uv[vi*2+1] = tuv[ti*2+1];
			out_normal[vi*3] = tnormal[ni*3];
			out_normal[vi*3+1] = tnormal[ni*3+1];
			out_normal[vi*3+2] = tnormal[ni*3+2];
			out_index[i/3] = vi;

		}

		c_vt = c_vn = len_vert;
		c_i = len_index/3;

		delete[] tuv;
		delete[] tnormal;
		delete[] tindex;

		*normal = out_normal;
		*uv = out_uv;
		*index = out_index;

		//顶点个数报警
		if(len_vert/3>65535)
		{
			g_logger->debug_print(WIP_NOTE,"Model %s has more than 65535 verteces!",model_path);
		}

	return true;
}

bool WIPModelLoader::load_fbx()
{
	return false;
}

bool WIPModelLoader::load_1(const char* model_path, float** vert,int &c_v, float** normal,int &c_vn, float** uv,int &c_vt, unsigned short** index,int& c_i)
{
	std::fstream f;
	f.open(model_path,std::ios::in);
	if(!f)
	{
		g_logger->debug_print(WIP_ERROR,"Invalid file:%s",model_path);
		return false;
	}
	std::string s;
	bool change = false;

	

	int len_v = 0;
	int len_i = 0;
	while (getline(f,s))
	{
		if(!change&&s[0]=='i')
		{
			change = true;
			continue;
		}
		if(change)
		{
			++len_i;
		}
		else
		{
			++len_v;
		}
	}

	change = false;

	c_i = len_i*3;
	c_v = len_v*3;
	c_vn = c_vt = 0;

	if (normal!=nullptr)
	{
		*normal = nullptr;
	}
	if (uv!=nullptr)
	{
		*uv = nullptr;
	}

	float *tvert =*vert = new float[c_v*sizeof(float)];
	unsigned short *tindex =*index = new unsigned short[c_i*sizeof(unsigned short)];

	f.clear();
	f.seekg(0,std::ios::beg);

	int count_v(0),count_i(0);

	while (getline(f,s))
	{
		if(!change&&s[0]=='i')
		{
			change = true;
			continue;
		}
		if(change)
		{
			sscanf(s.data(), "%d %d %d", &tindex[count_i], &tindex[count_i + 1], &tindex[count_i + 2]);
			--(tindex[count_i + 1]);
			--(tindex[count_i + 2]);
			--(tindex[count_i]);
			count_i += 3;
		}
		else
		{
			sscanf(s.data(),"%f %f %f",&tvert[count_v],&tvert[count_v+1],&tvert[count_v+2]);
			count_v += 3;
		}

	}

	return true;
}
