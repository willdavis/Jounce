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
		TestJObject(JObject* parent, const char* signature) : JObject(parent, signature){}
		void update(uint64_t* dt) {  }
	};

	class JMetaObjectTest : public ::testing::Test {
	public:
		JMetaObjectTest(){ obj = new TestJObject(0, "test"); }
		~JMetaObjectTest(){ delete obj; }
	protected:
		TestJObject* obj;
	};

	TEST_F(JMetaObjectTest, has_a_parent_JObject) {
		JMetaObject test(obj, "test()");
		ASSERT_EQ(obj, test.parent());
	}

	TEST_F(JMetaObjectTest, has_a_signature_string) {
		JMetaObject test(obj, "test()");
		ASSERT_EQ("test()", test.signature());
	}
} /* namespace core */
