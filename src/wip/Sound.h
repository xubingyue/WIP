#pragma once
#include "al.h"
#include "alut.h"
#include "ResourceManager.h"
#include "SoundBase.h"

class WIPSoundPlayer;
enum WIPSoundStates
{
	UNINITIAL,
	INITIAL,
	PALYING,
	PAUSED,
	STOPPED,

};

enum SoundInGameTypes
{
	WIP_SE,
	WIP_BGM
};

class WIPSound : public WIPSoundBase
{
public:
	
	WIPSound(const char* ptah,SoundInGameTypes type);
	~WIPSound();
	
	void free_source();
	inline SoundInGameTypes get_in_game_types()
	{
		return _sound_in_game_type;
	}
	inline int get_frequency()
	{
		return _frequency;
	}
	inline bool is_loop()
	{
		return _loop;
	}
	inline int get_size()
	{
		return _size;
	}
	ALCuint get_buffer_index()
	{
		return _buffer_index;
	}
	ALCuint get_source_index()
	{
		return _source_index;
	}
	ALenum get_al_format()
	{
		return _al_format;
	}

	int get_volume()
	{
		return _volume;
	}

	void set_state(WIPSoundStates state)
	{
		_state = state;
	}
	WIPSoundStates get_state()
	{
		return _state;
	}
	bool is_in_list()
	{
		return _bin_playing_list;
	}


private:
	bool load_source(const char* path);
	void set_volume(int volume)
	{
		_volume = volume;
	}
	void set_in_list_tag(bool val)
	{
		_bin_playing_list = val;
	}
	void set_loop(bool val)
	{
		_loop = val;
	}

private:
	bool generate_sound();
	void release_sound();
	SoundInGameTypes _sound_in_game_type;
	int _frequency;
	bool _loop;
	int _size;
	//每个资源一个，可能有两个sound具有一样的bufferindex但是每个资源仅有一个sourceindex
	ALCuint _buffer_index;
	//
	ALCuint _source_index;
	ALenum _al_format;
	ResHandler* _handler;

	bool _bin_playing_list;
	int _volume;
	WIPSoundStates _state;
	static WIPResourceManager* _manager;

	friend WIPSoundPlayer;
};