#pragma once
#include <list>

class WIPRenderBatch;
class WIPScene;
class WIPAppManager;

class WIPLayer
{
public:
	WIPLayer();
	~WIPLayer();
	friend WIPScene;
	
protected:
	friend WIPAppManager;
	WIPRenderBatch* _batch;
private:
	
};