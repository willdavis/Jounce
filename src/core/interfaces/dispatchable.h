/*
 * dispatchable.h
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#ifndef DISPATCHABLE_H_
#define DISPATCHABLE_H_

#include <stdint.h>
#include <memory>
#include "dispatcher.h"

namespace core
{

	class Dispatcher;
	class Dispatchable
	{
	public:
		Dispatchable();
		virtual ~Dispatchable();
		virtual void dispatch(std::shared_ptr<Dispatcher> dispatcher) = 0;
		virtual unsigned int priority() = 0;
		virtual uint64_t timestamp() = 0;
	};

	struct DispatchableComparator {
		bool operator() (std::shared_ptr<Dispatchable> left, std::shared_ptr<Dispatchable> right) {
			return left->priority() > right->priority();
		}
	};

} /* namespace core */
#endif /* DISPATCHABLE_H_ */
