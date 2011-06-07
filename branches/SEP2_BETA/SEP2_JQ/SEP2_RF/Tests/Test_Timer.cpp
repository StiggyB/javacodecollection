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

	struct timeval act_time;
	long millsec;
	gettimeofday(&act_time, NULL);
	millsec = ((act_time.tv_sec) * 1000 + act_time.tv_usec/1000.0) + 0.5;

	std::cout << "Test_Timer: millsec=" << millsec << std::endl;


	CallInterface<HALCore, void>* openswitch =
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::openSwitch);

	CallInterface<HALCore, void>* closeswitch =
			FunctorMaker<HALCore, void>::makeFunctor(h, &HALCore::closeSwitch);


	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(1);
	timer->stopAllTimer();

	sleep(5);
	/*timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	sleep(5);
	timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);
	*/
	sleep(5);
}
