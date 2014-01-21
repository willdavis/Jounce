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

  TEST_F(SimulationTest, duration_default_is_negative_one) {
    ASSERT_EQ(sim.duration, -1);
  }

  TEST_F(SimulationTest, duration_can_be_set) {
    sim.duration = 10;
    ASSERT_EQ(sim.duration, 10);
  }

  TEST_F(SimulationTest, simulation_runs_for_duration_then_exits) {
    timespec start;
    clock_gettime(1, &start);

    sim.duration = 0.2;
    sim.run();

    timespec end;
    clock_gettime(1, &end);

    int elapsed = end.tv_nsec - start.tv_nsec;
    ASSERT_GT(elapsed, 0);
    ASSERT_EQ(elapsed, sim.duration);
  }
} /* namespace core */
