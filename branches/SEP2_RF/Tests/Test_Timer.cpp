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
	sleep(1);
	HALCore* h;
	h = HALCore::getInstance();
	timer = Timer::getInstance();

	CallInterface<CallBackThrower, void>* openswitch = (CallInterface<CallBackThrower, void>*)
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::openSwitch);

	CallInterface<CallBackThrower, void>* closeswitch = (CallInterface<CallBackThrower, void>*)
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::closeSwitch);


	timer->addTimerFunction(openswitch, 2000);
	int id = timer->addTimerFunction(closeswitch, 3500);

	timer->stopTimerbyId(id);
	sleep(1);

	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)openswitch, 2000);
	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)closeswitch, 4000);


	sleep(5);
	/*timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(5);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	*/
	sleep(5);
}
