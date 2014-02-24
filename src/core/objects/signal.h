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
#include <vector>
#include "meta_object.h"

namespace core
{

	template<class Return, typename... Args>
	class JSignal : public JMetaObject
	{
	public:
		JSignal(JObject* parent, std::string signature) : JMetaObject(parent, signature){  }

		void emit(Args... args)
		{
			// nasty hack but now this works with GCC 4.7
			// binds the Args... parameter pack to a lambda, which allows for perfect forwarding via std::forward
			// work around for current GCC bug 41933 (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=41933)
			// NOTE: expected fix in 4.9.0.  Revisit this bug once that versions out!
			auto emit_to_slot = std::bind([&](std::function<Return(Args...)> func, Args... args) {
        func(std::forward<Args>(args)...);
			}, std::placeholders::_1, std::forward<Args>(args)...);

			// emit signal Args to all slots
			std::for_each(_slots.begin(), _slots.end(), emit_to_slot);
		}

		bool connect(std::function<Return(Args...)> slot)
		{
			try { _slots.push_back(slot); }
			catch(...) { return false; }
			return true;
		}

	protected:
		std::vector<std::function<Return(Args...)> > _slots;
	};

} /* namespace core */
#endif /* JSIGNAL_H_ */
