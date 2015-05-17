#pragma once



#include "OpenGL.h"

//#include "../Utilities/WPList.h"
#include <list>
#include <cstring>
//#define List std::list;

class WIPTexture;

//TODO:if it is necessary?
struct WIPCanvasObject 
{
	std::string words;
	int x,y;
	//may be other members

	WIPCanvasObject(const char* str,int tx,int ty)
	{
		words = str;
		x = tx;
		y = ty;
	}
	WIPCanvasObject(std::string str,int tx,int ty)
	{
		words = str;
		x = tx;
		y = ty;
	}

};

class WIPTextCanvas
{
public:
	WIPTextCanvas(int width = -1,int height = -1);
	~WIPTextCanvas();
	void draw_text(const char* text,int x,int y);
	void draw_text(const std::string text,int x,int y);
	void update();

	//////////////////////////////////////////////////////////////////////////
	//Getters
	//////////////////////////////////////////////////////////////////////////
	inline GLuint get_buffer()
	{
		return _out_buffer;
	}
	inline int get_width()
	{
		return _buffer_width;
	}
	inline int get_height()
	{
		return _buffer_height;
	}

	//for debug
	void draw_buffer(int x,int y,int w,int h);
protected:


private:
	typedef std::list<WIPCanvasObject*> _ObjectList;
	_ObjectList _object_list;

	int _buffer_width,_buffer_height;
	GLuint _out_buffer;
	GLuint _frame_buffer;
};