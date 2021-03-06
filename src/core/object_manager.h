/*
 * object_manager.h
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <list>
#include "./objects/object.h"
#include "./interfaces/updater.h"

namespace core
{

	typedef std::shared_ptr<Updateable> object_ptr;

	class ObjectManager : public JObject, public Updater
	{
	public:
		ObjectManager(JObject* parent, const char* signature);
		virtual ~ObjectManager();

		/* Updater interface */
		void register_object(object_ptr);
		void release_object(object_ptr);
		void update_all_objects(uint64_t*);
		/* end Updater interface */
		int get_collection_size();

	protected:
		std::list<object_ptr> object_list;
	};

} /* namespace core */
#endif /* OBJECT_MANAGER_H_ */
