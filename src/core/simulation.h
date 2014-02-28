/*
 * simulation.h
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "./objects/object.h"

#include "timer.h"
#include "time_manager.h"
#include "event_manager.h"
#include "state_manager.h"
#include "object_manager.h"

namespace core
{

  class Simulation : public JObject
  {
  public:
    Simulation(JObject* parent, const char* signature);
    virtual ~Simulation();

    void run();
    void exit();

    uint64_t get_elapsed_sim_time();
    uint64_t get_elapsed_real_time();
    uint64_t get_sim_time_remainder();

    uint64_t get_sim_duration();
    uint64_t get_real_duration();
    uint64_t get_frequency();

    void set_real_and_sim_duration(uint64_t, uint64_t);
    void set_real_duration_and_frequency(uint64_t, uint64_t);
    void set_sim_duration_and_frequency(uint64_t, uint64_t);

    int get_event_queue_size();
    int schedule_event(event_ptr);

    SimulationState get_current_state();
    bool is_off();
    bool is_running();
    bool is_exiting();

    int get_total_registered_objects();
    void register_simulated_object(object_ptr);
    void release_simulated_object(object_ptr);

  protected:
    Timer timer;								// core simulation timer
    TimeManager time_manager;		// provides an interface to configure simulation time
    StateManager state_manager;	// provides an interface to manage the simulation's state

    ObjectManager* obj_manager;	// provides an interface to manage objects within the simulation
    EventManager* event_manager; // provides an interface to manage events
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
