#include <ctime>
#include "CTimeSource.h"

CTimeSource::CTimeSource()
{

}

double CTimeSource::get_time() const
{
	return clock()/CLOCKS_PER_SEC;
}