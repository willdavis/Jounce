/*
 * slot_test.cpp
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/objects/slot.h"
#include "../../../src/core/objects/object.h"

namespace core
{
	class MyJObject : public JObject {
	public:
		void update(uint64_t* dt) { /* nothing */ }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){ /* not used */ }
	};

	class JSlotTest : public ::testing::Test {
	protected:
		MyJObject test_obj;
	};

	TEST_F(JSlotTest, has_a_parent_JObject) {
		JSlot<> void_test(&test_obj, "test()");
		JSlot<double> double_test(&test_obj, "test(double)");

		ASSERT_EQ(&test_obj, void_test.parent());
		ASSERT_EQ(&test_obj, double_test.parent());
	}

	TEST_F(JSlotTest, has_a_signature_string) {
		JSlot<> void_test(&test_obj, "test()");
		JSlot<double> double_test(&test_obj, "test(double)");

		ASSERT_EQ("test()", void_test.signature());
		ASSERT_EQ("test(double)", double_test.signature());
	}
} /* namespace core */
