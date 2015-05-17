#include "windows.h"
#include "Win32TimeSource.h"
#include "stdio.h"

Win32TimeSource::Win32TimeSource()
{
	LARGE_INTEGER __freq;
	QueryPerformanceFrequency(&__freq);
	//_secs_per_tick = 1000.0/__freq.QuadPart;
	_secs_per_tick = 1.0/__freq.QuadPart;
}

//∑µªÿ√Î
double Win32TimeSource::get_time() const
{
	LARGE_INTEGER __time;
	QueryPerformanceCounter(&__time);
	//printf("%f\n",__time.QuadPart * _secs_per_tick);
	return __time.QuadPart * _secs_per_tick;
}