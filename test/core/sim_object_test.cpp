/*
 * sim_object_test.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/sim_object.h"

namespace core
{
	class MyObject : public SimObject {
	public:
		void update(uint64_t dt){ /* do nothing */ }
	};

	class SimObjectTest : public ::testing::Test {
	protected:
		MyObject my_object;
	};

	TEST_F(SimObjectTest, must_implement_update_method) {
		uint64_t dt = 10;
		my_object.update(10);
	}

} /* namespace core */
