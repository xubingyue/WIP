#include "RenderQuad.h"
#include "Renderer.h"
#include "Texture.h"
#include "RenderBatch.h"
#include "Camera.h"
//#include "gl/GL.h"
#include "Utilities/WIPIniHelper.h"

Renderer* Renderer::_renderer = 0;

Renderer* Renderer::get_instance()
{
	if (!_renderer)
	{
		_renderer = new Renderer();
	}
	return _renderer;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete _renderer;
}

void Renderer::render(WIPTexture* texture,int x,int y)
{
	RenderQuad quad;
	quad.set_quickly(
		x,y,
		x,y+texture->get_height(),
		x+texture->get_width(),y+texture->get_height(),
		x+texture->get_width(),y
		);
	render(texture,&quad);
}

void Renderer::render(WIPTexture* texture,RenderQuad* rquad,RenderQuad* uvquad)
{
	//opengl left button
	//screen left top

	//x1 = (x-w/2 ) / ( w/2)
	//y1 =(-y+h/2) / ( h/2)
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	GLfloat vVertices[] = {
		rquad->lt.x*_iv_w-1,  1-rquad->lt.y*_iv_h, 0.0f,  // Position 0
		uvquad->lb.x,  uvquad->lb.y,        // TexCoord 1
		rquad->lb.x*_iv_w-1, 1-rquad->lb.y*_iv_h, 0.0f,  // Position 1
		uvquad->lt.x,  uvquad->lt.y,        // TexCoord 0 
		
		rquad->rb.x*_iv_w-1, 1-rquad->rb.y*_iv_h, 0.0f,  // Position 2
		uvquad->rt.x,  uvquad->rt.y,         // TexCoord 3
		
		rquad->rt.x*_iv_w-1,  1-rquad->rt.y*_iv_h, 0.0f,  // Position 3
		uvquad->rb.x,  uvquad->rb.y        // TexCoord 2
	};
	// Clear the color buffer
	//Clear every frame
	//glClear ( GL_COLOR_BUFFER_BIT );

	
	// Use the program object
	glUseProgram ( _shader_program_object);
	// Load the vertex position
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	// Load the texture coordinate
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	// Bind the base map
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, texture->get_texture_id() );
	// Set the base map sampler to texture unit to 0
	glUniform1i (_sampler_location, 0 );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	glBindTexture ( GL_TEXTURE_2D, 0);
	//when debug we need it 
	//eglSwapBuffers( _es_context->eglDisplay, _es_context->eglSurface );
}

void Renderer::render(WIPTexture* texture,RenderQuad* rquad)
{
	//opengl left button
	//screen left top

	//x1 = (x-w/2 ) / ( w/2)
	//y1 =(-y+h/2) / ( h/2)
	/*
	f32 ww = _es_context->width;
	f32 hh = _es_context->height;
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	*/
	/*
	GLfloat vVertices[] = {
		rquad->lt.x/w-1,  1-rquad->lt.y/h, 0.0f,  // Position 0
		0.0f,  0.0f,        // TexCoord 0 
		rquad->lb.x/w-1, 1-rquad->lb.y/h, 0.0f,  // Position 1
		0.0f,  1.0f,        // TexCoord 1
		rquad->rb.x/w-1, 1-rquad->rb.y/h, 0.0f,  // Position 2
		1.0f,  1.0f,        // TexCoord 2
		rquad->rt.x/w-1,  1-rquad->rt.y/h, 0.0f,  // Position 3
		1.0f,  0.0f         // TexCoord 3
	};
	*/
	GLfloat vVertices[] = {
		rquad->lt.x*_iv_w-1,  1-(rquad->lt.y)*_iv_h, 0.0f,  // Position 0
		0.0f,  1.0f,        // TexCoord 0 
		rquad->lb.x*_iv_w-1, 1-(rquad->lb.y)*_iv_h, 0.0f,  // Position 1
		0.0f,  0.0f,        // TexCoord 1
		rquad->rb.x*_iv_w-1, 1-(rquad->rb.y)*_iv_h, 0.0f,  // Position 2
		1.0f,  0.0f,        // TexCoord 2
		rquad->rt.x*_iv_w-1,  1-(rquad->rt.y)*_iv_h, 0.0f,  // Position 3
		1.0f,  1.0f,         // TexCoord 3
	};
	// Clear the color buffer
	//Clear every frame
	//glClear ( GL_COLOR_BUFFER_BIT );

	
	// Use the program object
	glUseProgram ( _shader_program_object);
	// Load the vertex position
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	// Load the texture coordinate
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	// Bind the base map
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, texture->get_texture_id() );
	// Set the base map sampler to texture unit to 0
	glUniform1i (_sampler_location, 0 );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	glBindTexture ( GL_TEXTURE_2D, 0);
}

void Renderer::render(GLuint texture,RenderQuad* rquad)
{
	//opengl left bottom
	//screen left top

	//x1 = (x-w/2 ) / ( w/2)
	//y1 =(-y+h/2) / ( h/2)
	/*
	f32 ww = _es_context->width;
	f32 hh = _es_context->height;
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	*/
	GLfloat vVertices[] = {
		rquad->lt.x*_iv_w-1,  1-rquad->lt.y*_iv_h, 0.0f,  // Position 0
		0.0f,  1.0f,        // TexCoord 0 
		rquad->lb.x*_iv_w-1, 1-rquad->lb.y*_iv_h, 0.0f,  // Position 1
		0.0f,  0.0f,        // TexCoord 1
		rquad->rb.x*_iv_w-1, 1-rquad->rb.y*_iv_h, 0.0f,  // Position 2
		1.0f,  0.0f,        // TexCoord 2
		rquad->rt.x*_iv_w-1,  1-rquad->rt.y*_iv_h, 0.0f,  // Position 3
		1.0f,  1.0f         // TexCoord 3
	};
	// Clear the color buffer
	//Clear every frame
	//glClear ( GL_COLOR_BUFFER_BIT );

	
	// Use the program object
	glUseProgram ( _shader_program_object);
	// Load the vertex position
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	// Load the texture coordinate
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	// Bind the base map
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, texture);
	// Set the base map sampler to texture unit to 0
	glUniform1i (_sampler_location, 0 );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	
	glBindTexture ( GL_TEXTURE_2D, 0);
	

}


void Renderer::render(GLuint texture,int x,int y,int w1,int h1)
{
	RenderQuad rquad;
	rquad.set_quickly(
		x,y,
		x,y+h1,
		x+w1,y+h1,
		x+w1,y
		);
	/*
	f32 ww = _es_context->width;
	f32 hh = _es_context->height;
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	*/
	
	GLfloat vVertices[] = {
		rquad.lt.x*_iv_w-1,  1-rquad.lt.y*_iv_h, 0.0f,  // Position 0
		0.0f,  1.0f,        // TexCoord 0 
		rquad.lb.x*_iv_w-1, 1-rquad.lb.y*_iv_h, 0.0f,  // Position 1
		0.0f,  0.0f,        // TexCoord 1
		rquad.rb.x*_iv_w-1, 1-rquad.rb.y*_iv_h, 0.0f,  // Position 2
		1.0f,  0.0f,        // TexCoord 2
		rquad.rt.x*_iv_w-1,  1-rquad.rt.y*_iv_h, 0.0f,  // Position 3
		1.0f,  1.0f         // TexCoord 3
	};
	
	/*
	GLfloat vVertices[] = {
		rquad.lt.x/w-1,  1-(rquad.lt.y)/h, 0.0f,  // Position 0
		0.0f,  0.0f,        // TexCoord 0 
		rquad.lb.x/w-1, 1-(rquad.lb.y)/h, 0.0f,  // Position 1
		0.0f,  1.0f,        // TexCoord 1
		rquad.rb.x/w-1, 1-(rquad.rb.y)/h, 0.0f,  // Position 2
		1.0f,  1.0f,        // TexCoord 2
		rquad.rt.x/w-1,  1-(rquad.rt.y)/h, 0.0f,  // Position 3
		1.0f,  0.0f,         // TexCoord 3
	};
	*/
	
	// Use the program object
	glUseProgram ( _shader_program_object);
	// Load the vertex position
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	// Load the texture coordinate
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	// Bind the base map         
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, texture);
	// Set the base map sampler to texture unit to 0
	glUniform1i (_sampler_location, 0 );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	glBindTexture ( GL_TEXTURE_2D, 0);
	
}

void Renderer::render_batch(WIPRenderBatch* batch)
{
	//渲染一个批次，引擎主要渲染路径
	//TODO:真正的opengl批渲染
	if(!batch)
		return;
	GLfloat vVertices[20];
	GLuint tex_id;
	if(batch->bsort)
		batch->sort();
	glUseProgram ( _shader_program_object);
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	glActiveTexture ( GL_TEXTURE0 );
	glUniform1i (_sampler_location, 0 );
	for(uint i=0;i<batch->_size;++i)
	{
		batch->unpack(vVertices,tex_id,_iv_h,_iv_w);
		glBindTexture ( GL_TEXTURE_2D, tex_id );
		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	}
		glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	glBindTexture ( GL_TEXTURE_2D, 0);
	

}

void Renderer::render_to_camera(WIPCamera* camera,WIPRenderBatch* batch)
{
	
	if(!camera||!batch)
		return;
		
	/*
	WIPTexture* nt = new WIPTexture("../Resources/bg.jpg");
	//render((*(batch->_packages.begin()))->tex_id,0,0,200,200);
	

	render(nt->get_texture_id(),0,0,200,200);

	delete nt;
	*/
	f32 iv_h = 1.f/(camera->world_h*0.5f);
	f32	iv_w = 1.f/(camera->world_w*0.5f);
	GLfloat vVertices[20];
	GLuint tex_id;
	if(batch->bsort)
		batch->sort();
	
	glUseProgram ( _shader_program_object);
	glVertexAttribPointer ( 0, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	glVertexAttribPointer ( 1, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
	glEnableVertexAttribArray ( 0 );
	glEnableVertexAttribArray ( 1 );
	glActiveTexture ( GL_TEXTURE0 );
	glUniform1i (_sampler_location, 0 );
	int n = batch->_size;
	camera->begin();
	glClear(GL_COLOR_BUFFER_BIT);
	for(uint i=0;i<n;++i)
	{
		batch->unpack(vVertices,tex_id,iv_h,iv_w);
		glBindTexture ( GL_TEXTURE_2D, tex_id );
		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, _indices );
	}
	camera->end();
		glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );
	glBindTexture ( GL_TEXTURE_2D, 0);
	
}

void Renderer::draw_box_ex(f32 x,f32 y,f32 z,f32 w,f32 h)
{
	GLfloat v[] = 
	{
		x,y+h,z,
		x,y,z,
		x+w,y,z,
		x+w,y+h,z
	};
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,v);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES,0,4);
}

void Renderer::draw_box(const RenderQuad& rquad,bool fill)
{
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	GLfloat vVertices[] = {
		rquad.lt.x*_iv_w-1,  1-rquad.lt.y*_iv_h, 0.0f,  // Position 0
		rquad.lb.x*_iv_w-1, 1-rquad.lb.y*_iv_h, 0.0f,  // Position 1
		rquad.rb.x*_iv_w-1, 1-rquad.rb.y*_iv_h, 0.0f,  // Position 2
		rquad.rt.x*_iv_w-1,  1-rquad.rt.y*_iv_h, 0.0f,  // Position 3
		

	};


	glUseProgram ( _debug_shader_program_object);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );

	glEnableVertexAttribArray( 0 );


	
	if(fill)
		glRectf(vVertices[0],vVertices[1],vVertices[6],vVertices[7]);
	else
	{
		glDrawArrays( GL_LINE_LOOP, 0, 4 );
	}
	
	//eglSwapBuffers( _es_context->eglDisplay, _es_context->eglSurface );
	//glDisableVertexAttribArray(0);
}

void Renderer::draw_point(int x,int y)
{
	int off = 10;
	float w = _es_context->width/2;
	float h = _es_context->height/2;
	GLfloat vVertices[] = {
		(x+off)*_iv_w-1,  1-(y-off)*_iv_h, 0.0f,  // Position 0

		(x+off)*_iv_w-1, 1-(y+off)*_iv_h, 0.0f,  // Position 1

		
	
		(x-off)*_iv_w-1,  1-(y+off)*_iv_h, 0.0f,  // Position 3
		(x-off)*_iv_w-1, 1-(y-off)*_iv_h, 0.0f,  // Position 2

	};
	//glClear( GL_COLOR_BUFFER_BIT );
	glUseProgram ( _debug_shader_program_object);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray( 0 );


	glDrawArrays( GL_LINE_LOOP, 0, 4 );
	
	//glDisableVertexAttribArray(0);
}

bool Renderer::startup( ESContext *esContext)
{
	/*
	WIPIniHelper::reset_ini_file("WIPCFG.ini");
	std::string p;
	WIPIniHelper::get_string("Common","project_resources",p);
	*/
	_shader_codes_handler[VSHADER] = g_res_manager->load_resource("engine/vertex.c",TEXT);
	_shader_codes_handler[FSHADER] = g_res_manager->load_resource("engine/fragment.c",TEXT);
	if (!_shader_codes_handler[VSHADER]||!_shader_codes_handler[FSHADER])
	{
		return false;
	}
	std::string* v = ((std::string*)(_shader_codes_handler[VSHADER]->ptr));
	std::string* f = ((std::string*)(_shader_codes_handler[FSHADER]->ptr));
	_shader_program_object = esLoadProgram(v->c_str(),f->c_str());
	if(0==_shader_program_object)
	{
		g_res_manager->free(_shader_codes_handler[VSHADER],_shader_codes_handler[VSHADER]->size);
		g_res_manager->free(_shader_codes_handler[FSHADER],_shader_codes_handler[FSHADER]->size);
		return false;
	}
	
	g_res_manager->free(_shader_codes_handler[FSHADER],_shader_codes_handler[FSHADER]->size);
	//load debug shader
	_shader_codes_handler[FSHADER] = g_res_manager->load_resource("engine/fragment1.c",TEXT);
	f = ((std::string*)(_shader_codes_handler[FSHADER]->ptr));
	_debug_shader_program_object = esLoadProgram(v->c_str(),f->c_str());
	g_res_manager->free(_shader_codes_handler[VSHADER],_shader_codes_handler[VSHADER]->size);
	g_res_manager->free(_shader_codes_handler[FSHADER],_shader_codes_handler[FSHADER]->size);
	if(0==_debug_shader_program_object)
	{
		return false;
	}
	

	_sampler_location = glGetUniformLocation(_shader_program_object,"s_baseMap");
	
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	_indices[0] = _indices[3] = 0;
	_indices[2] = _indices[4] = 2;
	_indices[1] = 1;
	_indices[5] = 3;
	_es_context = esContext;
	glViewport ( 0, 0, esContext->width, esContext->height );

	_iv_h = 1.f/(esContext->height*0.5f);
	_iv_w = 1.f/(esContext->width*0.5f);
	return true;

}

void Renderer::shutdown()
{
	glDeleteProgram(_shader_program_object);
}

Renderer* g_renderer = Renderer::get_instance();