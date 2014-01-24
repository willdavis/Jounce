/*
 * time_scalar.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: bill
 */

#include "time_scalar.h"

namespace core
{

	TimeScalar::TimeScalar()
	{
		// TODO Auto-generated constructor stub

	}

	TimeScalar::~TimeScalar()
	{
		// TODO Auto-generated destructor stub
	}

	double TimeScalar::get_time_scale()
	{
		return time_scale;
	}

	uint64_t TimeScalar::get_real_duration()
	{
		return real_duration;
	}

	uint64_t TimeScalar::get_simulated_duration()
	{
		return simulated_duration;
	}

	uint64_t TimeScalar::get_real_elapsed_time()
	{
		return real_elapsed_time;
	}

	uint64_t TimeScalar::get_simulated_elapsed_time()
	{
		return simulated_elapsed_time;
	}

	uint64_t TimeScalar::get_min_framerate()
	{
		return min_framerate;
	}

	uint64_t TimeScalar::get_max_framerate()
	{
		return max_framerate;
	}

	void TimeScalar::set_time_scale(double scale)
	{
		time_scale = scale;
	}

	void TimeScalar::set_real_duration(uint64_t duration)
	{
		real_duration = duration;
	}

	void TimeScalar::set_simulated_duration(uint64_t sim_duration)
	{
		simulated_duration = sim_duration;
	}

	void TimeScalar::set_min_framerate(uint64_t min)
	{
		min_framerate = min;
	}

	void TimeScalar::set_max_framerate(uint64_t max)
	{
		max_framerate = max;
	}

}
 /* namespace core */
