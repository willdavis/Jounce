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
		void notify_observer(std::string key) { index = 10; }
		void release_observer(std::string key) { index = 0; }
		unsigned int register_observer(std::pair<std::string, std::shared_ptr<Observer> > observer) { return index++; }
		unsigned int total_observers() { return index; }
	protected:
		unsigned int index = 0;
	};

	class MyObserver : public Observer {
	public:
		void notify(Observable* signal, std::shared_ptr<Observer> slot) {  }
	};

	class ObservableTest : public ::testing::Test {
	protected:
		MyObservable test;
	};

	TEST_F(ObservableTest, must_implement_observable_interface) {
		std::shared_ptr<Observer> observer(new MyObserver);
		std::pair<std::string, observer_ptr> pair("test", observer);
		test.register_observer(pair);
		ASSERT_EQ(1, test.total_observers());
		test.notify_observer("test");
		ASSERT_EQ(10, test.total_observers());
		test.release_observer("test");
		ASSERT_EQ(0, test.total_observers());
	}

} /* namespace core */
