#pragma once

#include <cstddef>
#include <vector>
#include <deque>
//#include <ctime>
#include "RBMath/Inc/Platform/RBBasedata.h"

#ifdef _WIN32
#include "Win32TimeSource.h"
typedef Win32TimeSource timesource;
#else
#include "CTimeSource.h"
typedef CTimeSource timesource;
#endif
class ITimeObserver;

class RBClock
{
public:
	~RBClock();

	static RBClock* Instance();

	static INI_RESULT init(timesource* a_timesource);

	void reset_time_source(const timesource* a_timesource);

	void update();

	f64 get_time() const
	{
		return _current_time;
	}

	f64 get_frame_time() const
	{
		return _frame_time;
	}

	i32 get_frame_number() const
	{
		return _frame_number;
	}

	f32 get_frame_rate() const
	{
		return 1.0f/(f32)_frame_time;
	}


	void add_observer(ITimeObserver* observer);
	void remove_observer(ITimeObserver* observer);

	void set_filtering(i32 frame_window,f64 frame_default = 0.030);

	//time_t get_system_time();
protected:
	RBClock();
	RBClock(const timesource* a_timesource);
private:
	f64 get_exact_last_frame_time();
	void add_to_frame_history(f64 exact_frame_time);
	//‘§—‘ ±º‰
	f64 get_predicted_frame_time() const;


	static RBClock* _clock_instance;
	const timesource* _time_source;
	f64 _current_time;
	f64 _frame_time;
	i32 _frame_number;

	f64 _source_start_value;
	f64 _source_last_value;

	i32 _frame_filtering_window;
	f64 _frame_default_time;
	std::deque<f64> _frame_time_history;

	std::vector<ITimeObserver*> _observers;
};
