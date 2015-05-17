#pragma once
#include "Clock.h"
#include "ITimeObserver.h"

class RBTimerBase : public ITimeObserver
{
public:
	RBTimerBase(RBClock& clock);
	~RBTimerBase();

	//get current time
	f64 get_time() const
	{
		return _current_time;

	}

	//get predicted time
	f64 get_frame_time() const
	{
		return _frame_time;
	}

	void pause (bool bOn);
    void set_scale (f32 fScale);   

	bool is_paused () const;
    f32 get_scale () const;
private:
	virtual void notify();

	RBClock& _clock;

	f64 _current_time;
	f64 _frame_time;

	bool _bpaused;
	f32 _scale;
};

class RBTimerCustom
{
public:

private:

};