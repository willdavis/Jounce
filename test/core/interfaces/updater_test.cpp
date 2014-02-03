/*
 * updater_test.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/updater.h"

namespace core
{
	class MyUpdater : public Updater {
	public:
	};

	class UpdateableTest : public ::testing::Test {
	protected:
		MyUpdater test;
	};
} /* namespace core */
