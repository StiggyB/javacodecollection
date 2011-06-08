/**
 * Puck_FSM 1
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
 * class for machine 1 - sort out WP with correct/incorrect height
 *
 *
 */

#include "Puck_FSM_1.h"

Puck_FSM_1::~Puck_FSM_1() {

}

Puck_FSM_1::Puck_FSM_1(std::vector<Puck_FSM*>* puck_listobj){
//	hc = HALCore::getInstance();
//	serial = Serial::getInstance();
	puck_list = puck_listobj;
	current = new FSM_1_start_state;
	current->entry(this);
	#ifdef PUCK_FSM_1_DEBUG
	printf("FSM Band1 is up\n");
	#endif
}


//functions for Start_M1
void FSM_1_start_state :: ls_b0(Puck_FSM * fsm){
    cout << "FSM_1_start_state: LS_B0 wurde ausgelöst" << endl;

    if( fsm->check_last_lb() == 0){
        fsm->setCurrent(new FSM_1_after_ls_b0());
    }//if

}
void FSM_1_start_state :: ls_b7_out(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: ls_b7_out" << endl;
	#endif

    if( fsm->check_last_lb() == 0){
        fsm->setCurrent(new FSM_1_after_ls_b0());
    }//if

}
void FSM_1_start_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: entry" << endl;
	#endif
	fsm->location = ON_FIRST_LB;
	fsm->engine_should_be_started = true;
}
void FSM_1_start_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: exit" << endl;
	#endif
}

//functions for Band1_aufgelegt
void FSM_1_after_ls_b0 :: ls_b1(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: LS_B1 wurde ausgelöst" << endl;
	#endif
	fsm->setCurrent(new FSM_1_height_measure() );
}
void FSM_1_after_ls_b0 :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: entry" << endl;
	#endif
	fsm->location = AFTER_FIRST_LB;
	fsm->hc->engineContinue();
	fsm->hc->engineRight();
	fsm->engine_should_be_started = 1;
}
void FSM_1_after_ls_b0 :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: exit" << endl;
	#endif
}


//functions for Band1_hoehenmessung
void FSM_1_height_measure :: entry(Puck_FSM * fsm){
	int height = fsm->hc->identifyHeight();
	fsm->location = AFTER_HEIGH_MEASURE;

	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_height_measure: entry" << endl;
	cout << "height: " << height << endl;
	#endif

	if(height == NORMAL_WP || height == POCKET_WP ){
		if(height == POCKET_WP){
			fsm->hasPocket = 1;
		}//if
		fsm->setCurrent( new FSM_1_correct_height() );
	}
	else{
		fsm->setCurrent( new FSM_1_sort_out() );
	}//if
}
void FSM_1_height_measure :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_height_measure: exit" << endl;
	#endif
}


//functions for durchschleusen
void FSM_1_correct_height :: ls_b3(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: LS_B3 wurde ausgelöst" << endl;
	#endif
	fsm->location = AFTER_METAL_SENSOR_FORWARD;
	fsm->hc->openSwitch();
	fsm->setCurrent(new FSM_1_ls_b3_passed_forward() );
}
void FSM_1_correct_height :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: entry" << endl;
	#endif

}
void FSM_1_correct_height :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: exit" << endl;
	#endif
	sleep(1);
	fsm->hc->closeSwitch();
}


//functions for durchschleusen_bei_LS3
void FSM_1_ls_b3_passed_forward :: ls_b7_in(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_forward: LS_B7 wurde ausgelöst" << endl;
	#endif
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->location = ON_LAST_LB;
	fsm->serial->send(REQUEST_FREE, 4);
	fsm->setCurrent(new FSM_1_end_state() );
}
void FSM_1_ls_b3_passed_forward :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_forward: entry" << endl;
	#endif
}
void FSM_1_ls_b3_passed_forward :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_forward: exit" << endl;
	#endif
}

//functions for pruef_LS7
void FSM_1_end_state :: entry(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: entry" << endl;
	#endif
}
void FSM_1_end_state :: exit(Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: exit" << endl;
	#endif
}
void FSM_1_end_state :: ls_b7_out (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: ls_b7 out" << endl;
	#endif
	fsm->location = AFTER_LAST_LB;
	fsm->starts_engine_if_nessecary();
}


//functions for ausschleusen
void FSM_1_sort_out :: ls_b3 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: LS_B3" << endl;
	#endif
	fsm->location = AFTER_METAL_SENSOR_SORT_OUT;
	fsm->hc->engineReset();
	fsm->hc->engineRight();
	fsm->engine_should_be_started = 1;
	fsm->lamp->shine(YELLOW);
	fsm->setCurrent(new FSM_1_ls_b3_passed() );
}

void FSM_1_sort_out :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: entry" << endl;
	#endif
}
void FSM_1_sort_out :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: exit" << endl;
	#endif
}


//functions for Weiche_zu
void FSM_1_ls_b3_passed :: ls_b6 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: LS_B6" << endl;
	#endif
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->location = SORT_OUT;
	fsm->starts_engine_if_nessecary();
	fsm->delete_unnecessary_wp();
	fsm->setCurrent(new FSM_1_wp_in_slide() );

}
void FSM_1_ls_b3_passed :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: entry" << endl;
	#endif
}
void FSM_1_ls_b3_passed :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: exit" << endl;
	#endif
}


//functions for WS_im_Schacht
void FSM_1_wp_in_slide :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_wp_in_slide: entry" << endl;
	#endif
	fsm->setCurrent(new FSM_1_check_slide() );
}
void FSM_1_wp_in_slide :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_wp_in_slide: exit" << endl;
	#endif
}


//functions for pruef_schacht_voll
void FSM_1_check_slide :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_check_slide: entry" << endl;
	#endif
//	Puck_FSM_1 fsm_1;
//	CallInterface<Puck_FSM_1, void>* checkTime =
//				FunctorMaker<Puck_FSM_1, void>::makeFunctor(&this, &Puck_FSM_1::checkSlide);
//	timer->addTimerFunction(checkTime, 50);

//	if( checkSlide() ){
//		fsm->setCurrent( new FSM_1_ErrorState() );
//	}
	fsm->delete_unnecessary_wp();
	fsm->lamp->shine(GREEN);
}
void FSM_1_check_slide :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_check_slide: exit" << endl;
	#endif
}


//functions for errorState
void FSM_1_ErrorState :: entry (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: entry" << endl;
	#endif
	fsm->lamp->flash(500,RED);
	//fsm->lamp.fast_blink();
	//fsm->lamp.start(NULL);
//	while ( fsm->hc->isSlideFull() ){
//		sleep(1);
//	}
	fsm->lamp->flash(1000,RED);
	//fsm->lamp.slow_blink();
}
void FSM_1_ErrorState :: ls_b6 (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: LS_B6" << endl;
	#endif
	fsm->lamp->removeLight(RED);
	//fsm->lamp->stop();

}
void FSM_1_ErrorState :: exit (Puck_FSM * fsm){
	#ifdef PUCK_FSM_1_DEBUG
	cout << "ErrorState: exit" << endl;
	#endif
	fsm->lamp->removeLight(RED);
	//fsm->lamp.stop();
}

//TODO lookup a better position (redundant)
void Puck_FSM_1::checkSlide() {
	if( hc->checkSlide() ){
		setCurrent( new FSM_1_ErrorState() );
	}
}

