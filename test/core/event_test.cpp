/*
 * event_test.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/events/event.h"

namespace core
{
  int dummy_int = 0;

  class NewEvent : public Event {
  public:
    void process_event () { dummy_int = 1; }
  };

  class EventTest : public ::testing::Test {
  protected:
    NewEvent event;
  };

  TEST_F(EventTest, can_implement_process_event) {
    EXPECT_EQ(dummy_int, 0);
    event.process_event();
    ASSERT_EQ(dummy_int, 1);
  }

} /* namespace core */
