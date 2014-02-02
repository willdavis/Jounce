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
	};

	class DispatcherTest : public ::testing::Test {
	protected:
		MyDispatcher test;
	};

	TEST_F(DispatcherTest, must_implement_interface) {
		ASSERT_NO_THROW(test.dispatch_top_event());
	}
} /* namespace core */
