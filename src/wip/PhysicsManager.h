#pragma once

#include "floekr2d/Floekr2d/Floekr2d.h"
#include "RBMath/Inc/Platform/RBBasedata.h"

class WIPScene;

class WIPPhysicsManager
{
	public:
	static WIPPhysicsManager* instance();
	//create a space,but now we don't support it
	static void create_space(){}

	static Floekr2d::f2PolygonShape* create_polygon();
	static Floekr2d::f2CircleShape* create_circle();
	static Floekr2d::f2Body* create_body();

	static void delete_body(Floekr2d::f2Body* b);

	bool startup();
	void update(WIPScene* scene);
	void shutdown();

protected:
	WIPPhysicsManager();
	~WIPPhysicsManager();

private:
	static WIPPhysicsManager* _instance;
	static Floekr2d::f2Space* _phy_space;

};

extern WIPPhysicsManager* g_physics_manager;