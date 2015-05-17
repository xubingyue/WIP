#pragma once
#define _POLYSHAPE_DISABLE_PRIVATE
#include "RBMath/Inc/Platform/RBBasedata.h"
#include "RBMath/Inc/Vector2.h"
#include "floekr2d/Floekr2d/Floekr2d.h"
using namespace Floekr2d;

class WIPSprite;
class WIPPhysicsManager;
class WIPAppManager;
class WIPMesh;

class WIPCollider
{
public:
	enum _FrictionTypes
	{
		E_DYNAMIC = 1,
		E_STATIC,
		E_FRICTION_COUNT,
	};

	enum _ShapeTypes
	{
		E_POLYGON = 1,
		E_CIRCLE,
		E_SHAPE_COUNT,
	};

	enum _CollisionTypes
	{
		//
		E_RIGIDBODY=1,
		//
		E_STATIC_RIGIDBODY,
		//参加碰撞检测但是没有物理
		E_NO_PHYSICS,
		//不参加碰撞检测没有物理
		E_GHOST,
		E_COLIISION_COUNT,
	};

	//now noly support polygon shape
	static WIPCollider* create_collider(WIPMesh* m = 0);
	WIPCollider();
	~WIPCollider();
	//n is vertex number v contains 2*v elements
	void reset_polygon_vertices(WIPMesh* v,i32 n = 4);
	void reset_polygon_position(f32 x,f32 y);
	void reset_polygon_density(f32 density);

	void reset_body_rad(f32 rad);
	void reset_body_restitution(f32 restitution);
	void reset_body_friction(f32 v,_FrictionTypes type);


	void reset_body_type(_CollisionTypes type);

	FORCEINLINE void add_force(f32 x,f32 y)
	{
		_body->applyForce(x,y);

		//Floekr2d::math::f2Vector2f a = _body->getForces() * _body->getInverseMass();
		//printf("%f, %f\n",a.x, a.y);
	}

	void update_out(WIPMesh& mesh,f32& rad,f32& x,f32 &y);
	void update_in(WIPMesh* mesh,f32 rad,f32 x,f32 y);
	//There is no attach method.It is in the Sprite.
	//void attach_sprite(WIPSprite* s);
	void set_active(bool v);
	FORCEINLINE bool get_active()
	{
		return _active;
	}

	i32 get_collision_list_size()
	{
		i32 t = _body->getCollideBodies().size();
		return t;
	}

	f2Body* get_collision_index_body(i32 i)
	{
		return _body->getCollideBodies()[i];
	}

	bool is_collision_list_empty()
	{
		return _body->getCollideBodies().isEmpty();
	}

	void set_density(f32 density)
	{
		_polygon_shape->setDensity(density);
		//_body->setShape(_polygon_shape);
	}

	FORCEINLINE f32 get_speed_x()
	{
		return _body->getLinearVelocity().x;
	}

	FORCEINLINE f32 get_speed_y()
	{
		return _body->getLinearVelocity().y;
	}

protected:
	
	
private:
	friend WIPPhysicsManager;
	friend WIPSprite;
	friend WIPAppManager;
	f2Shape* _shape;
	f2PolygonShape* _polygon_shape;
	f2Body* _body;
	f2CircleShape* _circle_shape;
	bool _active;
};