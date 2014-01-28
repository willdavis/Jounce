/*
 * exit_event_test.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/events/exit_event.h"
#include "../../../src/core/simulation.h"

namespace core
{
  class ExitEventTest : public ::testing::Test {
  protected:
    ExitEvent exit;
    Simulation sim;
  };

  TEST_F(ExitEventTest, priority_is_zero) {
  	ASSERT_EQ(0, exit.get_priority());
  }

  TEST_F(ExitEventTest, calls_exit_on_simulation) {
    EXPECT_EQ(sim.get_state(), 0);
    exit.process_event(&sim);
    ASSERT_EQ(sim.get_state(), 1);
  }

} /* namespace core */
