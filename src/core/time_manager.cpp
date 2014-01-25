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
		frequency = 1;							// set the default simulation frequency (nanoseconds / unit)
		real_elapsed_time = 0;			// set elapsed real time to zero
		simulated_elapsed_time = 0;	// set elapsed simulation time to zero
		real_duration = 0;					// default to infinite duration (wait for exit event)
		simulated_duration = 0; 		// default to infinite duration (wait for exit event)
		simulated_elapsed_time_remainder = 0;		// simulated time less than 1 simulation unit
	}

	TimeManager::~TimeManager()
	{
		// TODO Auto-generated destructor stub
	}

	// returns the simulation frequency (nanoseconds / unit)
	uint64_t TimeManager::get_frequency()
	{
		return frequency;
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

	uint64_t TimeManager::get_simulated_elapsed_time_remainder()
	{
		return simulated_elapsed_time_remainder;
	}

	// set the simulation frequency (nanoseconds / unit)
	void TimeManager::set_frequency(uint64_t freq)
	{
		frequency = freq;
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

	// add more real time to the simulations elapsed time
	void TimeManager::add_real_time(uint64_t real_time)
	{
		real_elapsed_time += real_time;
		if(real_time < frequency)
		{
			uint64_t remainder = frequency % real_time;
			simulated_elapsed_time_remainder += remainder;
			if(simulated_elapsed_time_remainder >= frequency)
			{
				simulated_elapsed_time_remainder -= frequency;
				simulated_elapsed_time++;
			}
		}
		else
		{
			uint64_t remainder = real_time % frequency;
			uint64_t quotient = real_time / frequency;
			simulated_elapsed_time_remainder += remainder;
			simulated_elapsed_time += quotient;
			if(simulated_elapsed_time_remainder >= frequency)
			{
				simulated_elapsed_time_remainder -= frequency;
				simulated_elapsed_time++;
			}
		}
	}

/* namespace core */

}

