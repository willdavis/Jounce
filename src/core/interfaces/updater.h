/*
 * updater.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef UPDATER_H_
#define UPDATER_H_

#include <memory>
#include "updateable.h"

namespace core
{

	class Updateable;
	class Updater
	{
	public:
		Updater();
		virtual ~Updater();
		virtual void register_object(std::shared_ptr<Updateable> object) = 0;
		virtual void release_object(std::shared_ptr<Updateable> object) = 0;
		virtual void update_all_objects(uint64_t* elapsed_time) = 0;
	};

} /* namespace core */
#endif /* UPDATER_H_ */
