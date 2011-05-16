/*
 * Puck_FSM_2.cpp
 *
 *  Created on: 13.05.2011
 *      Author: user
 */

#include "Puck_FSM_2.h"
#include "Puck_FSM.h"
#include "iostream.h"
#include "../Lampen/Lampen.h"
#include "../Lampen/Error_State_Lamp.h"

Puck_FSM_2::Puck_FSM_2() {
	current = new FSM_2_start_state;
	current->entry(this);
	printf("FSM Band2 is up\n");
	cc = CoreController::getInstance();

}

Puck_FSM_2::~Puck_FSM_2() {

}


//functions for FSM_2_start_state
void FSM_2_start_state :: ls_b0(Puck_FSM * fsm){
	cout << "FSM_2_start_state: ls_b0" << endl;
	fsm->setCurrent(new FSM_2_after_ls_b0() );
}
void FSM_2_start_state :: entry(Puck_FSM * fsm){
	cout << "FSM_2_start_state: entry" << endl;
}
void FSM_2_start_state :: exit(Puck_FSM * fsm){
	cout << "FSM_2_start_state: exit" << endl;
}

//functions for Band_2_aufgelegt
void FSM_2_after_ls_b0 :: entry(Puck_FSM * fsm){
	cout << "FSM_2_after_ls_b0: entry" << endl;
	fsm->cc->shine(GREEN);
	fsm->cc->engineReset();
	fsm->cc->engineRight();
	fsm->engine_should_be_started = 1;
}
void FSM_2_after_ls_b0 :: exit(Puck_FSM * fsm){
	cout << "Band_2_aufgelegt: exit" << endl;
}
void FSM_2_after_ls_b0 :: ls_b1(Puck_FSM * fsm){
	cout << "Band_2_aufgelegt: ls_b1" << endl;
	fsm->pass_ls_b1 = 1;
	fsm->setCurrent(new FSM_2_after_ls_b1() );
}


//functions for Bei_LS1
void FSM_2_after_ls_b1 :: entry(Puck_FSM * fsm){
	cout << "Bei_LS1: entry" << endl;
}
void FSM_2_after_ls_b1 :: exit(Puck_FSM * fsm){
	cout << "Bei_LS1: exit" << endl;
}
void FSM_2_after_ls_b1 :: ls_b3(Puck_FSM * fsm){
	cout << "Bei_LS1: ls_b3" << endl;
	fsm->pass_ls_b3 = 1;
	fsm->setCurrent(new FSM_2_in_metal_measure() );
}



//functions for In_Metallmessung
void FSM_2_in_metal_measure :: entry(Puck_FSM * fsm){
	cout << "In_Metallmessung: entry" << endl;
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	if( fsm->cc->isMetal() && ( fsm->hasPocket==1) ){ //eigene funktion in der HAL!
		cout << "is Metall" << endl;
		fsm->setCurrent(new FSM_2_after_metal_measure() );
	} else if( ( (fsm->cc->read(0x300+1)>>4)&1 ) == 0 && (fsm->hasPocket==0) ) {
		cout << "no Metall, no pocket" << endl;
		fsm->setCurrent(new FSM_2_after_metal_measure() );
	} else {
		cout << "Metall, but pocket" << endl;
		fsm->setCurrent(new FSM_2_sort_out() );
	}

}
void FSM_2_in_metal_measure :: exit(Puck_FSM * fsm){
	cout << "In_Metallmessung: exit" << endl;
	fsm->cc->engineReset();
	fsm->cc->engineRight();
	fsm->engine_should_be_started = 1;
}

//functions for durchschleusen
void FSM_2_after_metal_measure :: entry(Puck_FSM * fsm){
	cout << "durchschleusen: entry" << endl;
	if (fsm->cc->openSwitch() ) cout << "Weiche auf Durchlass" << endl;
	sleep(1);
	fsm->cc->closeSwitch();
}
void FSM_2_after_metal_measure :: exit(Puck_FSM * fsm){
	cout << "durchschleusen: exit" << endl;

}
void FSM_2_after_metal_measure :: ls_b7_in(Puck_FSM * fsm){
	cout << "durchschleusen: ls_b7_in" << endl;
	fsm->pass_ls_b7 = 1;
	fsm->setCurrent(new FSM_2_end_state() );
}



//functions for Ende_Band2
void FSM_2_end_state :: entry(Puck_FSM * fsm){
	cout << "Ende_Band2: entry" << endl;
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
}
void FSM_2_end_state :: exit(Puck_FSM * fsm){
	cout << "Ende_Band2: exit" << endl;
}
void FSM_2_end_state :: ls_b7_out(Puck_FSM * fsm){
	cout << "Ende_Band2: ls_b7_out" << endl;
	fsm->pass_ls_b7 = 0;
}


//functions for ausschleusen
void FSM_2_sort_out :: entry(Puck_FSM * fsm){
	cout << "FSM_2_sort_out: entry" << endl;
	fsm->cc->shine(YELLOW);
}
void FSM_2_sort_out :: exit(Puck_FSM * fsm){
	cout << "FSM_2_sort_out: exit" << endl;
}
void FSM_2_sort_out :: ls_b6(Puck_FSM * fsm){
	cout << "FSM_2_sort_out: ls_b3" << endl;
	fsm->pass_ls_b6 = 1;
	fsm->setCurrent(new FSM_2_in_slide() );
}


//functions for WS_im_Schacht
void FSM_2_in_slide :: entry(Puck_FSM * fsm){
	cout << "FSM_2_in_slide: entry" << endl;
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->setCurrent(new FSM_2_check_slide() );
}
void FSM_2_in_slide :: exit(Puck_FSM * fsm){
	cout << "FSM_2_in_slide: exit" << endl;
}

//functions for pruef_schacht_voll
void FSM_2_check_slide :: entry(Puck_FSM * fsm){
	cout << "FSM_2_check_slide: entry" << endl;

	sleep(2);
	if( fsm->cc->isSlideFull() ){
		fsm->setCurrent( new FSM_2_ErrorState() );
	}

}
void FSM_2_check_slide :: exit(Puck_FSM * fsm){
	cout << "FSM_2_check_slide: exit" << endl;

}

//functions for ErrorState
void FSM_2_ErrorState :: entry(Puck_FSM * fsm){
	cout << "FSM_2_ErrorState: entry" << endl;
	fsm->cc->shine(RED);
}
void FSM_2_ErrorState :: exit(Puck_FSM * fsm){
	cout << "ErrorState: exit" << endl;
}

