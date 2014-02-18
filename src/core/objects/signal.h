/*
 * signal.h
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#ifndef JSIGNAL_H_
#define JSIGNAL_H_

#include <map>
#include "object.h"
#include "slot.h"

namespace core
{

	template<typename SignalType = void*>
	class JSignal
	{
	public:
		JSignal(JObject* parent, std::string signature)
		{
			_parent = parent;
			_signature = signature;
		}

		JObject* parent() { return _parent; }
		std::string signature(){ return _signature; }
		SignalType emit(SignalType value = (void*)0) { return value; }

	protected:
		std::string _signature;
		JObject* _parent;
	};

} /* namespace core */
#endif /* JSIGNAL_H_ */
