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

	// call notify() on the Observer with the given id (also the index in the vector)
	void JObject::notify_observer(unsigned int id)
	{
		if(id+1 > total_observers()){ throw "index out of range"; }
		observers[id]->notify(this);
	}

	// release an observer by it's id (also it's index in the vector)
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

	// return the total number of observers registered to this object
	unsigned int JObject::total_observers()
	{
		return observers.size();
	}

} /* namespace core */
