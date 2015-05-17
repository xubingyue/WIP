#pragma once
class TimeSource
{
public:
    virtual ~TimeSource() {};
	//∑µªÿ∫¡√Î
    virtual double get_time() const = 0;

};