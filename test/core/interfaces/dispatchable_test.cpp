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
		void dispatch_top_event() { /* do nothing */ }
		void schedule(std::shared_ptr<Dispatchable> event) { /* do nothing */ }
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

	TEST_F(DispatchableTest, must_implement_dispatchable_interface) {
		MyDispatcher* dispatcher = new MyDispatcher;
		EXPECT_NO_THROW(event.dispatch(dispatcher));
		EXPECT_NO_THROW(event.priority());
		EXPECT_NO_THROW(event.timestamp());
		delete dispatcher;
	}

} /* namespace core */
