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
	int p = 0;
	if (!setUpChannel()) {
		cout << "Sensor: channel setup failed" << endl;
	} else {
		cout << "Sensor: channel setup successful" << endl;
	}
	if (!registerChannel()) {
		cout << "Sensor: register channel failed" << endl;
	} else {
		cout << "Sensor: register channel successful" << endl;
	}//*/

	if (!requestChannelIDForObject(INTERRUPTCONTROLLER)) {
		cout << "Sensor: request failed" << endl;
	} else {
		cout << "Sensor: request successful" << chid << endl;
	}//*/

	Message * m = (Message *) malloc(sizeof(Message));
	message * r_msg = (message*) malloc(sizeof(message));
	if (r_msg == NULL) {
		perror("Sensor: failed to get Space for Receive Message.");
		return false;
	}
	if ((coid = ConnectAttach(0, 0, id, _NTO_SIDE_CHANNEL, 0)) == -1) {
		perror("Sensor: failed to attach Channel for ID Request\n");
	}
	if (m == NULL) {
		perror("Sensor: failed to get Space for Message.");
		return false;
	}
	if (-1 == buildMessage(m, id, coid, addToServer, c)) {
		perror("Sensor: failed to create Message!");
		return false;
	}
	if (-1 == MsgSend(coid, m, sizeof(m), r_msg, sizeof(r_msg))) {
		perror("Communication: failed to send message to server!");
		return false;
	}//*/

	if (-1 == (id = getChannelIdForObject(INTERRUPTCONTROLLER))) {
		perror("Sensor: failed to get ChannelId!");
	}
	if (!attachConnection(id, INTERRUPTCONTROLLER)){
		perror("Sensor: failed to get ChannelId!");
	}

	while (1) {


		interrupt(p);
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to detach client from server!");
	}
	if (!registerChannel()) {
		cout << "Sensor: register channel failed" << endl;
	} else {
		cout << "Sensor: register channel successful" << endl;
	}//*/
	destroyChannel(chid);
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
