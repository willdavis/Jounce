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

	bool JObject::key_exists(std::string key)
	{
		std::unordered_map<std::string,observer_ptr>::const_iterator item = observers.find(key);
		if(item == observers.end()){ return false; }
		else { return true; }
	}

	void JObject::set_owner(ObjectManager* manager)
	{
		parent = manager;
	}

	ObjectManager* JObject::owner()
	{
		return parent;
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
