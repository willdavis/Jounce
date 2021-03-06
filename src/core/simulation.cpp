/*
 * simulation.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "simulation.h"

namespace core
{

  Simulation::Simulation(JObject* parent, const char* signature) : JObject(parent,signature)
  {
  	obj_manager = new ObjectManager(this, "Core::ObjectManager");
  	event_manager = new EventManager(this, "Core::EventManager");

    register_signal(new JSignal<void>(this, "exiting"));
	}

	Simulation::~Simulation()
	{
		delete obj_manager;
		delete event_manager;
	}

	void Simulation::exit()
	{
		state_manager.set_current_simulation_state(SimulationState::EXITING);
		signal<void>("exiting")->emit();	//signal to anyone listening that we're EXITING
	}

	void Simulation::run()
	{
		state_manager.set_current_simulation_state(SimulationState::RUNNING);
		timer.get_elapsed_time(); //bring the timer up to date
		while (is_running())
		{
			// get delta simulation time between last frame (nanoseconds)
			uint64_t dt = timer.get_elapsed_time();
			// check if this frame will push us over the duration.
			// if so, schedule an ExitEvent for immediate termination of the simulation!
			if ((dt + time_manager.get_real_elapsed_time())
					>= time_manager.get_real_duration()
					&& time_manager.get_real_duration() > 0)
			{
				this->exit();	// set and signal SimulationState::EXITING
				dt = time_manager.get_real_duration()
						- time_manager.get_real_elapsed_time(); //calculate remaining simulation time and set it as dt
			}
			// update the elapsed simulation time with delta time (dt)
			time_manager.add_real_time(&dt);

			// process the event queue for this cycle
			event_manager->process_event_queue();

			//update all objects in the simulation with elapsed time (dt)
			obj_manager->update_all_objects(&dt);
		}

		// the simulation is over!
		state_manager.set_current_simulation_state(SimulationState::OFF);
	}

// returns the elapsed real time of the simulation (nanoseconds)
	uint64_t
	Simulation::get_elapsed_real_time()
	{
		return time_manager.get_real_elapsed_time();
	}

// returns the current duration of the simulation (nanoseconds)
	uint64_t
	Simulation::get_real_duration()
	{
		return time_manager.get_real_duration();
	}

// returns the current simulation frequency (nanoseconds / 1 unit)
	uint64_t
	Simulation::get_frequency()
	{
		return time_manager.get_frequency();
	}

// returns the elapsed simulation time (arbitrary units)
	uint64_t
	Simulation::get_elapsed_sim_time()
	{
		return time_manager.get_simulated_elapsed_time();
	}

// returns the simulation time remainder (1 unit / x nanoseconds)
	uint64_t
	Simulation::get_sim_time_remainder()
	{
		return time_manager.get_simulated_elapsed_time_remainder();
	}

// returns the total simulation time (arbitrary units)
	uint64_t
	Simulation::get_sim_duration()
	{
		return time_manager.get_simulated_duration();
	}

// scales frequency time to match the given real and simulated times
	void Simulation::set_real_and_sim_duration(uint64_t real, uint64_t sim)
	{
		// check if the simulation is currently running
		if(!is_off()) { throw "cannot change duration while simulation is running"; }

		// frequency = real time / sim time
		time_manager.set_real_duration(real);
		time_manager.set_simulated_duration(sim);

		uint64_t remainder = real % sim;
		if(remainder > 0) { throw "simulation time must divide real time"; }
		else {
			uint64_t quotient = real / sim;
			time_manager.set_frequency(quotient);
		}
	}

// scales simulation time to match the given real and frequency times
	void Simulation::set_real_duration_and_frequency(uint64_t real, uint64_t freq)
	{
		// check if the simulation is currently running
		if(!is_off()) { throw "cannot change duration while simulation is running"; }

		// sim time = real time / frequency
		time_manager.set_real_duration(real);
		time_manager.set_frequency(freq);

		uint64_t remainder = real % freq;
		if(remainder > 0) { throw "frequency must divide real time"; }
		else {
			uint64_t quotient = real / freq;
			time_manager.set_simulated_duration(quotient);
		}
	}

	// scales real time to match the given simulation and frequency times
	void Simulation::set_sim_duration_and_frequency(uint64_t sim, uint64_t freq)
	{
		// check if the simulation is currently running
		if(!is_off()) { throw "cannot change duration while simulation is running"; }

		time_manager.set_simulated_duration(sim);
		time_manager.set_frequency(freq);

		// real time = sim time * frequency
		time_manager.set_real_duration(sim * freq);
	}

  // schedule event with EventManager and return the new queue size
  int Simulation::schedule_event(event_ptr event)
  {
    event_manager->schedule(event);
    return event_manager->queue_size();
  }

  // returns the current size of the event queue
  int Simulation::get_event_queue_size()
  {
  	return event_manager->queue_size();
  }

  // returns the current state of the simulation
  SimulationState Simulation::get_current_state()
  {
  	return state_manager.get_current_simulation_state();
  }

  bool Simulation::is_off()
  {
  	return state_manager.get_current_simulation_state() == SimulationState::OFF;
  }

  bool Simulation::is_running()
  {
  	return state_manager.get_current_simulation_state() == SimulationState::RUNNING;
  }

  bool Simulation::is_exiting()
  {
  	return state_manager.get_current_simulation_state() == SimulationState::EXITING;
  }

  int Simulation::get_total_registered_objects()
  {
  	return obj_manager->get_collection_size();
  }

  // register a new object with the ObjectManager
  void Simulation::register_simulated_object(object_ptr object)
  {
  	obj_manager->register_object(object);
  }

  // release the object from the ObjectManager
  void Simulation::release_simulated_object(object_ptr object)
  {
  	obj_manager->release_object(object);
  }

} /* namespace core */
