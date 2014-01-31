/*
 * object_manager.h
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <list>
#include "sim_object.h"

namespace core
{

	class ObjectManager
	{
	public:
		ObjectManager();
		virtual ~ObjectManager();

		int get_collection_size();
		void register_object(sim_object_ptr);
		void update_all_registered_objects(uint64_t);
		void release_registered_object(sim_object_ptr);

	protected:
		std::list<sim_object_ptr> object_list;
	};

} /* namespace core */
#endif /* OBJECT_MANAGER_H_ */
