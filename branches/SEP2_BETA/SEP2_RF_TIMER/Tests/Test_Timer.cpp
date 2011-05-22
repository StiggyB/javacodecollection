/**
 * Test_Timer
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 5: OS-Timer
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 *this class will test the functions from Timer.h
 *
 *
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
	usleep(100000);
	Puck_FSM_1 test_fsm;
	CallInterface<Puck_FSM, void, void*>* test_func_1 =
			FunctorMaker<Puck_FSM, void, void*>::makeFunctor(&test_fsm, &Puck_FSM::openswitch);

	HALCore *test_halcore = HALCore::getInstance();;
		CallInterface<HALCore, void, void*>* test_func_2 =
				FunctorMaker<HALCore, void, void*>::makeFunctor(test_halcore, &HALCore::closeSwitch);

	//timer->testTimer();
	timer->addTimerFunction(test_func_1,3000);


	/*timer->addTimerFunction(test_func_1,1000);
	struct timeval time_val;
	struct timezone time_zone;

	gettimeofday( &time_val, &time_zone);
	std::cout << "Time_val::" << time_val.tv_usec << std::endl;*/

	timer->addTimerFunction(test_func_1,1000);
	timer->addTimerFunction(test_func_1,999);
	timer->addTimerFunction(test_func_1,998);
	timer->addTimerFunction(test_func_1,1600);


	sleep(11);
	//timer->stop();
}
