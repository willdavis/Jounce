/*
 * timespec_helper.h
 *
 *  Created on: Jan 26, 2014
 *      Author: bill
 */

#ifndef TIMESPEC_HELPER_H_
#define TIMESPEC_HELPER_H_

#include <time.h>

namespace core
{

	class TimespecHelper
	{
	public:
		TimespecHelper();
		virtual ~TimespecHelper();
		static timespec get_timespec_diff(timespec*, timespec*);
	};

} /* namespace core */
#endif /* TIMESPEC_HELPER_H_ */
