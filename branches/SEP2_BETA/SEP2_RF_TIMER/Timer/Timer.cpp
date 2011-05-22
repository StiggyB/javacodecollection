/*
 * Timer.cpp
 *
 *  Created on: 19.05.2011
 *      Author: user
 */

#include "Timer.h"

Timer::Timer() {
	mine = TIMER;
	receiver = TIMER;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}
void Timer::testTimer(){
	timer_t             timerid;
    struct sigevent     event;
    struct itimerspec   timer;

	timer.it_value.tv_sec = 2;

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, PUCK_FSM, 22 );

	if( timer_create (CLOCK_REALTIME, &event, &timerid) == -1){
		perror( "Timer: cannot create OS-Timer");
		return ;
	}//if


	if( timer_settime (timerid, 0, &timer, NULL) == -1){
		perror( "Timer: cannot set OS-Timer");
		return ;
	}//if

}

bool Timer::addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int ms){
	timer_t             timerid;
    struct sigevent     event;
    struct itimerspec   timer;
    struct idTOfunction new_element;
    int nano_sec = 0;
    int sec = 0;
    volatile int retval = -1;

    if(ms <= 10000){
    	if(ms >= 1000){
    		sec = ms/1000;
    		nano_sec = (ms-(sec*1000))*1000*1000;
    	}else{
    		nano_sec = ms*1000*1000;
    	}//if
    } else {
    	perror( "Timer: parameter ms not in range (0 <= ms <= 10000)!");
    }//if

	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;

    //std::cout << "davor: size of list::::" << funcp_list.size() << std::endl;
    std::cout << "Timer: nextid: " << getnextid() << std::endl;

    if(getnextid() == -1){
    	return false;
    }//if

    new_element.funcp.funcp_fsm = funcp;
    new_element.id = getnextid();
    new_element.type = PUCK_FSM;
    funcp_list_fsm.push_back( new_element );

    //std::cout << "danach: size of list::::" << funcp_list.size() << std::endl;
    //std::cout << "danach: Timer: nextid: " << getnextid() << std::endl;

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, PUCK_FSM, new_element.id );

	//retval = timer_create (CLOCK_REALTIME, &event, &timerid);
	//std::cout << "retval: " << retval << std::endl;

	if( timer_create (CLOCK_REALTIME, &event, &timerid) == -1){
		perror( "Timer: cannot create OS-Timer");
		return false;
	}//if


	if( timer_settime (timerid, 0, &timer, NULL) == -1){
		perror( "Timer: cannot set OS-Timer");
		return false;
	}//if

	return true;
}

bool Timer::addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int ms){
	timer_t             timerid;
    struct sigevent     event;
    struct itimerspec   timer;
    struct idTOfunction new_element;
    int nano_sec = 0;
    int sec = 0;
    volatile int retval = -1;

    if(ms <= 10000){
    	if(ms >= 1000){
    		sec = ms/1000;
    		nano_sec = (ms-(sec*1000))*1000*1000;
    	}else{
    		nano_sec = ms*1000*1000;
    	}//if
    } else {
    	perror( "Timer: parameter ms not in range (0 <= ms <= 10000)!");
    }//if

	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;

    //std::cout << "davor: size of list::::" << funcp_list.size() << std::endl;
    std::cout << "Timer: nextid: " << getnextid() << std::endl;

    if(getnextid() == -1){
    	return false;
    }//if

    new_element.funcp.funcp_hal = funcp;
    new_element.id = getnextid();
    new_element.type = PUCK_FSM;
    funcp_list_fsm.push_back( new_element );

    //std::cout << "danach: size of list::::" << funcp_list.size() << std::endl;
    //std::cout << "danach: Timer: nextid: " << getnextid() << std::endl;

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, HALCORE, new_element.id );

	//retval = timer_create (CLOCK_REALTIME, &event, &timerid);
	//std::cout << "retval: " << retval << std::endl;

	if( timer_create (CLOCK_REALTIME, &event, &timerid) == -1){
		perror( "Timer: cannot create OS-Timer");
		return false;
	}//if


	if( timer_settime (timerid, 0, &timer, NULL) == -1){
		perror( "Timer: cannot set OS-Timer");
		return false;
	}//if

	return true;
}


void Timer::execute(void*) {
	std::cout << "Timer: Start" << std::endl;

	if (settingUpCommunicatorDevice(receiver)) {
		//std::cout << "Timer coid:" << coid << "Timer chid:" << chid << std::endl;
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
	//std::cout << "value:" << val << " code:" << code << std::endl;
	//std::cout << "size of list::::" << funcp_list.size() << std::endl;
	struct idTOfunction temp;
	temp = find_function(r_msg->pulse.value.sival_int);
	if( temp.id != -1 ){
		switch(temp.type){
		case PUCK_FSM: temp.funcp.funcp_fsm->call(NULL);
			break;
		case HALCORE: temp.funcp.funcp_hal->call(NULL);
			break;
		default:
			perror("Timer: unknown type for functionpointer!");
		}
	} else {
		perror( "Timer: got pulseMesage for a not known Timer?!");
	}


	//funcp_list[0]->call(NULL);
}

void Timer::shutdown() {

}

struct idTOfunction Timer::find_function(unsigned int id){
	struct idTOfunction result;
	result.id = -1;

	for(unsigned int i = 0; i<funcp_list_fsm.size(); i++){
		//std::cout << "find_function id:" << funcp_list[i].id << std::endl;
		if(funcp_list_fsm[i].id == id){
			//std::cout << "found" << std::endl;
			result = funcp_list_fsm[i];
			funcp_list_fsm.erase(funcp_list_fsm.begin()+i);
			return result;
		}//if
	}//for
	return result;
}

int Timer::getnextid(){
	unsigned int id = 0;
	bool reserved = false;

	while(id <= funcp_list_fsm.size()){
		reserved = false;

		for(unsigned int i = 0; i < funcp_list_fsm.size(); i++){
			//std::cout << "for i=" << i <<std::endl;
			if(funcp_list_fsm[i].id==id){
				//std::cout << "reserved id" << std::endl;
				reserved = true;
			}//if
		}//for

		if(reserved){
			id++;
		} else {
			return id;
		}//if
	}//while

	return  -1;
}

