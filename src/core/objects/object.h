/*
 * jObject.h
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#ifndef JOBJECT_H_
#define JOBJECT_H_

#include <map>
#include "../interfaces/observer.h"
#include "../interfaces/observable.h"
#include "../interfaces/updateable.h"
#include "../interfaces/dispatchable.h"
#include "../object_manager.h"

namespace core
{

	class ObjectManager;
	class JObject : public Updateable, public Observable, public Observer
	{
	public:
		JObject();
		virtual ~JObject();

		void schedule_event(std::shared_ptr<Dispatchable> event);
		void set_owner(ObjectManager*);

		bool key_exists(std::string key);
		/* Observable interface */
		void notify_observer(std::string key);
		void release_observer(std::string key);
		void register_observer(std::pair<std::string, std::shared_ptr<Observer> > pair);
		unsigned int total_observers();
		/* End Observable interface */

		/* Observer interface */
		void notify(Observable* signal, observer_ptr slot) = 0;
		/* End Observer interface */

		/* Updateable interface */
		void update(uint64_t*) = 0;
		/* End Updateable interface */

	protected:
		ObjectManager* parent;
		std::map<std::string, observer_ptr> observers;
	};

} /* namespace core */
#endif /* JOBJECT_H_ */
