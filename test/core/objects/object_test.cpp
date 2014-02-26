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
		MyJObject(JObject* parent, const char* signature) : JObject(parent, signature)
		{
			JSignal<void>* test_signal = new JSignal<void>(this, "test()");
			JSignal<void,int,double,JObject*>* test_signal2 = new JSignal<void,int,double,JObject*>(this, "awesome(int,double,JObject*)");
			register_signal(test_signal);
			register_signal(test_signal2);
		}
		uint64_t test_time = 0;
		void update(uint64_t* dt) { test_time = *dt; }
		void on_test(){  }
	};

	class MyEvent : public Dispatchable {
		void dispatch(Dispatcher* dispatcher){  }
		unsigned int priority() { return 0; }
		uint64_t timestamp() { return 0; }
	};

	class ObjectTest : public ::testing::Test {
	public:
		ObjectTest(){ obj = new MyJObject(0, "test"); }
	protected:
		MyJObject* obj;
		ObjectManager manager;
		EventManager event_manager;
	};

	TEST_F(ObjectTest, can_check_for_a_signal) {
		JSignal<void> signal(obj, "signal()");
		std::string test_str = "func(JObject*, int, double, std::string)";
		ASSERT_FALSE(obj->has_signal(&signal));	//JMetaObject* test
		ASSERT_FALSE(obj->has_signal(test_str));	//std::string test
		ASSERT_TRUE(obj->has_signal("test()"));	//const char* test
	}

	TEST_F(ObjectTest, can_emit_a_signal) {
		ASSERT_EQ((JMetaObject*)0, obj->signal<void>("**ERROR**"));

		JSignal<void>* signal = obj->signal<void>("test()");
		ASSERT_STREQ("test()", signal->signature());
		ASSERT_EQ(obj, signal->parent());
		ASSERT_NO_THROW(signal->emit());

		JSignal<void,int,double,JObject*>* signal2 = obj->signal<void,int,double,JObject*>("awesome(int,double,JObject*)");
		ASSERT_STREQ("awesome(int,double,JObject*)", signal2->signature());
		ASSERT_EQ(obj, signal2->parent());
		ASSERT_NO_THROW(signal2->emit(10, 1.5, obj));
	}

	TEST_F(ObjectTest, can_connect_a_slot_to_a_signal) {
		std::function<void()> func = [](){};
		std::function<int()> int_func = [](){ return 0; };
		std::function<void()> member_func = std::bind(&MyJObject::on_test, obj);

		// you can inline the function, just be sure to wrap it with std::function<Return(Args...)>
		// or you can use pre-defined std::function<Return(Args...)> variables (func, member_func, ect.)
		// auto keyword does not work in this context >_<
		ASSERT_TRUE(obj->connect(obj->signal<void>("test()"), std::function<void()>([](){}), "func_handle"));
		ASSERT_TRUE(obj->connect(obj->signal<void>("test()"),
				std::function<void()>(std::bind(&MyJObject::on_test, obj)),
				"member_func_handle"));

		// no duplicates allowed!!
		ASSERT_FALSE(obj->connect(obj->signal<void>("test()"), func, "func_handle"));

		// BEWARE!! this is not technically a duplicate since the handle is unique
		ASSERT_TRUE(obj->connect(obj->signal<void>("test()"), member_func, "different_handle"));

		// use static JObject::connect to connect slots
		ASSERT_TRUE(JObject::connect(obj, obj->signal<void>("test()"), func, "global_connect"));
	}

	TEST_F(ObjectTest, can_disconnect_a_slot_from_a_signal) {
		std::function<void()> member_func = std::bind(&MyJObject::on_test, obj);
		EXPECT_TRUE(obj->connect(obj->signal<void>("test()"), member_func, "test_handle"));
		EXPECT_TRUE(JObject::connect(obj, obj->signal<void>("test()"), member_func, "test_handle2"));

		ASSERT_TRUE(obj->disconnect(obj->signal<void>("test()"), "test_handle"));
		ASSERT_TRUE(JObject::disconnect(obj, obj->signal<void>("test()"), "test_handle2"));

		// can't delete non-existent handles
		ASSERT_FALSE(JObject::disconnect(obj, obj->signal<void>("test()"), "BADKEY"));

		// no double deletes
		ASSERT_FALSE(obj->disconnect(obj->signal<void>("test()"), "test_handle"));
		ASSERT_FALSE(JObject::disconnect(obj, obj->signal<void>("test()"), "test_handle2"));
	}

	TEST_F(ObjectTest, can_bind_to_an_object_manager) {
		ASSERT_NO_THROW(obj->set_owner(&manager));
	}

	TEST_F(ObjectTest, can_schedule_an_event) {
		EXPECT_NO_THROW(manager.set_dispatcher(&event_manager));
		EXPECT_NO_THROW(obj->set_owner(&manager));
		std::shared_ptr<Dispatchable> event(new MyEvent);
		ASSERT_NO_THROW(obj->schedule_event(event));
		ASSERT_EQ(1, event_manager.queue_size());
	}
} /* namespace core */
