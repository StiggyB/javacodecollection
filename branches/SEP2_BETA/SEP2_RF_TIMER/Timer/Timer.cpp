/*
 * Timer.cpp
 *
 *  Created on: 19.05.2011
 *      Author: user
 */

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub
	mine = TIMER;
	receiver = TIMER;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

bool Timer::addTimerFunction(){
	//funcp->call(NULL);
	//std::cout << "operation executed" << std::endl;
	sendPulses(TIMER, 0, 0);

		timer_t             timerid;
	    struct sigevent     event;
	    struct itimerspec   timer;

	    SIGEV_PULSE_INIT (&event, coid, SIGEV_PULSE_PRIO_INHERIT, 10, 0);
	    // Erzeuge den Timer
	    timer_create (CLOCK_REALTIME, &event, &timerid); // Fehlerbehandlung fehlt
	    // Setup und Start eines periodischen Timers
	    timer.it_value.tv_sec = 1;
	    timer.it_value.tv_nsec = 0;
	    timer.it_interval.tv_sec = 1;
	    timer.it_interval.tv_nsec = 0;
	    timer_settime (timerid, 0, &timer, NULL);

	    return true;
}

void Timer::execute(void*) {
	std::cout << "Start Timer" << std::endl;
	//while (!isStopped()) {

		/*Puck_FSM_1 fsm1;
		CallInterface<Puck_FSM, void, void*>* func1 =
					FunctorMaker<Puck_FSM, void, void*>::makeFunctor(&fsm1, &Puck_FSM::ls_b0);*/

		//addTimerFunction(func1);

		if (settingUpCommunicatorDevice(receiver)) {
			while (!isStopped()) {
				rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
				std::cout << "blaa" << std::endl;
				//handleMessage();
			}
			endCommunication(SENSOR);
		}else{
			perror("Sensor: Setting Up failed!");
		}

	//}
}

void Timer::handleNormalMessage(){

}


void Timer::handlePulsMessage(){
	std::cout << "Sensor: received a Puls, but doesn't know what to do with it" << std::endl;
}

void Timer::shutdown() {

}

