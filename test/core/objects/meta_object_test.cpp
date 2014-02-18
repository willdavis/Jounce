/*
 * meta_object_test.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/objects/meta_object.h"
#include "../../../src/core/objects/object.h"

namespace core
{
	class TestJObject : public JObject {
	public:
		void update(uint64_t* dt) {  }
		void notify(Observable* sender, std::shared_ptr<Observer> caller){  }
	};

	class JMetaObjectTest : public ::testing::Test {
	protected:
		TestJObject obj;
	};

	TEST_F(JMetaObjectTest, has_a_parent_JObject) {
		JMetaObject test(&obj, "test()");
		ASSERT_EQ(&obj, test.parent());
	}

	TEST_F(JMetaObjectTest, has_a_signature_string) {
		JMetaObject test(&obj, "test()");
		ASSERT_EQ("test()", test.signature());
	}
} /* namespace core */
