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

  TEST_F(SimulationTest, can_get_real_duration) {
    ASSERT_EQ(sim.get_real_duration(), 0);
  }

  TEST_F(SimulationTest, can_set_real_duration) {
    sim.set_real_duration(10);
    ASSERT_EQ(sim.get_real_duration(), 10);
  }

  TEST_F(SimulationTest, can_get_simulated_duration) {
    ASSERT_EQ(sim.get_simulated_duration(), 0);
  }

  TEST_F(SimulationTest, can_set_simulated_duration) {
    sim.set_simulated_duration(15);
    ASSERT_EQ(sim.get_simulated_duration(), 15);
  }

  TEST_F(SimulationTest, can_get_real_elapsed_time) {
    ASSERT_EQ(sim.get_real_elapsed_time(), 0);
  }

  TEST_F(SimulationTest, can_get_simulated_elapsed_time) {
    ASSERT_EQ(sim.get_simulated_elapsed_time(), 0);
  }

  TEST_F(SimulationTest, can_get_time_scale) {
    ASSERT_EQ(sim.get_time_scale(), 1);
  }

  TEST_F(SimulationTest, can_set_time_scale) {
    EXPECT_EQ(sim.get_time_scale(), 1);
    sim.set_time_scale(1.5);
    ASSERT_EQ(sim.get_time_scale(), 1.5);
  }

  TEST_F(SimulationTest, can_get_min_framerate) {
    ASSERT_EQ(sim.get_min_framerate(), 0);
  }

  TEST_F(SimulationTest, can_get_max_framerate) {
    ASSERT_EQ(sim.get_max_framerate(), 0);
  }

  TEST_F(SimulationTest, can_set_min_framerate) {
    sim.set_min_framerate(10);
    ASSERT_EQ(sim.get_min_framerate(), 10);
  }

  TEST_F(SimulationTest, can_set_max_framerate) {
    sim.set_max_framerate(10);
    ASSERT_EQ(sim.get_max_framerate(), 10);
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    timespec start;
    clock_gettime(1, &start);

    sim.set_real_duration(1000000000);  //1 second
    sim.run();

    timespec end;
    clock_gettime(1, &end);

    timespec* elapsed = sim.core_timer.get_timespec_diff(&end, &start);
    uint64_t nseconds = elapsed->tv_sec * 1000000000LL + elapsed->tv_nsec;
    ASSERT_GT(nseconds, 0);
    ASSERT_EQ(nseconds, sim.get_real_duration());
  }

  TEST_F(SimulationTest, simulation_processes_all_events_then_exits)
  {
    TestEvent event1;
    TestEvent event2;
    ExitEvent exit;
    sim.schedule_event(&event1);
    sim.schedule_event(&event2);
    sim.schedule_event(&exit);
    EXPECT_EQ(sim.get_event_queue_size(), 3);
    sim.run();
    ASSERT_EQ(sim.get_event_queue_size(), 0);
  }
} /* namespace core */
