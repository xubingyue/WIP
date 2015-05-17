#pragma once
#include "TimeSource.h"

class CTimeSource:public TimeSource
{
public:
	CTimeSource();
	virtual double get_time() const;
private:
	//double _secs_per_tick;
};