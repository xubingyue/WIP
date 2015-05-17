#pragma once
#include "stdio.h"
#include "RBMath/Inc/RBMath.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Renderer.h"
#include "vmath.h"
#include "Model3D.h"
#include "RBMath/Inc/Complex.h"

void init();
void gpu_fft_draw();
void update();


int N = 2;
int L = 2000;

WIPShader shader_test;
WIPShader shader_init_h0;
WIPShader shader_generate_wi;
WIPShader shader_gpu_fft;
WIPTexture *texture;
WIPRenderTexture *render_texture;
WIPModel3D model;

int cur = 1;
WIPRenderTexture *weight_index[2];
WIPRenderTexture *res_back[2];

float data_init[8] = {2.13,0.23,1.98,0.35,-0.983,1.2,2.1,0.3};

float *data_weight_index;
float *data_res_back;

void init_generate()
{

	data_res_back = new float[N*N*4];
	data_weight_index = new float[N*N*4];
	//初始化weight_index表
	//所有权都为  (1,0)或者(-1,0)
	//所有index按照tex_coord位置每两个交叉初始化
	//第一张res_back数据按照二进制反转后的顺序依次初始化到纹理内
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			data_weight_index[i*N+j] = 1.f;
			data_weight_index[i*N+j+1] = 0.f;
			data_weight_index[i*N+j+2] = i;
			data_weight_index[i*N+j+4] = j;

			data_res_back[i*N+j] = data_init[i*N+j];
			data_res_back[i*N+j+1] = data_init[i*N+j+1];
			data_res_back[i*N+j+2] = 0.f;
			data_res_back[i*N+j+3] = 1.f;

		}
	}

	weight_index[0]->set_data(data_weight_index,N+1,N+1);
	res_back[0]->set_data(data_res_back,N,N);

	//delete[] data_res_back;
	//delete[] data_weight_index;
}

void init()
{
	weight_index[0] = WIPRenderTexture::create(N,N,GL_FLOAT,GL_RGBA,GL_RGBA16F);
	weight_index[1] = WIPRenderTexture::create(N,N,GL_FLOAT,GL_RGBA,GL_RGBA32F);

	res_back[0] = WIPRenderTexture::create(N,N,GL_FLOAT,GL_RGBA,GL_RGBA32F);
	res_back[1] = WIPRenderTexture::create(N,N,GL_FLOAT,GL_RGBA,GL_RGBA32F);

	model.load("resources/panel.obj");
	texture = new WIPTexture("resources/s.jpg",N,N);
	render_texture = WIPRenderTexture::create(N,N,GL_FLOAT,GL_RGB,GL_RGBA16F);
	shader_test.load("resources/fft/basic_v.c","resources/fft/copy_texture_f.c",0);
	//shader_init_h0.load("","",0);
	shader_generate_wi.load("resources/fft/basic_v.c","resources/fft/generate_weight_and_index_f.c",0);
	shader_gpu_fft.load("resources/fft/basic_v.c","resources/fft/gpu_fft_f.c",0);


	render_texture->begin();
	render_texture->clear();
	//g_renderer->render(texture->get_texture_id(),-100,-100,1000,1000);
	g_renderer->render(texture->get_texture_id(),0,0,N,N);
	render_texture->end();

	init_generate();
}

void gpu_fft_draw()
{
	//g_renderer->draw_box_ex(0,0,-800,2000,200);
	
}

void update()
{
	return ;
	//printf("%f\n",RBMath::get_gaussian_random());

	//g_renderer->render(texture->get_texture_id(),0,0,500,500);
	int total = RBMath::log_2(N);
	int step = 2;
	

	for(int i=1;step<=total;step*=2,i++)
	{
		shader_gpu_fft.begin();
		shader_gpu_fft.set_uniform_i("size",N);
		shader_gpu_fft.set_uniform_i("n_step",step);
		shader_gpu_fft.set_uniform_texture("tex_index_weight",weight_index[cur]->get_texture_id(),1);
		shader_gpu_fft.set_uniform_texture("tex_res_back",res_back[cur]->get_texture_id(),2);
		res_back[1-cur%2]->begin();
		model.renderer(GL_TRIANGLES);
		res_back[1-cur%2]->end();
		shader_gpu_fft.end();

		shader_generate_wi.begin();
		shader_generate_wi.set_uniform_i("size",N);
		shader_generate_wi.set_uniform_i("n_step",step);
		shader_generate_wi.set_uniform_texture("tex_input",weight_index[cur]->get_texture_id(),3);
		weight_index[1-cur%2]->begin();
		model.renderer(GL_TRIANGLES);
		weight_index[1-cur%2]->end();
		shader_generate_wi.end();

		cur = 1-cur%2;
	}



}

void draw(vmath::mat4 mv,vmath::mat4 proj)
{	
	shader_test.begin();
	
	shader_test.set_uniform_matrix("mv_matrix",mv);
	shader_test.set_uniform_matrix("proj_matrix",proj);
	shader_test.set_uniform_texture("colorMap",weight_index[0]->get_texture_id(),1);
	model.renderer(GL_TRIANGLES);
	
	shader_test.end();

}