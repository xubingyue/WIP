#pragma once

class WIPFrameBox;
class WIPTexture;
class WIPBaseTexture;

class WIPSpriteFrame
{
public:
	WIPFrameBox* framebox;
	WIPBaseTexture* texture;

	//void reset_texture(WIPTexture* texture);
	//void update_frame_box();
};