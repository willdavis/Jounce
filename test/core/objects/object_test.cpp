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

	TEST_F(ObjectTest, can_check_if_a_key_is_present) {
		ASSERT_FALSE(obj.key_exists("test"));
	}

	TEST_F(ObjectTest, can_register_an_observer) {
		std::shared_ptr<Observer> test(new MyObserver);
		std::pair<std::string, observer_ptr> pair ("test", test);
		EXPECT_EQ(0, obj.total_observers());
		EXPECT_NO_THROW(obj.register_observer(pair));
		ASSERT_EQ(1, obj.total_observers());
	}

	TEST_F(ObjectTest, cannot_register_an_observer_multiple_times) {
		std::shared_ptr<Observer> test(new MyObserver);
		std::pair<std::string, observer_ptr> pair ("test", test);
		EXPECT_EQ(0, obj.total_observers());
		EXPECT_NO_THROW(obj.register_observer(pair));
		ASSERT_ANY_THROW(obj.register_observer(pair));
	}

	TEST_F(ObjectTest, can_release_an_observer) {
		std::shared_ptr<Observer> test(new MyObserver);
		std::shared_ptr<Observer> test2(new MyObserver);
		std::pair<std::string, observer_ptr> pair1("test", test);
		std::pair<std::string, observer_ptr> pair2("test2", test2);
		obj.register_observer(pair1);
		obj.register_observer(pair2);
		EXPECT_EQ(2, obj.total_observers());
		EXPECT_NO_THROW(obj.release_observer("test"));
		ASSERT_EQ(1, obj.total_observers());
		EXPECT_NO_THROW(obj.release_observer("test2"));
		ASSERT_EQ(0, obj.total_observers());
	}

	TEST_F(ObjectTest, cannot_release_nonexistant_objects) {
		std::shared_ptr<Observer> test(new MyObserver);
		std::pair<std::string, observer_ptr> pair("test", test);
		obj.register_observer(pair);
		EXPECT_EQ(1, obj.total_observers());
		ASSERT_ANY_THROW(obj.release_observer("test2"));
	}

	TEST_F(ObjectTest, can_notify_an_observer_by_its_key) {
		std::shared_ptr<Observer> test1(new MyObserver);
		std::shared_ptr<Observer> test2(new MyObserver);

		// initialize
		std::static_pointer_cast<MyObserver>(test1)->times_called = 0;
		std::static_pointer_cast<MyObserver>(test2)->times_called = 0;
		std::pair<std::string, observer_ptr> pair1("test1", test1);
		std::pair<std::string, observer_ptr> pair2("test2", test2);
		obj.register_observer(pair1);
		obj.register_observer(pair2);

		// update the object
		uint64_t dt = 10;
		obj.update(&dt);
		obj.notify_observer("test1");
		obj.notify_observer("test2");
		obj.notify_observer("test2");

		// verify updates
		EXPECT_EQ(10, obj.test_time);
		ASSERT_EQ(1, std::static_pointer_cast<MyObserver>(test1)->times_called);
		ASSERT_EQ(2, std::static_pointer_cast<MyObserver>(test2)->times_called);
	}

	TEST_F(ObjectTest, cannot_notify_nonexistant_observer_ids) {
		std::shared_ptr<Observer> test1(new MyObserver);
		std::pair<std::string, observer_ptr> pair("test", test1);
		obj.register_observer(pair);
		EXPECT_EQ(1, obj.total_observers());
		ASSERT_ANY_THROW(obj.notify_observer("test2"));
	}
} /* namespace core */
