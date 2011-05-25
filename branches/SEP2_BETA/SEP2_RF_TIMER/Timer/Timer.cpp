/**
 * Timer
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
 *this class will provide the functionality to execute functions in x milliseconds for Puck_fsm and HALCore objects
 *
 *
 */

#include "Timer.h"

Timer::Timer() {
	mine = TIMER;
	receiver = TIMER;
}


Timer::~Timer() {
	// TODO Auto-generated destructor stub
}


bool Timer::addTimerFunction(struct idTOfunction new_element, int ms){
	timer_t             timerid;
    struct sigevent     event;
    struct itimerspec   timer;
    int nano_sec = 0;
    int sec = 0;

    if( calculateTime(ms, &sec, &nano_sec) == -1 ){
    	perror( "Timer: cannot calculate seconds and nano seconds");
    	return false;
    }//if

	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;

    if( (new_element.id = getnextid()) == -1){
    	perror( "Timer: can't get id for timer");
    	return false;
    }//if


    struct idTOfunction new_element_copy = new_element;//copy to avoid timer_settime failure
    funcp_list_fsm.push_back(new_element_copy);

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, new_element.type, new_element.id );

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


bool Timer::addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int ms){
    struct idTOfunction new_element;
    new_element.type = PUCK_FSM;
    new_element.funcp.funcp_fsm = funcp;
    if(addTimerFunction(new_element, ms)){
    	return true;
    } else {
    	return false;
    }//if
}


bool Timer::addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int ms){
    struct idTOfunction new_element;
    new_element.type = HALCORE;
    new_element.funcp.funcp_hal = funcp;
    if( addTimerFunction(new_element, ms) ){
    	return true;
    } else {
    	return false;
    }//if
}


void Timer::execute(void*) {
	std::cout << "Timer: Start" << std::endl;

	if (settingUpCommunicatorDevice(receiver)) {

		//std::cout << "Timer coid:" << coid << "Timer chid:" << chid << std::endl;
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handlePulsMessage();
		}//while

	}else{
		perror("Timer: Setting Up failed!");
		endCommunication();
	}//if
}


void Timer::handleNormalMessage(){
	std::cout << "Timer: received a message, but doesn't know what to do with it" << std::endl;
}


void Timer::handlePulsMessage(){
	std::cout << "Timer: received a Puls" << std::endl;
	//std::cout << "value:" << val << " code:" << code << std::endl;
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
		}//if
	} else {
		perror( "Timer: got pulseMesage for a not known Timer?!");
	}//if
}


void Timer::shutdown() {

}


struct idTOfunction Timer::find_function(unsigned int id){
	struct idTOfunction result;
	result.id = -1;

	for(unsigned int i = 0; i<funcp_list_fsm.size(); i++){

		if(funcp_list_fsm[i].id == id){
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
			if(funcp_list_fsm[i].id==id){
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


int Timer::calculateTime(int ms, int *s, int *ns){
    if(ms <= 10000){

    	if(ms >= 1000){
    		(*s) = ms/1000;
    		(*ns) = (ms-( (*s)*1000))*1000*1000;
    	}else{
    		(*ns) = ms*1000*1000;
    	}//if

    } else {
    	perror( "Timer: parameter ms not in range (0 <= ms <= 10000)!");
    	return -1;
    }//if
    return 0;
}
