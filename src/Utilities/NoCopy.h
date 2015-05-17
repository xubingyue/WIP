#pragma once

//inherit WIPNoCopy for avoiding copy
class WIPNoCopy
{
public:
	WIPNoCopy(){};
	~WIPNoCopy(){};
protected:

private:
	WIPNoCopy(const WIPNoCopy&);
	WIPNoCopy& operator=(const WIPNoCopy&);
};