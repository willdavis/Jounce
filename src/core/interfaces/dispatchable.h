/*
 * dispatchable.h
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#ifndef DISPATCHABLE_H_
#define DISPATCHABLE_H_

#include <stdint.h>
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

	struct DispatchableComparator {
		bool operator() (Dispatchable* left, Dispatchable* right) {
			return left->priority() > right->priority();
		}
	};

} /* namespace core */
#endif /* DISPATCHABLE_H_ */
