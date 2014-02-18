/*
 * slot.h
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#ifndef JSLOT_H_
#define JSLOT_H_

#include "meta_object.h"

namespace core
{

	template<typename SlotType = void*>
	class JSlot : public JMetaObject
	{
	public:
		JSlot(JObject* parent, std::string signature) : JMetaObject(parent, signature){}
	};

} /* namespace core */
#endif /* JSLOT_H_ */
