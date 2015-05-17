#include "Model3D.h"
#include "ModelLoader.h"
#include "Logger.h"
#include "Assertion.h"
#include <fstream>
#include <string>

bool WIPModel3D::load( const char* file)
{
	_index_size = 0;
	_vert_size = 0;
	_index_count = 0;
	_vert_count = 0;
	GLushort *index=0;
	GLfloat *vert=0;
	GLfloat *vn=0,*vt=0;
	std::fstream f1, f2;
	std::string s;
	int kn = 0;
	int kt = 0;

	//bool r = WIPModelLoader::load_model(WIPModelType::E_1,"resources/1.sm",&vert,_vert_count,&vn,k,&vn,k,&index,_index_count);
	bool r = WIPModelLoader::load_model(WIPModelType::E_OBJ,file,&vert,_vert_count,&vn,kn,&vt,kt,&index,_index_count);

	
	/*
	GLushort *vi = new GLushort[_index_count/3*sizeof(GLushort)];
	for(int i=0;i<_index_count;i+=3)
	{
		vi[i/3] = index[i];
	}
	delete[] index;
	index = vi;
	_index_count /= 3;
	*/
	/*
	for (int i=0;i<_vert_count;i+=3)
	{
		printf("%f %f %f \n",vert[i],vert[i+1],vert[i+2]);
	}
	
	for (int i=0;i<_index_count;i+=3)
	{
		printf("%d %d %d \n",index[i],index[i+1],index[i+2]);
	}
	*/

	//printf("%d\n",_vert_count);
	//printf("%d\n",_index_count);

	_vert_size = _vert_count*sizeof(GLfloat);
	_index_size = _index_count*sizeof(GLushort);


	glGenBuffers(1,&_tbo);
	glBindBuffer(GL_ARRAY_BUFFER, _tbo);
	glBufferData(GL_ARRAY_BUFFER,kt*sizeof(GLfloat),vt,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1,&_nbo);
	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glBufferData(GL_ARRAY_BUFFER,kn*sizeof(GLfloat),vn,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1,&_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER,_vert_size,vert,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index_size, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _tbo);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	

	if (GL_NO_ERROR!=glGetError())
	{
		_index_size = 0;
		_vert_size = 0;
		_index_count = 0;
		_vert_count = 0;
		_vbo = _vao = _ebo = 0;
		printf("gl failed!\n");
		return false;
	}
	delete[] vert;
	delete[] index;
	delete[] vn;
	delete[] vt;

	return true;
}

bool WIPModel3D::load_weight(const char* model_path)
{
	std::fstream f;
	std::string s;
	int k = 0;
	bool check = false;

	f.open(model_path,std::ios::in);
	if (!f)
	{
		g_logger->debug_log(WIP_ERROR,"Open model file %s failed!",model_path);
		return false;
	}
	
	char temp_s[25];
	int bones_count = _vert_count;

	float* tweights = new float[_vert_count*3*sizeof(float)];

	unsigned int count_v(0);
	while (getline(f,s))
	{
		
			sscanf(s.data(),"%f %f %f",&tweights[count_v],&tweights[count_v+1],&tweights[count_v+2]);
			count_v += 3;
		
	}

#ifdef _DEBUG
	CHECK(count_v==bones_count);
#endif


	glGenBuffers(1,&_bbo);
	glBindBuffer(GL_ARRAY_BUFFER, _bbo);
	glBufferData(GL_ARRAY_BUFFER,_vert_size,tweights,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(_vao);
	if (GL_NO_ERROR!=glGetError())
	{
		printf("gl failed!\n");
		return false;
	}
	glEnableVertexAttribArray(3);
		if (GL_NO_ERROR!=glGetError())
	{
		printf("gl failed!\n");
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER,_bbo);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GLenum e = glGetError();
		if (GL_NO_ERROR!=e)
	{
		printf("gl failed!\n");
		return false;
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	if (GL_NO_ERROR!=glGetError())
	{
		printf("gl failed!\n");
		return false;
	}
	return true;
}

void WIPModel3D::renderer(int glmode)
{
	glBindVertexArray(_vao);
	//glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(glmode, _index_count, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

WIPModel3D::~WIPModel3D()
{
	glDeleteBuffers(1,&_vbo);
	glDeleteBuffers(1,&_ebo);
	glDeleteVertexArrays(1,&_vao);
}

WIPModel3D::WIPModel3D()
{
	_index_size = 0;
	_vert_size = 0;
	_index_count = 0;
	_vert_count = 0;
	_vbo = _vao = _ebo = 0;
}

bool WIPModel3D::attach_bone()
{
	return true;
}

