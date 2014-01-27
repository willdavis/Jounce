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

  TEST_F(TimerTest, can_get_elapsed_time) {
    uint64_t nseconds = timer.get_elapsed_time();
    ASSERT_GT(nseconds, 0);
    //ASSERT_LT(nseconds, 1);             //uncomment to break test and view nseconds
  }

  TEST_F(TimerTest, clock_frequency_must_be_greater_than_zero) {
    int freq = timer.get_clock_frequency();
    ASSERT_GT(freq, 0);
    ASSERT_EQ(freq, 1);         //this is probably wrong.. but frequency doesn't seem to matter any more.
  }

} /* namespace core */
