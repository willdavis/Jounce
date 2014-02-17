/*
 * slot.h
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#ifndef JSLOT_H_
#define JSLOT_H_

#include "object.h"

namespace core
{

	class JSlot
	{
	public:
		JSlot();
		virtual ~JSlot();

		JObject* parent();	//returns the parent JObject of this slot
		std::string signature();	//returns the signature of this slot in string form
	};

} /* namespace core */
#endif /* JSLOT_H_ */
