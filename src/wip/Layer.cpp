#include "Layer.h"
#include "RenderBatch.h"

WIPLayer::WIPLayer()
{
	_batch = new WIPRenderBatch();
}

WIPLayer::~WIPLayer()
{
	delete _batch;
}