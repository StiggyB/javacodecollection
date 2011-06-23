/**
 * Sensor
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 3: HAL Sensorik
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Class which deals with the interrupts.
 *
 * Inherits: HAWThread.h
 */
#include "Sensor.h"

//TODO CLEANUP EVERYTHING!!!

Sensor::Sensor() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	h = HALCore::getInstance();
	l = Lampen::getInstance();
	timer = Timer::getInstance();
	/**
	 * Initialize with start values
	 */
	last_Reg_State_B = 0xD3;
	last_Reg_State_C = 0x90;
	running_mode = false;
	mine = SENSOR;
	input_TID = timer->getnextid();
	callDummyFunction = (CallInterface<
			CallBackThrower, void>*) FunctorMaker<Sensor, void>::makeFunctor(
			this, &Sensor::dummyFunction);
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	dummy_fsm = new Puck_FSM_1(&wp_list);
	dummy_fsm->setGlobalUnstoppable = true;

	if (settingUpCommunicatorDevice(INTERRUPTCONTROLLER)) {
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}
		endCommunication();
	} else {
		perror("Sensor: Setting Up failed!");
	}
}

void Sensor::handleNormalMessage() {
	int port = 0;
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, r_msg->m.chid, coid, OK, SENSOR);
	if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
		perror("Sensor: failed to send reply message to IC!");
	}
	if (r_msg->m.ca == react) {
		port = INTERRUPT_D_PORT_B;
	} else if (r_msg->m.ca == reactC) {
		port = INTERRUPT_D_PORT_C_HIGH;
	} else if (r_msg->m.ca == reactSerial) {
		port = INTERRUPT_D_SERIAL;
	}

	//cout << "Sensor: some input m.ca: " << r_msg->m.ca << " val: " << (*r_msg).pulse.value.sival_int << endl;
#ifdef TEST_FSM
	tests_fsm->handleSignal(r_msg->pulse.value.sival_int, port);
#endif
#ifdef TEST_SEN
	ts->test_sen_interrupt(port, r_msg->pulse.value.sival_int);
#endif
#ifndef TEST_SEN
#ifndef TEST_FSM

	int val = (*r_msg).pulse.value.sival_int;

	switch (port) {
	case INTERRUPT_D_PORT_C_HIGH:

		if (!((val >> WP_E_STOP) & 1) && ((last_Reg_State_C >> WP_E_STOP) & 1)) {
			cout << "Sensor: E-Stop Button in" << endl;
			running_mode = false;
			l->removeLight(GREEN);
			dummy_fsm->estop_in_signal(false);

		} else if (((val >> WP_E_STOP) & 1)
				&& !((last_Reg_State_C >> WP_E_STOP) & 1)) {
			cout << "Sensor: E-Stop Button out" << endl;
			dummy_fsm->estop_out_signal(false);
			cout << "Sensor: nach E-Stop Button out" << endl;

		} else if (!((val >> WP_STOP) & 1)) {
			cout << "Sensor: stop Button" << endl;
			dummy_fsm->stop_signal(false);
			running_mode = false;
			l->removeLight(GREEN);
		} else if ((val >> WP_START) & 1) {
			cout << "Sensor: Start Button" << endl;
			dummy_fsm->start_signal(false);
			running_mode = true;

		} else if ((val >> WP_RESET) & 1) {
			cout << "Sensor: Reset Button" << endl;
			running_mode = true;
			if (wp_list.size() == 0) {
				dummy_fsm->reset_signal(false);
			} else {
				for (unsigned int i = 0; i < wp_list.size(); i++) {
					if (wp_list[i]->errType != NO_ERROR) {
						wp_list[i]->reset();
					}
				}
			}//if
		}
		last_Reg_State_C = val;
		break;

	case INTERRUPT_D_SERIAL:
		if (val == MACHINE2_FREE) {
			cout << "Sensor: MACHINE2_FREE" << endl;
			dummy_fsm->machine2_free();
			timer->startAllTimer();

		} else if (val == PUCK_ARRIVED) {
			cout << "Sensor: PUCK_ARRIVED" << endl;
			dummy_fsm->puck_arrived();

		} else if (val == REQUEST_FREE) {
			cout << "Sensor: REQUEST_FREE" << endl;
			wp_list.push_back(new Puck_FSM_2(&wp_list));
			dummy_fsm->requestfromMachine1();

		} else if (val == POCKET) {
			cout << "Sensor: POCKET" << endl;
			dummy_fsm->PuckhasPocket();

		} else if (val == NO_POCKET) {
			cout << "Sensor: NO_POCKET" << endl;
			dummy_fsm->PuckhasnoPocket();

		} else if (val == E_STOP_PUSHED) {
			cout << "Sensor: E_STOP_PUSHED" << endl;
			running_mode = false;
			l->removeLight(GREEN);
			dummy_fsm->estop_in_signal(true);

		} else if (val == E_STOP_PULLED) {
			cout << "Sensor: E_STOP_PULLED" << endl;
			running_mode = true;
			l->shine(GREEN);
			dummy_fsm->estop_out_signal(true);

		} else if (val == STOP_BUTTON) {
			cout << "Sensor: STOP_BUTTON" << endl;
			dummy_fsm->stop_signal(true);
			running_mode = false;
			l->removeLight(GREEN);
		} else if (val == START_BUTTON) {
			cout << "Sensor: START_BUTTON" << endl;
			running_mode = true;
			l->shine(GREEN);
			dummy_fsm->start_signal(true);

		} else if (val == RESET_BUTTON) {
			running_mode = true;
			cout << "Sensor: RESET_BUTTON" << endl;
			dummy_fsm->reset_signal(true);
		} else if(val == ERROR_OCCURED) {
			cout << "Sensor: ERROR_STATE" << endl;
			dummy_fsm->error_arrived_serial();
		} else if (val == ERROR_SOLVED) {
			cout << "Sensor: ERROR_SOLVED" << endl;
			dummy_fsm->error_solved_serial();
		}
		break;

	case INTERRUPT_D_PORT_B:
		if (!running_mode)
			return;

		if (!((val >> WP_RUN_IN) & 1) && ((last_Reg_State_B >> WP_RUN_IN) & 1)) {
			cout << "Sensor: first LB in" << endl;
#ifdef PUCK_FSM_1
			if( timer->existTimer(input_TID) ){
				cout << "!! WORK PIECE TO EARLY INCOMMING!!" << endl;
				cout << "PLEAS REMOVE WORK PIECE FROM FIRST LIGHT BARRIER AND PRESS THE START BUTTON" << endl;
				dummy_fsm->stop_signal(false);
			} else {
				timer->addTimerFunction(callDummyFunction, 800, input_TID);
				wp_list.push_back(new Puck_FSM_1(&wp_list));
				if( !(h->isEngineRunning()) && wp_list.size() > 1){
					timer->stopAll_actual_Timer();
				}
			}

#endif

			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == ON_FIRST_LB) {
					wp_list[i]->ls_b0();
					break;
				}//if
			}//for
		}

//#ifdef PUCK_FSM_1
//		if (((val >> WP_RUN_IN) & 1) && !((last_Reg_State_B >> WP_RUN_IN) & 1)) {
//			cout << "Sensor: first LB out" << endl;
//			if( !(h->isEngineRunning())){
//				if(wp_list.size() > 0) {
//					wp_list.erase( wp_list.begin() + wp_list.size() -1 );
//					timer->deleteAllTimer();
//				}
//			}//if
//		}//if
//#endif
		if (!((val >> WP_IN_HEIGHT) & 1) && ((last_Reg_State_B >> WP_IN_HEIGHT)
				& 1)) {
			cout << "Sensor: in height measure " << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == AFTER_FIRST_LB) {
					wp_list[i]->ls_b1();
					break;
				}//if
			}//for
		}

		if (!((val >> WP_IN_SWITCH) & 1) && ((last_Reg_State_B >> WP_IN_SWITCH)
				& 1)) {
			cout << "Sensor: in metal measure" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == AFTER_HEIGH_MEASURE) {
					wp_list[i]->ls_b3();
					break;
				}//if
			}//for
		}

		if (!((val >> WP_IN_SLIDE) & 1) && ((last_Reg_State_B >> WP_IN_SLIDE)
				& 1)) {
			cout << "Sensor: in slide" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == AFTER_METAL_SENSOR) {
					wp_list[i]->ls_b6();
					break;
				}//if
			}//for
		}

		if (((val >> WP_IN_SLIDE) & 1) && !((last_Reg_State_B >> WP_IN_SLIDE)
				& 1)) {
			cout << "Sensor: work piece in slide removed" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == SORT_OUT) {
					cout << "COUNT OF WORKPIECES: " << wp_list.size() << endl;
					wp_list[i]->ls_b6();
					break;
				}//if
			}//for
		}

		if (!((val >> WP_OUTLET) & 1) && ((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band in" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == AFTER_METAL_SENSOR_FORWARD) {
					wp_list[i]->ls_b7_in();
					break;
				}//if
			}//for
		}

		if (((val >> WP_OUTLET) & 1) && !((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band out" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == ON_LAST_LB ) {
					wp_list[i]->ls_b7_out();
					break;
				}//if
			}//for
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->location == ON_FIRST_LB ) {
					wp_list[i]->ls_b7_out();
					break;
				}//if
			}//for
		}
		last_Reg_State_B = val;
	}//switch
#endif
#endif
#ifdef TEST_IRQ
	interrupt(port, r_msg->pulse.value.sival_int);
#endif
}

void Sensor::handlePulsMessage() {
	std::cout << "Sensor: received a Puls, but doesn't know what to do with it"
			<< std::endl;
}

void Sensor::shutdown() {

}

void Sensor::dummyFunction() {
	cout << "dummyFunction called!" << endl;
}

