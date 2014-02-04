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
		void dispatch_top_event() { /* do nothing */ }
		void close() { /* do nothing */ }
	};

	class DispatcherTest : public ::testing::Test {
	protected:
		MyDispatcher test;
	};

	TEST_F(DispatcherTest, must_implement_dispatcher_interface) {
		EXPECT_NO_THROW(test.dispatch_top_event());
		EXPECT_NO_THROW(test.close());
	}
} /* namespace core */
