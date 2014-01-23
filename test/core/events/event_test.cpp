/*
 * event_test.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/events/event.h"

namespace core
{
  // test event with arguments
  class ArgsEvent : public Event {
  public:
    void process_event(void* input) {
      int new_value = 0;
      int *pInt = static_cast<int*>(input);
      *pInt = new_value;
    }
  };

  // test event with no arguments
  class NoArgsEvent : public Event {
  public:
    void process_event(void* input) { /* do nothing */ }
  };

  class EventTest : public ::testing::Test {
  protected:
    NoArgsEvent blank_event;
    ArgsEvent event;
  };

  TEST_F(EventTest, must_implement_basic_process_event_method) {
    blank_event.process_event((void*)0);
  }

  TEST_F(EventTest, process_event_accepts_a_single_argument) {
    int test_input = 50;
    event.process_event(&test_input);
    ASSERT_EQ(test_input, 0);
  }

} /* namespace core */
