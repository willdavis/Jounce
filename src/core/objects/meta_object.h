/*
 * meta_object.h
 *
 *  Created on: Feb 17, 2014
 *      Author: bill
 */

#ifndef JMETA_OBJECT_H_
#define JMETA_OBJECT_H_

#include <string>

namespace core
{
	class JObject;
	class JMetaObject
	{
	public:
		JMetaObject(JObject* parent, std::string signature);
		virtual ~JMetaObject();

		JObject* parent();
		std::string signature();

	protected:
		JObject* _parent;
		std::string _signature;
	};

} /* namespace core */
#endif /* JMETA_OBJECT_H_ */
