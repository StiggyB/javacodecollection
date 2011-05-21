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
	id_index = 0;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

bool Timer::addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int ms){
	timer_t             timerid;
    struct sigevent     event;
    struct itimerspec   timer;

    struct idTOfunction new_element;

    int nano_sec = 0;
    int sec = 0;

    if(ms <= 10000){
    	if(ms >= 1000){
    		sec = ms/1000;
    		nano_sec = (ms-(sec*1000))*1000*1000;
    	}else{
    		nano_sec = ms*1000*1000;
    	}
    } else {
    	perror( "Timer: parameter ms not in range (0 <= ms <= 10000)!");
    }


    new_element.funcp = funcp;
    new_element.id = id_index;
    funcp_list.push_back( new_element );



	SIGEV_PULSE_INIT (&event, coid, SIGEV_PULSE_PRIO_INHERIT, 0, (id_index++) );
	// Erzeuge den Timer
	timer_create (CLOCK_REALTIME, &event, &timerid); // Fehlerbehandlung fehlt
	// Setup und Start eines periodischen Timers
	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;
	//timer.it_interval.tv_sec = 2;
	//timer.it_interval.tv_nsec = 0;
	timer_settime (timerid, 0, &timer, NULL);

	return true;
}

void Timer::execute(void*) {
	std::cout << "Timer: Start" << std::endl;

	if (settingUpCommunicatorDevice(receiver)) {
		std::cout << "Timer coid:" << coid << "Timer chid:" << chid << std::endl;
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handlePulsMessage();
		}
	}else{
		perror("Timer: Setting Up failed!");
		endCommunication();
	}
}

void Timer::handleNormalMessage(){
	std::cout << "Timer: received a message, but doesn't know what to do with it" << std::endl;
}


void Timer::handlePulsMessage(){
	std::cout << "Timer: received a Puls" << std::endl;
	unsigned int val = r_msg->pulse.value.sival_int;
	unsigned int code = r_msg->pulse.code;
	std::cout << "value:" << val << " code:" << code << std::endl;
	struct idTOfunction temp;
	temp = find_function(val);
	if( temp.id != -1 ){
		temp.funcp->call(NULL);
	} else {
		perror( "Timer: got pulseMesage for a not known Timer?!");
	}

	std::cout << "size ff list::::" << funcp_list.size() << std::endl;
	//funcp_list[0]->call(NULL);
}

void Timer::shutdown() {

}

struct idTOfunction Timer::find_function(int id){
	struct idTOfunction result;
	result.funcp = NULL;
	result.id = -1;

	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if(funcp_list[i].id == id){
			//std::cout << "found" << std::endl;
			result = funcp_list[i];
			funcp_list.erase(funcp_list.begin()+i);
			return result;
		}//if
	}//for
	return result;
}
