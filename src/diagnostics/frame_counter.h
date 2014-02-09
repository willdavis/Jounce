/*
 * frame_counter.h
 *
 *  Created on: Feb 8, 2014
 *      Author: bill
 */

#ifndef FRAME_COUNTER_H_
#define FRAME_COUNTER_H_

#include <stdint.h>
#include "./core/interfaces/observer.h"

using namespace core;

namespace Diagnostics
{

	class FrameCounter : public JObject
	{
	public:
		FrameCounter();
		virtual ~FrameCounter();

		void notify(Observable* signal, std::shared_ptr<Observer> slot);
		void update(uint64_t* dt);

		uint64_t get_average();

		uint64_t min_framerate;
		uint64_t max_framerate;

		uint64_t long_frame;
		uint64_t long_frame_count;

		uint64_t total_frames;
	};

} /* namespace Diagnostics */
#endif /* FRAME_COUNTER_H_ */
