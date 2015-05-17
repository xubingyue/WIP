/*
Copyright (C) 2007, 2010 - Bit-Blot

This file is part of Aquaria.

Aquaria is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef __ogg_h__
#define __ogg_h__

#include <string>
#include <iostream>

#include "al.h"
#include "vorbisfile.h"
#include "SoundBase.h"
#include "Utilities/NoCopy.h"

class WIPSoundPlayer;

class OggStream : public WIPSoundBase
{
public:
	OggStream();
	void open(std::string path);
    void release();
    void display();
    bool play(bool loop=false);
    bool isPlaying();
    bool update();
	//0.0-1.0
	void setGain(float g);
	void pause();
	void resume();
protected:
    bool stream(ALuint buffer);
    void empty();
    void check();
	std::string errorString(int code);
	friend WIPSoundPlayer;
private:
    FILE*           oggFile;
    OggVorbis_File  oggStream;
    vorbis_info*    vorbisInfo;
    vorbis_comment* vorbisComment;

    ALuint buffers[2];
    ALuint source;
    ALenum format;
	bool loop;

	bool bstop;

	bool in_list;
};


#endif // __ogg_h__

