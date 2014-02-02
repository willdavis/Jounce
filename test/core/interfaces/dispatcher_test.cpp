/*
 * dispatcher_test.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/dispatcher.h"

namespace core
{
	class MyDispatcher : public Dispatcher {
	public:
		unsigned int queue_size() { return 0; }
		void process_all_dispatchables() { /* do nothing */ }
		void schedule(Dispatchable* d) { /* do nothing */ }
		void close() { /* do nothing */ }
	};

	class MyDispatchable : public Dispatchable {
	public:
		void dispatch(Dispatcher* dispatcher){ /* do nothing */ }
		unsigned int priority() { return 10; }
		uint64_t timestamp() { return (uint64_t)10; }
	};

	class DispatcherTest : public ::testing::Test {
	protected:
		MyDispatcher test;
	};

	TEST_F(DispatcherTest, must_implement_interface) {
		Dispatchable* event = new MyDispatchable;
		EXPECT_NO_THROW(test.schedule(event));
		EXPECT_NO_THROW(test.process_all_dispatchables());
		EXPECT_NO_THROW(test.queue_size());
		EXPECT_NO_THROW(test.close());
		delete event;
	}
} /* namespace core */
