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
		void update(uint64_t* dt) { /* nothing */ }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){ /* not used */ }
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

} /* namespace core */
