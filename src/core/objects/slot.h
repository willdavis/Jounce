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

	template<typename SlotType = void*>
	class JSlot
	{
	public:
		JSlot(JObject* parent, std::string signature)
		{
			_parent = parent;
			_signature = signature;
		}

		JObject* parent() { return _parent; }
		std::string signature() { return _signature; }

	protected:
		JObject* _parent;
		std::string _signature;
	};

} /* namespace core */
#endif /* JSLOT_H_ */
