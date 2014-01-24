/*
 * time_scalar_test.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/time_manager.h"

namespace core
{
	class TimeManagerTest : public ::testing::Test {
	protected:
		TimeManager scalar;
	};

	TEST_F(TimeManagerTest, can_add_real_time) {
		EXPECT_EQ(scalar.get_real_elapsed_time(), 0);
		scalar.add_real_time(10);
		ASSERT_EQ(scalar.get_real_elapsed_time(), 10);
	}

	TEST_F(TimeManagerTest, can_add_simulated_time) {
		EXPECT_EQ(scalar.get_simulated_elapsed_time(), 0);
		scalar.add_simulated_time(10);
		ASSERT_EQ(scalar.get_simulated_elapsed_time(), 10);
	}

	TEST_F(TimeManagerTest, can_get_real_duration) {
		ASSERT_EQ(scalar.get_real_duration(), 0);
	}

	TEST_F(TimeManagerTest, can_set_real_duration) {
		scalar.set_real_duration(10);
		ASSERT_EQ(scalar.get_real_duration(), 10);
	}

	TEST_F(TimeManagerTest, can_get_simulated_duration) {
		ASSERT_EQ(scalar.get_simulated_duration(), 0);
	}

	TEST_F(TimeManagerTest, can_set_simulated_duration) {
		scalar.set_simulated_duration(15);
		ASSERT_EQ(scalar.get_simulated_duration(), 15);
	}

	TEST_F(TimeManagerTest, can_get_real_elapsed_time) {
		ASSERT_EQ(scalar.get_real_elapsed_time(), 0);
	}

	TEST_F(TimeManagerTest, can_get_simulated_elapsed_time) {
		ASSERT_EQ(scalar.get_simulated_elapsed_time(), 0);
	}

	TEST_F(TimeManagerTest, can_get_time_scale) {
		ASSERT_EQ(scalar.get_time_scale(), 1);
	}

	TEST_F(TimeManagerTest, can_set_time_scale) {
		EXPECT_EQ(scalar.get_time_scale(), 1);
		scalar.set_time_scale(1.5);
		ASSERT_EQ(scalar.get_time_scale(), 1.5);
	}

	TEST_F(TimeManagerTest, can_get_min_framerate) {
		ASSERT_EQ(scalar.get_min_framerate(), 0);
	}

	TEST_F(TimeManagerTest, can_get_max_framerate) {
		ASSERT_EQ(scalar.get_max_framerate(), 0);
	}

	TEST_F(TimeManagerTest, can_set_min_framerate) {
		scalar.set_min_framerate(10);
		ASSERT_EQ(scalar.get_min_framerate(), 10);
	}

	TEST_F(TimeManagerTest, can_set_max_framerate) {
		scalar.set_max_framerate(10);
		ASSERT_EQ(scalar.get_max_framerate(), 10);
	}
} /* namespace core */
