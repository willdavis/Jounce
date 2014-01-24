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
		time_scale = 1;							// set time scale to normal time (1x)
		real_elapsed_time = 0;			// set elapsed real time to zero
		simulated_elapsed_time = 0;	// set elapsed simulation time to zero
		real_duration = 0;					// default to infinite duration (wait for exit event)
		simulated_duration = 0; 		// default to infinite duration (wait for exit event)

		min_framerate = 0;					// not tracked by default
		max_framerate = 0;					// not tracked by default
	}

	TimeManager::~TimeManager()
	{
		// TODO Auto-generated destructor stub
	}

	// returns the scalar which is used to modify time
	double TimeManager::get_time_scale()
	{
		return time_scale;
	}

	// returns the real time duration
	uint64_t TimeManager::get_real_duration()
	{
		return real_duration;
	}

	// returns the simulated duration
	uint64_t TimeManager::get_simulated_duration()
	{
		return simulated_duration;
	}

	// returns the real time elapsed in the simulation
	uint64_t TimeManager::get_real_elapsed_time()
	{
		return real_elapsed_time;
	}

	// returns the simulated time elapsed in the simulation
	uint64_t TimeManager::get_simulated_elapsed_time()
	{
		return simulated_elapsed_time;
	}

	// returns the frame rate range for the simulation (nanoseconds)
	uint64_t TimeManager::get_framerate_range()
	{
		if(max_framerate > min_framerate) return max_framerate - min_framerate;
		else return min_framerate;
	}

	// set the scalar to modify time by
	void TimeManager::set_time_scale(double scale)
	{
		time_scale = scale;
	}

	// set the duration of the simulation (real time)
	void TimeManager::set_real_duration(uint64_t duration)
	{
		real_duration = duration;
	}

	// set the duration of the simulation (simulated time)
	void TimeManager::set_simulated_duration(uint64_t sim_duration)
	{
		simulated_duration = sim_duration;
	}

	// set the requested minimum frame rate for the simulation (nanoseconds)
	void TimeManager::set_min_framerate(uint64_t min)
	{
		min_framerate = min;
	}

	// set the requested maximum frame rate for the simulation (nanoseconds)
	void TimeManager::set_max_framerate(uint64_t max)
	{
		max_framerate = max;
	}

	// add more real time to the simulations elapsed time
	void TimeManager::add_real_time(uint64_t real_time)
	{
		real_elapsed_time += real_time;
	}

	// add more simulated time to the simulation elapsed time
	void
	TimeManager::add_simulated_time(uint64_t sim_time)
	{
		simulated_elapsed_time += sim_time;
	}

/* namespace core */

}

