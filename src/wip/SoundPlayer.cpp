#include "SoundPlayer.h"

WIPSoundPlayer*  WIPSoundPlayer::_instance = 0;

WIPSoundPlayer* WIPSoundPlayer::get_instance()
{
	if(!_instance)
	{
		_instance = new WIPSoundPlayer();
	}
	return _instance;
}

bool WIPSoundPlayer::startup()
{
	//create openAL
	// 设备
	_device = 0;
	// 上下文
	_context = 0;
	_device = alcOpenDevice(NULL);
	if (alGetError() != AL_NO_ERROR)
	{
		// 出错,log
		return false;
	}
	else
	{
		// 未出错，创建并选择当前上下文
		_context = alcCreateContext(_device,NULL);
		alcMakeContextCurrent(_context);
	}
	return true;
}

void WIPSoundPlayer::shutdown()
{
	clear_all_sounds();
	_context = alcGetCurrentContext();
	_device = alcGetContextsDevice(_context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

void WIPSoundPlayer::play(WIPSound* sound)
{
	alSourcePlay(sound->get_source_index());
	int e = alGetError();
	if ( e!= AL_NO_ERROR)
	{
		printf("play:%s\n",e);
		getchar();
		exit(0);
	}
	sound->set_state(WIPSoundStates::PALYING);
	if(!sound->is_in_list())
	{
		_audio_list.pushBack(sound);
		sound->set_in_list_tag(true);
	}
}

void WIPSoundPlayer::play(WIPSound* sound,int volume)
{

	alSourcef(sound->get_source_index(), AL_GAIN, volume);
	int e = alGetError();
	if ( e!= AL_NO_ERROR)
	{
		printf("alSourcef(sound->get_source_index(), AL_GAIN, volume);:%d\n",e);
		getchar();
		exit(0);
	}
	sound->set_volume(volume);
	play(sound);
}

void WIPSoundPlayer::pause(WIPSound* sound)
{
	if(sound->is_in_list())
	{
	alSourcePause(sound->get_source_index());
	sound->set_state(WIPSoundStates::PAUSED);
	}
}

void WIPSoundPlayer::rewind(WIPSound* sound)
{
	if(sound->is_in_list())
	{
		alSourceRewind(sound->get_source_index());
		play(sound);
	}
}

void WIPSoundPlayer::stop(WIPSound*sound)
{
	if(sound->is_in_list())
	{
	alSourceStop(sound->get_source_index());
	sound->set_state(WIPSoundStates::STOPPED);
	}
	
}

void WIPSoundPlayer::stop_forever(WIPSound* sound)
{
	if(sound->is_in_list())
	{
	stop(sound);
	delete_sound(sound);
	}
}

void WIPSoundPlayer::update()
{
	for (_VectorList::iterator it=_audio_list.begin();it!=_audio_list.end();++it)
	{
		if ((*it)->stream)
		{
			((OggStream*)(*it))->update();
		}
		else
		{
			WIPSound* s = ((WIPSound*)(*it));
			if (s->get_state()==WIPSoundStates::PALYING)
			{
				ALint st;
				alGetSourcei (s->get_source_index(), AL_SOURCE_STATE, &st);
				set_sound_state( s,st);
			}
		}
	}
}

void WIPSoundPlayer::set_volume(WIPSound* sound,float volume)
{
	alSourcef(sound->get_source_index(), AL_GAIN, volume);
	int e = alGetError();
	if ( e!= AL_NO_ERROR)
	{
		printf("alSourcef(sound->get_source_index(), AL_GAIN, volume);:%d\n",e);
		getchar();
		exit(0);
	}
	sound->set_volume(volume);
}

WIPSoundPlayer::WIPSoundPlayer() 
{
	//let it be empty
}

WIPSoundPlayer::~WIPSoundPlayer()
{
	//let it be empty
}

//no use
WIPSoundStates WIPSoundPlayer::get_sound_state()
{
	return UNINITIAL;
}

void WIPSoundPlayer::delete_sound(WIPSound* sound)
{
	_VectorList::iterator it =_audio_list.find(sound);
	if(it!=_audio_list.end())
	{
		((WIPSound*)(*it))->set_in_list_tag(false);
		_audio_list.erase(it);
		
	}
	
}

void WIPSoundPlayer::clear_all_sounds()
{
	for (_VectorList::iterator it=_audio_list.begin();it!=_audio_list.end();++it)
	{
		if ((*it)->stream)
		{
			((OggStream*)(*it))->in_list = false;
		}
		else
		{
			((WIPSound*)(*it))->set_in_list_tag(false);
		}
	}
	_audio_list.clear();
}

void WIPSoundPlayer::set_sound_state(WIPSound* sound,ALint st)
{
	switch (st)
	{
	case AL_INITIAL:
		sound->set_state(WIPSoundStates::INITIAL);
		break;
	case AL_PLAYING:
		sound->set_state(WIPSoundStates::PALYING);
		break;
	case AL_PAUSED:
		sound->set_state(WIPSoundStates::PAUSED);
		break;
	case AL_STOPPED:
		sound->set_state(WIPSoundStates::STOPPED);
		break;
	default:
		sound->set_state(WIPSoundStates::UNINITIAL);
		break;
	}
}

void WIPSoundPlayer::set_loop( WIPSound* sound,bool v )
{
	sound->set_loop(v);
}

void WIPSoundPlayer::play_stream( WIPSoundBase* sound,bool loop )
{
	((OggStream*)sound)->play(loop);
	if(!((OggStream*)sound)->in_list)
	{
		_audio_list.pushBack(sound);
		((OggStream*)sound)->in_list = true;
	}

}

WIPSoundPlayer* g_sound_palyer = WIPSoundPlayer::get_instance();