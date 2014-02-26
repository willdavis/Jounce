/*
 * object_manager_test.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/object_manager.h"
#include "../../src/core/event_manager.h"

namespace core
{

	uint64_t object_manager_update_test = 0;

	class ObjectManagerTest : public ::testing::Test {
	protected:
		ObjectManager manager;
		EventManager event_manager;
	};

	class MyObject : public JObject {
	public:
		void update(uint64_t* dt){ object_manager_update_test += *dt; }
	};

	class BlankObject : public Updateable {
	public:
		void update(uint64_t* dt){ /* do nothing */ }
	};

	TEST_F(ObjectManagerTest, can_bind_to_an_event_manager) {
		ASSERT_NO_THROW(manager.set_dispatcher(&event_manager));
		ASSERT_EQ(&event_manager, manager.dispatcher());
	}

	TEST_F(ObjectManagerTest, can_get_collection_size) {
		ASSERT_EQ(0, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_register_an_object) {
		object_ptr obj(new MyObject);
		manager.register_object(obj);
		ASSERT_EQ(1, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_release_an_object) {
		object_ptr obj(new MyObject);
		manager.register_object(obj);
		EXPECT_EQ(1, manager.get_collection_size());
		manager.release_object(obj);
		ASSERT_EQ(0, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, cannot_release_a_non_existant_object) {
		object_ptr obj(new MyObject);
		object_ptr nope(new MyObject);
		EXPECT_EQ(0, manager.get_collection_size());
		manager.register_object(obj);									// add an object so the list size isn't empty
		manager.release_object(nope);			// does not find any matching values, list size remains unchanged
		ASSERT_EQ(1, manager.get_collection_size());
	}

	TEST_F(ObjectManagerTest, can_update_all_registered_objects) {
		EXPECT_EQ((uint64_t)0, object_manager_update_test);
		object_ptr obj1(new MyObject);
		object_ptr obj2(new MyObject);
		object_ptr obj3(new MyObject);

		manager.register_object(obj1);
		manager.register_object(obj2);
		manager.register_object(obj3);

		uint64_t dt = 10;
		manager.update_all_objects(&dt);

		ASSERT_EQ((uint64_t)30, object_manager_update_test);	// verify the update() methods were called
	}

} /* namespace core */
