/*
 * time_manager_test.cpp
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
		TimeManager manager;
	};

	TEST_F(TimeManagerTest, can_add_real_time) {
		EXPECT_EQ(manager.get_real_elapsed_time(), 0);
		manager.add_real_time(10);
		ASSERT_EQ(manager.get_real_elapsed_time(), 10);
	}

	TEST_F(TimeManagerTest, can_add_simulated_time) {
		EXPECT_EQ(manager.get_simulated_elapsed_time(), 0);
		manager.add_simulated_time(10);
		ASSERT_EQ(manager.get_simulated_elapsed_time(), 10);
	}

	TEST_F(TimeManagerTest, can_get_real_duration) {
		ASSERT_EQ(manager.get_real_duration(), 0);
	}

	TEST_F(TimeManagerTest, can_set_real_duration) {
		manager.set_real_duration(10);
		ASSERT_EQ(manager.get_real_duration(), 10);
	}

	TEST_F(TimeManagerTest, can_get_simulated_duration) {
		ASSERT_EQ(manager.get_simulated_duration(), 0);
	}

	TEST_F(TimeManagerTest, can_set_simulated_duration) {
		manager.set_simulated_duration(15);
		ASSERT_EQ(manager.get_simulated_duration(), 15);
	}

	TEST_F(TimeManagerTest, can_get_real_elapsed_time) {
		ASSERT_EQ(manager.get_real_elapsed_time(), 0);
	}

	TEST_F(TimeManagerTest, can_get_simulated_elapsed_time) {
		ASSERT_EQ(manager.get_simulated_elapsed_time(), 0);
	}

	TEST_F(TimeManagerTest, can_get_time_scale) {
		ASSERT_EQ(manager.get_time_scale(), 1);
	}

	TEST_F(TimeManagerTest, can_set_time_scale) {
		EXPECT_EQ(manager.get_time_scale(), 1);
		manager.set_time_scale(1.5);
		ASSERT_EQ(manager.get_time_scale(), 1.5);
	}

	TEST_F(TimeManagerTest, can_get_framerate_range) {
		manager.set_min_framerate(10);
		manager.set_max_framerate(20);
		ASSERT_EQ(manager.get_framerate_range(), 10);

		manager.set_min_framerate(0);
		manager.set_max_framerate(20);
		ASSERT_EQ(manager.get_framerate_range(), 20);

		manager.set_min_framerate(10);
		manager.set_max_framerate(0);
		ASSERT_EQ(manager.get_framerate_range(), 10);

		manager.set_min_framerate(0);
		manager.set_max_framerate(0);
		ASSERT_EQ(manager.get_framerate_range(), 0);
	}

	TEST_F(TimeManagerTest, can_set_min_framerate) {
		manager.set_min_framerate(10);
		ASSERT_EQ(manager.get_framerate_range(), 10);
	}

	TEST_F(TimeManagerTest, can_set_max_framerate) {
		manager.set_max_framerate(10);
		ASSERT_EQ(manager.get_framerate_range(), 10);
	}
} /* namespace core */
