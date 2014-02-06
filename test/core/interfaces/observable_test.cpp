/*
 * observable_test.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/observable.h"

namespace core
{
	class MyObservable : public Observable {
	public:
		void notify_observer(unsigned int id) { index = 10; }
		void release_observer(unsigned int id) { index = 0; }
		unsigned int register_observer(std::shared_ptr<Observer> observer) { return index++; }
		unsigned int total_observers() { return index; }
	protected:
		unsigned int index = 0;
	};

	class MyObserver : public Observer {
	public:
		void notify(Observable* object) {  }
	};

	class ObservableTest : public ::testing::Test {
	protected:
		MyObservable test;
	};

	TEST_F(ObservableTest, must_implement_observable_interface) {
		std::shared_ptr<Observer> observer(new MyObserver);
		unsigned int id = test.register_observer(observer);
		ASSERT_EQ(1, test.total_observers());
		test.notify_observer(id);
		ASSERT_EQ(10, test.total_observers());
		test.release_observer(id);
		ASSERT_EQ(0, test.total_observers());
	}

} /* namespace core */
