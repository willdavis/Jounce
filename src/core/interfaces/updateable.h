/*
 * updateable.h
 *
 *  Created on: Feb 2, 2014
 *      Author: bill
 */

#ifndef UPDATEABLE_H_
#define UPDATEABLE_H_

#include <stdint.h>

namespace core
{

	class Updateable
	{
	public:
		Updateable();
		virtual ~Updateable();
		virtual void update(uint64_t*) = 0;
	};

} /* namespace core */
#endif /* UPDATEABLE_H_ */
