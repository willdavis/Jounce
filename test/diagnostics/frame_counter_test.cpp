/*
 * frame_counter_test.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/diagnostics/frame_counter.h"

namespace Diagnostics
{
	class FrameCounterTest : public ::testing::Test {
	public:
		FrameCounterTest(){ counter = new FrameCounter(0, "counter_test"); }
		~FrameCounterTest(){ delete counter; }
	protected:
		FrameCounter* counter;
	};

	TEST_F(FrameCounterTest, can_get_average_framerate) {
		ASSERT_EQ(0, counter->average_frame());
	}

	TEST_F(FrameCounterTest, can_get_long_frame_ratio) {
		ASSERT_EQ(0, counter->long_frame_ratio());
	}

	TEST_F(FrameCounterTest, can_get_short_frame_ratio) {
		ASSERT_EQ(0, counter->short_frame_ratio());
	}

	TEST_F(FrameCounterTest, can_get_shortest_frame) {
		ASSERT_EQ(1000000000, counter->shortest_frame());
	}

	TEST_F(FrameCounterTest, can_get_longest_frame) {
		ASSERT_EQ(0, counter->longest_frame());
	}

	TEST_F(FrameCounterTest, can_get_total_frames) {
		ASSERT_EQ(0, counter->total_frames());
	}

	TEST_F(FrameCounterTest, can_get_total_time) {
		ASSERT_EQ(0, counter->total_time());
	}

	TEST_F(FrameCounterTest, can_get_short_frame) {
		ASSERT_EQ(0, counter->short_frame());
	}

	TEST_F(FrameCounterTest, can_set_short_frame) {
		uint64_t dt = 10;
		ASSERT_NO_THROW(counter->set_short_frame(&dt));
		ASSERT_EQ(10, counter->short_frame());
	}

	TEST_F(FrameCounterTest, can_get_long_frame) {
		ASSERT_EQ(0, counter->long_frame());
	}

	TEST_F(FrameCounterTest, can_set_long_frame) {
		uint64_t dt = 10;
		ASSERT_NO_THROW(counter->set_long_frame(&dt));
		ASSERT_EQ(10, counter->long_frame());
	}
} /* namespace Diagnostics */
