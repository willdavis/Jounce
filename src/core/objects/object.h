/*
 * jObject.h
 *
 *  Created on: Feb 5, 2014
 *      Author: bill
 */

#ifndef JOBJECT_H_
#define JOBJECT_H_

#include <map>
#include "signal.h"
#include "../interfaces/updateable.h"

namespace core
{

	class JObject : public Updateable, public JMetaObject
	{
	public:
		JObject(JObject* parent, const char* signature);
		virtual ~JObject();

		bool has_signal(JMetaObject* signal);
		bool has_signal(std::string signature);
		bool has_signal(const char* signature);

		/* Updateable interface */
		void update(uint64_t*) = 0;
		/* End Updateable interface */

		template<class Return, typename... Args>
		JSignal<Return,Args...>* signal(const char* signature)
		{
			if(has_signal(signature)){ return static_cast<JSignal<Return,Args...>* >((*_signals.find(signature)).second); }
			return (JSignal<Return,Args...>*)0;
		}

		template<class Return, typename... Args>
		bool connect(JSignal<Return,Args...>* signal,
				std::function<Return(Args...)> slot,
				const char* handle)
		{
			if(signal == 0){ return false; }
			if(signal->connect(handle, slot)){ return true; }
			else { return false; }
		}

		template<class Return, typename... Args>
		static bool connect(JObject* sender,
				JSignal<Return,Args...>* signal,
				std::function<Return(Args...)> slot,
				const char* handle)
		{
			if(signal == 0){ return false; }
			if(!sender->has_signal(signal)){ return false; }
			else
			{
				if(sender->connect(signal, slot, handle)){ return true; }
				else { return false; }
			}
		}

		template<class Return, typename... Args>
		bool disconnect(JSignal<Return,Args...>* signal, const char* handle)
		{
			if(signal == 0){ return false; }
			if(!signal->has_slot(handle)){ return false; }
			else
			{
				if(signal->disconnect(handle)){ return true; }
				else { return false; }
			}
		}

		template<class Return, typename... Args>
		static bool disconnect(JObject* sender, JSignal<Return,Args...>* signal, const char* handle)
		{
			if(signal == 0){ return false; }
			if(!sender->has_signal(signal)){ return false; }
			else
			{
				if(signal->disconnect(handle)){ return true; }
				else { return false; }
			}
		}

	protected:
		std::map<const char*, JMetaObject*> _signals;

		bool register_signal(JMetaObject* signal);
		void delete_all_signals();
	};

} /* namespace core */
#endif /* JOBJECT_H_ */
