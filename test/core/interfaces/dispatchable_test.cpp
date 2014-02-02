/*
 * dispatchable_test.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/dispatchable.h"

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

	class DispatchableTest : public ::testing::Test {
	protected:
		MyDispatchable event;
	};

	TEST_F(DispatchableTest, must_implement_dispatcher_interface) {
		MyDispatcher* dispatcher = new MyDispatcher;
		EXPECT_NO_THROW(event.dispatch(dispatcher));
		EXPECT_NO_THROW(event.priority());
		EXPECT_NO_THROW(event.timestamp());
		delete dispatcher;
	}

} /* namespace core */
