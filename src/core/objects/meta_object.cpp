/*
 * meta_object.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: bill
 */

#include "meta_object.h"

namespace core
{

	JMetaObject::JMetaObject(JObject* parent, std::string signature)
	{
		_parent = parent;
		_signature = signature;
	}

	JMetaObject::~JMetaObject()
	{
		// TODO Auto-generated destructor stub
	}

	JObject* JMetaObject::parent()
	{
		return _parent;
	}

	std::string JMetaObject::signature()
	{
		return _signature;
	}

} /* namespace core */
