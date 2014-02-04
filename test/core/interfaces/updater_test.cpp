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

	int updater_test_int = 0;

	class MyUpdater : public Updater {
	public:
		void register_object(std::shared_ptr<Updateable> object) { updater_test_int++; }
		void release_object(std::shared_ptr<Updateable> object) { updater_test_int--; }
		void update_all_objects(uint64_t* elapsed_time) { updater_test_int = (int)(*elapsed_time); }
	};

	class MyUpdateable : public Updateable {
	public:
		void update(uint64_t* dt) { /* do nothing */ }
	};

	class UpdaterTest : public ::testing::Test {
	protected:
		MyUpdater test;
	};

	TEST_F(UpdaterTest, must_implement_updater_interface) {
		EXPECT_EQ(0, updater_test_int);
		std::shared_ptr<Updateable> obj(new MyUpdateable);
		uint64_t* dt = new uint64_t(10);
		test.register_object(obj);
		EXPECT_EQ(1, updater_test_int);
		test.release_object(obj);
		EXPECT_EQ(0, updater_test_int);
		test.update_all_objects(dt);
		EXPECT_EQ(10, updater_test_int);
		delete dt;
	}
} /* namespace core */
