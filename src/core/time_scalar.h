/*
 * time_scalar.h
 *
 *  Created on: Jan 23, 2014
 *      Author: bill
 */

#ifndef TIME_SCALAR_H_
#define TIME_SCALAR_H_

namespace core
{

	class TimeScalar
	{
	public:
		TimeScalar();
		virtual ~TimeScalar();

    double get_time_scale();
    void set_time_scale(double);

    uint64_t get_real_duration();
    void set_real_duration(uint64_t);

    uint64_t get_simulated_duration();
    void set_simulated_duration(uint64_t);

    uint64_t get_real_elapsed_time();
    uint64_t get_simulated_elapsed_time();

    uint64_t get_min_framerate();
    uint64_t get_max_framerate();
    void set_min_framerate(uint64_t);
    void set_max_framerate(uint64_t);

	protected:
    double time_scale;								// factor to scale simulation time
    uint64_t min_framerate;						// desired minimum time per simulation frame (nanoseconds)
    uint64_t max_framerate;						// desired maximum time per simulation frame (nanoseconds)

    uint64_t real_duration;						// real time duration of the simulation (nanoseconds) (optional)
    uint64_t simulated_duration;			// simulated duration of the simulation (optional)

    uint64_t real_elapsed_time;				// current elapsed real time (nanoseconds)
    uint64_t simulated_elapsed_time;	// current elapsed simulated time
	};

} /* namespace core */
#endif /* TIME_SCALAR_H_ */
