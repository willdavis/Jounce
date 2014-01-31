/*
 * object_manager_test.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/object_manager.h"

namespace core
{

	uint64_t test_int = 0;

	class ObjectManagerTest : public ::testing::Test {
	protected:
		ObjectManager manager;
	};

	class MyObject : public SimObject {
	public:
		void update(uint64_t dt){ test_int += dt; }
	};

	class BlankObject : public SimObject {
	public:
		void update(uint64_t dt){ /* do nothing */ }
	};

	TEST_F(ObjectManagerTest, can_get_collection_size) {
		ASSERT_EQ(0, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_register_an_object) {
		sim_object_ptr obj(new MyObject);
		manager.register_object(obj);
		ASSERT_EQ(1, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_release_an_object) {
		sim_object_ptr obj(new MyObject);
		manager.register_object(obj);
		EXPECT_EQ(1, manager.get_collection_size());
		manager.release_registered_object(obj);
		ASSERT_EQ(0, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, cannot_release_a_non_existant_object) {
		sim_object_ptr obj(new MyObject);
		sim_object_ptr nope(new MyObject);
		EXPECT_EQ(0, manager.get_collection_size());
		manager.register_object(obj);									// add an object so the list size isn't empty
		manager.release_registered_object(nope);			// does not find any matching values, list size remains unchanged
		ASSERT_EQ(1, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_update_all_registered_objects) {
		EXPECT_EQ((uint64_t)0, test_int);
		sim_object_ptr obj1(new MyObject);
		sim_object_ptr obj2(new MyObject);
		sim_object_ptr obj3(new MyObject);

		manager.register_object(obj1);
		manager.register_object(obj2);
		manager.register_object(obj3);

		manager.update_all_registered_objects(10);

		ASSERT_EQ((uint64_t)30, test_int);	// verify the update() methods were called
	}

} /* namespace core */
