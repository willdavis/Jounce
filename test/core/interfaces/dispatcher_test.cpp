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
		void dispatch_the_queue() { /* do nothing */ }
		void schedule(std::shared_ptr<Dispatchable> event) { /* do nothing */ }
		void close() { /* do nothing */ }
	};

	class MyDispatchable : public Dispatchable {
	public:
		void dispatch(std::shared_ptr<Dispatcher> dispatcher){ /* do nothing */ }
		unsigned int priority() { return 10; }
		uint64_t timestamp() { return (uint64_t)10; }
	};

	class DispatcherTest : public ::testing::Test {
	protected:
		MyDispatcher test;
	};

	TEST_F(DispatcherTest, must_implement_dispatcher_interface) {
		std::shared_ptr<Dispatchable> event(new MyDispatchable);
		EXPECT_NO_THROW(test.schedule(event));
		EXPECT_NO_THROW(test.dispatch_the_queue());
		EXPECT_NO_THROW(test.queue_size());
		EXPECT_NO_THROW(test.close());
	}
} /* namespace core */
