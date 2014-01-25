/*
 * time_scalar.h
 *
 *  Created on: Jan 23, 2014
 *      Author: bill
 */

#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <cmath>
#include <stdint.h>

namespace core
{

	class TimeManager
	{
	public:
		TimeManager();
		virtual ~TimeManager();

    uint64_t get_frequency();
    void set_frequency(uint64_t);

    uint64_t get_real_duration();
    void set_real_duration(uint64_t);

    uint64_t get_simulated_duration();
    void set_simulated_duration(uint64_t);

    uint64_t get_real_elapsed_time();
    uint64_t get_simulated_elapsed_time();
    uint64_t get_simulated_elapsed_time_remainder();

    void add_real_time(uint64_t);

	protected:
    uint64_t frequency;								// factor to scale simulation time

    uint64_t real_duration;						// real time duration of the simulation (nanoseconds) (optional)
    uint64_t simulated_duration;			// simulated duration of the simulation (optional)

    uint64_t real_elapsed_time;				// current elapsed real time (nanoseconds)
    uint64_t simulated_elapsed_time;	// current elapsed simulated time
    uint64_t simulated_elapsed_time_remainder;	// elapsed simulation time less than 1 simulation unit
	};

} /* namespace core */
#endif /* TIME_MANAGER_H_ */
