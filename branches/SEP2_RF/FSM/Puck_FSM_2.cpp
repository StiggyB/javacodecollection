/**
 * Puck_FSM 2
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
 *class for machine 1 - sort out WP with with/without metal
 *
 *
 */

#include "Puck_FSM_2.h"

Puck_FSM_2::~Puck_FSM_2() {

}


Puck_FSM_2::Puck_FSM_2(std::vector<Puck_FSM*>* puck_listobj){
//	hc = HALCore::getInstance();
//	serial = Serial::getInstance();
	puck_list = puck_listobj;
	current = new FSM_2_start_state;
	current->entry(this);
	#ifdef PUCK_FSM_2_DEBUG
	printf("FSM Band2 is up\n");
	#endif
}




//functions for FSM_2_start_state
void FSM_2_start_state :: ls_b0(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: ls_b0" << endl;
	#endif
	fsm->serial->send(PUCK_ARRIVED, sizeof(msgType));
	fsm->setCurrent(new FSM_2_after_ls_b0() );
}
void FSM_2_start_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: entry" << endl;
	#endif
	fsm->location = ON_FIRST_LB;
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
	fsm->location = AFTER_FIRST_LB;
	fsm->hc->engineContinue();
	fsm->hc->engineRight();
	fsm->lamp->shine(GREEN);
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
	fsm->location = AFTER_HEIGH_MEASURE;
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
	fsm->setCurrent(new FSM_2_in_metal_measure() );
}



//functions for FSM_2_in_metal_measure
void FSM_2_in_metal_measure :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: entry" << endl;
	#endif
	//fsm->cc->engineStop();
	fsm->engine_should_be_started = 0;
	if( fsm->hc->isMetal() && ( fsm->hasPocket==1) ){
		#ifdef PUCK_FSM_2_DEBUG
		cout << "is Metall and has pocket" << endl;
		#endif
		fsm->location = AFTER_METAL_SENSOR_FORWARD;
		fsm->setCurrent(new FSM_2_after_metal_measure() );

	} else if( (fsm->hc->isMetal() == 0) && (fsm->hasPocket==0) ) {
		#ifdef PUCK_FSM_2_DEBUG
		cout << "no Metall, no pocket" << endl;
		#endif
		fsm->location = AFTER_METAL_SENSOR_FORWARD;
		fsm->setCurrent(new FSM_2_after_metal_measure() );

	} else {
		#ifdef PUCK_FSM_2_DEBUG
		if( fsm->hc->isMetal() )cout << "isMetal" << endl;
		if( fsm->hasPocket ) cout << "pocket" << endl;
		#endif
		fsm->location = AFTER_METAL_SENSOR_SORT_OUT;
		fsm->setCurrent(new FSM_2_sort_out() );
	}

}
void FSM_2_in_metal_measure :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: exit" << endl;
	#endif
	fsm->hc->engineContinue();
	fsm->hc->engineRight();
	fsm->engine_should_be_started = 1;
}

//functions for FSM_2_after_metal_measure
void FSM_2_after_metal_measure :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: entry" << endl;
	#endif
	fsm->hc->openSwitch();
	CallInterface<CallBackThrower, void>* callCloseSwitch = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<HALCore, void>::makeFunctor(
			fsm->hc, &HALCore::closeSwitch);
	fsm->timer->addTimerFunction(callCloseSwitch, 1000);
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
	fsm->location = ON_LAST_LB;
	fsm->setCurrent(new FSM_2_end_state() );
}



//functions for FSM_2_end_state
void FSM_2_end_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: entry" << endl;
	#endif
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
}
void FSM_2_end_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: exit" << endl;
	#endif
}
void FSM_2_end_state :: ls_b7_out(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: ls_b7_out" << endl;
	#endif
	fsm->location = AFTER_LAST_LB;
	fsm->puck_fsm2_outgoing();
	fsm->delete_unnecessary_wp();
}


//functions for ausschleusen
void FSM_2_sort_out :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: entry" << endl;
	#endif
	fsm->lamp->shine(YELLOW);
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
	fsm->location = SORT_OUT;
	fsm->puck_fsm2_outgoing();
	fsm->setCurrent(new FSM_2_in_slide() );
}


//functions for WS_im_Schacht
void FSM_2_in_slide :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: entry" << endl;
	#endif
	fsm->hc->engineStop();
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
//	CallInterface<Puck_FSM_2, void> checkTime =
//				FunctorMaker<Puck_FSM_2, void>::makeFunctor(fsm,
//						&Puck_FSM_2::checkSlide);
//	timer->addTimerFunction(checkTime, 50);

//	sleep(2);
//	if( fsm->hc->isSlideFull() ){
//		fsm->setCurrent( new FSM_2_ErrorState() );
//	}
	fsm->delete_unnecessary_wp();
	fsm->lamp->shine(GREEN);
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
	fsm->lamp->shine(RED);
}
void FSM_2_ErrorState :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_2_DEBUG
	cout << "ErrorState: exit" << endl;
	#endif
}

//TODO lookup a better position (redundant)
void Puck_FSM_2::checkSlide() {
	if( hc->checkSlide() ){
		setCurrent( new FSM_2_ErrorState() );
	}
}

