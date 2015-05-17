#pragma once
#include "TimeSource.h"

class Win32TimeSource:public TimeSource
{
public:
	Win32TimeSource();
	virtual double get_time() const;
private:
	double _secs_per_tick;
};