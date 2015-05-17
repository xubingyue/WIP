#include "extension.h"
#include "spine.h"
#include "Texture.h"

void _spAtlasPage_createTexture (spAtlasPage* self, const char* path)
{
	/*
	CxImage *px  = new CxImage();
	TCHAR p[256] = {'\0'};
	mbstowcs(p,path,strlen(path));
	if(!px->Load(p,CXIMAGE_FORMAT_PNG)) return;
	self->rendererObject = px;
	self->width = px->GetWidth();
	self->height = px->GetHeight();
	*/
	WIPTexture* tex = new WIPTexture(path);
	if (!tex->get_resource_reference())
	{
		getchar();
		return;
	}
	self->rendererObject = tex;
	self->width = tex->get_width();
	self->height = tex->get_height();
}

void _spAtlasPage_disposeTexture (spAtlasPage* self)
{
	delete (WIPTexture*)self->rendererObject;
	//delete (CxImage*)self->rendererObject;
}

char* _spUtil_readFile (const char* path, int* length)
{
	//can't delete.
	/*
	ResHandler* res = g_res_manager->load_resource(path,TEXT);
	if(!res)
		return NULL;
	*length = res->size;

	char* ret = (char*)((std::string*)(res->ptr))->data();

	return ret;
	*/
	
	return _readFile(path, length);
}
