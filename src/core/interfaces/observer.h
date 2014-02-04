/*
 * observer.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "observable.h"

namespace core
{

	class Observable;
	class Observer
	{
	public:
		Observer();
		virtual ~Observer();
		virtual void notify(std::shared_ptr<Observable>) = 0;
	};

} /* namespace core */
#endif /* OBSERVER_H_ */
