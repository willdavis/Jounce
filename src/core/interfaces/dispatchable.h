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
		virtual void dispatch(Dispatcher* dispatcher) = 0;
		virtual unsigned int priority() = 0;
		virtual uint64_t timestamp() = 0;
	};

	typedef std::shared_ptr<Dispatchable> dispatchable_ptr;

	struct DispatchableComparator {
		bool operator() (dispatchable_ptr left, dispatchable_ptr right) {
			return left->priority() > right->priority();
		}
	};

} /* namespace core */
#endif /* DISPATCHABLE_H_ */
