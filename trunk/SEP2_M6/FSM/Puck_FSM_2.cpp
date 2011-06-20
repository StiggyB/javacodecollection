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
 * class for machine 1 - sort out WP with with/without metal
 *
 *
 */

#include "Puck_FSM_2.h"

//TODO 0prio -- sector 1 implemented test & implement sector 2-4

Puck_FSM_2::Puck_FSM_2(std::vector<Puck_FSM*>* puck_listobj) {
	//	hc = HALCore::getInstance();
	//	serial = Serial::getInstance();
	puck_list = puck_listobj;
	current = new FSM_2_start_state;
	current->entry(this);
	minTimerId = timer->getnextid();
	maxTimerId = timer->getnextid();
	checkSlide_TID = timer->getnextid();
	closeSwitch_TID = timer->getnextid();
	checked_to_early = false;
#ifdef PUCK_FSM_2_DEBUG
	printf("FSM Band2 is up\n");
#endif
}
Puck_FSM_2::~Puck_FSM_2() {

}

//functions for FSM_2_start_state
void FSM_2_start_state::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: entry" << endl;
#endif
	fsm->location = ON_FIRST_LB;
}
void FSM_2_start_state::ls_b0(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: ls_b0" << endl;
#endif
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->serial->send(PUCK_ARRIVED, sizeof(msgType));
	fsm->setCurrent(new FSM_2_after_ls_b0());
}
void FSM_2_start_state::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_start_state::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_start_state: exit" << endl;
#endif
	//Callback in errorState in reference time x
	fsm->setDummyTimer(MIN_TIME_B1);
	fsm->setErrorStateTimer(MAX_TIME_B1);
}

//functions for FSM_2_after_ls_b0
void FSM_2_after_ls_b0::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: entry" << endl;
#endif
	fsm->location = AFTER_FIRST_LB;
	fsm->hc->engineContinue();
	fsm->hc->engineRight();
	fsm->lamp->shine(GREEN);
	fsm->engine_should_be_started = 1;
}
void FSM_2_after_ls_b0::ls_b1(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: ls_b1" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->location = AFTER_HEIGH_MEASURE;
	fsm->setCurrent(new FSM_2_after_ls_b1());
}
void FSM_2_after_ls_b0::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_after_ls_b0::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b0: exit" << endl;
#endif
	//Callback in errorState in reference time x
	fsm->setDummyTimer(MIN_TIME_B3);
	fsm->setErrorStateTimer(MAX_TIME_B3);
}

//functions for FSM_2_after_ls_b1
void FSM_2_after_ls_b1::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: entry" << endl;
#endif
}
void FSM_2_after_ls_b1::ls_b3(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: ls_b3" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->setCurrent(new FSM_2_in_metal_measure());
}
void FSM_2_after_ls_b1::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_after_ls_b1::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_ls_b1: exit" << endl;
#endif
}

//functions for FSM_2_in_metal_measure
void FSM_2_in_metal_measure::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: entry" << endl;
#endif
	fsm->engine_should_be_started = 0;
	if (fsm->hc->isMetal() && (fsm->hasPocket == 1)) {
#ifdef PUCK_FSM_2_DEBUG
		cout << "is Metall and has pocket" << endl;
#endif
		fsm->location = AFTER_METAL_SENSOR_FORWARD;
		fsm->setDummyTimer(MIN_TIME_B7);
		fsm->setErrorStateTimer(MAX_TIME_B7);
		fsm->setCurrent(new FSM_2_after_metal_measure_correct_wp());

	} else if ((fsm->hc->isMetal() == 0) && (fsm->hasPocket == 0)) {
#ifdef PUCK_FSM_2_DEBUG
		cout << "no Metall, no pocket" << endl;
#endif
		fsm->location = AFTER_METAL_SENSOR_FORWARD;
		fsm->setDummyTimer(MIN_TIME_B7);
		fsm->setErrorStateTimer(MAX_TIME_B7);
		fsm->setCurrent(new FSM_2_after_metal_measure_correct_wp());

	} else {
#ifdef PUCK_FSM_2_DEBUG
		if (fsm->hc->isMetal())
			cout << "isMetal" << endl;
		if (fsm->hasPocket)
			cout << "pocket" << endl;
#endif
		fsm->location = AFTER_METAL_SENSOR;
		fsm->setDummyTimer(MIN_TIME_B6);
		fsm->setErrorStateTimer(MAX_TIME_B6);
		fsm->setCurrent(new FSM_2_after_metal_measure_uncorrect_wp());
	}
}
void FSM_2_in_metal_measure::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_in_metal_measure::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_metal_measure: exit" << endl;
#endif
	fsm->hc->engineContinue();
	fsm->hc->engineRight();
	fsm->engine_should_be_started = 1;
	//Callback in errorState in reference time x

}

//functions for ausschleusen
void FSM_2_after_metal_measure_uncorrect_wp::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: entry" << endl;
#endif
	fsm->lamp->shine(YELLOW);
}
void FSM_2_after_metal_measure_uncorrect_wp::ls_b6(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: ls_b3" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->location = SORT_OUT;
	fsm->setCurrent(new FSM_2_wp_in_slide());
}
void FSM_2_after_metal_measure_uncorrect_wp::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_after_metal_measure_uncorrect_wp::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_sort_out: exit" << endl;
#endif
}

//functions for WS_im_Schacht
void FSM_2_wp_in_slide::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: entry" << endl;
#endif
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->setCurrent(new FSM_2_check_slide());
}
void FSM_2_wp_in_slide::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_wp_in_slide::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_in_slide: exit" << endl;
#endif
}

//functions for pruef_schacht_voll
void FSM_2_check_slide::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_check_slide: entry" << endl;
#endif
	CallInterface<CallBackThrower, void>* checkSlide = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<Puck_FSM, void>::makeFunctor(
			fsm, &Puck_FSM::isSlideFull);
	fsm->timer->addTimerFunction(checkSlide, MAX_TIME_IN_SLIDE, fsm->checkSlide_TID);
}
void FSM_2_check_slide::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_check_slide: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_check_slide::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_check_slide: exit" << endl;
#endif
}

//functions for FSM_2_after_metal_measure
void FSM_2_after_metal_measure_correct_wp::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: entry" << endl;
#endif
	fsm->hc->openSwitch();
	CallInterface<CallBackThrower, void>* callCloseSwitch = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<HALCore, void>::makeFunctor(
			fsm->hc, &HALCore::closeSwitch);
	fsm->timer->addTimerFunction(callCloseSwitch, 1000, fsm->closeSwitch_TID);
}
void FSM_2_after_metal_measure_correct_wp::ls_b7_in(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: ls_b7_in" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->location = ON_LAST_LB;
	fsm->setCurrent(new FSM_2_end_state());
}
void FSM_2_after_metal_measure_correct_wp::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}

void FSM_2_after_metal_measure_correct_wp::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_after_metal_measure: exit" << endl;
#endif
}

//functions for FSM_2_end_state
void FSM_2_end_state::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: entry" << endl;
#endif
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
}
void FSM_2_end_state::ls_b7_out(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: ls_b7_out" << endl;
#endif
	fsm->location = AFTER_LAST_LB;
	fsm->delete_unnecessary_wp();
	fsm->puck_fsm2_outgoing();
}
void FSM_2_end_state::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_2_ErrorState());
}
void FSM_2_end_state::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_end_state: exit" << endl;
#endif
}

//functions for ErrorState
void FSM_2_ErrorState::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_ErrorState: entry" << endl;
#endif
	//	fsm->timer->stopAll_actual_Timer();
	fsm->setErrorNoticed(true);
	cout << "fsm->errorNoticed = true: " << fsm->getErrorNoticed() << endl;
	fsm->hc->engineStop();
	fsm->removeAllLights();
	fsm->lamp->flash(500, RED);
	fsm->selectErrorType();
}
void FSM_2_ErrorState::ls_b6(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_ErrorState: LS_B6" << endl;
#endif
	if (fsm->errType == SLIDE_FULL_B6) {
		if (fsm->hc->checkSlide() == false) {
			cout << "slide is now free" << endl;
			fsm->removeAllLights();
			fsm->lamp->flash(1000, RED);

			if(fsm->getErrorNoticed() == true ){ //error was noticed
				fsm->noticed_error_confirmed();
			} else {
				fsm->noticed_error_confirmed();
			}//if

		}//if
	}//if
}
void FSM_2_ErrorState::reset(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_ErrorState: reset" << endl;
#endif
	fsm->lamp->flash(1000, RED);
	fsm->noticed_error_confirmed();
}
void FSM_2_ErrorState::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_2_DEBUG
	cout << "FSM_2_ErrorState: exit" << endl;
#endif
}

