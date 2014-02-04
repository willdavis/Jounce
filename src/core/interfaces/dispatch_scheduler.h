/*
 * dispatch_scheduler.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef DISPATCH_SCHEDULER_H_
#define DISPATCH_SCHEDULER_H_

#include "dispatchable.h"

namespace core
{

	class Dispatchable;
	class DispatchScheduler
	{
	public:
		DispatchScheduler();
		virtual ~DispatchScheduler();
		virtual unsigned int queue_size() = 0;
		virtual void schedule(std::shared_ptr<Dispatchable> event) = 0;
	};

} /* namespace core */
#endif /* DISPATCH_SCHEDULER_H_ */
