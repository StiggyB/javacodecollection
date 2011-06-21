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
 * Class for machine 1 - sort out WP with correct/incorrect height
 *
 *
 */

//TODO // stop all timer, wenn band 1 auf band2 wartet
#include "Puck_FSM_1.h"


Puck_FSM_1::Puck_FSM_1(std::vector<Puck_FSM*>* puck_listobj) {
	puck_list = puck_listobj;
	current = new FSM_1_start_state;
	current->entry(this);
	minTimerId = timer->getnextid();
	maxTimerId = timer->getnextid();
	printf("my minTimerid: %i, maxTimer: %i\n", minTimerId, maxTimerId);
	checkSlide_TID = timer->getnextid();
	closeSwitch_TID = timer->getnextid();
#ifdef PUCK_FSM_1_DEBUG
	printf("FSM Band1 is up\n");
#endif
}

Puck_FSM_1::~Puck_FSM_1() {

}

//functions for Start_M1
void FSM_1_start_state::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: entry" << endl;
#endif
	fsm->location = ON_FIRST_LB;
	fsm->engine_should_be_started = true;
}
void FSM_1_start_state::ls_b0(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: LS_B0 wurde ausgelöst" << endl;
#endif
	if (fsm->check_last_lb() == 0) {
		fsm->setCurrent(new FSM_1_after_ls_b0());
	}//if
}
void FSM_1_start_state::ls_b7_out(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: ls_b7_out" << endl;
#endif
	if (fsm->check_last_lb() == 0) {
		fsm->setCurrent(new FSM_1_after_ls_b0());
	}//if
}
void FSM_1_start_state::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_start_state: exit" << endl;
#endif
	//Callback in errorState in reference time x
	fsm->setDummyTimer(MIN_TIME_B1);
	fsm->setErrorStateTimer(MAX_TIME_B1);
}

//functions for Band1_aufgelegt
void FSM_1_after_ls_b0::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: entry" << endl;
#endif
	fsm->location = AFTER_FIRST_LB;
	fsm->engine_should_be_started = 1;
	fsm->starts_engine_if_nessecary();

}
void FSM_1_after_ls_b0::ls_b1(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: LS_B1 wurde ausgelöst" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->setCurrent(new FSM_1_height_measure());
}
void FSM_1_after_ls_b0::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_after_ls_b0::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_after_ls_b0: exit" << endl;
#endif
}

//functions for Band1_hoehenmessung
void FSM_1_height_measure::entry(Puck_FSM * fsm) {
	fsm->timer->deleteTimer(fsm->maxTimerId);
	int height = fsm->hc->identifyHeight();
	fsm->location = AFTER_HEIGH_MEASURE;

#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_height_measure: entry" << endl;
	cout << "height: " << height << endl;
#endif
	if (height == NORMAL_WP || height == POCKET_WP) {
		if (height == POCKET_WP) {
			fsm->hasPocket = 1;
		}//if
		fsm->setCurrent(new FSM_1_correct_height());
	} else {
		fsm->setCurrent(new FSM_1_sort_out());
	}//if
}
void FSM_1_height_measure::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_height_measure: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_height_measure::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_height_measure: exit" << endl;
#endif
	//Callback in errorState in reference time x
	fsm->setDummyTimer(MIN_TIME_B3);
	fsm->setErrorStateTimer(MAX_TIME_B3);
}

//functions for ausschleusen
void FSM_1_sort_out::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: entry" << endl;
#endif
}
void FSM_1_sort_out::ls_b3(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: LS_B3" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->location = AFTER_METAL_SENSOR;
	fsm->engine_should_be_started = 1;
	fsm->starts_engine_if_nessecary();
	fsm->lamp->shine(YELLOW);
	fsm->setCurrent(new FSM_1_ls_b3_passed_sort_out());
}
void FSM_1_sort_out::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_sort_out::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_sort_out: exit" << endl;
#endif
	fsm->setDummyTimer(MIN_TIME_B6);
	fsm->setErrorStateTimer(MAX_TIME_B6);
}

//functions for Weiche_zu
void FSM_1_ls_b3_passed_sort_out::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: entry" << endl;
#endif
}
void FSM_1_ls_b3_passed_sort_out::ls_b6(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: LS_B6" << endl;
#endif

	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->location = SORT_OUT;
	fsm->starts_engine_if_nessecary();
	fsm->setCurrent(new FSM_1_wp_in_slide());
}
void FSM_1_ls_b3_passed_sort_out::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_ls_b3_passed_sort_out::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed: exit" << endl;
#endif
}

//functions for WS_im_Schacht
void FSM_1_wp_in_slide::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_wp_in_slide: entry" << endl;
#endif
	fsm->setCurrent(new FSM_1_check_slide());
}
void FSM_1_wp_in_slide::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_wp_in_slide: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_wp_in_slide::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_wp_in_slide: exit" << endl;
#endif
}

//functions for pruef_schacht_voll
void FSM_1_check_slide::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_check_slide: entry" << endl;
#endif
	CallInterface<CallBackThrower, void>* checkSlide = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<Puck_FSM, void>::makeFunctor(
			fsm, &Puck_FSM::isSlideFull);
	fsm->timer->addTimerFunction(checkSlide, MAX_TIME_IN_SLIDE,
			fsm->checkSlide_TID);
}

void FSM_1_check_slide::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_check_slide: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}

void FSM_1_check_slide::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_check_slide: exit" << endl;
#endif
}

//functions for durchschleusen
void FSM_1_correct_height::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: entry" << endl;
#endif
}
void FSM_1_correct_height::ls_b3(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: LS_B3 wurde ausgelöst" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->location = AFTER_METAL_SENSOR_FORWARD;
	fsm->hc->openSwitch();
	fsm->setCurrent(new FSM_1_ls_b3_passed_correct_height());
}
void FSM_1_correct_height::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_correct_height::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_correct_height: exit" << endl;
#endif
	CallInterface<CallBackThrower, void>* callCloseSwitch = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<HALCore, void>::makeFunctor(
			fsm->hc, &HALCore::closeSwitch);
	fsm->timer->addUnstoppableFunction(callCloseSwitch);
	fsm->timer->addTimerFunction(callCloseSwitch, 1000, fsm->closeSwitch_TID);
	fsm->setDummyTimer(MIN_TIME_B7);
	fsm->setErrorStateTimer(MAX_TIME_B7);
}

//functions for durchschleusen_bei_LS3
void FSM_1_ls_b3_passed_correct_height::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_correct_height: entry" << endl;
#endif
}
void FSM_1_ls_b3_passed_correct_height::ls_b7_in(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_correct_height: LS_B7 in" << endl;
#endif
	if (fsm->timer->existTimer(fsm->minTimerId)) {
		fsm->checked_to_early = true;
		fsm->errorState();
		return;
	}
	fsm->timer->deleteTimer(fsm->maxTimerId);
	fsm->hc->engineStop();
	fsm->engine_should_be_started = 0;
	fsm->location = ON_LAST_LB;
	fsm->serial->send(REQUEST_FREE, 4);
	fsm->timer->stopAll_actual_Timer();
	fsm->setCurrent(new FSM_1_end_state());
}
void FSM_1_ls_b3_passed_correct_height::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_correct_height: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_ls_b3_passed_correct_height::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ls_b3_passed_correct_height: exit" << endl;
#endif
}

//functions for pruef_LS7
void FSM_1_end_state::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: entry" << endl;
#endif
}
void FSM_1_end_state::ls_b7_out(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: ls_b7 out" << endl;
#endif
	fsm->location = AFTER_LAST_LB;
	fsm->starts_engine_if_nessecary();
	//Callback in errorState in reference time x
	fsm->setErrorStateTimer(MAX_TIME_FSM2);
}
void FSM_1_end_state::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: errorState" << endl;
#endif
	fsm->setCurrent(new FSM_1_ErrorState());
}
void FSM_1_end_state::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_end_state: exit" << endl;
#endif
}

//functions for errorState
void FSM_1_ErrorState::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ErrorState: entry" << endl;
#endif
	fsm->timer->stopAll_actual_Timer();
	fsm->setErrorNoticed(true);
	fsm->hc->engineStop();
	fsm->removeAllLights();
	fsm->lamp->flash(500, RED);
	fsm->selectErrorType();
}
void FSM_1_ErrorState::ls_b6(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ErrorState: LS_B6" << endl;
#endif
	if (fsm->errType == SLIDE_FULL_B6) {
		if (fsm->hc->checkSlide() == false) {
			//should be work without removeLight or need removeAll
			fsm->removeAllLights();
			fsm->lamp->flash(1000, RED);
			if (fsm->getErrorNoticed() == true) { //error was noticed
				fsm->noticed_error_confirmed();
			} else {
				fsm->noticed_error_confirmed();
			}//if
		}//if
	}//if
}
void FSM_1_ErrorState::reset(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ErrorState: reset_button_pushed" << endl;
#endif
	fsm->lamp->flash(1000, RED);
	fsm->noticed_error_confirmed();
}
void FSM_1_ErrorState::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_1_DEBUG
	cout << "FSM_1_ErrorState: exit" << endl;
#endif
}

