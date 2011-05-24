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
	s = new Serial();
	/**
	 * Initialize with start values
	 */
	last_Reg_State_B = 0xD3;
	last_Reg_State_C = 0x50;
	is_Band_has_wp_ls7 = false;
	mine = SENSOR;
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	s->init(1, true);
	s->start(NULL);
	if (settingUpCommunicatorDevice(INTERRUPTCONTROLLER)) {
		initPucks();
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}

		endCommunication();
	} else {
		perror("Sensor: Setting Up failed!");
	}
}

void Sensor::initPucks() {
	//int last_Reg_State_B = 0xD3;//defines a standard state of register B
	//int last_Reg_State_C = 0x50;//defines a standard state of register C
	cout << "Sensor: Start" << endl;
	/*Machine1 *fsm;
	 fsm = new Machine1();
	 //fsm->setPocket();*/
}

void Sensor::handleNormalMessage() {
	int port = 0;
#ifdef PUCK_FSM_2
	bool request = false;
#endif
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
			int ls7blocked = 0;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->pass_ls_b7) {
					ls7blocked = 1;
				}
			}
			if (ls7blocked == 0) {
#ifdef PUCK_FSM_1
				wp_list.push_back(new Puck_FSM_1);
#endif
#ifdef PUCK_FSM_2
				wp_list.push_back(new Puck_FSM_2);
				s->send(PUCK_ARRIVED, sizeof(msgType));
#endif
				wp_list[wp_list.size() - 1]->hasPocket = 0;
			}
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
			delete_unnecessary_wp();
			starts_engine_if_nessecary();
		}
		if (!((val >> WP_OUTLET) & 1) && ((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band in" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b7_in();
			}
#ifdef PUCK_FSM_1
			s->send(REQUEST_FREE, 4);
#endif
		}
		if (((val >> WP_OUTLET) & 1) && !((last_Reg_State_B >> WP_OUTLET) & 1)) {
			cout << "Sensor: end of band out" << endl;
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				wp_list[i]->ls_b7_out();
			}
#ifdef PUCK_FSM_2
			delete_unnecessary_wp();
			if(request == true) {
				h->engineContinue();
				s->send(MACHINE2_FREE, sizeof(msgType));
				request = false;
			}
#endif
			starts_engine_if_nessecary();
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

		}
		last_Reg_State_C = val;
		break;
	case INTERRUPT_D_SERIAL:

#ifdef PUCK_FSM_1
		if (val == MACHINE2_FREE) {
			h->engineContinue();
			cout << "Sensor: MACHINE2_FREE" << endl;
		} else if (val == PUCK_ARRIVED) {
			cout << "Sensor: PUCK_ARRIVED" << endl;
			h->engineStop();
			for (unsigned int i = 0; i < wp_list.size(); i++) {
				if (wp_list[i]->pass_ls_b7) {
					s->send(wp_list[i]->hasPocket ? POCKET : NO_POCKET,
							sizeof(msgType));

				}
				wp_list[i]->ls_b7_out();
			}
			delete_unnecessary_wp();
			starts_engine_if_nessecary();
		}
#endif
#ifdef PUCK_FSM_2
		if(val == REQUEST_FREE) {
			cout << "Sensor: REQUEST_FREE" << endl;
			if(wp_list.size() > 0) {
				request = true;
			} else {
				s->send(MACHINE2_FREE, sizeof(msgType));
			}
		} else if (val == POCKET) {
			cout << "Sensor: POCKET" << endl;
			if(wp_list.size() > 1) {
				perror("SENSOR: Machine2 has more than 1 work pieces");
			} else {
				wp_list[0]->hasPocket = true;
			}
		} else if(val == NO_POCKET) {
			cout << "Sensor: NO_POCKET" << endl;
			if(wp_list.size() > 1) {
				perror("SENSOR: Machine2 has more than 1 work pieces");
			} else {
				wp_list[0]->hasPocket = false;
			}
		}

#endif
	}
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

void Sensor::delete_unnecessary_wp() {
	for (unsigned int i = 0; i < wp_list.size(); i++) {
		if (wp_list[i]->pass_ls_b7 || wp_list[i]->pass_ls_b6) {
			cout << "deleted" << endl;
			wp_list.erase(wp_list.begin() + i);
		}
	}
}

void Sensor::starts_engine_if_nessecary() {
	int active_state = 0;
	for (unsigned int i = 0; i < wp_list.size(); i++) {
		if (wp_list[i]->engine_should_be_started) {
			cout << "PUCK FOUND" << endl;
			active_state = 1;
		}
	}
	if (active_state == 1) {
		h->engineContinue();
		h->engineRight();
	}
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
