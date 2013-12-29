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

  TEST_F(TimerTest, elapsed_time_must_be_greater_than_zero) {
    ASSERT_GT(timer.get_elapsed_time(), 0);
  }

  TEST_F(TimerTest, clock_frequency_must_be_greater_than_zero) {
    ASSERT_GT(timer.get_clock_frequency(), 0);
  }

} /* namespace core */
