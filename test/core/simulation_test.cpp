/*
 * simulation_test.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/simulation.h"

namespace core
{
  class SimulationTest : public ::testing::Test {
  protected:
    Simulation sim;
  };

  class TestEvent : public Event {
  public:
    void process_event () { /* do nothing */ }
  };

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
    EXPECT_EQ(sim.state, 0);
    sim.exit();
    ASSERT_EQ(sim.state, 1);
  }

  TEST_F(SimulationTest, state_defaults_to_zero) {
    ASSERT_EQ(sim.state, 0);
  }

  TEST_F(SimulationTest, duration_default_is_zero) {
    ASSERT_EQ(sim.duration, 0);
  }

  TEST_F(SimulationTest, duration_can_be_set) {
    sim.duration = 10;
    ASSERT_EQ(sim.duration, 10);
  }

  TEST_F(SimulationTest, time_scale_can_be_set) {
    EXPECT_EQ(sim.time_scale, 1);
    sim.time_scale = 1.5;
    ASSERT_EQ(sim.time_scale, 1.5);
  }

  TEST_F(SimulationTest, can_scale_a_frame_by_the_time_scale) {
    uint64_t test_time = 200;           //simulates a 200ns frame
    sim.time_scale = 1.5;               //set 1.5x time scale
    uint64_t scaled_time = sim.get_scaled_time(test_time);
    EXPECT_GT(scaled_time, 0);
    ASSERT_EQ(scaled_time, 300);
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    timespec start;
    clock_gettime(1, &start);

    sim.duration = 1000000000;  //1 second
    sim.run();

    timespec end;
    clock_gettime(1, &end);

    timespec* elapsed = sim.core_timer.get_timespec_diff(&end, &start);
    uint64_t nseconds = elapsed->tv_sec * 1000000000LL + elapsed->tv_nsec;
    ASSERT_GT(nseconds, 0);
    ASSERT_EQ(nseconds, sim.duration);
  }

  TEST_F(SimulationTest, simulation_processes_all_events_then_exits)
  {
    TestEvent event1;
    TestEvent event2;
    sim.schedule_event(&event1);
    sim.schedule_event(&event2);
    EXPECT_EQ(sim.get_event_queue_size(), 2);
    sim.run();
    ASSERT_EQ(sim.get_event_queue_size(), 0);
  }
} /* namespace core */
