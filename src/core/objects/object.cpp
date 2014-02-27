/*
 * jObject.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#include "object.h"

namespace core
{

	JObject::JObject(JObject* parent, const char* signature) : JMetaObject(parent, signature)
	{

	}

	JObject::~JObject()
	{
		delete_all_signals();
	}

	bool JObject::has_signal(JMetaObject* signal)
	{
		return _signals.find(signal->signature()) != _signals.end();
	}

	bool JObject::has_signal(std::string signature)
	{
		return _signals.find(signature.c_str()) != _signals.end();
	}

	bool JObject::has_signal(const char* signature)
	{
		return _signals.find(signature) != _signals.end();
	}

	bool JObject::register_signal(JMetaObject* signal)
	{
		if(!has_signal(signal)){ _signals.insert(std::make_pair(signal->signature(), signal)); return true; }
		else { return false; }
	}

	bool JObject::remove_signal(JMetaObject* signal)
	{
		if(has_signal(signal)){ _signals.erase(signal->signature()); return true; }
		else { return false; }
	}

	void JObject::delete_all_signals()
	{
		std::for_each(_signals.begin(), _signals.end(), [this](std::pair<std::string,JMetaObject*> pair){
			delete pair.second;
		});
	}

	void JObject::set_owner(ObjectManager* manager)
	{
		parent = manager;
	}

	void JObject::schedule_event(std::shared_ptr<Dispatchable> event)
	{
		parent->dispatcher()->schedule(event);
	}

} /* namespace core */
