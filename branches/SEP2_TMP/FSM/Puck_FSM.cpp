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
}

Puck_FSM::~Puck_FSM() {
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
