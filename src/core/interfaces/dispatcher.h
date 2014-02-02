/*
 * dispatcher.h
 *
 *  Created on: Feb 1, 2014
 *      Author: bill
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

namespace core
{

	class Dispatcher
	{
	public:
		Dispatcher();
		virtual ~Dispatcher();
		virtual void dispatch_top_event() = 0;
	};

} /* namespace core */
#endif /* DISPATCHER_H_ */
