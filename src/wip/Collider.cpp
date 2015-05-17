#include "Collider.h"

#include "Sprite.h"
#include "PhysicsManager.h"
WIPCollider* WIPCollider::create_collider(WIPMesh* m)
{

	WIPCollider* ret;
	ret = new WIPCollider();
	ret->_polygon_shape = g_physics_manager->create_polygon();
	
	if(m)
	{
		ret->reset_polygon_vertices(m,4);
		ret->_active = true;
	}
	else
	{
		ret->_polygon_shape->vertices[0].x = 
			ret->_polygon_shape->vertices[0].y = 
			ret->_polygon_shape->vertices[1].x = 
			ret->_polygon_shape->vertices[1].y = 
			ret->_polygon_shape->vertices[2].x = 
			ret->_polygon_shape->vertices[2].y = 
			ret->_polygon_shape->vertices[3].x = 
			ret->_polygon_shape->vertices[3].y = 0;
		ret->_polygon_shape->vertexCount = 4;
	}
	ret->_polygon_shape->setDensity(0.001f);
	ret->_body = g_physics_manager->create_body();
	ret->_body->setShape(ret->_polygon_shape);
	return ret;
}

void WIPCollider::set_active(bool v)
{
	_active = v;
	if(!_active)
	{
		_body->setCollisionDetectable(false);
		_body->setType(f2Body::e_static);
	}
	else
	{
		_body->setCollisionDetectable(true);
		_body->setType(f2Body::e_kinematic);
	}

}

void WIPCollider::reset_body_type(_CollisionTypes type)
{
	switch (type)
	{
	case E_RIGIDBODY:
		
		_body->setCollisionDetectable(true);
		_body->setCollisionFeedBack(true);
		_body->setType(f2Body::e_kinematic);
		
		break;
	case E_STATIC_RIGIDBODY:
		
		_body->setCollisionDetectable(true);
		_body->setCollisionFeedBack(true);
		_body->setType(f2Body::e_static);
		_body->setShape(_polygon_shape);
		


		break;
	case E_NO_PHYSICS:
		_body->setCollisionDetectable(true);
		_body->setCollisionFeedBack(false);
		break;
	case E_GHOST:
	default:
		_body->setCollisionDetectable(false);
		_body->setCollisionFeedBack(false);
		break;
	}
	
}

WIPCollider::WIPCollider()
{
	_active = false;
}

WIPCollider::~WIPCollider()
{
	g_physics_manager->delete_body(_body);
}

void WIPCollider::reset_polygon_vertices(WIPMesh* v,i32 n)
{
	i32 i = 0;
	math::f2Vector2f *ve = new math::f2Vector2f[n];
	ve[0].x = v->rb.x;
	ve[0].y = v->rb.y;
	ve[1].x = v->lt.x;
	ve[1].y = v->lt.y;
	ve[2].x = v->rt.x;
	ve[2].y = v->rt.y;
	ve[3].x = v->lb.x;
	ve[3].y = v->lb.y;
	//setVertices this auto sort
	_polygon_shape->setVertices(ve,4);
	delete[] ve;

	/*
	_polygon_shape->vertices[0].x = v->lt.x;
	_polygon_shape->vertices[0].y = v->lt.y;
	_polygon_shape->vertices[1].x = v->lb.x;
	_polygon_shape->vertices[1].y = v->lb.y;
	_polygon_shape->vertices[2].x = v->rb.x;
	_polygon_shape->vertices[2].y = v->rb.y;
	_polygon_shape->vertices[3].x = v->rt.x;
	_polygon_shape->vertices[3].y = v->rt.y;

	_polygon_shape->vertexCount = n;

	//generate normals
	*/

	
}

void WIPCollider::reset_polygon_position(f32 x,f32 y)
{
	_polygon_shape->setPosition(x,y);
}

void WIPCollider::reset_polygon_density(f32 density)
{
	_polygon_shape->setDensity(density);
}

void WIPCollider::reset_body_rad(f32 rad)
{
	_body->setRadians(rad);
}

void WIPCollider::reset_body_restitution(f32 v)
{
	_body->restitution = v;
}

void WIPCollider::reset_body_friction(f32 v,_FrictionTypes type)
{
	switch (type)
	{
	case _FrictionTypes::E_DYNAMIC:
		_body->dynamicFriction = v;
		break;
	case _FrictionTypes::E_STATIC:
		_body->staticFriction = v;
		break;
	default:
		break;
	}
	

}

void WIPCollider::update_out(WIPMesh& mesh,f32& rad,f32& x,f32 &y)
{
	math::f2Vector2f p = _body->getPosition();
	x = p.x;
	y = p.y;

	math::f2Vector2f v = _polygon_shape->getVertice(2);
	mesh.lt.x = v.x;
	mesh.lt.y = v.y;
	v = _polygon_shape->getVertice(3);
	mesh.lb.x = v.x;
	mesh.lb.y = v.y;
	v = _polygon_shape->getVertice(0);
	mesh.rb.x = v.x;
	mesh.rb.y = v.y;
	v = _polygon_shape->getVertice(1);
	mesh.rt.x = v.x;
	mesh.rt.y = v.y;


}

void WIPCollider::update_in(WIPMesh* mesh,f32 rad,f32 x,f32 y)
{
	reset_polygon_position(x,y);
	reset_body_rad(rad);

}