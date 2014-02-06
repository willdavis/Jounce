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

	void JObject::notify_observer(unsigned int id)
	{
		if(id+1 > total_observers()){ throw "index out of range"; }
		observers[id]->notify(this);
	}

	void JObject::release_observer(unsigned int id)
	{
		if(id+1 > total_observers()){ throw "index out of range"; }
		observers.erase(observers.begin()+id);
	}

	// register an observer into the observers collection
	// return the index of the registered observer
	unsigned int JObject::register_observer(observer_ptr observer)
	{
		observers.push_back(observer);
		return observers.size()-1;
	}

	unsigned int JObject::total_observers()
	{
		return observers.size();
	}

} /* namespace core */
