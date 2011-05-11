/*
 * Machine2.cpp
 *
 *  Created on: 10.05.2011
 *      Author: user
 */

#include "Machine2.h"

Machine2::Machine2() {
	hasPocket = false;
	isOnLS7 = false;
	printf("FSM Band2 is up\n");
	cc = CoreController::getInstance();
	current = new Start_M2;
	current->entry(this);
}

Machine2::~Machine2() {
	// TODO Auto-generated destructor stub
}

State_M2::State_M2(){
	cc = CoreController::getInstance();
}

State_M2::~State_M2(){

}

void State_M2::ls_b0(Machine2 *){ printf("LS_B1 standard function\n"); }
void State_M2::ls_b1(Machine2 *){ printf("LS_B1 standard function\n"); }
void State_M2::ls_b3(Machine2 *){ printf("LS_B3 standard function\n"); }
void State_M2::ls_b6(Machine2 *){ printf("LS_B6 standard function\n"); }
void State_M2::ls_b7(Machine2 *){ printf("LS_B7 standard function\n"); }
void State_M2::entry(Machine2 *){ printf("entry standard function\n"); }
void State_M2::exit(Machine2 *){ printf("exit standard function\n"); }
void State_M2::errorState(Machine2 *){ printf("errorState standard function\n"); }

//functions for
void Start_M2 :: ls_b0(Machine2 * fsm){
	cout << "Start_M2: ls_b0" << endl;
	(*cc).engineReset();
	(*cc).engineRight();
	fsm->setCurrent(new Band_2_aufgelegt() );
}
void Start_M2 :: entry(Machine2 * fsm){
	cout << "Start_M2: entry" << endl;
	(*cc).shine(GREEN);
}
void Start_M2 :: exit(Machine2 * fsm){
	cout << "Start_M2: exit" << endl;
}

//functions for Band_2_aufgelegt
void Band_2_aufgelegt :: entry(Machine2 * fsm){
	cout << "Band_2_aufgelegt: entry" << endl;
}
void Band_2_aufgelegt :: exit(Machine2 * fsm){
	cout << "Band_2_aufgelegt: exit" << endl;
}
void Band_2_aufgelegt :: ls_b1(Machine2 * fsm){
	cout << "Band_2_aufgelegt: ls_b1" << endl;
	fsm->setCurrent(new Bei_LS1() );
}


//functions for Bei_LS1
void Bei_LS1 :: entry(Machine2 * fsm){
	cout << "Bei_LS1: entry" << endl;
}
void Bei_LS1 :: exit(Machine2 * fsm){
	cout << "Bei_LS1: exit" << endl;
}
void Bei_LS1 :: ls_b3(Machine2 * fsm){
	cout << "Bei_LS1: ls_b3" << endl;
	fsm->setCurrent(new In_Metallmessung() );
}



//functions for In_Metallmessung
void In_Metallmessung :: entry(Machine2 * fsm){
	cout << "In_Metallmessung: entry" << endl;
	(*cc).engineStop();
	if( ( ((*cc).read(0x300+1)>>4)&1 ) == 1 && (fsm->hasPocket==1) ){
		cout << "is Metall" << endl;
		fsm->setCurrent(new durchschleusen_M2() );
	} else if( ( ((*cc).read(0x300+1)>>4)&1 ) == 0 && (fsm->hasPocket==0) ) {
		cout << "is kein Metall, kein Loch" << endl;
		fsm->setCurrent(new durchschleusen_M2() );
	} else {
		cout << "is kein Metall, hat aber Loch" << endl;
		fsm->setCurrent(new ausschleusen_M2() );
	}

}
void In_Metallmessung :: exit(Machine2 * fsm){
	cout << "In_Metallmessung: exit" << endl;
	(*cc).engineReset();
	(*cc).engineRight();
}

//functions for durchschleusen
void durchschleusen_M2 :: entry(Machine2 * fsm){
	cout << "durchschleusen: entry" << endl;
	if ((*cc).openSwitch() ) cout << "Weiche auf Durchlass" << endl;
	sleep(1);
	(*cc).closeSwitch();
}
void durchschleusen_M2 :: exit(Machine2 * fsm){
	cout << "durchschleusen: exit" << endl;

}
void durchschleusen_M2 :: ls_b7(Machine2 * fsm){
	cout << "durchschleusen: ls_b7" << endl;
	fsm->setCurrent(new Ende_Band2() );
}



//functions for Ende_Band2
void Ende_Band2 :: entry(Machine2 * fsm){
	cout << "Ende_Band2: entry" << endl;
	(*cc).engineStop();
}
void Ende_Band2 :: exit(Machine2 * fsm){
	cout << "Ende_Band2: exit" << endl;
}
void Ende_Band2 :: ls_b7(Machine2 * fsm){
	cout << "Ende_Band2: ls_b7" << endl;
}


//functions for ausschleusen
void ausschleusen_M2 :: entry(Machine2 * fsm){
	cout << "ausschleusen: entry" << endl;
	(*cc).shine(YELLOW);
}
void ausschleusen_M2 :: exit(Machine2 * fsm){
	cout << "ausschleusen: exit" << endl;
}
void ausschleusen_M2 :: ls_b6(Machine2 * fsm){
	cout << "ausschleusen: ls_b3" << endl;
	fsm->setCurrent(new WS_im_Schacht_M2() );
}


//functions for WS_im_Schacht
void WS_im_Schacht_M2 :: entry(Machine2 * fsm){
	cout << "WS_im_Schacht: entry" << endl;
	(*cc).engineStop();
	fsm->setCurrent(new pruef_schacht_voll_M2() );
}
void WS_im_Schacht_M2 :: exit(Machine2 * fsm){
	cout << "WS_im_Schacht: exit" << endl;
}

//functions for pruef_schacht_voll
void pruef_schacht_voll_M2 :: entry(Machine2 * fsm){
	cout << "pruef_schacht_voll: entry" << endl;

	sleep(2);
	if( (*cc).isSlideFull() ){
		fsm->setCurrent( new ErrorState_M2() );
	}

}
void pruef_schacht_voll_M2 :: exit(Machine2 * fsm){
	cout << "pruef_schacht_voll: exit" << endl;

}

//functions for ErrorState
void ErrorState_M2 :: entry(Machine2 * fsm){
	cout << "ErrorState: entry" << endl;
	(*cc).shine(RED);
}
void ErrorState_M2 :: exit(Machine2 * fsm){
	cout << "ErrorState: exit" << endl;
}

//functions for Machine
void Machine2::ls_b0(){
	current->ls_b0(this);
}
void Machine2::ls_b1(){
	current->ls_b1(this);
}
void Machine2::ls_b3(){
	current->ls_b3(this);
}
void Machine2::ls_b6(){
	current->ls_b6(this);
}
void Machine2::ls_b7(){
	current->ls_b7(this);
}
void Machine2::entry(){
	current->entry(this);
}
void Machine2::exit(){
	current->exit(this);
}
void Machine2::setCurrent(State_M2 *s){
	current->exit(this);
	current = s;
    this->entry();
}
void Machine2::errorState(){
	current->errorState(this);
}
void Machine2::setPocket(){
	cout << "setPocket: has Pocket now" << endl;
	hasPocket = true;
}


