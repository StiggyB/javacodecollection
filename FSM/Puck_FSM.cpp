/**
 * Puck_FSM
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 4: Automatenimplementierung
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * interface for the finite state machine's
 *
 *
 */
#include "Puck_FSM.h"


//Methods for class Puck_FSM
Puck_FSM::Puck_FSM() {
	hc = HALCore::getInstance();
	lamp = Lampen::getInstance();
	serial = NULL;
}

Puck_FSM::~Puck_FSM() {
}

void Puck_FSM::start_signal(bool was_serial){
	hc->shine(GREEN);
	if(!was_serial) serial->send(START_BUTTON, sizeof(int) );
	if( (check_last_lb() == 0) && (puck_list->size() > 0)){
		starts_engine_if_nessecary();
	}//if
}
void Puck_FSM::stop_signal(bool was_serial){
	if(!was_serial) serial->send(STOP_BUTTON, sizeof(int) );
	hc->engineStop();

}
void Puck_FSM::reset_signal(bool was_serial){
	//TODO implement reset
	if(!was_serial) serial->send(RESET_BUTTON, sizeof(int) );
}
void Puck_FSM::estop_in_signal(bool was_serial){
	if(!was_serial) serial->send(E_STOP_PUSHED, sizeof(int) );
	hc->emergencyStop();

}
void Puck_FSM::estop_out_signal(bool was_serial){
	if(!was_serial) serial->send(E_STOP_PULLED, sizeof(int) );
	hc->resetAll();
//	if( (check_last_lb() == 0) && (puck_list->size() > 0)){
//		starts_engine_if_nessecary();
//	}//if

}


void Puck_FSM::puck_fsm2_outgoing() {
	if (request == true) {
		cout << "Sensor: request true, seriel message will be send" << endl;
		hc->engineContinue();
		serial->send(MACHINE2_FREE, sizeof(msgType));
		hc->engineContinue();
		request = false;
	}//if
}
void Puck_FSM::delete_unnecessary_wp() {
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->location == SORT_OUT || (*puck_list)[i]->location == AFTER_LAST_LB) {
			cout << "deleted" << endl;
			puck_list->erase(puck_list->begin() + i);
		}
	}
	cout << "********** COUNT OF WP´S: " << puck_list->size() << endl;
}

void Puck_FSM::starts_engine_if_nessecary() {
	int active_state = 0;
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ( (*puck_list)[i]->engine_should_be_started ) {
			cout << "A PUCK NEED ENGINE" << endl;
			active_state = 1;
		}
	}
	if (active_state == 1) {
		hc->engineContinue();
		hc->engineRight();
	}
}

int Puck_FSM::check_last_lb(){
    for(unsigned int i = 0;i < puck_list->size();i++){
        if( (*puck_list)[i]->location == ON_LAST_LB){
            return -1;
        }//if
    }//for
    return 0;
}

void Puck_FSM::requestfromMachine1(){
	if(puck_list->size() > 1) {
		//request = true;
		(*puck_list)[0]->request = true;
		cout << "request, but wp is on machine" << endl;
	} else {
		serial->send(MACHINE2_FREE, sizeof(msgType));
		hc->engineContinue();
		hc->engineRight();
	}//if
}
void Puck_FSM::PuckhasPocket(){
	if(puck_list->size() > 1) {
		perror("Puck_FSM_2: Machine2 has more than 1 work pieces");
	} else {
		(*puck_list)[0]->hasPocket = true;
	}//if

}
void Puck_FSM::PuckhasnoPocket(){
	if(puck_list->size() > 1) {
		perror("Puck_FSM_2: Machine2 has more than 1 work pieces");
	} else {
		(*puck_list)[0]->hasPocket = false;
	}//if

}
void Puck_FSM::machine2_free(){
	hc->engineRight();
	hc->engineContinue();
}
void Puck_FSM::puck_arrived(){
	hc->engineStop();
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->location == AFTER_LAST_LB) {
			serial->send((*puck_list)[i]->hasPocket ? POCKET : NO_POCKET, sizeof(msgType));
		}
		(*puck_list)[i]->ls_b7_out();
	}
	delete_unnecessary_wp();
	starts_engine_if_nessecary();
}

void Puck_FSM::ls_b0(){
	current->ls_b0(this);
}
void Puck_FSM::ls_b1(){
	current->ls_b1(this);
}
void Puck_FSM::ls_b3(){
	current->ls_b3(this);
}
void Puck_FSM::ls_b6(){
	current->ls_b6(this);
}
void Puck_FSM::ls_b7_in(){
	current->ls_b7_in(this);
}
void Puck_FSM::ls_b7_out(){
	current->ls_b7_out(this);
}
void Puck_FSM::entry(){
	current->entry(this);
}
void Puck_FSM::exit(){
	current->exit(this);
}
void Puck_FSM::setCurrent(State *s){
	current->exit(this);
	delete current;
	current = s;
    this->entry();
}
void Puck_FSM::errorState(){
	current->errorState(this);
}


//Methods for class State
State::State(){

}

State::~State(){

}

void State::ls_b0(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("ls_b0 standard function\n");
	#endif
}

void State::ls_b1(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B1 standard function\n");
	#endif
}

void State::ls_b3(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B3 standard function\n");
	#endif
}

void State::ls_b6(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B6 standard function\n");
	#endif
}

void State::ls_b7_in(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B7_in standard function\n");
	#endif
}

void State::ls_b7_out(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B7_out standard function\n");
	#endif
}

void State::entry(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("entry standard function\n");
	#endif
}

void State::exit(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("exit standard function\n");
	#endif
}

void State::errorState(Puck_FSM *){
	#ifdef PUCK_FSM_STATE_DEBUG
	printf("errorState standard function\n");
	#endif
}
