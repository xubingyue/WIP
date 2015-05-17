#include "Renderable.h"


WIPRenderable::_WIPRenderPack::_WIPRenderPack()
{
	framebox = 0;
	tex_id = 0;
	z_order = -1;

}

		void WIPRenderable::_WIPRenderPack::update(GLuint tex_id,i32 z_order)
		{
			this->tex_id = tex_id;
			this->z_order = z_order;
		}

		bool WIPRenderable::_WIPRenderPack::operator < (const _WIPRenderPack& n)
		{
			return z_order < n.z_order;
		}

		bool WIPRenderable::_WIPRenderPack::operator > (const _WIPRenderPack& n)
		{
			return z_order > n.z_order;
		}