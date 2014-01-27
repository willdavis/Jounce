/*
 * timespec_helper.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: bill
 */

#include "timespec_helper.h"

namespace core
{

	TimespecHelper::TimespecHelper()
	{
		// TODO Auto-generated constructor stub

	}

	TimespecHelper::~TimespecHelper()
	{
		// TODO Auto-generated destructor stub
	}

	timespec TimespecHelper::get_timespec_diff(timespec* end, timespec* start)
	{
		timespec ts;
		ts.tv_sec = end->tv_sec - start->tv_sec;
		ts.tv_nsec = end->tv_nsec - start->tv_nsec;
		if (ts.tv_nsec < 0) {
			ts.tv_sec--;
			ts.tv_nsec += 1000000000;
		}

		if(ts.tv_sec < 0 || ts.tv_nsec < 0) { throw "cannot have negative time"; }
		else { return ts; }
	}

}
 /* namespace core */
