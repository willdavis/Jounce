/*
 * signal_test.cpp
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/objects/signal.h"
#include "../../../src/core/objects/object.h"

namespace core
{
	class MyJObject : public JObject {
	public:
		void update(uint64_t* dt) {  }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){  }
		void test_func(JObject* obj){ some_number += 10; }
		int some_number;
	};

	class JSignalTest : public ::testing::Test {
	protected:
		MyJObject test_obj;
	};

	TEST_F(JSignalTest, must_have_a_parent_JObject) {
		JSignal<void> void_signal(&test_obj, "nothing()");
		JSignal<int, int, double> val_signal(&test_obj, "some_func(int,double)");
		JSignal<void, JObject*> ptr_signal(&test_obj, "another_func(JObject*)");

		ASSERT_EQ(&test_obj, void_signal.parent());
		ASSERT_EQ(&test_obj, val_signal.parent());
		ASSERT_EQ(&test_obj, ptr_signal.parent());
	}

	TEST_F(JSignalTest, must_have_a_signature_string) {
		JSignal<void> void_signal(&test_obj, "nothing()");
		JSignal<int, int, double> val_signal(&test_obj, "some_func(int,double)");
		JSignal<void, JObject*> ptr_signal(&test_obj, "another_func(JObject*)");

		ASSERT_EQ("nothing()", void_signal.signature());
		ASSERT_EQ("some_func(int,double)", val_signal.signature());
		ASSERT_EQ("another_func(JObject*)", ptr_signal.signature());
	}

	TEST_F(JSignalTest, can_be_emitted_with_params) {
		JSignal<void> void_signal(&test_obj, "nothing()");
		JSignal<int, int, double> val_signal(&test_obj, "some_func(int,double)");
		JSignal<void, JObject*> ptr_signal(&test_obj, "another_func(JObject*)");

		ASSERT_NO_THROW(void_signal.emit());
		ASSERT_NO_THROW(val_signal.emit(10, 1.5));
		ASSERT_NO_THROW(ptr_signal.emit(&test_obj));
	}

	TEST_F(JSignalTest, can_connect_a_slot) {
		JSignal<void> void_signal(&test_obj, "nothing()");
		JSignal<int, int, double> val_signal(&test_obj, "some_func(int,double)");
		JSignal<void, JObject*> ptr_signal(&test_obj, "another_func(JObject*)");

		auto void_func = [](){};
		auto val_func = [](int i, double d){ return i; };
		auto ptr_func = std::bind(&MyJObject::test_func, &test_obj, std::placeholders::_1);

		ASSERT_TRUE(void_signal.connect(void_func));
		ASSERT_TRUE(val_signal.connect(val_func));
		ASSERT_TRUE(ptr_signal.connect(ptr_func));
	}

	TEST_F(JSignalTest, notifies_connected_slots_when_emitted) {
		JSignal<void> void_signal(&test_obj, "nothing()");
		JSignal<int, int, double> val_signal(&test_obj, "some_func(int,double)");
		JSignal<void, JObject*> ptr_signal(&test_obj, "another_func(JObject*)");

		test_obj.some_number = 0;
		int test_number = 0;
		int another_number = 0;

		auto void_func = [&another_number](){ another_number += 10; };
		auto val_func = [&test_number](int i, double d){ test_number = i; return i; };
		auto ptr_func = std::bind(&MyJObject::test_func, &test_obj, std::placeholders::_1);

		EXPECT_TRUE(void_signal.connect(void_func));
		EXPECT_TRUE(val_signal.connect(val_func));
		EXPECT_TRUE(ptr_signal.connect(ptr_func));

		EXPECT_NO_THROW(void_signal.emit());
		EXPECT_NO_THROW(val_signal.emit(10, 1.5));
		EXPECT_NO_THROW(ptr_signal.emit(&test_obj));

		ASSERT_EQ(10, another_number);	//check that the void_func was called
		ASSERT_EQ(10, test_number);	//check that val_func was called
		ASSERT_EQ(10, test_obj.some_number);	//check that ptr_fuc was called
	}

} /* namespace core */
