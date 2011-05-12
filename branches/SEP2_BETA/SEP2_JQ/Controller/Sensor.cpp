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

Sensor::Sensor():cnt(0),p(0),id(0),coid(0){
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if (h == NULL){
		h = HALCore::getInstance();
	}
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	if (settingUpCommunicatorDevice(SENSOR,INTERRUPTCONTROLLER)) {
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}
		endCommunication(SENSOR);
	}else{
		perror("Sensor: Setting Up failed!");
	}
}

void Sensor::handleNormalMessage(){
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, r_msg->m.chid, coid, OK, SENSOR);
	if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
		perror("Sensor: failed to send reply message to IC!");
	}
	if (r_msg->m.ca == react) {
		p = INTERRUPT_D_PORT_B;
	} else {
		p = INTERRUPT_D_PORT_C_HIGH;
	}
	interrupt(p, r_msg->pulse.value.sival_int);
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
			if (val & BIT_SWITCH_OPEN) {
				h->closeSwitch();
				cout << "Sensor: closes switch " << endl;
			}
		} else {
			if (val & BIT_WP_METAL) {
				if (!(val & BIT_SWITCH_OPEN)) {
					h->openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(val & BIT_SLIDE_FULL)) {
			cnt++;
			if(cnt == 4){
				cnt = 0;
				h->shine(RED);
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
			h->emergencyStop();
		} else {
			if (!(val & BIT_STOP)) {
				h->stopMachine();
			} else {
				if (val & BIT_START) {
					cnt = 0;
					h->shineLED(START_LED);
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
