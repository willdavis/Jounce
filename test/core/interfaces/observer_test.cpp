/*
 * observer_test.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/interfaces/observer.h"

namespace core
{
	class MyObservable : public Observable {
	public:
		void notify_observer(unsigned int id) {  }
		void release_observer(unsigned int id) {  }
		unsigned int register_observer(std::shared_ptr<Observer> observer) { return 0; }
		unsigned int total_observers() { return 0; }
	};

	class MyObserver : public Observer {
	public:
		void notify(Observable* object) {  }
	};

	class ObserverTest : public ::testing::Test {
	protected:
		MyObserver test;
	};

	TEST_F(ObserverTest, must_implement_observer_interface) {
		MyObservable obj;
		ASSERT_NO_THROW(test.notify(&obj));
	}

} /* namespace core */
