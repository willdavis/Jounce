/*
 * timespec_helper_test.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/helpers/timespec_helper.h"

namespace core
{
	TEST(TimespecHelperTest, can_get_difference_between_timespecs) {
		timespec start;
		start.tv_sec = 10;
		start.tv_nsec = 1000;

		timespec end;
		end.tv_sec = 11;
		end.tv_nsec = 1010;

		timespec diff = TimespecHelper::get_timespec_diff(&end, &start);
		ASSERT_EQ(diff.tv_sec, 1);
		ASSERT_EQ(diff.tv_nsec, 10);
	}

	TEST(TimespecHelperTest, throws_exception_if_timespec_difference_is_less_than_zero) {
		timespec start;
		start.tv_sec = 10;
		start.tv_nsec = 1000;

		timespec end;
		end.tv_sec = 9;
		end.tv_nsec = 500;

		ASSERT_ANY_THROW(TimespecHelper::get_timespec_diff(&end, &start));
	}
} /* namespace core */
