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
  public:
  	EventManagerTest(){ manager = new EventManager(0,"manager"); }
  	~EventManagerTest(){ delete manager; }
  protected:
    EventManager* manager;
  };

  int event_dispatch_test = 0;

  class TestEvent : public Dispatchable {
	public:
		void dispatch(Dispatcher* dispatcher){ event_dispatch_test = 1; }
		unsigned int priority() { return 1000; }
		uint64_t timestamp() { return (uint64_t)10; }
	};

  class CriticalEvent : public Dispatchable {
	public:
		void dispatch(Dispatcher* dispatcher){ /* do nothing */ }
		unsigned int priority() { return 0; }
		uint64_t timestamp() { return (uint64_t)10; }
	};

  TEST_F(EventManagerTest, can_bind_to_a_parent_object) {
    int test = 5;
    manager->set_parent(&test);
    int* test2 = static_cast<int*>(manager->get_parent());
    ASSERT_EQ(*test2, 5);
  }

  TEST_F(EventManagerTest, can_check_the_event_queue_size) {
    int size = manager->queue_size();
    ASSERT_EQ(size, 0);
  }

  TEST_F(EventManagerTest, can_schedule_an_event) {
    EXPECT_EQ(manager->queue_size(), 0);
    event_ptr event(new TestEvent);
    manager->schedule(event);
    ASSERT_EQ(manager->queue_size(), 1);
  }

  TEST_F(EventManagerTest, can_process_the_top_event) {
		EXPECT_EQ(manager->queue_size(), 0);
		event_ptr event(new TestEvent);
		manager->schedule(event);
		ASSERT_EQ(manager->queue_size(), 1);     //same as can_schedule_an_event test

		manager->dispatch_top_event();

		ASSERT_EQ(manager->queue_size(), 0);     //make sure the event was removed from the queue
		ASSERT_EQ(event_dispatch_test, 1);           //make sure the callback fired
	}

  TEST_F(EventManagerTest, can_peek_at_top_event) {
  	event_ptr event(new TestEvent);
  	manager->schedule(event);
  	ASSERT_EQ(1000, manager->get_top_event()->priority());
  }

  TEST_F(EventManagerTest, can_prioritize_events) {
  	event_ptr event(new TestEvent);
  	event_ptr critical(new CriticalEvent);

  	manager->schedule(event);
  	manager->schedule(critical);

  	ASSERT_EQ(0, manager->get_top_event()->priority());
  	manager->dispatch_top_event();
  	ASSERT_EQ(1000, manager->get_top_event()->priority());
	}

} /* namespace core */
