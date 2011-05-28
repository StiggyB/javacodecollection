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
	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if( timer_delete( funcp_list[i].timer_id ) != 0){
			perror( "Timer: cannot delete OS-Timer");
		}//if
	}//for
	funcp_list.clear();
}

int Timer::addFunction_staticTimer(timer_section timer, CallInterface<HALCore, void, void*>* funcp){
	return 0;
}

int Timer::addFunction_staticTimer(timer_section timer, CallInterface<Puck_FSM, void, void*>* funcp ){
	return 0;
}
/*
int Timer::initTimer_list(){
	int numberOfStaticTimer = 5;
	struct TimerData timer[numberOfStaticTimer];

	timer[0].timer.it_value.tv_sec = 3;
	timer[0].timer.it_value.tv_nsec = 5*1000*100;

	timer[1].timer.it_value.tv_sec = 2;
	timer[1].timer.it_value.tv_nsec = 5*1000*100;

	timer[2].timer.it_value.tv_sec = 2;
	timer[2].timer.it_value.tv_nsec = 5*1000*100;

	timer[3].timer.it_value.tv_sec = 3;
	timer[3].timer.it_value.tv_nsec = 5*1000*100;

	timer[4].timer.it_value.tv_sec = 1;
	timer[4].timer.it_value.tv_nsec = 0;

	for(int i = 0; i < numberOfStaticTimer; i++){
		if( timer_create (CLOCK_REALTIME, &timer[i].event, &timer[i].timerid) == -1){
			perror( "Timer: cannot create a static OS-Timer");
			return false;
		}//if
		timer_list.push_back(timer[i]);
	}//for

	//timer_list
	return 0;
}*/

bool Timer::addTimerFunction(struct IdTOfunction new_element, int ms) {
	timer_t timerid;
	struct sigevent event;
	struct itimerspec timer;
	int nano_sec = 0;
	int sec = 0;

	if (calculateTime(ms, &sec, &nano_sec) == -1) {
		perror("Timer: cannot calculate seconds and nano seconds");
		return false;
	}//if

	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;
	timer.it_interval.tv_nsec = 0;
	timer.it_interval.tv_sec = 0;

	if ((new_element.id = getnextid()) == -1) {
		perror("Timer: can't get id for timer");
		return false;
	}//if


	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, new_element.type, new_element.id );

	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		perror("Timer: cannot create OS-Timer");
		return false;
	}//if

	new_element.timer_id = timerid;
	funcp_list.push_back(new_element);
	printf("timerid: %i, sec: %i, nsec: %i\n", timerid, timer.it_value.tv_sec, timer.it_value.tv_nsec);

	if (timer_settime(timerid, 0, &timer, NULL) == -1) {
		perror("Timer: cannot set OS-Timer");
		printf("errno: %i", errno);
		return false;
	}//if

	return true;
}


bool Timer::addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int ms){
    struct IdTOfunction new_element;
    new_element.type = PUCK_FSM;
    new_element.funcp.funcp_fsm = funcp;
    if(addTimerFunction(new_element, ms)){
    	return true;
    } else {
    	return false;
    }//if
}


bool Timer::addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int ms){
    struct IdTOfunction new_element;
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
	struct IdTOfunction temp;
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


struct IdTOfunction Timer::find_function(int id){
	struct IdTOfunction result;
	result.id = -1;

	for(unsigned int i = 0; i<funcp_list.size(); i++){

		if(funcp_list[i].id == id){
			result = funcp_list[i];

			if( timer_delete( funcp_list[i].timer_id ) == -1){
				perror( "Timer: cannot delete OS-Timer");
				return result;
			}//if

			funcp_list.erase(funcp_list.begin()+i);
			return result;
		}//if

	}//for
	return result;
}


int Timer::getnextid(){
	int id = 0;
	bool reserved = false;

	while(id <= (signed int) funcp_list.size()){
		reserved = false;

		for(unsigned int i = 0; i < funcp_list.size(); i++){
			if(funcp_list[i].id==id){
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
