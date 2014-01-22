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

  int event_dispatch_test = 0;

  class TestEvent : public Event {
  public:
    void process_event () { event_dispatch_test = 1; }
  };

  TEST_F(EventManagerTest, can_check_the_event_queue_size) {
    int size = manager.get_queue_size();
    ASSERT_EQ(size, 0);
  }

  TEST_F(EventManagerTest, can_schedule_an_event) {
    EXPECT_EQ(manager.get_queue_size(), 0);
    TestEvent event;
    manager.schedule_event(&event);
    ASSERT_EQ(manager.get_queue_size(), 1);
  }

  TEST_F(EventManagerTest, can_process_the_top_event) {
    EXPECT_EQ(manager.get_queue_size(), 0);
    TestEvent event;
    manager.schedule_event(&event);
    ASSERT_EQ(manager.get_queue_size(), 1);     //same as can_schedule_an_event test

    manager.process_top_event();

    ASSERT_EQ(manager.get_queue_size(), 0);     //make sure the event was removed from the queue
    ASSERT_EQ(event_dispatch_test, 1);           //make sure the callback fired
  }
} /* namespace core */
