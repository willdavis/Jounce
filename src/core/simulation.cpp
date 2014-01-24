/*
 * simulation.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "simulation.h"
#include "./events/exit_event.h"

namespace core
{

  Simulation::Simulation()
  {
    event_manager.set_parent((void*) (((this))));
		state = 0; //set default state
	}

	Simulation::~Simulation()
	{
		// TODO Auto-generated destructor stub
	}

	void Simulation::exit()
	{
		state = 1;
	}

	void Simulation::run()
	{
		core_timer.get_elapsed_time(); //bring the timer up to date
		while (state == 0)
		{
			// get delta simulation time between last frame (nanoseconds)
			uint64_t dt = core_timer.get_elapsed_time();
			// check if this frame will push us over the duration.
			// if so, schedule an ExitEvent for immediate termination of the simulation!
			if ((dt + time_manager.get_real_elapsed_time())
					>= time_manager.get_real_duration()
					&& time_manager.get_real_duration() > 0)
			{
				event_manager.schedule_event(new ExitEvent); //setup an ExitEvent to kill the simulation
				dt = time_manager.get_real_duration()
						- time_manager.get_real_elapsed_time(); //calculate remaining simulation time and set it as dt
			}
			// update the elapsed simulation time with delta time (dt)
			time_manager.add_real_time(dt);
			// process the event queue for this cycle
			int queue_size = event_manager.get_queue_size();
			while (queue_size > 0)
			{
				event_manager.process_top_event();
				queue_size = event_manager.get_queue_size();
			}
		}

	}

	// returns the elapsed time of the simulation
	uint64_t Simulation::get_elapsed_time()
	{
		return time_manager.get_real_elapsed_time();
	}

	// sets the duration of the simulation
	void Simulation::set_duration(uint64_t duration)
	{
		time_manager.set_real_duration(duration);
	}

	// returns the current duration of the simulation
	uint64_t Simulation::get_duration()
	{
		return time_manager.get_real_duration();
  }

  // schedule event with EventManager and return the new queue size
  int Simulation::schedule_event(Event* event)
  {
    event_manager.schedule_event(event);
    return event_manager.get_queue_size();
  }

  // returns the current simulation state (0=ready, 1=done, -1=errors)
  int Simulation::get_state() { return state; }

  // returns the current size of the event queue
  int Simulation::get_event_queue_size() { return event_manager.get_queue_size(); }

} /* namespace core */
