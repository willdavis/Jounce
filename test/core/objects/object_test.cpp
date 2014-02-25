/*
 * jObject_test.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/objects/object.h"
#include "../../../src/core/object_manager.h"
#include "../../../src/core/event_manager.h"

namespace core
{
	class MyJObject : public JObject {
	public:
		MyJObject()
		{
			JSignal<void>* test_signal = new JSignal<void>(this, "test()");
			JSignal<void,int,double,JObject*>* test_signal2 = new JSignal<void,int,double,JObject*>(this, "awesome(int,double,JObject*)");
			register_signal(test_signal);
			register_signal(test_signal2);
		}
		uint64_t test_time = 0;
		void update(uint64_t* dt) { test_time = *dt; }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){ /* not used */ }
		void on_test(){  }
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

	class MyEvent : public Dispatchable {
		void dispatch(Dispatcher* dispatcher){  }
		unsigned int priority() { return 0; }
		uint64_t timestamp() { return 0; }
	};

	class ObjectTest : public ::testing::Test {
	protected:
		MyJObject obj;
		ObjectManager manager;
		EventManager event_manager;
	};

	TEST_F(ObjectTest, can_check_for_a_signal) {
		JSignal<void> signal(&obj, "signal()");
		std::string test_str = "func(JObject*, int, double, std::string)";
		ASSERT_FALSE(obj.has_signal(&signal));	//JMetaObject* test
		ASSERT_FALSE(obj.has_signal(test_str));	//std::string test
		ASSERT_TRUE(obj.has_signal("test()"));	//const char* test
	}

	TEST_F(ObjectTest, can_emit_a_signal) {
		ASSERT_EQ((JMetaObject*)0, obj.signal("**ERROR**"));

		JSignal<void>* signal = static_cast<JSignal<void>* >(obj.signal("test()"));
		ASSERT_STREQ("test()", signal->signature());
		ASSERT_EQ(&obj, signal->parent());
		ASSERT_NO_THROW(signal->emit());

		JSignal<void,int,double,JObject*>* signal2 = static_cast<JSignal<void,int,double,JObject*>* >(obj.signal("awesome(int,double,JObject*)"));
		ASSERT_STREQ("awesome(int,double,JObject*)", signal2->signature());
		ASSERT_EQ(&obj, signal2->parent());
		ASSERT_NO_THROW(signal2->emit(10, 1.5, &obj));
	}

	TEST_F(ObjectTest, can_connect_a_slot_to_a_signal) {
		std::function<void()> func = [](){};
		std::function<int(int)> bad_func = [](int i){ return i; };
		std::function<void()> member_func = std::bind(&MyJObject::on_test, &obj);

		ASSERT_TRUE(obj.connect(obj.signal("test()"), func, "func_handle"));
		ASSERT_TRUE(obj.connect(obj.signal("test()"), member_func, "member_func_handle"));

		// no duplicates allowed
		ASSERT_FALSE(obj.connect(obj.signal("test()"), func, "func_handle"));

		// BEWARE!! this is not technically a duplicate (different handle)
		ASSERT_TRUE(obj.connect(obj.signal("test()"), func, "new_func_handle"));
	}

	TEST_F(ObjectTest, can_get_ammount_of_registered_observers) {
		ASSERT_EQ(0, obj.total_observers());
	}

	TEST_F(ObjectTest, can_bind_to_an_object_manager) {
		ASSERT_NO_THROW(obj.set_owner(&manager));
	}

	TEST_F(ObjectTest, can_schedule_an_event) {
		EXPECT_NO_THROW(manager.set_dispatcher(&event_manager));
		EXPECT_NO_THROW(obj.set_owner(&manager));
		std::shared_ptr<Dispatchable> event(new MyEvent);
		ASSERT_NO_THROW(obj.schedule_event(event));
		ASSERT_EQ(1, event_manager.queue_size());
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

	TEST_F(ObjectTest, cannot_register_duplicate_observer_keys) {
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

	TEST_F(ObjectTest, cannot_release_nonexistant_observers) {
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

	TEST_F(ObjectTest, cannot_notify_nonexistant_observers) {
		ASSERT_ANY_THROW(obj.notify_observer("test2"));
	}
} /* namespace core */
