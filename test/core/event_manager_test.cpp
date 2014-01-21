/*
 * event_manager_test.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/event_manager.h"

namespace core
{
  class EventManagerTest : public ::testing::Test {
  protected:
    EventManager manager;
  };

  class TestEvent : public Event {
  public:
    void process_event () { /*do nothing*/ }
  };

  TEST_F(EventManagerTest, can_check_the_event_queue_size) {
    int size = manager.get_queue_size();
    ASSERT_EQ(size, 1);
  }

  TEST_F(EventManagerTest, can_schedule_an_event) {
    TestEvent event;
  }

  TEST_F(EventManagerTest, can_process_the_top_event) {

  }
} /* namespace core */
