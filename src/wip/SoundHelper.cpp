#include "SoundHelper.h"
#include "PathTool.h"
#include <codec.h>
#include <vorbisfile.h>
#include <al.h>
#include <alc.h>
#include <alext.h>
#include <alut.h>

bool WIPSoundHelper::load_sound(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop)
{
	if(!WIPPathTool::check_path_available(file_path))
	{
		//log
		return false;
	}

	bool ret = false;
	std::string exe = WIPPathTool::get_file_extension(std::string(file_path));
	if (exe == "wav")
	{
		ret = load_sound_wav(file_path,format,data,size,frequency,loop);
	}
	else if(exe == "ogg")
	{
		ret = load_sound_ogg(file_path,format,data,size,frequency,loop);
	}
	return ret;
}

bool WIPSoundHelper::load_sound_ogg(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop)
{
	 OggVorbis_File vf;
	 int eof=0;
	 int current_section;
	 FILE * ff;
	 ff = fopen(file_path,"rb");
	 if(ff==NULL)
	 {
		 printf("can't open!\n");
		 //log
		 getchar();
		 return false;
	 }
	 if(ov_open(ff, &vf, NULL, 0) < 0) {
		 fprintf(stderr,"Input does not appear to be an Ogg bitstream.\n");
		 exit(1);
	 }
	 char **ptr=ov_comment(&vf,-1)->user_comments;
	 vorbis_info *vi=ov_info(&vf,-1);
	 while(*ptr){
		 fprintf(stderr,"%s\n",*ptr);
		 ++ptr;
	 }
	 fprintf(stderr,"\nBitstream is %d channel, %ldHz\n",vi->channels,vi->rate);
	 fprintf(stderr,"\nDecoded length: %ld samples\n",
		 (long)ov_pcm_total(&vf,-1));
	 fprintf(stderr,"Encoded by: %s\n\n",ov_comment(&vf,-1)->vendor);


	 int sizea;
	 char *buffers;
	 sizea = vi->channels * 2 * ov_pcm_total(&vf,-1);
	 buffers = (char *)malloc(sizea);
	 char* buf = buffers;
	  while(!eof){
    long ret=ov_read(&vf,buf,1024,0,2,1,&current_section);
    if (ret == 0) {
      /* EOF */
      eof=1;
    } else if (ret < 0) {

    } else {

		buf += ret;
		
    }
  }
	  if(vi->channels==1)
	  {
		  *format = AL_FORMAT_MONO16;
	  }
	  else
	  {
		  *format = AL_FORMAT_STEREO16;
	  }
	  *data = buffers;
	  *size = sizea;
	  *frequency = vi->rate;
	  *loop = false;
	  ov_clear(&vf);
	 

	
	  
	return true;
}

bool WIPSoundHelper::load_sound_wav(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop)
{
	alutLoadWAVFile((signed char*)file_path,format,data,size,frequency,loop);
	int e = alutGetError();
	if (e != AL_NO_ERROR)
	{
		printf("alutLoadWAVFile failed:%s\n",alutGetErrorString (e) );
		//log
		getchar();
		alutExit ();
		exit(0);
	}
	return true;
}

void WIPSoundHelper::unload_sound(void * data,int format,int size,int frequency,SoundOutFormat type)
{
	if (type==SoundOutFormat::OGG)
	{
		unload_sound_ogg(data,format,size,frequency);
	}
	else if(type==SoundOutFormat::WAV)
	{
		unload_sound_wav(data,format,size,frequency);
	}

}

void WIPSoundHelper::unload_sound_ogg(void * data,int format,int size,int frequency)
{
	free(data);// data;
}

void WIPSoundHelper::unload_sound_wav(void * data,int format,int size,int frequency)
{
	alutUnloadWAV(format,data,size,frequency);
}