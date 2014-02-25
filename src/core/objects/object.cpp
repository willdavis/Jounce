/*
 * jObject.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#include "object.h"

namespace core
{

	JObject::JObject()
	{
		// TODO Auto-generated constructor stub

	}

	JObject::~JObject()
	{
		// TODO Auto-generated destructor stub
	}

	bool JObject::has_signal(JMetaObject* signal)
	{
		return _signals.find(signal->signature()) != _signals.end();
	}

	bool JObject::has_signal(std::string signature)
	{
		return _signals.find(signature) != _signals.end();
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

	JMetaObject* JObject::signal(std::string signature)
	{
		if(has_signal(signature)){ return (*_signals.find(signature)).second; }
		return (JMetaObject*)0;
	}

	bool JObject::key_exists(std::string key)
	{
		if(observers.find(key) != observers.end()){ return true; }
		else { return false; }
	}

	void JObject::set_owner(ObjectManager* manager)
	{
		parent = manager;
	}

	void JObject::schedule_event(std::shared_ptr<Dispatchable> event)
	{
		parent->dispatcher()->schedule(event);
	}

	// call notify() on the Observer with the given key
	void JObject::notify_observer(std::string key)
	{
		if(!key_exists(key)){ throw "key not present"; }
		observers[key]->notify(this, observers[key]);
	}

	// release an observer by it's key
	void JObject::release_observer(std::string key)
	{
		if(!key_exists(key)){ throw "key not present"; }
		observers.erase(key);
	}

	// register an observer into the observers collection
	void JObject::register_observer(std::pair<std::string, std::shared_ptr<Observer> > pair)
	{
		if(key_exists(pair.first)){ throw "key already present"; }
		observers.insert(pair);
	}

	// return the total number of observers registered to this object
	unsigned int JObject::total_observers()
	{
		return observers.size();
	}

} /* namespace core */
