// TimeSystem.cpp : 定义控制台应用程序的入口点。
//
/*
#include "Win32TimeSource.h"
#include "Clock.h"
#include "Timer.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	Win32TimeSource times;
	RBClock::init(&times);
	RBClock* clock = RBClock::Instance();
	RBTimerBase timer(*clock);
	int i = 0;
	while (1)
	{
		//for(int s=0;s<=1000000;++s) new Win32TimeSource();
		clock->update();
		//printf("%f,%f\n",clock->get_frame_time(),clock->get_frame_rate());
		printf("%f,%f,%f\n",timer.get_frame_time(),timer.get_time(),timer.get_scale());
		if(i>=2000)
			timer.pause(true);
		i++;
	}
	return 0;
}

*/