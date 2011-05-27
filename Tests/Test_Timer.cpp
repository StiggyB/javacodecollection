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

}

Test_Timer::~Test_Timer() {

}

void Test_Timer::shutdown(){

}

void Test_Timer::execute(void* data){
	usleep(100000);
	Puck_FSM_1 test_fsm(serial, &puck_list);

	CallInterface<Puck_FSM, void, void*>* openswitch =
			FunctorMaker<Puck_FSM, void, void*>::makeFunctor(&test_fsm, &Puck_FSM::openswitch);

	CallInterface<Puck_FSM, void, void*>* closeswitch =
			FunctorMaker<Puck_FSM, void, void*>::makeFunctor(&test_fsm, &Puck_FSM::closeswitch);


	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(4);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(4);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);

	sleep(5);
}
