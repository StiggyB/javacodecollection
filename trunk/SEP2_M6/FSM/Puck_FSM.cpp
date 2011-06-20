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
 * interface for the finite state machine's
 *
 */
#include "Puck_FSM.h"

//Methods for class Puck_FSM
Puck_FSM::Puck_FSM() {
	hc = HALCore::getInstance();
	lamp = Lampen::getInstance();
	serial = Serial::getInstance();
	timer = Timer::getInstance();
	errType = NO_ERROR;
}

Puck_FSM::~Puck_FSM() {
}

void Puck_FSM::start_signal(bool was_serial) {
	if (!was_serial)
		serial->send(START_BUTTON, sizeof(int));
	if ((check_last_lb() == 0) && (puck_list->size() > 0)) {
		starts_engine_if_nessecary();
	} else if ((puck_list->size() == 0)) {
		lamp->shine(GREEN);
	}//if
}

void Puck_FSM::stop_signal(bool was_serial) {
	lamp->shine(RED);
	if (!was_serial)
		serial->send(STOP_BUTTON, sizeof(int));
	hc->engineStop();
}

void Puck_FSM::reset_signal(bool was_serial) {
	if (!was_serial)
		serial->send(RESET_BUTTON, sizeof(int));
}

void Puck_FSM::estop_in_signal(bool was_serial) {
	if (!was_serial)
		serial->send(E_STOP_PUSHED, sizeof(int));
	hc->emergencyStop();
}

void Puck_FSM::estop_out_signal(bool was_serial) {
	if (!was_serial)
		serial->send(E_STOP_PULLED, sizeof(int));
	hc->resetAll();
}

void Puck_FSM::isSlideFull() {
	if (hc->checkSlide()) {
		cout << "Puck_FSM::isSlideFull: errorState" << endl;
		errType = SLIDE_FULL_B6;
		errorState();
	} else {
		cout << "Puck_FSM::isSlideFull: delete_wp" << endl;
		delete_unnecessary_wp();
#ifdef PUCK_FSM_2
		puck_fsm2_outgoing();
#endif
	}
}

int Puck_FSM::setDummyTimer(ReferenceTime refTime) {
	CallInterface<CallBackThrower, void>* callDummyFunction = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<Puck_FSM, void>::makeFunctor(
			this, &Puck_FSM::dummyFunction);
	return timer->addTimerFunction(callDummyFunction, refTime, minTimerId);
}

int Puck_FSM::setErrorStateTimer(ReferenceTime refTime) {
	CallInterface<CallBackThrower, void>* callErrorState = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<Puck_FSM, void>::makeFunctor(
			this, &Puck_FSM::errorState);
	return timer->addTimerFunction(callErrorState, refTime, maxTimerId);
}

void Puck_FSM::dummyFunction() {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("Puck_FSM::dummyFunction: called\n");
#endif
}

int Puck_FSM::check_last_lb() {
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->location == ON_LAST_LB) {
			return -1;
		}//if
	}//for
	return 0;
}

void Puck_FSM::removeAllLights() {
	lamp->removeLight(GREEN);
	lamp->removeLight(YELLOW);
	lamp->removeLight(RED);
}

bool Puck_FSM::getErrorNoticed() {
	return errorNoticed;
}
void Puck_FSM::setErrorNoticed(bool errorNoticed) {
	this->errorNoticed = errorNoticed;
}

void Puck_FSM::selectErrorType() {
	if (errType != NO_ERROR) {
		return;
	}
	setErrorNoticed(true);
	if (checked_to_early == true) {
		switch (location) {
		case AFTER_FIRST_LB:
			errType = WP_UNKOWN_B1;
			cout << ">> UNKOWN WORK PIECE APPEARED BETWEEN >FIRST LIGHT BARRIER< AND >HEIGHT MEASURE< <<" << endl;
			break;
		case AFTER_HEIGH_MEASURE:
			errType = WP_UNKOWN_B3;
			cout << ">> UNKOWN WORK PIECE APPEARED BETWEEN >HEIGHT MEASURE< AND >SWITCH< <<" << endl;
			break;
		case AFTER_METAL_SENSOR:
			errType = WP_UNKOWN_B6;
			cout << ">> UNKOWN WORK PIECE APPEARED BETWEEN >SWITCH< AND >SLIDE< <<" << endl;
			timer->deleteTimer(checkSlide_TID);
			break;
		case AFTER_METAL_SENSOR_FORWARD:
			cout << ">> UNKOWN WORK PIECE APPEARED BETWEEN >SWITCH< AND >LAST LIGHT BARRIER< <<" << endl;
			errType = WP_UNKOWN_B7;
			break;
		default:
			cout << ">> UNKOWN WORK PIECE APPEARED >NO ERROR DEFINED< <<" << endl;
		}
		checked_to_early = false;
	} else {
		switch (location) {
		case AFTER_FIRST_LB:
			errType = WP_DISAPPEARED_B1;
			cout << ">> WORK PIECE DISAPPEARED BETWEEN >FIRST LIGHT BARRIER< AND >HEIGHT MEASURE< <<" << endl;
			break;
		case AFTER_HEIGH_MEASURE:
			errType = WP_DISAPPEARED_B3;
			cout << ">> WORK PIECE DISAPPEARED BETWEEN >HEIGHT MEASURE< AND >SWITCH< <<" << endl;
			break;
		case AFTER_METAL_SENSOR:
			errType = WP_DISAPPEARED_B6;
			cout << ">> WORK PIECE DISAPPEARED BETWEEN >SWITCH< AND >SLIDE< <<" << endl;
			break;
		case AFTER_METAL_SENSOR_FORWARD:
			errType = WP_DISAPPEARED_B7;
			cout << ">> WORK PIECE DISAPPEARED BETWEEN >SWITCH< AND >LAST LIGHT BARRIER< <<" << endl;
			break;
		case AFTER_LAST_LB:
		case ON_FIRST_LB:
			errType = WP_DISAPPEARED_FSM2;
			cout << ">> WORK PIECE DISAPPEARED BETWEEN >SYSTEM1< AND >SYSTEM2< <<" << endl;
			break;
		default:
			cout << ">> WORK PIECE DISAPPEARED >NO ERROR DEFINED< <<" << endl;
		}
	}
	cout << "Puck_FSM::selectErrorType: ErrorType: " << errType << endl;
}

void Puck_FSM::noticed_error_confirmed() {
	if (errorNoticed == true) {
		//		cout << "reset_button_pushed: errorNoticed == true"  << endl;
		location = SORT_OUT;
		errorNoticed = false;
	} else {
		//		cout << "reset_button_pushed: errorNoticed == false"  << endl;
		cout << "Puck_FSM::noticed_error_confirmed(): ERRORTYPE -> " << errType
				<< endl;
		if (errType == SLIDE_FULL_B6) {
			if (hc->checkSlide()) {
				return;
			}
		}
		delete_unnecessary_wp();
		starts_engine_if_nessecary();

		//timer->deleteAllTimer();
//		timer->startAllTimer();
		removeAllLights();
		lamp->shine(GREEN);
		errType = NO_ERROR;
	}
}

void Puck_FSM::puck_fsm2_outgoing() {
	if (request == true) {
		cout
				<< "Puck_FSM::puck_fsm2_outgoing: request true, serial message will be send"
				<< endl;
		serial->send(MACHINE2_FREE, sizeof(msgType));
		cout << "size of list" << puck_list->size() << endl;
		(*puck_list)[0]->setErrorStateTimer(MAX_TIME_FSM2);
		hc->engineContinue();
		request = false;
	}//if
}
void Puck_FSM::delete_unnecessary_wp() {
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->location == SORT_OUT || (*puck_list)[i]->location
				== AFTER_LAST_LB) {
			cout << "Puck_FSM::delete_unnecessary_wp: deleted" << endl;
			puck_list->erase(puck_list->begin() + i);
			//TODO 0prio -- Puck in slide where should shine the lamp?
			//			lamp->shine(GREEN);
		}
	}
	cout << "********** COUNT OF WP´S: " << puck_list->size() << endl;
}

bool Puck_FSM::starts_engine_if_nessecary() {
	int active_state = 0;
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		cout << "Puck_FSM::starts_engine_if_nessecary: errorNoticed: "
				<< errType << endl;
		if ((*puck_list)[i]->errType != NO_ERROR) {
			cout << "Puck_FSM::starts_engine_if_nessecary: inErrorState"
					<< endl;
			return false;
		}
	}

	lamp->shine(GREEN);

	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->engine_should_be_started) {
			cout << "A PUCK NEEDS ENGINE" << endl;
			active_state = 1;
		}
	}
	if (active_state == 1) {
		hc->engineContinue();
		hc->engineRight();
	}

	return true;
}


void Puck_FSM::requestfromMachine1() {
	if (puck_list->size() > 1) {
		//request = true;
		(*puck_list)[0]->request = true;
		cout << "Puck_FSM::requestfromMachine1: request, but wp is on machine"
				<< endl;
	} else {
		serial->send(MACHINE2_FREE, sizeof(msgType));
		cout << "size of list" << puck_list->size() << endl;
		(*puck_list)[0]->setErrorStateTimer(MAX_TIME_FSM2);
		hc->engineContinue();
		hc->engineRight();
	}//if
}
void Puck_FSM::PuckhasPocket() {
	if (puck_list->size() > 1) {
		perror("Puck_FSM_2: Machine2 has more than 1 work pieces");
	} else {
		(*puck_list)[0]->hasPocket = true;
	}//if

}
void Puck_FSM::PuckhasnoPocket() {
	if (puck_list->size() > 1) {
		perror("Puck_FSM_2: Machine2 has more than 1 work pieces");
	} else {
		(*puck_list)[0]->hasPocket = false;
	}//if

}
void Puck_FSM::machine2_free() {
	hc->engineRight();
	hc->engineContinue();
}
void Puck_FSM::puck_arrived() {
	//todo erkennt nicht den fehler -> noch einbaun für den weg zur fsm
	hc->engineStop();
	for (unsigned int i = 0; i < puck_list->size(); i++) {
		if ((*puck_list)[i]->location == AFTER_LAST_LB) {
			serial->send((*puck_list)[i]->hasPocket ? POCKET : NO_POCKET,sizeof(msgType));
			cout << "MaxTimerId is: " << maxTimerId << endl;
			timer->deleteTimer((*puck_list)[i]->maxTimerId);
			cout << "timer->deleteTimer(maxTimerId) puck_arrived:  " << errType << endl;
		}
//		(*puck_list)[i]->ls_b7_out();
	}
	delete_unnecessary_wp();
	starts_engine_if_nessecary();
}

void Puck_FSM::ls_b0() {
	current->ls_b0(this);
}
void Puck_FSM::ls_b1() {
	current->ls_b1(this);
}
void Puck_FSM::ls_b3() {
	current->ls_b3(this);
}
void Puck_FSM::ls_b6() {
	current->ls_b6(this);
}
void Puck_FSM::ls_b7_in() {
	current->ls_b7_in(this);
}
void Puck_FSM::ls_b7_out() {
	current->ls_b7_out(this);
}
void Puck_FSM::reset() {
	current->reset(this);
}
void Puck_FSM::entry() {
	current->entry(this);
}
void Puck_FSM::exit() {
	current->exit(this);
}
void Puck_FSM::setCurrent(State *s) {
	current->exit(this);
	delete current;
	current = s;
	this->entry();
}
void Puck_FSM::errorState() {
	current->errorState(this);
}

//Methods for class State
State::State() {

}

State::~State() {

}

void State::ls_b0(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("ls_b0 standard function\n");
#endif
}

void State::ls_b1(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B1 standard function\n");
#endif
}

void State::ls_b3(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B3 standard function\n");
#endif
}

void State::ls_b6(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B6 standard function\n");
#endif
}

void State::ls_b7_in(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B7_in standard function\n");
#endif
}

void State::ls_b7_out(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("LS_B7_out standard function\n");
#endif
}

void State::entry(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("entry standard function\n");
#endif
}

void State::exit(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("exit standard function\n");
#endif
}

void State::errorState(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("errorState standard function\n");
#endif
}

void State::reset(Puck_FSM * fsm) {
#ifdef PUCK_FSM_STATE_DEBUG
	printf("reset button pushed standard function\n");
#endif
}
