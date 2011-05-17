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
 *class for machine 2 - sort out WP with/without metal
 *
 *
 */

#include "Puck_FSM_1.h"
#include "Puck_FSM.h"
#include "iostream.h"
#include "../Lampen/Lampen.h"
#include "../Lampen/Error_State_Lamp.h"

Puck_FSM_1::Puck_FSM_1() {
	current = new FSM_1_start_state;
	current->entry(this);
	#ifdef PUCK_FSM_1_DEBUG
	printf("FSM Band1 is up\n");
	#endif
	cc = CoreController::getInstance();
}

Puck_FSM_1::~Puck_FSM_1() {

}



//functions for Start_M1
void FSM_1_start_state :: ls_b0(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Start_M1: LS_B0 wurde ausgelöst" << endl;
	#endif

	fsm->setCurrent(new FSM_1_after_ls_b0());
}
void FSM_1_start_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Start_M1: entry" << endl;
	#endif

}
void FSM_1_start_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Start_M1: exit" << endl;
	#endif
}

//functions for Band1_aufgelegt
void FSM_1_after_ls_b0 :: ls_b1(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Band1_aufgelegt: LS_B1 wurde ausgelöst" << endl;
	#endif
	fsm->pass_ls_b1 = 1;
	fsm->setCurrent(new FSM_1_height_measure() );
}
void FSM_1_after_ls_b0 :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Band1_aufgelegt: entry" << endl;
	#endif
	fsm->cc->engineReset();
	fsm->cc->engineRight();
	fsm->cc->shine(GREEN);
	fsm->engine_should_be_started = 1;
}
void FSM_1_after_ls_b0 :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Band1_aufgelegt: exit" << endl;
	#endif
}


//functions for Band1_hoehenmessung
void FSM_1_height_measure :: entry(Puck_FSM * fsm){
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	int height = fsm->cc->identifyHeight();

	#ifdef PUCK_FSM_1_DEBUG
	cout << "Band1_hoehenmessung: entry" << endl;
	cout << "height: " << height << endl;
	#endif

	if(height == NORMAL_WP || height == POCKET_WP ){
		fsm->setCurrent( new FSM_1_correct_height() );
	}
	else{
		fsm->setCurrent( new FSM_1_sort_out() );
	}
}
void FSM_1_height_measure :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Band1_hoehenmessung: exit" << endl;
	#endif
	fsm->cc->engineReset();
	fsm->cc->engineRight();
	fsm->engine_should_be_started = 1;
}


//functions for durchschleusen
void FSM_1_correct_height :: ls_b3(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen: LS_B3 wurde ausgelöst" << endl;
	#endif
	fsm->cc->openSwitch();
	fsm->setCurrent(new FSM_1_ls_b3_passed_forward() );
}
void FSM_1_correct_height :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen: entry" << endl;
	#endif

}
void FSM_1_correct_height :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen: exit" << endl;
	#endif
	sleep(1);
	fsm->cc->closeSwitch();
}


//functions for durchschleusen_bei_LS3
void FSM_1_ls_b3_passed_forward :: ls_b7_in(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen_bei_LS3: LS_B7 wurde ausgelöst" << endl;
	#endif
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->pass_ls_b7 = true;
	fsm->setCurrent(new FSM_1_end_state() );
}
void FSM_1_ls_b3_passed_forward :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen_bei_LS3: entry" << endl;
	#endif
}
void FSM_1_ls_b3_passed_forward :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "durchschleusen_bei_LS3: exit" << endl;
	#endif
}

//functions for pruef_LS7
void FSM_1_end_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "pruef_LS7: entry" << endl;
	#endif
}
void FSM_1_end_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "pruef_LS7: exit" << endl;
	#endif
}
void FSM_1_end_state :: ls_b7_out (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "pruef_LS7: ls_b7 out" << endl;
	#endif
	fsm->pass_ls_b7 = 0;
}


//functions for ausschleusen
void FSM_1_sort_out :: ls_b3 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ausschleusen: LS_B3" << endl;
	#endif
	fsm->cc->engineReset();
	fsm->cc->engineRight();
	fsm->engine_should_be_started = 1;
	fsm->cc->shine(YELLOW);
	fsm->setCurrent(new FSM_1_ls_b3_passed() );
}

void FSM_1_sort_out :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ausschleusen: entry" << endl;
	#endif
}
void FSM_1_sort_out :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ausschleusen: exit" << endl;
	#endif
}


//functions for Weiche_zu
void FSM_1_ls_b3_passed :: ls_b6 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Weiche_zu: LS_B6" << endl;
	#endif
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->setCurrent(new FSM_1_wp_in_slide() );
	fsm->pass_ls_b6 = 1;

}
void FSM_1_ls_b3_passed :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Weiche_zu: entry" << endl;
	#endif
}
void FSM_1_ls_b3_passed :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "Weiche_zu: exit" << endl;
	#endif
}


//functions for WS_im_Schacht
void FSM_1_wp_in_slide :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "WS_im_Schacht: entry" << endl;
	#endif
	fsm->setCurrent(new FSM_1_check_slide() );
}
void FSM_1_wp_in_slide :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "WS_im_Schacht: exit" << endl;
	#endif
}



//functions for pruef_schacht_voll
void FSM_1_check_slide :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "pruef_schacht_voll: entry" << endl;
	#endif
	sleep(1);

	if( fsm->cc->isSlideFull() ){
		fsm->setCurrent( new FSM_1_ErrorState() );
	}
}
void FSM_1_check_slide :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "pruef_schacht_voll: exit" << endl;
	#endif
}


//functions for errorState
void FSM_1_ErrorState :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: entry" << endl;
	#endif
	fsm->lamp.fast_blink();
	fsm->lamp.start(NULL);
	while ( fsm->cc->isSlideFull() ){
		sleep(1);
	}
	fsm->lamp.slow_blink();

}
void FSM_1_ErrorState :: ls_b6 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: LS_B6" << endl;
	#endif
	fsm->lamp.stop();

}
void FSM_1_ErrorState :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: exit" << endl;
	#endif
	fsm->lamp.stop();
}
