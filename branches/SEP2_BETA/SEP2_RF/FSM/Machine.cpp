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

void State::ls_b1(Machine *){ printf("LS_B1 standard function\n"); }
void State::ls_b3(Machine *){ printf("LS_B3 standard function\n"); }
void State::ls_b6(Machine *){ printf("LS_B6 standard function\n"); }
void State::ls_b7(Machine *){ printf("LS_B7 standard function\n"); }
void State::entry(Machine *){ printf("entry standard function\n"); }
void State::exit(Machine *){ printf("exit standard function\n"); }
void State::wp_after_Switch(Machine *){ printf("wp_after_Switch standard function\n"); }
void State::errorState(Machine *){ printf("errorState standard function\n"); }

//functions for Band1_aufgelegt
void Band1_aufgelegt :: ls_b1(Machine * fsm){
	cout << "Band1_aufgelegt: LS_B1 wurde ausgelöst" << endl;
	fsm->setCurrent(new Band1_hoehenmessung() );
}
void Band1_aufgelegt :: entry(Machine * fsm){
	cout << "Band1_aufgelegt: entry" << endl;
}
void Band1_aufgelegt :: exit(Machine * fsm){
	cout << "Band1_aufgelegt: exit" << endl;
}


//functions for Band1_hoehenmessung
void Band1_hoehenmessung :: entry(Machine * fsm){
	(*cc).engineStop();

	cout << "Band1_hoehenmessung: entry" << endl;
	int height = NORMAL_WP;//(*cc).identifyHeight();
	cout << "höhe: " << height << endl;
	if(height == NORMAL_WP){
		cout << "gute Höhe!" << endl;
		fsm->setCurrent( new durchschleusen() );
	}
	else{
		fsm->setCurrent( new ausschleusen() );
	}
}
void Band1_hoehenmessung :: exit(Machine * fsm){
	cout << "Band1_hoehenmessung: exit" << endl;
	(*cc).engineReset();
	(*cc).engineRight();
}


//functions for durchschleusen
void durchschleusen :: ls_b3(Machine * fsm){
	cout << "durchschleusen: LS_B3 wurde ausgelöst" << endl;
	(*cc).openSwitch();
}
void durchschleusen :: entry(Machine * fsm){
	cout << "durchschleusen: entry" << endl;

}
void durchschleusen :: exit(Machine * fsm){
	cout << "durchschleusen: exit" << endl;
}
void durchschleusen::wp_after_Switch(Machine * fsm){
	(*cc).closeSwitch();
	fsm->setCurrent(new durchschleusen_bei_LS3() );
}


//functions for durchschleusen_bei_LS3
void durchschleusen_bei_LS3 :: ls_b7(Machine * fsm){
	cout << "durchschleusen_bei_LS3: LS_B7 wurde ausgelöst" << endl;
	(*cc).engineStop();
	fsm->isOnLS7 = true;
	fsm->setCurrent(new pruef_LS7() );
}
void durchschleusen_bei_LS3 :: entry(Machine * fsm){
	cout << "durchschleusen_bei_LS3: entry" << endl;
}
void durchschleusen_bei_LS3 :: exit(Machine * fsm){
	cout << "durchschleusen_bei_LS3: exit" << endl;
}

//functions for pruef_LS7
void pruef_LS7 :: entry(Machine * fsm){
	cout << "pruef_LS7: entry" << endl;
}
void pruef_LS7 :: exit(Machine * fsm){
	cout << "pruef_LS7: exit" << endl;
}


//functions for ausschleusen
void ausschleusen :: ls_b3 (Machine * fsm){
	cout << "ausschleusen: LS_B3" << endl;
	(*cc).engineRight();
	fsm->setCurrent(new Weiche_zu() );
}

void ausschleusen :: entry (Machine * fsm){
	cout << "ausschleusen: entry" << endl;
}
void ausschleusen :: exit (Machine * fsm){
	cout << "ausschleusen: exit" << endl;
}


//functions for Weiche_zu
void Weiche_zu :: ls_b6 (Machine * fsm){
	cout << "Weiche_zu: LS_B6" << endl;
	(*cc).engineStop();
	fsm->setCurrent(new WS_im_Schacht() );

}
void Weiche_zu :: entry (Machine * fsm){
	cout << "Weiche_zu: entry" << endl;
}
void Weiche_zu :: exit (Machine * fsm){
	cout << "Weiche_zu: exit" << endl;
}


//functions for WS_im_Schacht
void WS_im_Schacht :: entry (Machine * fsm){
	cout << "WS_im_Schacht: entry" << endl;
	fsm->setCurrent(new pruef_schacht_voll() );
}
void WS_im_Schacht :: exit (Machine * fsm){
	cout << "WS_im_Schacht: exit" << endl;
}



//functions for pruef_schacht_voll
void pruef_schacht_voll :: entry (Machine * fsm){
	cout << "pruef_schacht_voll: entry" << endl;
	sleep(2);

	if( (*cc).isSlideFull() ){
		fsm->setCurrent( new ErrorState() );
	}
}
void pruef_schacht_voll :: exit (Machine * fsm){
	cout << "pruef_schacht_voll: exit" << endl;
}


//functions for errorState
void ErrorState :: entry (Machine * fsm){
	cout << "pruef_schacht_voll: errorState" << endl;
	(*cc).shine(RED);
}
void ErrorState :: exit (Machine * fsm){
	cout << "pruef_schacht_voll: errorState" << endl;
	(*cc).addLight(RED);
}

//functions for Machine
void Machine::ls_b1(){
	current->ls_b1(this);
}
void Machine::ls_b3(){
	current->ls_b3(this);
}
void Machine::ls_b6(){
	current->ls_b6(this);
}
void Machine::ls_b7(){
	current->ls_b7(this);
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
void Machine::wp_after_Switch(){
	current->wp_after_Switch(this);
}
void Machine::errorState(){
	current->errorState(this);
}
