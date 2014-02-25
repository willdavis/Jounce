/*
 * signal.h
 *
 *  Created on: Feb 16, 2014
 *      Author: bill
 */

#ifndef JSIGNAL_H_
#define JSIGNAL_H_

#include <algorithm>
#include <functional>
#include <utility>
#include <map>
#include "meta_object.h"

namespace core
{

	template<class Return, typename... Args>
	class JSignal : public JMetaObject
	{
	public:
		JSignal(JObject* parent, const char* signature) : JMetaObject(parent, signature){  }

		void emit(Args... args)
		{
			// nasty hack but now this works with GCC 4.7
			// binds the Args... parameter pack to a lambda, which allows for perfect forwarding via std::forward
			// work around for current GCC bug 41933 (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=41933)
			// NOTE: expected fix in 4.9.0.  Revisit this bug once that versions out!
			auto emit_to_slot = std::bind([&](std::pair<const char*,std::function<Return(Args...)> > pair, Args... args) {
        pair.second(std::forward<Args>(args)...);	//call the slot with params(args)
			}, std::placeholders::_1, std::forward<Args>(args)...);

			// emit signal Args to all slots
			std::for_each(_slots.begin(), _slots.end(), emit_to_slot);
		}

		bool has_slot(const char* signature)
		{
			if(_slots.find(signature) != _slots.end()){ return true; }
			else { return false; }
		}

		bool connect(const char* signature, std::function<Return(Args...)> slot)
		{
			if(!has_slot(signature))
			{
				_slots.insert(std::make_pair(signature, slot));
				return true;
			}
			else
			{
				return false;
			}
		}

		bool disconnect(const char* signature)
		{
			if(has_slot(signature))
			{
				_slots.erase(signature);
				return true;
			}
			else
			{
				return false;
			}
		}

	protected:
		std::map<const char*, std::function<Return(Args...)> > _slots;
	};

} /* namespace core */
#endif /* JSIGNAL_H_ */
