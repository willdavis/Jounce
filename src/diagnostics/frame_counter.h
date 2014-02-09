/*
 * frame_counter.h
 *
 *  Created on: Feb 8, 2014
 *      Author: bill
 */

#ifndef FRAME_COUNTER_H_
#define FRAME_COUNTER_H_

#include <stdint.h>
#include "../core/objects/object.h"

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

		double average_frame();
		double long_frame_ratio();
		double short_frame_ratio();

		uint64_t shortest_frame();
		uint64_t longest_frame();

		uint64_t total_frames();
		uint64_t total_time();

		uint64_t short_frame();
		void set_short_frame(uint64_t* nanoseconds);

		uint64_t long_frame();
		void set_long_frame(uint64_t* nanoseconds);

	protected:
		uint64_t _shortest_frame;
		uint64_t _longest_frame;

		uint64_t _short_frame;
		uint64_t _short_frame_count;

		uint64_t _long_frame;
		uint64_t _long_frame_count;

		uint64_t _total_frames;
		uint64_t _total_time;
	};

} /* namespace Diagnostics */
#endif /* FRAME_COUNTER_H_ */
