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

  TEST_F(TimerTest, can_get_timespec_difference) {
    timespec start;
    clock_gettime(1, &start);

    //for(int i=0; i<1000; i++){}

    timespec end;
    clock_gettime(1, &end);

    timespec* diff = timer.get_timespec_diff(&end, &start);
    ASSERT_EQ(diff->tv_sec, 0);
    ASSERT_GT(diff->tv_nsec, 0);
    //ASSERT_LT(diff->tv_nsec, 1);      //uncomment to break test and view diff->tv_nsec
  }

  TEST_F(TimerTest, elapsed_time_must_be_greater_than_zero) {
    timer.get_elapsed_time();
    int nanoseconds = timer.get_elapsed_time();
    ASSERT_GT(nanoseconds, 0);
    ASSERT_LT(nanoseconds, 200);
  }

  TEST_F(TimerTest, clock_frequency_must_be_greater_than_zero) {
    int freq = timer.get_clock_frequency();
    ASSERT_GT(freq, 0);
    ASSERT_EQ(freq, 1);         //this is probably wrong.. but frequency doesn't seem to matter any more.
  }

} /* namespace core */
