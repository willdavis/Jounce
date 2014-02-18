/*
 * signal.h
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#ifndef JSIGNAL_H_
#define JSIGNAL_H_

#include "meta_object.h"

namespace core
{

	template<typename SignalType = void*>
	class JSignal : public JMetaObject
	{
	public:
		JSignal(JObject* parent, std::string signature) : JMetaObject(parent, signature){ }
		SignalType emit(SignalType value = (void*)0) { return value; }
	};

} /* namespace core */
#endif /* JSIGNAL_H_ */
