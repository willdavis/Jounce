/*
 * state_manager.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "state_manager.h"

namespace core
{

	StateManager::StateManager()
	{
		current_simulation_state = SimulationState::OFF;
	}

	StateManager::~StateManager()
	{
		// TODO Auto-generated destructor stub
	}

	SimulationState StateManager::get_current_simulation_state()
	{
		return current_simulation_state;
	}

	void StateManager::set_current_simulation_state(SimulationState simulation_state)
	{
		current_simulation_state = simulation_state;
	}

} /* namespace core */
