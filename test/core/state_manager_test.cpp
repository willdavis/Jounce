/*
 * state_manager_test.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/state_manager.h"

namespace core
{
	class StateManagerTest : public ::testing::Test {
	protected:
		StateManager state_manager;
	};

	TEST_F(StateManagerTest, can_get_current_simulation_state) {
		ASSERT_EQ(SimulationState::OFF, state_manager.get_current_simulation_state());
	}

	TEST_F(StateManagerTest, can_set_current_simulation_state) {
		state_manager.set_current_simulation_state(SimulationState::RUNNING);
		ASSERT_EQ(SimulationState::RUNNING, state_manager.get_current_simulation_state());
	}

	TEST_F(StateManagerTest, default_state_is_off) {
		ASSERT_EQ(SimulationState::OFF, state_manager.get_current_simulation_state());
	}
} /* namespace core */
