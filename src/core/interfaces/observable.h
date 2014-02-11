/*
 * observable.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <string>
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
		virtual void notify_observer(std::string key) = 0;
		virtual void release_observer(std::string key) = 0;
		virtual unsigned int register_observer(std::pair<std::string, std::shared_ptr<Observer> > pair) = 0;
		virtual unsigned int total_observers() = 0;
	};

	typedef std::shared_ptr<Observable> observable_ptr;

} /* namespace core */
#endif /* OBSERVABLE_H_ */
