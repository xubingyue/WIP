#include "Timer.h"

RBTimerBase::RBTimerBase(RBClock& clock):_clock(clock)
{
	_current_time = _frame_time = 0;
	_bpaused = false;
	_scale = 1;
	_clock.add_observer(this);
}

RBTimerBase::~RBTimerBase()
{
	_clock.remove_observer(this);
}

void RBTimerBase::notify()
{
	if(!_bpaused)
	{
		_frame_time = _clock.get_frame_time()*_scale;
		_current_time += _frame_time;
	}
}

void RBTimerBase::pause(bool bOn)
{
	_bpaused = bOn;
}

void RBTimerBase::set_scale(f32 fScale)
{
	_scale = fScale;
}

f32 RBTimerBase::get_scale() const
{
	return _scale;
}

bool RBTimerBase::is_paused() const
{
	return _bpaused;
}