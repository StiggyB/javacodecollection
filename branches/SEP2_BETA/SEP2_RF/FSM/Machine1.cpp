/*
 * Machine.cpp
 *
 *  Created on: 06.05.2011
 *      Author: user
 */

#include "Machine1.h"
#include "iostream.h"

Machine1::Machine1() {
	current = new Band1_aufgelegt;
	current->entry(this);
	printf("FSM is up\n");
	cc = CoreController::getInstance();
}

Machine1::~Machine1() {

}

State_M1::State_M1(){
	cc = CoreController::getInstance();
}

State_M1::~State_M1(){

}

void State_M1::ls_b1(Machine1 *){ printf("LS_B1 standard function\n"); }
void State_M1::ls_b3(Machine1 *){ printf("LS_B3 standard function\n"); }
void State_M1::ls_b6(Machine1 *){ printf("LS_B6 standard function\n"); }
void State_M1::ls_b7(Machine1 *){ printf("LS_B7 standard function\n"); }
void State_M1::entry(Machine1 *){ printf("entry standard function\n"); }
void State_M1::exit(Machine1 *){ printf("exit standard function\n"); }
void State_M1::wp_after_Switch(Machine1 *){ printf("wp_after_Switch standard function\n"); }
void State_M1::errorState(Machine1 *){ printf("errorState standard function\n"); }

//functions for Band1_aufgelegt
void Band1_aufgelegt :: ls_b1(Machine1 * fsm){
	cout << "Band1_aufgelegt: LS_B1 wurde ausgelöst" << endl;
	fsm->setCurrent(new Band1_hoehenmessung() );
}
void Band1_aufgelegt :: entry(Machine1 * fsm){
	cout << "Band1_aufgelegt: entry" << endl;
	(*cc).shine(GREEN);
}
void Band1_aufgelegt :: exit(Machine1 * fsm){
	cout << "Band1_aufgelegt: exit" << endl;
}


//functions for Band1_hoehenmessung
void Band1_hoehenmessung :: entry(Machine1 * fsm){
	(*cc).engineStop();

	cout << "Band1_hoehenmessung: entry" << endl;
	int height = (*cc).identifyHeight();
	cout << "höhe: " << height << endl;
	if(height == NORMAL_WP || height == POCKET_WP){
		cout << "gute Höhe!" << endl;
		fsm->setCurrent( new durchschleusen() );
	}
	else{
		fsm->setCurrent( new ausschleusen() );
	}
}
void Band1_hoehenmessung :: exit(Machine1 * fsm){
	cout << "Band1_hoehenmessung: exit" << endl;
	(*cc).engineReset();
	(*cc).engineRight();
}


//functions for durchschleusen
void durchschleusen :: ls_b3(Machine1 * fsm){
	cout << "durchschleusen: LS_B3 wurde ausgelöst" << endl;
	(*cc).openSwitch();
	fsm->setCurrent(new durchschleusen_bei_LS3() );
}
void durchschleusen :: entry(Machine1 * fsm){
	cout << "durchschleusen: entry" << endl;

}
void durchschleusen :: exit(Machine1 * fsm){
	cout << "durchschleusen: exit" << endl;
	sleep(1);
	(*cc).closeSwitch();
}
void durchschleusen::wp_after_Switch(Machine1 * fsm){
	(*cc).closeSwitch();
	fsm->setCurrent(new durchschleusen_bei_LS3() );
}


//functions for durchschleusen_bei_LS3
void durchschleusen_bei_LS3 :: ls_b7(Machine1 * fsm){
	cout << "durchschleusen_bei_LS3: LS_B7 wurde ausgelöst" << endl;
	(*cc).engineStop();
	fsm->isOnLS7 = true;
	fsm->setCurrent(new pruef_LS7() );
}
void durchschleusen_bei_LS3 :: entry(Machine1 * fsm){
	cout << "durchschleusen_bei_LS3: entry" << endl;
}
void durchschleusen_bei_LS3 :: exit(Machine1 * fsm){
	cout << "durchschleusen_bei_LS3: exit" << endl;
}

//functions for pruef_LS7
void pruef_LS7 :: entry(Machine1 * fsm){
	cout << "pruef_LS7: entry" << endl;
}
void pruef_LS7 :: exit(Machine1 * fsm){
	cout << "pruef_LS7: exit" << endl;
}


//functions for ausschleusen
void ausschleusen :: ls_b3 (Machine1 * fsm){
	cout << "ausschleusen: LS_B3" << endl;
	(*cc).engineRight();
	fsm->setCurrent(new Weiche_zu() );
}

void ausschleusen :: entry (Machine1 * fsm){
	cout << "ausschleusen: entry" << endl;
}
void ausschleusen :: exit (Machine1 * fsm){
	cout << "ausschleusen: exit" << endl;
}


//functions for Weiche_zu
void Weiche_zu :: ls_b6 (Machine1 * fsm){
	cout << "Weiche_zu: LS_B6" << endl;
	(*cc).engineStop();
	fsm->setCurrent(new WS_im_Schacht() );

}
void Weiche_zu :: entry (Machine1 * fsm){
	cout << "Weiche_zu: entry" << endl;
}
void Weiche_zu :: exit (Machine1 * fsm){
	cout << "Weiche_zu: exit" << endl;
}


//functions for WS_im_Schacht
void WS_im_Schacht :: entry (Machine1 * fsm){
	cout << "WS_im_Schacht: entry" << endl;
	fsm->setCurrent(new pruef_schacht_voll() );
}
void WS_im_Schacht :: exit (Machine1 * fsm){
	cout << "WS_im_Schacht: exit" << endl;
}



//functions for pruef_schacht_voll
void pruef_schacht_voll :: entry (Machine1 * fsm){
	cout << "pruef_schacht_voll: entry" << endl;
	sleep(2);

	if( (*cc).isSlideFull() ){
		fsm->setCurrent( new ErrorState() );
	}
}
void pruef_schacht_voll :: exit (Machine1 * fsm){
	cout << "pruef_schacht_voll: exit" << endl;
}


//functions for errorState
void ErrorState :: entry (Machine1 * fsm){
	cout << "pruef_schacht_voll: errorState" << endl;
	(*cc).shine(RED);
}
void ErrorState :: exit (Machine1 * fsm){
	cout << "pruef_schacht_voll: errorState" << endl;
}

//functions for Machine
void Machine1::ls_b1(){
	current->ls_b1(this);
}
void Machine1::ls_b3(){
	current->ls_b3(this);
}
void Machine1::ls_b6(){
	current->ls_b6(this);
}
void Machine1::ls_b7(){
	current->ls_b7(this);
}
void Machine1::entry(){
	current->entry(this);
}
void Machine1::exit(){
	current->exit(this);
}
void Machine1::setCurrent(State_M1 *s){
	current->exit(this);
	current = s;
    this->entry();
}
void Machine1::wp_after_Switch(){
	current->wp_after_Switch(this);
}
void Machine1::errorState(){
	current->errorState(this);
}
