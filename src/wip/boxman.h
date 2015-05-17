#pragma once
#include "Shader.h"
#include "vmath.h"
#include "Model3D.h"
#include "Input.h"


WIPShader shader;
WIPModel3D man;
WIPModel3D leg1;
WIPModel3D leg2;
WIPModel3D leg3;

vmath::mat4 proj_matrix;
vmath::mat4 mv_matrix;

float thetax = 0.f;
float alphax = 0.f;
float gamax  = 0.f;
float thetay = 0.f;
float alphay = 0.f;
float gamay = 0.f;
float thetaz = 0.f;
float alphaz = 0.f;
float gamaz = 0.f;

bool mouse_drag = false;

int blend = 0;

WIPShader boxman_shader;

#include "AppManager.h"

struct Node
{
	vmath::mat4 mat;
	int bn;
	Node* next[4];
	Node* parent;
	Node()
	{
		bn = 0;
		next[0] = next[1] = next[2] = next[3] = 0;
		parent = 0;
	}
};

struct Boxman
{
	vmath::mat4 root[2];
	vmath::mat4 left_leg_up[2];
	vmath::mat4 left_leg_down[2];
	vmath::mat4 right_leg_up[2];
	vmath::mat4 right_leg_down[2];
	vmath::mat4 body_middle[2];
	vmath::mat4 body_up[2];
	vmath::mat4 left_arm_up[2];
	vmath::mat4 left_arm_down[2];
	vmath::mat4 right_arm_up[2];
	vmath::mat4 right_arm_down[2];
	WIPModel3D * model_ref;
	Node* hroot;
	vmath::mat4 mats[11];
	Boxman(WIPModel3D * model_ref)
	{
		for(int i=0;i<11;i++)
		{
			mats[i] = vmath::mat4::identity();
		}


		this->model_ref = model_ref;
		//³õÊ¼»¯Æ«ÒÆ¾ØÕó
		root[0] = vmath::translate(0.f,-40.f,0.f);
		left_leg_up[0] = vmath::translate(3.75f,-40.f,0.f);
		left_leg_down[0] = vmath::translate(3.75f,-20.f,0.f);
		right_leg_up[0] = vmath::translate(-3.75f,-40.f,0.f);
		right_leg_down[0] = vmath::translate(-3.75f,-20.f,0.f);
		body_middle[0] = vmath::translate(0.f,-55.f,0.f);
		body_up[0] = vmath::translate(0.f,-70.f,0.f);
		left_arm_up[0] = vmath::translate(10.f,-70.f,0.f);
		left_arm_down[0] = vmath::translate(10.f,-55.f,0.f);
		right_arm_up[0] = vmath::translate(-10.f,-70.f,0.f);
		right_arm_down[0] = vmath::translate(-10.f,-55.f,0.f);
		//³õÊ¼»¯Ðý×ª¾ØÕó
		root[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		left_leg_up[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		left_leg_down[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		right_leg_up[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		right_leg_down[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		body_middle[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		body_up[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		left_arm_up[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		left_arm_down[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		right_arm_up[1] = vmath::rotate(0.f,0.f,1.f,0.f);
		right_arm_down[1] = vmath::rotate(0.f,0.f,1.f,0.f);


		Node* mroot = new Node;
		mroot->mat = vmath::translate(0.f,40.f,0.f)*root[1];
		mroot->bn = 0;

		Node* mleft_leg_up = new Node;
		mleft_leg_up->mat = vmath::translate(-3.75f,0.f,0.f)*left_leg_up[1];
		mleft_leg_up->bn = 1;

		Node* mleft_leg_down = new Node;
		mleft_leg_down->mat = vmath::translate(0.f,-20.f,0.f)*left_leg_down[1];
		mleft_leg_down->bn = 2;

		Node* mright_leg_up = new Node;
		mright_leg_up->mat = vmath::translate(3.75f,0.f,0.f)*right_leg_up[1];
		mright_leg_up->bn = 3;

		Node* mright_leg_down = new Node;
		mright_leg_down->mat = vmath::translate(0.f,-20.f,0.f)*right_leg_down[1];
		mright_leg_down->bn = 4;

		Node* mbody_middle = new Node;
		mbody_middle->mat = vmath::translate(0.f,15.f,0.f)*body_middle[1];
		mbody_middle->bn = 5;

		Node* mbody_up = new Node;
		mbody_up->mat = vmath::translate(0.f,15.f,0.f)*body_up[1];
		mbody_up->bn = 6;

		Node* mleft_arm_up = new Node;
		mleft_arm_up->mat = vmath::translate(-10.f,15.f,0.f)*left_arm_up[1];
		mleft_arm_up->bn = 7;

		Node* mleft_arm_down = new Node;
		mleft_arm_down->mat = vmath::translate(0.f,-15.f,0.f)*left_arm_down[1];
		mleft_arm_down->bn = 8;

		Node* mright_arm_up = new Node;
		mright_arm_up->mat = vmath::translate(10.f,15.f,0.f)*right_arm_up[1];
		mright_arm_up->bn = 9;

		Node* mright_arm_down = new Node;
		mright_arm_down->mat = vmath::translate(0.f,-15.f,0.f)*right_arm_down[1];
		mright_arm_down->bn = 10;

		mroot->next[0] = mleft_leg_up;mleft_leg_up->parent = mroot;
		mroot->next[1] = mright_leg_up;mright_leg_up->parent = mroot;
		mroot->next[2] = mbody_middle;mbody_middle->parent = mroot;

		mleft_leg_up->next[0] = mleft_leg_down;mleft_leg_down->parent = mleft_leg_up;
		mright_leg_up->next[0] = mright_leg_down;mright_leg_down->parent = mright_leg_up;

		mbody_middle->next[0] = mleft_arm_up;mleft_arm_up->parent = mbody_middle;
		mbody_middle->next[1] = mright_arm_up;mright_arm_up->parent = mbody_middle;
		mbody_middle->next[2] = mbody_up;mbody_up->parent = mbody_middle;

		mleft_arm_up->next[0] = mleft_arm_down;mleft_arm_down->parent = mleft_arm_up;
		mright_arm_up->next[0] = mright_arm_down;mright_arm_down->parent = mright_arm_up;

		hroot = mroot;
	}

	void push(Node* n,vmath::mat4 m)
	{
		if(n)
		{
			switch (n->bn)
			{
			case 0:
				n->mat *= root[1];
				break;
			case 1:
				n->mat*=left_leg_up[1];
				break;
			case 2:
				n->mat*=left_leg_down[1];
				break;
			case 3:
				n->mat*=right_leg_up[1];
				break;
			case 4:
				n->mat*=right_leg_down[1];
				break;
			case 5:
				n->mat*=body_middle[1];
				break;
			case 6:
				n->mat *= body_up[1];
				break;
			case 7:
				n->mat*=left_arm_up[1];
				break;
			case 8:
				n->mat*=left_arm_down[1];
				break;
			case 9:
				n->mat*=right_arm_up[1];
				break;
			case 10:
				n->mat*=right_arm_down[1];
				break;
			default:
				break;
			}

			mats[n->bn] = m*n->mat*mats[n->bn];
		}
		else
		{
			return;
		}
		for(int i=0;i<4;i++)
		{
			if(n->next[i])
			{
				push(n->next[i],mats[n->bn]);
				
			}
		}

			


	}

	void calc(Node* node)
	{



		push(node,vmath::mat4::identity());
		/*
		//mats[node->bn] = node->mat*mats[node->bn];


		for(int i=0;i<4;i++)
		{
			if(node->next[i])
			{

				calc(node->next[i]);
				//mats[node->next[i]->bn] = node->mat*mats[node->next[i]->bn];
				
			}

		}
		
		if(node)
		{
			mats[node->bn] = node->mat*mats[node->bn];
	
		}
		else
			return;
			*/
	}
	void draw()
	{
			boxman_shader.begin();
			boxman_shader.set_uniform_matrix("m00",root[0]);
			boxman_shader.set_uniform_matrix("m10",left_leg_up[0]);
			boxman_shader.set_uniform_matrix("m20",left_leg_down[0]);
			boxman_shader.set_uniform_matrix("m30",right_leg_up[0]);
			boxman_shader.set_uniform_matrix("m40",right_leg_down[0]);
			boxman_shader.set_uniform_matrix("m50",body_middle[0]);
			boxman_shader.set_uniform_matrix("m60",body_up[0]);
			boxman_shader.set_uniform_matrix("m70",left_arm_up[0]);
			boxman_shader.set_uniform_matrix("m80",left_arm_down[0]);
			boxman_shader.set_uniform_matrix("m90",right_arm_up[0]);
			boxman_shader.set_uniform_matrix("m100",right_arm_down[0]);
			boxman_shader.set_uniform_matrix("m0",mats[0]);
			boxman_shader.set_uniform_matrix("m1",mats[1]);
			boxman_shader.set_uniform_matrix("m2",mats[2]);
			boxman_shader.set_uniform_matrix("m3",mats[3]);
			boxman_shader.set_uniform_matrix("m4",mats[4]);
			boxman_shader.set_uniform_matrix("m5",mats[5]);
			boxman_shader.set_uniform_matrix("m6",mats[6]);
			boxman_shader.set_uniform_matrix("m7",mats[7]);
			boxman_shader.set_uniform_matrix("m8",mats[8]);
			boxman_shader.set_uniform_matrix("m9",mats[9]);
			boxman_shader.set_uniform_matrix("m11",mats[10]);
			boxman_shader.set_uniform_matrix("mv_matrix",mv_matrix);
			boxman_shader.set_uniform_matrix("proj_matrix",proj_matrix);
			boxman_shader.set_uniform_i("vn",0);
			model_ref->renderer(GL_TRIANGLES);
			glPointSize(20);
			glDrawArrays(GL_POINTS,0,1);

			boxman_shader.end();
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK   ,GL_LINE   );
			boxman_shader.begin();
			boxman_shader.set_uniform_matrix("m00",root[0]);
			boxman_shader.set_uniform_matrix("m10",left_leg_up[0]);
			boxman_shader.set_uniform_matrix("m20",left_leg_down[0]);
			boxman_shader.set_uniform_matrix("m30",right_leg_up[0]);
			boxman_shader.set_uniform_matrix("m40",right_leg_down[0]);
			boxman_shader.set_uniform_matrix("m50",body_middle[0]);
			boxman_shader.set_uniform_matrix("m60",body_up[0]);
			boxman_shader.set_uniform_matrix("m70",left_arm_up[0]);
			boxman_shader.set_uniform_matrix("m80",left_arm_down[0]);
			boxman_shader.set_uniform_matrix("m90",right_arm_up[0]);
			boxman_shader.set_uniform_matrix("m100",right_arm_down[0]);
			boxman_shader.set_uniform_matrix("m0",mats[0]);
			boxman_shader.set_uniform_matrix("m1",mats[1]);
			boxman_shader.set_uniform_matrix("m2",mats[2]);
			boxman_shader.set_uniform_matrix("m3",mats[3]);
			boxman_shader.set_uniform_matrix("m4",mats[4]);
			boxman_shader.set_uniform_matrix("m5",mats[5]);
			boxman_shader.set_uniform_matrix("m6",mats[6]);
			boxman_shader.set_uniform_matrix("m7",mats[7]);
			boxman_shader.set_uniform_matrix("m8",mats[8]);
			boxman_shader.set_uniform_matrix("m9",mats[9]);
			boxman_shader.set_uniform_matrix("m11",mats[10]);
			boxman_shader.set_uniform_matrix("mv_matrix",mv_matrix);
			boxman_shader.set_uniform_matrix("proj_matrix",proj_matrix);
			boxman_shader.set_uniform_i("vn",1);
			model_ref->renderer(GL_TRIANGLES);
			glPointSize(20);
			glDrawArrays(GL_POINTS,0,1);
			boxman_shader.end();
			glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK   ,GL_FILL   );
			for(int i=0;i<11;i++)
		{
			mats[i] = vmath::mat4::identity();
		}
			
			body_up[1] = vmath::mat4::identity();
			root[1] = vmath::mat4::identity();
			left_leg_up[1] = vmath::mat4::identity();
			left_leg_down[1] = vmath::mat4::identity();
			right_leg_up[1] = vmath::mat4::identity();
			right_leg_down[1] = vmath::mat4::identity();
			body_middle[1] = vmath::mat4::identity();

			left_arm_up[1] = vmath::mat4::identity();
			left_arm_down[1] = vmath::mat4::identity();
			right_arm_up[1] = vmath::mat4::identity();
			right_arm_down[1] = vmath::mat4::identity();
	}
	void rotate_body_middle(float degree)
	{
		body_middle[1] = vmath::rotate(degree,0.f,1.f,0.f);
	}
	void rotate_head(float degree)
	{

		body_up[1] = vmath::rotate(degree,0.f,1.f,0.f);
	}
	void rotate_left_arm_up(float degree)
	{
		left_arm_up[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_left_arm_down(float degree)
	{
		left_arm_down[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_right_arm_up(float degree)
	{
		right_arm_up[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_right_arm_down(float degree)
	{
		right_arm_down[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_left_leg_up(float degree)
	{
		left_leg_up[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_left_leg_down(float degree)
	{
		left_leg_down[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_right_leg_up(float degree)
	{
		right_leg_up[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void rotate_right_leg_down(float degree)
	{
		right_leg_down[1] = vmath::rotate(degree,1.f,0.f,0.f);
	}
	void roatate_root(float degree)
	{
		root[1] =  vmath::rotate(degree,0.f,1.f,0.f);
	}
} boxman1(&man),boxman2(&man);

void handle_input();

void handle_input()
{
	int sx(-1),sy(-1);
	int ex,ey;

	if(Input::get_sys_key_pressed(WIP_MOUSE_RBUTTON))
	{
		if(sx==-1&&sy==-1)
		{
			sx = Input::get_mouse_x();
			sy = Input::get_mouse_y();
		}

		if(Input::is_move())
		{
			
			ex = Input::get_mouse_x() - sx;
			ey = Input::get_mouse_y() - sy;
		}




	}

	if (Input::get_sys_key_up(WIP_MOUSE_RBUTTON))
	{
		sx = -1;
		sy = -1;
	}
	

	//if(Input::get_key_pressed(WIP_W))
	//{
	//	ty += transform_speed_y;
	//}
	//if (Input::get_key_pressed(WIP_S))
	//{
	//	ty -= transform_speed_y;
	//}
	//if(Input::get_key_pressed(WIP_A))
	//{
	//	tx -= transform_speed_x;
	//}
	//if(Input::get_key_pressed(WIP_D))
	//{
	//	tx += transform_speed_x;
	//}
	//if (Input::get_sys_key_pressed(WIP_MOUSE_SCROLLER_DOWN))
	//{
	//	tz -= 5.f; 
	//}
	//if (Input::get_sys_key_pressed(WIP_MOUSE_SCROLLER_UP))
	//{
	//	tz += 5.f;
	//}
	//if(Input::get_key_pressed(WIP_J))
	//{

	//	degreex += 2.f;
	//}


	//if(Input::get_key_pressed(WIP_K))
	//{

	//	degreey += 2.f;
	//}
	//if(Input::get_key_pressed(WIP_L))
	//{
	//	degreez += 2.f;
	//}
	//if(Input::get_key_pressed(WIP_U))
	//{

	//	degreex -= 2.f;
	//}

	//if(Input::get_key_pressed(WIP_I))
	//{
	//	
	//	degreey -= 2.f;
	//}
	//if(Input::get_key_pressed(WIP_O))
	//{

	//	degreez -= 2.f;
	//}


	if(Input::get_key_pressed(WIP_R))
	{

		boxman1.rotate_body_middle(5);
	}
	if(Input::get_key_pressed(WIP_F))
	{

		boxman1.rotate_right_arm_up(5);
	}
	if(Input::get_key_pressed(WIP_G))
	{

		boxman1.rotate_right_leg_down(5);
	}
	if(Input::get_key_pressed(WIP_H))
	{

		boxman1.rotate_right_leg_up(5);
	}
	if(Input::get_key_pressed(WIP_C))
	{

		boxman1.rotate_left_arm_down(5);
	}
	if(Input::get_key_pressed(WIP_V))
	{
		boxman1.rotate_left_arm_up(5);
	}
	if(Input::get_key_pressed(WIP_B))
	{

		boxman1.rotate_left_leg_down(5);
		
	}
	if(Input::get_key_pressed(WIP_N))
	{

		boxman1.rotate_left_leg_up(5);
	}
	if(Input::get_key_pressed(WIP_M))
	{

		boxman1.rotate_right_arm_down(5);

	}
	if(Input::get_key_pressed(WIP_X))
	{
		boxman1.roatate_root(5);
	}
	if(Input::get_key_pressed(WIP_Z))
	{

		boxman1.rotate_head(5);
	}
}

void init()
{
	bool o = shader.load("resources/vertex.c","resources/fragment.c",0);
	boxman_shader.load("resources/boxman_v.c","resources/boxman_f.c","resources/boxman_g.c");
	man.load("resources/boxman.obj");
	//man.load_weight("resources/boxman.weight");
	//leg1.load("resources/legl.obj");
	//leg1.load_weight("resources/legl.weight");
		glClearDepth(1);
}

void update()
{
	handle_input();
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK   ,GL_LINE   );



	


	vmath::mat4 mat_rotate_alpha = vmath::rotate(alphax,1.f,0.f,0.f)*vmath::rotate(alphay,0.f,1.f,0.f)*vmath::rotate(alphaz,0.f,0.f,1.f);
	vmath::mat4 mat_rotate_theta = vmath::rotate(thetax,1.f,0.f,0.f)*vmath::rotate(thetay,0.f,1.f,0.f)*vmath::rotate(thetaz,0.f,0.f,1.f);
	vmath::mat4 mat_rotate_gama = vmath::rotate(gamax,1.f,0.f,0.f)*vmath::rotate(gamay,0.f,1.f,0.f)*vmath::rotate(gamaz,0.f,0.f,1.f);


	vmath::mat4 matb1 = mat_rotate_alpha;
	vmath::mat4 matb2 = mat_rotate_alpha*vmath::translate(0.f,24.f,0.f)*mat_rotate_theta;
	vmath::mat4 matb3 = 
		mat_rotate_alpha*vmath::translate(0.f,24.f,0.f)*mat_rotate_theta*vmath::translate(0.f,24.f,0.f)*
		mat_rotate_gama;

	vmath::mat4 i_matw = (mv_matrix*proj_matrix);

	/*
	shader.begin();
	shader.set_uniform_matrix("mv_matrix",mv_matrix);
	shader.set_uniform_matrix("proj_matrix",proj_matrix);
	shader.set_uniform_matrix("b1_matrix",matb1);
	shader.set_uniform_matrix("b2_matrix",matb2);
	shader.set_uniform_matrix("b3_matrix",matb3);
	shader.set_uniform_i("bone",1);
	shader.set_uniform_i("blend",blend);
	leg1.renderer(GL_TRIANGLES);
	shader.end();
	*/
	
	
	boxman1.calc(boxman1.hroot);
	boxman1.draw();
	/*
	mv_matrix = vmath::translate(tx+100,ty,tz) *
		vmath::rotate(degreex, 1.f, 0.f, 0.f)*vmath::rotate(degreey, 0.f, 1.f, 0.f)*vmath::rotate(degreez,0.f, 0.f, 1.f);
		boxman2.calc(boxman2.hroot);
	boxman2.draw();
	shader.begin();
	shader.set_uniform_matrix("mv_matrix",mv_matrix);
	shader.set_uniform_matrix("proj_matrix",proj_matrix);
	shader.set_uniform_i("blend",2);
	glPointSize(10);
	glDrawArrays(GL_POINTS,0,1);
	shader.end();
	*/

	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK   ,GL_FILL   );
}

void draw(...)
{

}