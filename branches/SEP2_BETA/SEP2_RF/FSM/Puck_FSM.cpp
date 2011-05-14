/*
 * IPuck_FSM.cpp
 *
 *  Created on: 13.05.2011
 *      Author: user
 */

#include "Puck_FSM.h"

Puck_FSM::Puck_FSM() {
	cc = CoreController::getInstance();
}

Puck_FSM::~Puck_FSM() {
	// TODO Auto-generated destructor stub
}

State::State(){

}

State::~State(){

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
	current = s;
    this->entry();
}
void Puck_FSM::errorState(){
	current->errorState(this);
}



void State::ls_b0(Puck_FSM *){ printf("ls_b0 standard function\n"); }
void State::ls_b1(Puck_FSM *){ printf("LS_B1 standard function\n"); }
void State::ls_b3(Puck_FSM *){ printf("LS_B3 standard function\n"); }
void State::ls_b6(Puck_FSM *){ printf("LS_B6 standard function\n"); }
void State::ls_b7_in(Puck_FSM *){ printf("LS_B7_in standard function\n"); }
void State::ls_b7_out(Puck_FSM *){ printf("LS_B7_out standard function\n"); }
void State::entry(Puck_FSM *){ printf("entry standard function\n"); }
void State::exit(Puck_FSM *){ printf("exit standard function\n"); }
void State::errorState(Puck_FSM *){ printf("errorState standard function\n"); }
