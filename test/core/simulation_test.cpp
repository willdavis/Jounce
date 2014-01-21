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

  TEST_F(SimulationTest, state_defaults_to_zero) {
    ASSERT_EQ(sim.state, 0);
  }

  TEST_F(SimulationTest, state_is_1_on_exit) {
    sim.run();
    ASSERT_EQ(sim.state, 1);
  }

  TEST_F(SimulationTest, duration_default_is_zero) {
    ASSERT_EQ(sim.duration, 0);
  }

  TEST_F(SimulationTest, duration_can_be_set) {
    sim.duration = 10;
    ASSERT_EQ(sim.duration, 10);
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    timespec start;
    clock_gettime(1, &start);

    sim.duration = 1000000000;  //1 second or 1000 ms
    sim.run();

    timespec end;
    clock_gettime(1, &end);

    timespec* elapsed = sim.core_timer.get_timespec_diff(&end, &start);
    uint64_t nseconds = elapsed->tv_sec * 1000000000LL + elapsed->tv_nsec;
    ASSERT_GT(nseconds, 0);
    ASSERT_EQ(nseconds, sim.duration);
  }
} /* namespace core */
