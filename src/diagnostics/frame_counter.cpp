/*
 * frame_counter.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: bill
 */

#include "frame_counter.h"

namespace Diagnostics
{

	FrameCounter::FrameCounter()
	{
		_total_time = 0;
		_total_frames = 0;

		_shortest_frame = 1000000000;
		_longest_frame = 0;

		_short_frame = 0;
		_short_frame_count = 0;

		_long_frame = 0;
		_long_frame_count = 0;
	}

	FrameCounter::~FrameCounter()
	{
		// TODO Auto-generated destructor stub
	}

	void FrameCounter::notify(Observable* signal, std::shared_ptr<Observer> slot)
	{
	}

	void FrameCounter::update(uint64_t* dt)
	{
		_total_frames++;
		_total_time += *dt;
		if(*dt < _shortest_frame){ _shortest_frame = *dt; }
		if(*dt > _longest_frame){ _longest_frame = *dt; }

		if(*dt < _short_frame){ _short_frame_count++; }
		if(*dt > _long_frame){ _long_frame_count++; }
	}

	double FrameCounter::average_frame()
	{
		if(_total_frames == 0){ return 0; }
		return (double)_total_time / (double)_total_frames;
	}

	double FrameCounter::long_frame_ratio()
	{
		if(_total_frames == 0){ return 0; }
		return (double)_long_frame_count / (double)_total_frames * 100;
	}

	double FrameCounter::short_frame_ratio()
	{
		if(_total_frames == 0){ return 0; }
		return (double)_short_frame_count / (double)_total_frames * 100;
	}

	uint64_t FrameCounter::shortest_frame()
	{
		return _shortest_frame;
	}

	uint64_t FrameCounter::longest_frame()
	{
		return _longest_frame;
	}

	uint64_t FrameCounter::total_frames()
	{
		return _total_frames;
	}

	uint64_t FrameCounter::total_time()
	{
		return _total_time;
	}

	uint64_t FrameCounter::short_frame()
	{
		return _short_frame;
	}

	void FrameCounter::set_short_frame(uint64_t* nanoseconds)
	{
		_short_frame = *nanoseconds;
	}

	uint64_t FrameCounter::long_frame()
	{
		return _long_frame;
	}

	void FrameCounter::set_long_frame(uint64_t* nanoseconds)
	{
		_long_frame = *nanoseconds;
	}
}
 /* namespace Diagnostics */
