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
#include "../FSM/Puck_FSM.h"
#include "../Tests/Test_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include <vector>

Sensor::Sensor() :
	cnt(0) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if (h == NULL) {
		h = HALCore::getInstance();
	}
	l = Lampen::getInstance();
	/**
	 * Initialize with start values
	 */
	last_Reg_State_B = 0xD3;
	last_Reg_State_C = 0x50;
	is_Band_has_wp_ls7 = false;
	request = false;
	mine = SENSOR;
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	serial->init(1, true);
	serial->start(NULL);
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

	int val = (*r_msg).pulse.value.sival_int;

	switch (port) {
	case INTERRUPT_D_PORT_B:
		if (!((val >> WP_RUN_IN) & 1) && ((last_Reg_State_B >> WP_RUN_IN) & 1)) {
			cout << "Sensor: in" << endl;
				#ifdef PUCK_FSM_1
					wp_list.push_back(new Puck_FSM_1(serial, &wp_list));
				#endif
				#ifdef PUCK_FSM_2
					wp_list.push_back(new Puck_FSM_2(serial, &wp_list));
				#endif
				cout << "FSM CREATED" << endl;

			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b0();
			}
		}
		if (!((val >> WP_IN_HEIGHT) & 1) && ((last_Reg_State_B >> WP_IN_HEIGHT)
				& 1)) {
			cout << "Sensor: in height measure " << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b1();
			}
		}
		if (!((val >> WP_IN_SWITCH) & 1) && ((last_Reg_State_B >> WP_IN_SWITCH)
				& 1)) {
			cout << "Sensor: in metal measure" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b3();
			}
		}
		if (!((val >> WP_IN_SLIDE) & 1) && ((last_Reg_State_B >> WP_IN_SLIDE)
				& 1)) {
			cout << "Sensor: in slide" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b6();
			}

		}
		if (!((val >> WP_OUTLET) & 1) && ((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band in" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b7_in();
			}

		}
		if (((val >> WP_OUTLET) & 1) && !((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band out" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b7_out();
			}

		}
		last_Reg_State_B = val;
		break;
	case INTERRUPT_D_PORT_C_HIGH:
		if (!((val >> WP_E_STOP) & 1) && ((last_Reg_State_C >> WP_E_STOP) & 1)) {
			cout << "Sensor: E-Stop Button in" << endl;

		} else if (((val >> WP_E_STOP) & 1)
				&& !((last_Reg_State_C >> WP_E_STOP) & 1)) {
			cout << "Sensor: E-Stop Button out" << endl;

		} else if (!((val >> WP_STOP) & 1)) {
			cout << "Sensor: stop Button" << endl;

		} else if ((val >> WP_START) & 1) {
			cout << "Sensor: Start Button" << endl;

		} else if ((val >> WP_RESET) & 1) {
			cout << "Sensor: Reset Button" << endl;

		}//if
		last_Reg_State_C = val;
		break;

	case INTERRUPT_D_SERIAL:
		if (val == MACHINE2_FREE) {
			if(wp_list.size() >0 ) wp_list[0]->machine2_free();
		} else if (val == PUCK_ARRIVED) {
			if(wp_list.size() >0 ) wp_list[0]->puck_arrived();
		}else if(val == REQUEST_FREE) {
			if(wp_list.size() >0 ) wp_list[0]->requestfromMachine1();
		} else if (val == POCKET) {
			if(wp_list.size() >0 ) wp_list[0]->PuckhasPocket();
		} else if(val == NO_POCKET) {
			if(wp_list.size() >0 ) wp_list[0]->PuckhasnoPocket();
		}//if

	}//switch

#ifdef TEST_FSM
	cout << "TEST_FSM" << endl;
	tests_fsm->handleSignal(r_msg->pulse.value.sival_int, port);
#endif
#ifdef TEST_SEN
	ts.test_sen_interrupt(port, r_msg->pulse.value.sival_int);
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

void Sensor::interrupt(int port, int val) {
	switch (port) {
	case INTERRUPT_D_PORT_B:
		if (!(val & BIT_WP_IN_HEIGHT)) {
			cout << "Sensor: WP_IN_H " << endl;
		}
		if (!(val & BIT_WP_RUN_IN)) {
			h->engineRight();
			cout << "Sensor: BIT_WP_RUN_IN" << endl;
		}
		if (val & BIT_WP_IN_SWITCH) {
			if (val & BIT_SWITCH_STATUS) {
				h->closeSwitch();
				cout << "Sensor: closes switch " << endl;
			}
		} else {
			if (val & BIT_WP_METAL) {
				if (!(val & BIT_SWITCH_STATUS)) {
					h->openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(val & BIT_WP_IN_SLIDE)) {
			cnt++;
			if (cnt == 4) {
				cnt = 0;
				l->shine(RED);
				h->stopMachine();
			}

		}
		if (!(val & BIT_WP_OUTLET)) {
			h->engineReset();
			cout << "Sensor: somethings coming out ;)" << endl;
		}
		break;
	case INTERRUPT_D_PORT_C_HIGH:
		if (!(val & BIT_E_STOP)) {
			l->shine(RED);
			h->emergencyStop();
		} else {
			if (!(val & BIT_STOP)) {
				l->shine(RED);
				h->stopMachine();
			} else {
				if (val & BIT_START) {
					cnt = 0;
					h->shineLED(START_LED);
					l->shine(GREEN);
					h->restart();
				} else {
					h->removeLED(START_LED);

					if (val & BIT_RESET) {
						cnt = 0;
						h->shineLED(RESET_LED);
						h->resetAll();
					} else {
						h->removeLED(RESET_LED);
					}
				}
			}
		}
		break;
	}
}