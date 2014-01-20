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
    ASSERT_EQ(sim.get_state(), 0);
  }

  TEST_F(SimulationTest, state_is_1_on_exit) {
    sim.run();
    ASSERT_EQ(sim.get_state(), 1);
  }
} /* namespace core */
