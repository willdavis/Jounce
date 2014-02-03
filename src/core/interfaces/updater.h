/*
 * updater.h
 *
 *  Created on: Feb 3, 2014
 *      Author: bill
 */

#ifndef UPDATER_H_
#define UPDATER_H_

#include "updateable.h"

namespace core
{

	class Updateable;
	class Updater
	{
	public:
		Updater();
		virtual ~Updater();
	};

} /* namespace core */
#endif /* UPDATER_H_ */
