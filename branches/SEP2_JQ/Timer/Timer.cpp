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
 * This class will provide the functionality to execute functions in x milliseconds for Puck_fsm and HALCore objects
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

void Timer::shutdown() {

}

bool Timer::addTimerFunction(struct IdTOfunction new_element, int ms) {
	timer_t timerid;
	struct sigevent event;
	struct itimerspec timer;
	int nano_sec = 0;
	int sec = 0;

	new_element.duration_ms = ms;

	new_element.systemtime_ms = getSystemTime_ms();

	if (calculateTime(ms, &sec, &nano_sec) == -1) {
		perror("Timer: cannot calculate seconds and nano seconds");
		return false;
	}//if

	timer.it_value.tv_sec = sec;
	timer.it_value.tv_nsec = nano_sec;
	timer.it_interval.tv_nsec = 0;
	timer.it_interval.tv_sec = 0;

	locker.lock();
	if ((new_element.id = getnextid()) == -1) {
		perror("Timer: can't get id for timer");
		locker.unlock();
		return false;
	}//if
	locker.unlock();

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, NULL, new_element.id );

	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		perror("Timer: cannot create OS-Timer");
		return false;
	}//if

	new_element.timer_id = timerid;
	locker.lock();
	funcp_list.push_back(new_element);
	locker.unlock();

	printf("timerid: %i, sec: %i, nsec: %i\n", timerid, timer.it_value.tv_sec, timer.it_value.tv_nsec);

	if (timer_settime(timerid, 0, &timer, NULL) == -1) {
		perror("Timer: cannot set OS-Timer");
		printf("errno: %i", errno);
		return false;
	}//if

	return true;
}

/*
bool Timer::addTimerFunction( CallInterface<Puck_FSM_1, void>* funcp, int ms){
    struct IdTOfunction new_element;
    new_element.type = PUCK_FSM;
    new_element.funcp.funcp_fsm = funcp;
    return (addTimerFunction(new_element, ms));
}

bool Timer::addTimerFunction( CallInterface<HALCore, void>* funcp, int ms){
    struct IdTOfunction new_element;
    new_element.type = HALCORE;
    new_element.funcp.funcp_hal = funcp;
    return (addTimerFunction(new_element, ms));
}*/

bool Timer::addTimerFunction( CallInterface<CallBackThrower, void>* funcp, int ms){
    struct IdTOfunction new_element;
    new_element.funcp.funcp_cbt = funcp;
    return (addTimerFunction(new_element, ms));
}

void Timer::handleNormalMessage(){
	std::cout << "Timer: received a message, but doesn't know what to do with it" << std::endl;
}

void Timer::handlePulsMessage(){
	std::cout << "Timer: received a Puls" << std::endl;
	struct IdTOfunction temp;
	temp = find_function(r_msg->pulse.value.sival_int);
	if( temp.id != -1 ){

		printf("Timer: start_execute_duration=%i ", getSystemTime_ms()-temp.systemtime_ms );

		if( temp.funcp.funcp_cbt != NULL ){
			temp.funcp.funcp_cbt->call();
			std::cout << "Timer: -->call()" << std::endl;
		}//if

		//std::cout << "Timer: start_execute_duration=" << millisec-temp.millisec << std::endl;

		/*switch(temp.type){
		case PUCK_FSM: temp.funcp.funcp_fsm->call(); std::cout << "-->call()" << std::endl;
			break;
		case HALCORE: temp.funcp.funcp_hal->call(); std::cout << "-->call()" << std::endl;
			break;
		default:
			perror("Timer: unknown type for functionpointer!");
		}//switch
		*/

	} else {
		perror( "Timer: got pulseMesage for a not known Timer?!");
	}//if
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

long Timer::getSystemTime_ms(){
	struct timeval act_time;
	if ( gettimeofday(&act_time, NULL) != 0 ){
		perror("Timer: getSystemTime_ms failed - gettimeofday!=0");
		return -1;
	}
	return ((act_time.tv_sec) * 1000 + act_time.tv_usec/1000.0) + 0.5;
}

int Timer::stopAll_actual_Timer(){
	long diff = 0;

	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if( timer_delete( funcp_list[i].timer_id ) == -1){
			perror( "Timer: cannot delete OS-Timer in Timer_stopAllTimer()");
			return -1;
		}//if
		funcp_list[i].timer_id = -1;
		diff = getSystemTime_ms()-funcp_list[i].systemtime_ms;
		printf("Timer: start_stop_duration=%i\n", diff );
		funcp_list[i].duration_ms = funcp_list[i].duration_ms - diff;
		printf("Timer: rest_duration=%i\n", funcp_list[i].duration_ms);

	}//for

	return 0;
}

int Timer::startAllTimer(){
	std::vector< struct IdTOfunction> funcp_list_local;

	funcp_list_local = funcp_list;
	funcp_list.clear();

	while(funcp_list_local.size() > 0){
		if( funcp_list_local[0].timer_id != -1 ){//a not stopped timer
			funcp_list.push_back( funcp_list_local[0] );
			std::cout << "Timer: not stopped timer" << std::endl;

		} else {
			addTimerFunction(funcp_list_local[0].funcp.funcp_cbt, funcp_list_local[0].duration_ms);
			/*
			switch( funcp_list_local[0].type ){
			case PUCK_FSM: addTimerFunction(funcp_list_local[0].funcp.funcp_fsm, funcp_list_local[0].duration_ms);
				break;
			case HALCORE: addTimerFunction(funcp_list_local[0].funcp.funcp_hal, funcp_list_local[0].duration_ms);
				break;
			default:
				perror("Timer: unknown type for functionpointer in startAllTimer()");
			}//switch
			*/
			std::cout << "Timer: restart timer" << std::endl;

		}//if

		funcp_list_local.erase( funcp_list_local.begin() );

	}//while
	return 0;
}

