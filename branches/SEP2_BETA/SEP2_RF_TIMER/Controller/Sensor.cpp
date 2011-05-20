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

Sensor::Sensor():cnt(0) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if (h == NULL){
		h = HALCore::getInstance();
	}
	l = Lampen::getInstance();
	is_Band_has_wp_ls7 = false;
	mine = SENSOR;
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	if (settingUpCommunicatorDevice(INTERRUPTCONTROLLER)) {
		initPucks();
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			std::cout << "Sensor: Interrupt" << std::endl;
			handleMessage();
		}
		endCommunication();
	}else{
		perror("Sensor: Setting Up failed!");
	}
}

void Sensor::initPucks(){
	//int last_Reg_State_B = 0xD3;//defines a standard state of register B
	//int last_Reg_State_C = 0x50;//defines a standard state of register C
	cout << "Sensor: Start" << endl;
	/*Machine1 *fsm;
	fsm = new Machine1();
	//fsm->setPocket();*/
	std::vector<Puck_FSM*> wp_list;
}

void Sensor::handleNormalMessage(){
	int port = 0;
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, r_msg->m.chid, coid, OK, SENSOR);
	if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
		perror("Sensor: failed to send reply message to IC!");
	}
	if (r_msg->m.ca == react) {
		port = INTERRUPT_D_PORT_B;
	} else {
		port = INTERRUPT_D_PORT_C_HIGH;
	}
	#ifdef TEST_FSM
	tests_fsm->handleSignal(r_msg->pulse.value.sival_int, port);
	#endif
	#ifdef TEST_SEN
	ts.test_sen_interrupt(port, r_msg->pulse.value.sival_int);
	#endif
	#ifdef TEST_IRQ
	interrupt(port, r_msg->pulse.value.sival_int);
	#endif
}

void Sensor::handlePulsMessage(){
	std::cout << "Sensor: received a Puls, but doesn't know what to do with it" << std::endl;
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
			if(cnt == 4){
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
