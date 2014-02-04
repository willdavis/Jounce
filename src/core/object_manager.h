/*
 * object_manager.h
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <list>
#include "./interfaces/updater.h"

namespace core
{

	typedef std::shared_ptr<Updateable> sim_object_ptr;

	class ObjectManager : public Updater
	{
	public:
		ObjectManager();
		virtual ~ObjectManager();

		int get_collection_size();

		/* Updater interface */
		void register_object(sim_object_ptr);
		void release_object(sim_object_ptr);
		void update_all_objects(uint64_t*);
		/* end Updater interface */

	protected:
		std::list<sim_object_ptr> object_list;
	};

} /* namespace core */
#endif /* OBJECT_MANAGER_H_ */
