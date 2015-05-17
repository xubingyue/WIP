#pragma once

class WIPTexture;
class WIPRenderTexture;

class WIPExtraTool
{
public:
	static bool save_png(WIPRenderTexture* texture,const char* path);
	static bool save_ini(const char* content,const char* path);
private:
	
};