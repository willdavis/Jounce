/*
 * updateable_test.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/updateable.h"

namespace core
{
	class MyUpdateable : public Updateable {
	public:
		void update(uint64_t* dt){ *dt = 10; }
	};

	class UpdateableTest : public ::testing::Test {
	protected:
		MyUpdateable test;
	};

	TEST_F(UpdateableTest, must_implement_updateable_interface) {
		uint64_t* test_int = new uint64_t(0);
		test.update(test_int);
		ASSERT_EQ(10, *test_int);
		delete test_int;
	}
} /* namespace core */
