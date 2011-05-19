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
 *class for machine 1 - sort out WP with correct/incorrect height
 *
 *
 */

#include "Puck_FSM_2.h"

Puck_FSM_2::Puck_FSM_2() {
	current = new FSM_2_start_state;
	current->entry(this);
	#ifdef PUCK_FSM_2_DEBUG
	printf("FSM Band2 is up\n");
	#endif
	cc = HALCore::getInstance();

}

Puck_FSM_2::~Puck_FSM_2() {

}


//functions for FSM_2_start_state
void FSM_2_start_state :: ls_b0(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: ls_b0" << endl;
	#endif
	fsm->setCurrent(new FSM_2_after_ls_b0() );
}
void FSM_2_start_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: entry" << endl;
	#endif
}
void FSM_2_start_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: exit" << endl;
	#endif
}

//functions for FSM_2_after_ls_b0
void FSM_2_after_ls_b0 :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: entry" << endl;
	#endif
	fsm->cc->engineContinue();
	fsm->cc->engineRight();
	fsm->cc->shine(GREEN);
	fsm->engine_should_be_started = 1;
}
void FSM_2_after_ls_b0 :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: exit" << endl;
	#endif
}
void FSM_2_after_ls_b0 :: ls_b1(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: ls_b1" << endl;
	#endif
	fsm->pass_ls_b1 = 1;
	fsm->setCurrent(new FSM_2_after_ls_b1() );
}


//functions for FSM_2_after_ls_b1
void FSM_2_after_ls_b1 :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: entry" << endl;
	#endif
}
void FSM_2_after_ls_b1 :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: exit" << endl;
	#endif
}
void FSM_2_after_ls_b1 :: ls_b3(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: ls_b3" << endl;
	#endif
	fsm->pass_ls_b3 = 1;
	fsm->setCurrent(new FSM_2_in_metal_measure() );
}



//functions for FSM_2_in_metal_measure
void FSM_2_in_metal_measure :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: entry" << endl;
	#endif
	//fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	if( fsm->cc->isMetal() && ( fsm->hasPocket==1) ){
		#ifdef PUCK_FSM_2_DEBUG
		cout << "is Metall and has pocket" << endl;
		#endif
		fsm->setCurrent(new FSM_2_after_metal_measure() );

	} else if( (fsm->cc->isMetal() == 0) && (fsm->hasPocket==0) ) {
		#ifdef PUCK_FSM_2_DEBUG
		cout << "no Metall, no pocket" << endl;
		#endif
		fsm->setCurrent(new FSM_2_after_metal_measure() );

	} else {
		#ifdef PUCK_FSM_2_DEBUG
		if( fsm->cc->isMetal() )cout << "fsm->cc->isMetal(): true";
		if( fsm->hasPocket ) cout << "pocket" << endl;
		#endif
		fsm->setCurrent(new FSM_2_sort_out() );
	}

}
void FSM_2_in_metal_measure :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: exit" << endl;
	#endif
	fsm->cc->engineContinue();
	fsm->cc->engineRight();
	fsm->engine_should_be_started = 1;
}

//functions for FSM_2_after_metal_measure
void FSM_2_after_metal_measure :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: entry" << endl;
	#endif
	fsm->cc->openSwitch();
	sleep(1);
	fsm->cc->closeSwitch();
}
void FSM_2_after_metal_measure :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: exit" << endl;
	#endif
}
void FSM_2_after_metal_measure :: ls_b7_in(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: ls_b7_in" << endl;
	#endif
	fsm->pass_ls_b7 = 1;
	fsm->setCurrent(new FSM_2_end_state() );
}



//functions for FSM_2_end_state
void FSM_2_end_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: entry" << endl;
	#endif
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
}
void FSM_2_end_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: exit" << endl;
	#endif
}
void FSM_2_end_state :: ls_b7_out(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "Ende_Band2: ls_b7_out" << endl;
	#endif

	fsm->pass_ls_b7 = 0;
}


//functions for ausschleusen
void FSM_2_sort_out :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: entry" << endl;
	#endif
	fsm->cc->shine(YELLOW);
}
void FSM_2_sort_out :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: exit" << endl;
	#endif
}
void FSM_2_sort_out :: ls_b6(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: ls_b3" << endl;
	#endif
	fsm->pass_ls_b6 = 1;
	fsm->setCurrent(new FSM_2_in_slide() );
}


//functions for WS_im_Schacht
void FSM_2_in_slide :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: entry" << endl;
	#endif
	fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->setCurrent(new FSM_2_check_slide() );
}
void FSM_2_in_slide :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: exit" << endl;
	#endif
}

//functions for pruef_schacht_voll
void FSM_2_check_slide :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_check_slide: entry" << endl;
	#endif

	sleep(2);
	if( fsm->cc->isSlideFull() ){
		fsm->setCurrent( new FSM_2_ErrorState() );
	}

}
void FSM_2_check_slide :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_check_slide: exit" << endl;
	#endif

}

//functions for ErrorState
void FSM_2_ErrorState :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_ErrorState: entry" << endl;
	#endif
	fsm->cc->shine(RED);
}
void FSM_2_ErrorState :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "ErrorState: exit" << endl;
	#endif
}

