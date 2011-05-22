/*
 * Test_Timer.cpp
 *
 *  Created on: 20.05.2011
 *      Author: User
 */

#include "Test_Timer.h"

Test_Timer::Test_Timer() {
	// TODO Auto-generated constructor stub

}

Test_Timer::~Test_Timer() {
	// TODO Auto-generated destructor stub
}

void Test_Timer::shutdown(){

}

void Test_Timer::execute(void*){
	Puck_FSM_1 test_fsm;
	CallInterface<Puck_FSM, void, void*>* test_func_1 =
			FunctorMaker<Puck_FSM, void, void*>::makeFunctor(&test_fsm, &Puck_FSM::ls_b1);

	HALCore *test_halcore = HALCore::getInstance();;
		CallInterface<HALCore, void, void*>* test_func_2 =
				FunctorMaker<HALCore, void, void*>::makeFunctor(test_halcore, &HALCore::openSwitch);

	timer->addTimerFunction(test_func_2,7000);

	/*struct timeval time_val;
	struct timezone time_zone;

	gettimeofday( &time_val, &time_zone);
	std::cout << "Time_val::" << time_val.tv_usec << std::endl;

	timer->addTimerFunction(test_func_1,1000);
	timer->addTimerFunction(test_func_1,999);
	timer->addTimerFunction(test_func_1,998);
	timer->addTimerFunction(test_func_1,1600);*/

	while(!isStopped()){}
}
