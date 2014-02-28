/*
 * object_manager.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "object_manager.h"

namespace core
{

	ObjectManager::ObjectManager()
	{
		// TODO Auto-generated constructor stub

	}

	ObjectManager::~ObjectManager()
	{
		// TODO Auto-generated destructor stub
	}

	int ObjectManager::get_collection_size()
	{
		return object_list.size();
	}

	void ObjectManager::register_object(object_ptr obj)
	{
		object_list.push_back(obj);
	}

	void ObjectManager::update_all_objects(uint64_t* dt)
	{
		for(std::list<object_ptr>::iterator i=object_list.begin(); i != object_list.end(); i++)
			(*i)->update(dt);
	}

	void ObjectManager::release_object(object_ptr obj)
	{
		object_list.remove(obj);
	}

	EventManager* ObjectManager::dispatcher()
	{
		return linked_dispatcher;
	}

	void ObjectManager::set_dispatcher(EventManager* dispatcher)
	{
		linked_dispatcher = dispatcher;
	}


} /* namespace core */
