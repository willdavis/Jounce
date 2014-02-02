/*
 * dispatcher.h
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "dispatchable.h"

namespace core
{

	class Dispatchable;
	class Dispatcher
	{
	public:
		Dispatcher();
		virtual ~Dispatcher();
		virtual unsigned int queue_size() = 0;
		virtual void schedule(Dispatchable*) = 0;
		virtual void dispatch_the_queue() = 0;
		virtual void close() = 0;
	};

} /* namespace core */
#endif /* DISPATCHER_H_ */
