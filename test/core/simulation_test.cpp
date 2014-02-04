/*
 * simulation_test.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include <thread> // needed for cannot_scale_time_while_sim_is_running test

#include "gtest/gtest.h"
#include "../../src/core/simulation.h"
#include "../../src/core/events/exit_event.h"

namespace core
{
  class SimulationTest : public ::testing::Test {
  protected:
    Simulation sim;
  };

  class TestEvent : public Dispatchable {
	public:
		void dispatch(Dispatcher* dispatcher){ /* do nothing */ }
		unsigned int priority() { return 10; }
		uint64_t timestamp() { return (uint64_t)10; }
	};

  class TestObject : public Updateable {
	public:
		void update(uint64_t* dt){  }
	};

  void async_sim_run(Simulation* sim) { sim->run(); }

  TEST_F(SimulationTest, can_check_the_current_simulation_state) {
    EXPECT_EQ(sim.get_current_state(), SimulationState::OFF);
  }

  TEST_F(SimulationTest, can_check_if_simulation_is_off) {
  	ASSERT_TRUE(sim.is_off());
  }

  TEST_F(SimulationTest, can_check_if_simulation_is_running) {
		ASSERT_FALSE(sim.is_running());
	}

  TEST_F(SimulationTest, can_check_if_simulation_is_exiting) {
		ASSERT_FALSE(sim.is_exiting());
	}

  TEST_F(SimulationTest, can_schedule_an_event) {
  	event_ptr event(new TestEvent);
    int size_of_queue = sim.schedule_event(event);
    ASSERT_EQ(size_of_queue, 1);
  }

  TEST_F(SimulationTest, can_get_event_queue_size) {
  	event_ptr event(new TestEvent);
    EXPECT_EQ(sim.get_event_queue_size(), 0);
    sim.schedule_event(event);
    ASSERT_EQ(sim.get_event_queue_size(), 1);
  }

  TEST_F(SimulationTest, can_exit_the_simulation) {
    EXPECT_TRUE(sim.is_off());
    sim.exit();
    ASSERT_TRUE(sim.is_exiting());
  }

  TEST_F(SimulationTest, can_get_simulation_frequency) {
  	ASSERT_EQ(sim.get_frequency(), (uint64_t)1);
  }

  TEST_F(SimulationTest, can_get_real_duration) {
		ASSERT_EQ(sim.get_real_duration(), (uint64_t)0);
	}

  TEST_F(SimulationTest, can_get_simulated_duration) {
		ASSERT_EQ(sim.get_sim_duration(), (uint64_t)0);
	}

  TEST_F(SimulationTest, can_get_elapsed_simulated_time) {
		ASSERT_EQ(sim.get_elapsed_sim_time(), (uint64_t)0);
	}

  TEST_F(SimulationTest, can_get_elapsed_simulated_time_remainder) {
		ASSERT_EQ(sim.get_sim_time_remainder(), (uint64_t)0);
	}

  TEST_F(SimulationTest, can_get_elapsed_real_time) {
		ASSERT_EQ(sim.get_elapsed_real_time(), (uint64_t)0);
	}

  TEST_F(SimulationTest, cannot_scale_time_while_sim_is_running) {
  	timespec sleep_time;
  	sleep_time.tv_sec = 0;
  	sleep_time.tv_nsec = 50000;

  	sim.set_real_duration_and_frequency(100000,1);	// run for 100,000 ns
  	std::thread do_work (async_sim_run, &sim);
  	nanosleep(&sleep_time, NULL);	// sleep for 50,000 ns
  	EXPECT_ANY_THROW(sim.set_real_duration_and_frequency(1000000,1));
  	EXPECT_ANY_THROW(sim.set_real_and_sim_duration(10,10));
  	EXPECT_ANY_THROW(sim.set_sim_duration_and_frequency(100,1));
  	do_work.join();
  }

  // real time = sim time * frequency
  TEST_F(SimulationTest, can_scale_real_time) {
  	sim.set_sim_duration_and_frequency(10,10);	//10 units * (10 ns / 1 unit) = 100ns real time
  	ASSERT_EQ(sim.get_real_duration(), (uint64_t)100);
  }

  // sim time = real time / frequency
  TEST_F(SimulationTest, can_scale_simulation_time) {
  	sim.set_real_duration_and_frequency(100,50);
  	ASSERT_EQ(sim.get_sim_duration(), (uint64_t)2);

  	// an assert is thrown if: real time % frequency > 0
  	ASSERT_ANY_THROW(sim.set_real_duration_and_frequency(102,50));
  }

  // frequency = real time / sim time
  TEST_F(SimulationTest, can_scale_frequency) {
  	sim.set_real_and_sim_duration(1000,10);
  	ASSERT_EQ(sim.get_frequency(), (uint64_t)100);

  	// an assert is thrown if: real time % frequency > 0
		ASSERT_ANY_THROW(sim.set_real_and_sim_duration(100, 13));
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    sim.set_real_duration_and_frequency(1000000, 100000);
    sim.run();
    EXPECT_EQ(sim.get_sim_duration(), (uint64_t)10);
    ASSERT_EQ(sim.get_elapsed_real_time(), sim.get_real_duration());
    ASSERT_EQ(sim.get_elapsed_sim_time(), sim.get_sim_duration());
  }

  TEST_F(SimulationTest, can_get_total_registered_object_size) {
  	ASSERT_EQ(0, sim.get_total_registered_objects());
  }

  TEST_F(SimulationTest, can_register_a_simulated_object) {
  	sim_object_ptr object(new TestObject);
  	sim.register_simulated_object(object);
  	ASSERT_EQ(1, sim.get_total_registered_objects());
  }

  TEST_F(SimulationTest, can_remove_a_simulated_object) {
  	sim_object_ptr object(new TestObject);
		sim.register_simulated_object(object);
		EXPECT_EQ(1, sim.get_total_registered_objects());
		sim.release_simulated_object(object);
		ASSERT_EQ(0, sim.get_total_registered_objects());
  }

} /* namespace core */
