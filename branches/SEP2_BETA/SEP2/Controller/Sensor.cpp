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

extern CoreController* cc;

Sensor::Sensor() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if (cc == NULL){
		cc = CoreController::getInstance();
	}
}

Sensor::~Sensor() {

}

//TODO
void Sensor::execute(void*) {
	while (1) {
		int p = 0;
		//MsgReceive();
		interrupt(p);
	}
}

void Sensor::shutdown() {

}

void Sensor::interrupt(int port) {
	switch (port) {
	case INTERRUPT_D_PORT_B:
		cout << "Sensor: pB: " << portB << endl;
		if (!(portB & BIT_WP_IN_HEIGHT)) {
			cout << "Sensor: WP_IN_H " << endl;
		}
		if (!(portB & BIT_WP_RUN_IN)) {
			(*cc).engineRight();
			cout << "Sensor: BIT_WP_RUN_IN" << endl;
		}

		if (portB & BIT_WP_IN_SWITCH) {
			if (portB & BIT_SWITCH_OPEN) {
				(*cc).closeSwitch();
				cout << "Sensor: closes switch " << endl;
			}
		} else {
			if (portB & BIT_WP_METAL) {
				if (!(portB & BIT_SWITCH_OPEN)) {
					(*cc).openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(portB & BIT_SLIDE_FULL)) {
			(*cc).stopMachine();
			(*cc).addLight(RED);
		}
		if (!(portB & BIT_WP_OUTLET)) {
			(*cc).engineReset();
			cout << "Sensor: somethings coming out ;)" << endl;
		}
		break;
	case INTERRUPT_D_PORT_C_HIGH:
		cout << "Sensor: pC: " << portC << endl;
		if (!(portC & BIT_E_STOP)) {
			(*cc).emergencyStop();
		} else if (!(portC & BIT_STOP)) {
			(*cc).stopMachine();
		} else if (portC & BIT_START) {
			(*cc).restart();
		} else if (portC & BIT_RESET) {
			(*cc).resetAll();
		}
		break;
	}
}
