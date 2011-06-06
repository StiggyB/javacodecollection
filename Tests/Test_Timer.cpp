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
	sleep(4);
	HALCore* h;
	h = HALCore::getInstance();

	CallInterface<HALCore, void>* openswitch =
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::openSwitch);

	CallInterface<HALCore, void>* closeswitch =
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::closeSwitch);


	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(5);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(5);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);

	sleep(5);
}
