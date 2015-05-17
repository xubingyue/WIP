#include "Sound.h"
#include "ResourceManager.h"

WIPResourceManager* WIPSound::_manager = g_res_manager;

WIPSound::WIPSound(const char* path,SoundInGameTypes type) : WIPSoundBase(false)
{
	_handler = NULL;
	_sound_in_game_type = type;
	_al_format = AL_FORMAT_MONO16;
	_buffer_index = _source_index = 0;
	_size = 0;
	_frequency = 0;
	_loop = false;
	if(load_source(path))
	{
		_state = WIPSoundStates::INITIAL;
		
	}
	else
	{
		//log
		_handler = NULL;
		_state = WIPSoundStates::UNINITIAL;
	}
	_bin_playing_list = false;
}

WIPSound::~WIPSound()
{
	free_source();
}

bool WIPSound::load_source(const char* path)
{

	_handler = g_res_manager->load_resource(path,SOUND);

	/*
	ALCuint si,si2;
	alGenSources(1,&si);
	alGenSources(1,&si2);
	alSourcei(si,AL_BUFFER,((SoundData*)_handler->extra)->buffer_index);
	alSourcei(si2,AL_BUFFER,((SoundData*)_handler->extra)->buffer_index);
	*/
	_size = _handler->size;
	_frequency = ((SoundData*)_handler->extra)->frequency;
	_al_format =  ((SoundData*)_handler->extra)->al_format;
	_loop =  ((SoundData*)_handler->extra)->loop;
	_buffer_index =  ((SoundData*)_handler->extra)->buffer_index;
	if(!_handler)
		return false;
	generate_sound();
	return true;
}

bool WIPSound::generate_sound()
{
	/*
	if (!_handler->ptr)
	{
		return false;
	}
	*/
	if(_buffer_index==0)
		return false;
	alGenSources(1,&_source_index);
	if (alGetError() != AL_NO_ERROR)
	{
		//log
		printf("alGenSources failed!\n");
		getchar();
		exit(0);
	}
	alSourcei (_source_index, AL_BUFFER, _buffer_index);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("alSourcei failed!\n");
		//log
		getchar();
		exit(0);
	}

	return true;
}

void WIPSound::release_sound()
{
	alDeleteSources(1,&_source_index);
	int e = alGetError();
	if ( e!= AL_NO_ERROR)
	{
		printf("alDeleteSources failed!:%d\n",e);
		getchar();
		exit(0);
	}
	_source_index = 0;
}

void WIPSound::free_source()
{
	if(_handler==NULL)
		return;
	release_sound();
	
	if(_manager->free(_handler,_handler->size)!=FAIL)
		_handler = NULL;

}