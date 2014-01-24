/*
 * time_manager.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: bill
 */

#include "time_manager.h"

namespace core
{

	TimeManager::TimeManager()
	{
		// TODO Auto-generated constructor stub

	}

	TimeManager::~TimeManager()
	{
		// TODO Auto-generated destructor stub
	}

	double TimeManager::get_time_scale()
	{
		return time_scale;
	}

	uint64_t TimeManager::get_real_duration()
	{
		return real_duration;
	}

	uint64_t TimeManager::get_simulated_duration()
	{
		return simulated_duration;
	}

	uint64_t TimeManager::get_real_elapsed_time()
	{
		return real_elapsed_time;
	}

	uint64_t TimeManager::get_simulated_elapsed_time()
	{
		return simulated_elapsed_time;
	}

	uint64_t TimeManager::get_min_framerate()
	{
		return min_framerate;
	}

	uint64_t TimeManager::get_max_framerate()
	{
		return max_framerate;
	}

	void TimeManager::set_time_scale(double scale)
	{
		time_scale = scale;
	}

	void TimeManager::set_real_duration(uint64_t duration)
	{
		real_duration = duration;
	}

	void TimeManager::set_simulated_duration(uint64_t sim_duration)
	{
		simulated_duration = sim_duration;
	}

	void TimeManager::set_min_framerate(uint64_t min)
	{
		min_framerate = min;
	}

	void TimeManager::set_max_framerate(uint64_t max)
	{
		max_framerate = max;
	}

}
 /* namespace core */
