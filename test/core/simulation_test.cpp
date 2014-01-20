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
} /* namespace core */
