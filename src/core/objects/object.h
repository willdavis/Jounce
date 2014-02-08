/*
 * jObject.h
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#ifndef JOBJECT_H_
#define JOBJECT_H_

#include <vector>
#include "../interfaces/observable.h"
#include "../interfaces/updateable.h"

namespace core
{

	class JObject : public Updateable, public Observable, public Observer
	{
	public:
		JObject();
		virtual ~JObject();

		/* Observable interface */
		void notify_observer(unsigned int id);
		void release_observer(unsigned int id);
		unsigned int register_observer(observer_ptr observer);
		unsigned int total_observers();
		/* End Observable interface */

		/* Observer interface */
		void notify(Observable* signal, observer_ptr slot) = 0;
		/* End Observer interface */

		/* Updateable interface */
		void update(uint64_t*) = 0;
		/* End Updateable interface */

	protected:
		std::vector<observer_ptr> observers;
	};

} /* namespace core */
#endif /* JOBJECT_H_ */
