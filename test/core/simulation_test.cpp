/*
 * simulation_test.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/simulation.h"
#include "../../src/core/events/exit_event.h"

namespace core
{
  class SimulationTest : public ::testing::Test {
  protected:
    Simulation sim;
  };

  class TestEvent : public Event {
  public:
    void process_event(void* input) { /* do nothing */ }
  };

  TEST_F(SimulationTest, can_check_the_current_simulation_state) {
    EXPECT_EQ(sim.get_state(), 0);
  }

  TEST_F(SimulationTest, can_schedule_an_event) {
    TestEvent event;
    int size_of_queue = sim.schedule_event(&event);
    ASSERT_EQ(size_of_queue, 1);
  }

  TEST_F(SimulationTest, can_get_event_queue_size) {
    TestEvent event;
    EXPECT_EQ(sim.get_event_queue_size(), 0);
    sim.schedule_event(&event);
    ASSERT_EQ(sim.get_event_queue_size(), 1);
  }

  TEST_F(SimulationTest, can_exit_the_simulation) {
    EXPECT_EQ(sim.get_state(), 0);
    sim.exit();
    ASSERT_EQ(sim.get_state(), 1);
  }

  TEST_F(SimulationTest, state_defaults_to_zero) {
    ASSERT_EQ(sim.get_state(), 0);
  }

  TEST_F(SimulationTest, can_get_simulation_frequency) {
  	ASSERT_EQ(sim.get_frequency(), 1);
  }

  TEST_F(SimulationTest, can_get_real_duration) {
		ASSERT_EQ(sim.get_real_duration(), 0);
	}

  TEST_F(SimulationTest, can_get_simulated_duration) {
		ASSERT_EQ(sim.get_sim_duration(), 0);
	}

  TEST_F(SimulationTest, can_get_elapsed_simulated_time) {
		ASSERT_EQ(sim.get_elapsed_sim_time(), 0);
	}

  TEST_F(SimulationTest, can_get_elapsed_simulated_time_remainder) {
		ASSERT_EQ(sim.get_sim_time_remainder(), 0);
	}

  TEST_F(SimulationTest, can_get_elapsed_real_time) {
		ASSERT_EQ(sim.get_elapsed_real_time(), 0);
	}

  // real time = sim time * frequency
  TEST_F(SimulationTest, can_scale_real_time) {
  	sim.set_sim_duration_and_frequency(10,10);	//10 units * (10 ns / 1 unit) = 100ns real time
  	ASSERT_EQ(sim.get_real_duration(), 100);
  }

  // sim time = real time / frequency
  TEST_F(SimulationTest, can_scale_simulation_time) {
  	sim.set_real_duration_and_frequency(100,50);
  	ASSERT_EQ(sim.get_sim_duration(), 2);

  	// an assert is thrown if: real time % frequency > 0
  	ASSERT_ANY_THROW(sim.set_real_duration_and_frequency(102,50));
  }

  // frequency = real time / sim time
  TEST_F(SimulationTest, can_scale_frequency) {
  	sim.set_real_and_sim_duration(1000,10);
  	ASSERT_EQ(sim.get_frequency(), 100);

  	// an assert is thrown if: real time % frequency > 0
		ASSERT_ANY_THROW(sim.set_real_and_sim_duration(100, 13));
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    sim.set_real_and_sim_duration(1000000, 50);
    timespec start, end;        //to track the actual time offset
    /*
    timespec t1,t2,t3,t4,t5;    //used to calibrate average time for clock_gettime() call
    int scale = 1;
    int count = scale;
    int sum_of_gettime = 0;
    while(count > 0) {
      //calibrate average time for clock_gettime
      clock_gettime(1, &t1);
      clock_gettime(1, &t2);
      clock_gettime(1, &t3);
      clock_gettime(1, &t4);
      clock_gettime(1, &t5);

      timespec* elapsed1 = sim.core_timer.get_timespec_diff(&t2, &t1);
      timespec* elapsed2 = sim.core_timer.get_timespec_diff(&t3, &t2);
      timespec* elapsed3 = sim.core_timer.get_timespec_diff(&t4, &t3);
      timespec* elapsed4 = sim.core_timer.get_timespec_diff(&t5, &t4);
      sum_of_gettime += elapsed1->tv_nsec + elapsed2->tv_nsec + elapsed3->tv_nsec + elapsed4->tv_nsec;

      count--;
    }
    uint64_t average_time_for_gettime = sum_of_gettime / (scale*4);
    EXPECT_GT(average_time_for_gettime, 0);
    EXPECT_LT(average_time_for_gettime, 1);
    */
    clock_gettime(1, &start);
    sim.run();
    clock_gettime(1, &end);

    timespec* elapsed = sim.core_timer.get_timespec_diff(&end, &start);
    uint64_t nseconds = elapsed->tv_sec * 1000000000LL + elapsed->tv_nsec;// + average_time_for_gettime;
    EXPECT_GT(nseconds - sim.get_elapsed_real_time(), 0);
    ASSERT_EQ(sim.get_elapsed_real_time(), sim.get_real_duration());
  }

} /* namespace core */
