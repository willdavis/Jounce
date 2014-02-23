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
#include <vector>
#include "meta_object.h"

namespace core
{

	template<class Return, class... Args>
	class JSignal : public JMetaObject
	{
	public:
		JSignal(JObject* parent, std::string signature) : JMetaObject(parent, signature){  }

		void emit(Args...)
		{
			// notify connected slots
			// currently all slots are directly called.  Async calls will come shortly ^_^
			// ye be warned!
		}

		bool connect(std::function<Return(Args...)> slot)
		{
			try { _connections.push_back(slot); }
			catch(...) { return false; }
			return true;
		}

	protected:
		std::vector<std::function<Return(Args...)> > _connections;
	};

} /* namespace core */
#endif /* JSIGNAL_H_ */
