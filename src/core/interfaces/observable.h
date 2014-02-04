/*
 * observable.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <memory>
#include "observer.h"

namespace core
{

	class Observer;
	class Observable
	{
	public:
		Observable();
		virtual ~Observable();
		virtual void notify_observer(unsigned int id) = 0;
		virtual void release_observer(unsigned int id) = 0;
		virtual unsigned int register_observer(std::shared_ptr<Observer> observer) = 0;
		virtual unsigned int total_observers() = 0;
	};

} /* namespace core */
#endif /* OBSERVABLE_H_ */
