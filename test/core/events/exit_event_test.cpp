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
  public:
  	ExitEventTest(){ sim = new Simulation(0,"test"); }
  	~ExitEventTest(){ delete sim; }
  protected:
    ExitEvent exit;
    Simulation* sim;
  };

  TEST_F(ExitEventTest, priority_is_zero) {
  	ASSERT_EQ((unsigned int)0, exit.priority());
  }

  TEST_F(ExitEventTest, calls_exit_on_simulation) {
  	event_ptr exit(new ExitEvent);
  	sim->schedule_event(exit);
    EXPECT_TRUE(sim->is_off());
    sim->run();
    ASSERT_TRUE(sim->is_off());
  }

} /* namespace core */
