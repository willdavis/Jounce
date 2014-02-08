/*
 * jObject_test.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/objects/object.h"
#include "../../../src/core/object_manager.h"

namespace core
{
	class MyJObject : public JObject {
	public:
		uint64_t test_time = 0;
		void update(uint64_t* dt) { test_time = *dt; }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){ /* not used */ }
	};

	class MyObserver : public Observer {
	public:
		int times_called;
		void notify(Observable* sender, std::shared_ptr<Observer> caller)
		{
			//static_cast<MyJObject*>(sender)->test_time++;
			std::static_pointer_cast<MyObserver>(caller)->on_notify();
		}
		void on_notify(){ times_called++; }
	};

	class ObjectTest : public ::testing::Test {
	protected:
		MyJObject obj;
		ObjectManager manager;
	};

	TEST_F(ObjectTest, can_get_ammount_of_registered_observers) {
		ASSERT_EQ(0, obj.total_observers());
	}

	TEST_F(ObjectTest, can_bind_to_an_object_manager) {
		ASSERT_NO_THROW(obj.set_owner(&manager));
		ASSERT_EQ(&manager, obj.owner());
	}

	TEST_F(ObjectTest, can_register_an_observer) {
		std::shared_ptr<Observer> test(new MyObserver);
		EXPECT_EQ(0, obj.total_observers());
		EXPECT_NO_THROW(obj.register_observer(test));
		ASSERT_EQ(1, obj.total_observers());
	}

	TEST_F(ObjectTest, can_release_an_observer) {
		std::shared_ptr<Observer> test(new MyObserver);
		std::shared_ptr<Observer> test2(new MyObserver);
		unsigned int test_id = obj.register_observer(test);
		unsigned int test2_id = obj.register_observer(test2);
		EXPECT_EQ(2, obj.total_observers());
		EXPECT_EQ(0, test_id);
		EXPECT_EQ(1, test2_id);
		EXPECT_NO_THROW(obj.release_observer(test_id));
		ASSERT_EQ(1, obj.total_observers());
	}

	TEST_F(ObjectTest, cannot_release_nonexistant_objects) {
		std::shared_ptr<Observer> test(new MyObserver);
		obj.register_observer(test);
		unsigned int bad_id = 2;
		EXPECT_EQ(1, obj.total_observers());
		ASSERT_ANY_THROW(obj.release_observer(bad_id));
	}

	TEST_F(ObjectTest, can_notify_an_observer_by_id) {
		std::shared_ptr<Observer> test1(new MyObserver);
		std::shared_ptr<Observer> test2(new MyObserver);

		// initialize
		std::static_pointer_cast<MyObserver>(test1)->times_called = 0;
		std::static_pointer_cast<MyObserver>(test2)->times_called = 0;
		unsigned int test1_id = obj.register_observer(test1);
		unsigned int test2_id = obj.register_observer(test2);

		// update the object
		uint64_t dt = 10;
		obj.update(&dt);
		obj.notify_observer(test1_id);
		obj.notify_observer(test2_id);
		obj.notify_observer(test2_id);

		// verify updates
		EXPECT_EQ(10, obj.test_time);
		EXPECT_EQ(0, test1_id);
		EXPECT_EQ(1, test2_id);
		ASSERT_EQ(1, std::static_pointer_cast<MyObserver>(test1)->times_called);
		ASSERT_EQ(2, std::static_pointer_cast<MyObserver>(test2)->times_called);
	}

	TEST_F(ObjectTest, cannot_notify_nonexistant_observer_ids) {
		std::shared_ptr<Observer> test1(new MyObserver);
		obj.register_observer(test1);
		unsigned int bad_id = 50;
		EXPECT_EQ(1, obj.total_observers());
		ASSERT_ANY_THROW(obj.notify_observer(bad_id));
	}
} /* namespace core */
