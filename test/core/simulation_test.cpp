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
    sim.set_real_duration(1000000000);  //1 second
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
    ASSERT_GT(nseconds, 0);
    ASSERT_EQ(sim.get_real_duration(), nseconds);
    delete elapsed;
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
