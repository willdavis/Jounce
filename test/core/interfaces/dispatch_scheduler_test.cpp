/*
 * dispatch_scheduler_test.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/dispatch_scheduler.h"

namespace core
{

	class MyScheduler : public DispatchScheduler {
	public:
		unsigned int queue_size() { return 0; }
		void schedule(std::shared_ptr<Dispatchable> event) { /* do nothing */ }
	};

	class DispatchSchedulerTest : public ::testing::Test {
	protected:
		MyScheduler test;
	};

	TEST_F(DispatchSchedulerTest, must_implement_dispatchable_interface) {
		EXPECT_NO_THROW(test.queue_size());
	}
} /* namespace core */
