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

	int TID_1 = timer->getnextid();
	int TID_2 = timer->getnextid();
	int TID_3 = timer->getnextid();
	int TID_4 = timer->getnextid();

///////////////////
    struct timeval start, end;
    long mtime, seconds, useconds;

    gettimeofday(&start, NULL);
    usleep(2000);
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    printf("Elapsed time: %ld milliseconds\n", mtime);


//////////////
	timer->addTimerFunction(openswitch, 1200, TID_1);
	//timer->addTimerFunction(closeswitch, 9000, TID_2);

	usleep(150000);
	timer->stopAll_actual_Timer();
	usleep(150000);
	timer->startAllTimer();

	usleep(150000);
	timer->stopAll_actual_Timer();
	usleep(150000);
	timer->startAllTimer();

	usleep(150000);
	timer->stopAll_actual_Timer();
	usleep(150000);
	timer->startAllTimer();

	usleep(100000);
	timer->stopAll_actual_Timer();
	usleep(100000);
	timer->startAllTimer();

	sleep(100);

	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)openswitch, 1000, TID_3);
//	timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)openswitch);
	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)closeswitch, 2500, TID_4);
	//timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)closeswitch);

	timer->stopAll_actual_Timer();
	cout << "stopAll_actual_Timer()" <<endl;
	sleep(7);
	timer->startAllTimer();
	cout << "startAllTimer()" <<endl;

	sleep(4);
	timer->addTimerFunction(openswitch, 1000, TID_1);
	timer->addTimerFunction(closeswitch, 2000, TID_2);
	sleep(5);
	/*timer->addTimerFunction(openswitch, 2000);
	timer->addTimerFunction(closeswitch, 4000);*/

	sleep(50);
}
