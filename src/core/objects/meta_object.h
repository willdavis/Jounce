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
		JMetaObject(JObject* parent, const char* signature);
		virtual ~JMetaObject();

		JObject* parent();
		const char* signature();

	protected:
		JObject* _parent;
		const char* _signature;
	};

} /* namespace core */
#endif /* JMETA_OBJECT_H_ */
