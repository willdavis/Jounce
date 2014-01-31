/*
 * sim_object.h
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#ifndef SIM_OBJECT_H_
#define SIM_OBJECT_H_

#include <memory>
#include <stdint.h>

namespace core
{

	class SimObject
	{
	public:
		SimObject();
		virtual ~SimObject();
		virtual void update(uint64_t) = 0;	// update the simulation object with elapsed time (dt)
	};

	typedef std::shared_ptr<SimObject> sim_object_ptr;

} /* namespace core */
#endif /* SIM_OBJECT_H_ */
