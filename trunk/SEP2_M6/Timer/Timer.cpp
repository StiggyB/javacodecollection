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

int Timer::addTimerFunction(struct IdTOfunction new_element, int ms) {
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

	//printf("timerid: %i, sec: %i, nsec: %i\n", timerid, timer.it_value.tv_sec, timer.it_value.tv_nsec);

	if (timer_settime(timerid, 0, &timer, NULL) == -1) {
		perror("Timer: cannot set OS-Timer");
		printf("errno: %i", errno);
		return false;
	}//if

	return new_element.id;
}


int Timer::addTimerFunction( CallInterface<CallBackThrower, void>* funcp, int ms){
    struct IdTOfunction new_element;
    new_element.funcp.funcp_cbt_void = funcp;
    return (addTimerFunction(new_element, ms));
}

void Timer::handleNormalMessage(){
	std::cout << "Timer: received a message, but doesn't know what to do with it" << std::endl;
}

void Timer::handlePulsMessage(){
	//std::cout << "Timer: received a Puls" << std::endl;
	struct IdTOfunction temp;
	temp = find_function(r_msg->pulse.value.sival_int);
	if( temp.id != -1 ){

		//printf("Timer: start_execute_duration=%i ", getSystemTime_ms()-temp.systemtime_ms );

		if( temp.funcp.funcp_cbt_void != NULL ){
			temp.funcp.funcp_cbt_void->call();
//			std::cout << "Timer: -->call()" << std::endl;
		}//if


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
	locker.lock();
	long diff = 0;
	bool unstoppablefound = false;
	bool notfound = true;

	for(unsigned int i = 0; i<funcp_list.size(); i++){
		notfound = true;
		unstoppablefound = false;

		for(unsigned int j = 0; j<unstoppable_funcp_list.size() && notfound; j++){
			if(funcp_list[i].funcp.funcp_cbt_void == unstoppable_funcp_list[j]){
				unstoppablefound = true;
				//cout << "unstoppablefound found" << endl;
				notfound = false;
			}//if
		}//for

		if(!unstoppablefound){

			if( timer_delete( funcp_list[i].timer_id ) == -1){
				perror( "Timer: cannot delete OS-Timer in Timer_stopAllTimer()");
				locker.unlock();
				return -1;
			}//if
			funcp_list[i].timer_id = -1;
			diff = getSystemTime_ms()-funcp_list[i].systemtime_ms;
			printf("Timer: start_stop_duration=%i\n", diff );
			funcp_list[i].duration_ms = funcp_list[i].duration_ms - diff;
			printf("Timer: rest_duration=%i\n", funcp_list[i].duration_ms);

		}//for

	}//for
	locker.unlock();

	return 0;
}

int Timer::startAllTimer(){
	locker.lock();
	int sec = 0;
	int nano = 0;
	timer_t timerid;
	struct sigevent event;
	struct itimerspec timer;

	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if( funcp_list[i].timer_id == -1 ){//a not stopped timer

			calculateTime(funcp_list[i].duration_ms, &sec, &nano);

			timer.it_value.tv_sec = sec;
			timer.it_value.tv_nsec = nano;
			timer.it_interval.tv_nsec = 0;
			timer.it_interval.tv_sec = 0;

			SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, NULL, funcp_list[i].id );

			if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
				perror("Timer: cannot create OS-Timer in startAllTimer()");
				return -1;
			}//if

			funcp_list[i].timer_id = timerid;

			//printf("restart timerid: %i, sec: %i, nsec: %i\n", timerid, timer.it_value.tv_sec, timer.it_value.tv_nsec);

			if (timer_settime(timerid, 0, &timer, NULL) == -1) {
				perror("Timer: cannot set OS-Timer in startAllTimer()");
				printf("errno: %i", errno);
				return -1;
			}//if

		}//if
	}//for


	locker.unlock();
	return 0;
}


int Timer::deleteTimer(int id){
	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if( funcp_list[i].id == id && funcp_list[i].timer_id != -1 ){ //

			if( timer_delete( funcp_list[i].timer_id ) == -1){
				perror( "Timer: cannot delete OS-Timer in stopTimerbyId()");
				return -1;
			}//if

//			std::cout << "Timer: stopTimerbyId has delete a Timer - ID: " << funcp_list[i].timer_id << std::endl;
			funcp_list.erase( funcp_list.begin()+i );
		}//if

	}//for
	return 0;
}


int Timer::deleteAllTimer(){
	locker.lock();
	for(unsigned int i = 0; i<funcp_list.size(); i++){

		if( timer_delete( funcp_list[i].timer_id ) == -1){
			perror( "Timer: cannot delete OS-Timer in deleteAllTimer()");
			locker.unlock();
			return -1;
		}//if

	}//for
	funcp_list.clear();

	locker.unlock();
	return 0;
}

int Timer::addUnstoppableFunction( CallInterface<CallBackThrower,void>* funcp ){
	unstoppable_funcp_list.push_back(funcp);
	return 0;
}


bool Timer::existTimer(int id){
	for(unsigned int i = 0; i<funcp_list.size(); i++){
		if(funcp_list[i].id == id){
			return true;
		}
	}
	return false;

}
