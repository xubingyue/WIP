#ifndef __TIMEOBSERVER_H__
#define __TIMEOBSERVER_H__
#pragma once

class ITimeObserver
{
public:
	virtual ~ITimeObserver(){};
	virtual void notify() = 0;
};


#endif