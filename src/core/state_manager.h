/*
 * state_manager.h
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

namespace core
{

	enum SimulationState {
		OFF,
		RUNNING,
		EXITING
	};

	class StateManager
	{
	public:
		StateManager();
		virtual ~StateManager();

		SimulationState get_current_simulation_state();
		void set_current_simulation_state(SimulationState);

	protected:
		SimulationState current_simulation_state;
	};

} /* namespace core */
#endif /* STATE_MANAGER_H_ */
