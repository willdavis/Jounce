/*
 * timer_test.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/timer.h"

namespace core
{

  class TimerTest : public ::testing::Test {
  protected:
    Timer timer;
  };

  TEST_F(TimerTest, can_get_the_current_time) {
    ASSERT_TRUE(timer.get_time());
  }

} /* namespace core */
