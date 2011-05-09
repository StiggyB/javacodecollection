/*
 * Machine.cpp
 *
 *  Created on: 06.05.2011
 *      Author: user
 */

#include "Machine.h"
#include "iostream.h"

Machine::Machine() {
	current = new Band1_aufgelegt;
	printf("FSM is up\n");
	cc = CoreController::getInstance();
}

Machine::~Machine() {

}

State::State(){
	cc = CoreController::getInstance();
}

State::~State(){

}

void State::LS_B1(Machine *){ printf("LS_B1 standart function\n"); }
void State::LS_B3(Machine *){ printf("LS_B3 standart function\n"); }
void State::LS_B6(Machine *){ printf("LS_B6 standart function\n"); }
void State::LS_B7(Machine *){ printf("LS_B7 standart function\n"); }
void State::entry(Machine *){ printf("entry standart function\n"); }
void State::exit(Machine *){ printf("exit standart function\n"); }

//functions for Band1_aufgelegt
void Band1_aufgelegt :: LS_B1(Machine * fsm){
	cout << "Band1_aufgelegt: LS_B1 wurde ausgelöst" << endl;
	fsm->setCurrent(new Band1_hoehenmessung() );
}

void Band1_aufgelegt :: entry(Machine * fsm){
	cout << "Band1_aufgelegt: entry" << endl;
}

void Band1_aufgelegt :: exit(Machine * fsm){
	cout << "Band1_aufgelegt: exit" << endl;
}

//functions for durchschleusen
void durchschleusen :: LS_B3(Machine * fsm){
	cout << "durchschleusen: LS_B3 wurde ausgelöst" << endl;
	//fsm->setCurrent(new durchschleusen_bei_LS3() );
}

void durchschleusen :: entry(Machine * fsm){
	cout << "durchschleusen: entry" << endl;
}

void durchschleusen :: exit(Machine * fsm){
	cout << "durchschleusen: exit" << endl;
}

//functions for durchschleusen_bei_LS3
void durchschleusen_bei_LS3 :: LS_B7(Machine * fsm){
	cout << "durchschleusen_bei_LS3: LS_B7 wurde ausgelöst" << endl;
	//(*fsm).setCurrent(new durchschleusen_bei_LS3() );
}

void durchschleusen_bei_LS3 :: entry(Machine * fsm){
	cout << "durchschleusen_bei_LS3: entry" << endl;
}

void durchschleusen_bei_LS3 :: exit(Machine * fsm){
	cout << "durchschleusen_bei_LS3: exit" << endl;
}

//functions for Band1_hoehenmessung
void Band1_hoehenmessung :: entry(Machine * fsm){
	cout << "Band1_hoehenmessung: entry" << endl;
	int height = (*cc).identifyHeight();
	cout << "höhe: " << height << endl;
	if(height == NORMAL_WP){
		cout << "gute Höhe!" << endl;
		fsm->setCurrent(new durchschleusen() );
	}
	else{
		fsm->setCurrent(new ausschleusen() );
	}
}

void Band1_hoehenmessung :: exit(Machine * fsm){
	cout << "Band1_hoehenmessung: exit" << endl;
}

//functions for ausschleusen
void ausschleusen :: LS_B3 (Machine * fsm){
	cout << "ausschleusen: LS_B3" << endl;

}

void ausschleusen :: entry (Machine * fsm){
	cout << "ausschleusen: entry" << endl;
}

void ausschleusen :: exit (Machine * fsm){
	cout << "ausschleusen: exit" << endl;
}

//functions for Machine
void Machine::LS_B1(){
	current->LS_B1(this);
	(*cc).engineStop();
}

void Machine::LS_B3(){
	current->LS_B3(this);
}

void Machine::LS_B6(){
	current->LS_B6(this);
}

void Machine::LS_B7(){
	current->LS_B7(this);
}

void Machine::entry(){
	current->entry(this);
}

void Machine::exit(){
	current->exit(this);
}

void Machine::setCurrent(State *s){
	current->exit(this);
	current = s;
    this->entry();
}
