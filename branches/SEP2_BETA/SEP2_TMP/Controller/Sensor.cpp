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

//TODO Who is the server between ic and sensor? -- ic -> dispatcher-thread(server) / sensor -> server
//should be the processing part the sensor?

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

void Sensor::execute(void*) {
	//int rcvid;
	while (1) {
		//rcvid = MsgReceive(chid, rmsg, sizeof(rmsg), NULL);
		//MsgReply(rcvid, state, data, sizeof(data));
		//interrupt(data.port);
	}
}

void Sensor::shutdown() {

}

void Sensor::interrupt(int port) {

	switch (port) {
	case INTERRUPT_D_PORT_B:
		// CA = 1100 1010 ->
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
				cout << " ist metall " << endl;
				if (!(portB & BIT_SWITCH_OPEN)) {
					(*cc).openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(portB & BIT_WP_IN_SLIDE)) {
			(*cc).stopMachine();
			(*cc).addLight(RED);
		}
		if (!(portB & BIT_WP_OUTLET)) {
			(*cc).engineReset();
			cout << "Sensor: something coming out ;)" << endl;
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
