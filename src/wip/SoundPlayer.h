#pragma once
#include "alut.h"
#include "al.h"
#include "alc.h"
#include "alext.h"
#include "codec.h"
#include "vorbisfile.h"
#include "Sound.h"
#include "Utilities/NoCopy.h"
#include "Utilities/WPVector.h"
#include "OggStream.h"
#include "SoundBase.h"


/*
对应关系：
SoundPlayer----renderer
sound----texture

SoundPlayer的机制是，加入队列的声音仅仅是为了同一标识此声音已经播放过，与动画队列不同

*/



class WIPSoundPlayer : private WIPNoCopy
{
public:
	static WIPSoundPlayer* get_instance();
	

	bool startup();
	void shutdown();
	void play(WIPSound* sound,int volume);
	void play_stream(WIPSoundBase* sound,bool loop);
	void play(WIPSound* sound);
	void pause(WIPSound* sound);
	//0.0-1.0
	void set_volume(WIPSound* sound,float volume);
	//
	void rewind(WIPSound* sound);
	void stop(WIPSound*sound);
	void stop_forever(WIPSound* sound);
	void delete_sound(WIPSound* sound);
	void clear_all_sounds();
	WIPSoundStates get_sound_state();
	void set_sound_state(WIPSound* sound,ALint st);
	void update();
	void set_loop(WIPSound* sound,bool v);

	~WIPSoundPlayer();
protected:

private:
	WIPSoundPlayer();
	typedef Vector<WIPSoundBase*> _VectorList;
	_VectorList _audio_list;
	ALCdevice* _device;
	// 上下文
	ALCcontext* _context;
	static WIPSoundPlayer* _instance;
	
};

extern WIPSoundPlayer* g_sound_palyer;