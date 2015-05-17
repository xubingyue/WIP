#pragma once

#include "ResourceManager.h"
#include "Utilities/Utilities.h"
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "OpenGL.h"



#define VSHADER 0
#define FSHADER 1
class WIPTexture;
class WIPRenderBatch;
class WIPCamera;
struct RenderQuad;

class Renderer
{
public:
	static Renderer* get_instance();

	bool startup( ESContext *esContext);
	void shutdown();
	void render(WIPTexture* texture,RenderQuad* rquad);
	void render(WIPTexture* texture,RenderQuad* rquad,RenderQuad* uvquad);
	void render(WIPTexture* texture,int x,int y);
	void render(GLuint texture,int x,int y,int w,int h);
	void render(GLuint texture,RenderQuad* rquad);

	void render_to_camera(WIPCamera* camera,WIPRenderBatch* batch);
	void render_batch(WIPRenderBatch* batch);
	//tools
	void draw_box(const RenderQuad& rquad,bool fill);
	void draw_point(int x,int y);
	//draw box in world space
	void draw_box_ex(f32 x,f32 y,f32 z,f32 w,f32 h);

	//getters
	inline GLuint get_shader_program()
	{
		return _shader_program_object;
	}
	inline ESContext* get_context()
	{
		return _es_context;
	}
	inline GLushort* get_indices()
	{
		return _indices;
	}
	inline GLint get_sampler_location()
	{
		return _sampler_location;
	}
	inline void reset_iv_w(f32 w)
	{
		_iv_w = 1.f/(w*0.5f);
	}
	inline void reset_iv_h(f32 h)
	{
		_iv_h = 1.f/(h*0.5f);
	}
	~Renderer();
protected:
	Renderer();
private:
	static Renderer* _renderer;
	GLuint _shader_program_object;
	GLuint _debug_shader_program_object;
	ESContext* _es_context;
	//0 for vertex,1 for fragment
	ResHandler* _shader_codes_handler[2];
	GLushort _indices[6];// = { 0, 1, 2, 0, 2, 3 };
	GLint _sampler_location;

	f32 _iv_w;
	f32 _iv_h;
};

extern Renderer* g_renderer;