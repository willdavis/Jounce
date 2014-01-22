/*
 * exit_event_test.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../../src/core/events/exit_event.h"

namespace core
{
  class ExitEventTest : public ::testing::Test {
  protected:
    ExitEvent exit;
  };

} /* namespace core */
