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

Sensor::Sensor():cnt(0) {
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
	settingUpAndWaitingSensor();
}

void Sensor::settingUpAndWaitingSensor(){
	int p = 0,id=0,coid=0,rcvid  = 0;
	if (!setUpChannel()) {
		perror("Sensor: channel setup failed!");
		return;
	}
	if (!registerChannel(SENSOR)) {
		perror("Sensor: register channel failed!");
		return;
	}
	if (!requestChannelIDForObject(INTERRUPTCONTROLLER)) {
		perror("Sensor: request failed");
		unregisterChannel(SENSOR);
		return;
	}
	//TODO: Messages zusammen kleistern
	Message * m = (Message *) malloc(sizeof(Message));
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Sensor: failed to get Space for Receive Message.");
		unregisterChannel(SENSOR);
		cleanUp(0, NULL,NULL);
		destroyChannel(chid);
		return;
	}
	if (m == NULL) {
		perror("Sensor: failed to get Space for Message.");
		unregisterChannel(SENSOR);
		cleanUp(0,NULL,r_msg);
		destroyChannel(chid);
		return;
	}
	id = getChannelIdForObject(INTERRUPTCONTROLLER);
	if (!attachConnection(id, INTERRUPTCONTROLLER)) {
		perror("Sensor: failed to AttachConnection!");
		unregisterChannel(SENSOR);
		cleanUp(0,m,r_msg);
		destroyChannel(chid);
		return;
	}
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, chid, coid, startConnection, SENSOR);
	if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Sensor: failed to send message to IC!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}//*/
	if (-1 == (id = getChannelIdForObject(INTERRUPTCONTROLLER))) {
		perror("Sensor: failed to get ChannelId!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}//TODO: Schleife ausgliedern
	while (!isStopped()) {
		rcvid = MsgReceive(chid,r_msg, sizeof(Message), NULL);
		coid = getConnectIdForObject(INTERRUPTCONTROLLER);
		buildMessage(m, (*r_msg).m.chid, coid, OK, SENSOR);
		if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
			perror("Sensor: failed to send reply message to IC!");
		}//*/
		if ((*r_msg).m.ca == react) {
			p = INTERRUPT_D_PORT_B;
		} else {
			p = INTERRUPT_D_PORT_C_HIGH;
		}
		interrupt(p,(*r_msg).pulse.value.sival_int);
	}
	if (!detachConnection(id,coid,SENSOR)) {
		perror("Sensor: failed to detach Channel for Interrupt\n");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}
	if (!unregisterChannel(SENSOR)) {
		perror("Sensor: register channel failed!");
		cleanUp(coid,m,r_msg);
	}
	cleanUp(0,m,r_msg);
	destroyChannel(chid);
}

void Sensor::shutdown() {

}

void Sensor::interrupt(int port, int val) {
	switch (port) {
	case INTERRUPT_D_PORT_B:

		//cout << "Sensor: pB: " << portB << endl;
		if (!(val & BIT_WP_IN_HEIGHT)) {
			cout << "Sensor: WP_IN_H " << endl;
		}
		if (!(val & BIT_WP_RUN_IN)) {
			(*h).engineRight();
			cout << "Sensor: BIT_WP_RUN_IN" << endl;
		}

		if (val & BIT_WP_IN_SWITCH) {
			if (val & BIT_SWITCH_OPEN) {
				(*h).closeSwitch();
				cout << "Sensor: closes switch " << endl;
			}
		} else {
			if (val & BIT_WP_METAL) {
				//cout << " ist metall " << endl;
				if (!(val & BIT_SWITCH_OPEN)) {
					(*h).openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(val & BIT_SLIDE_FULL)) {
			cnt++;
			if(cnt == 4){
				cnt = 0;
				(*h).shine(RED);
				(*h).stopMachine();
			}

		}
		if (!(val & BIT_WP_OUTLET)) {
			(*h).engineReset();
			cout << "Sensor: somethings coming out ;)" << endl;
		}
		break;
	case INTERRUPT_D_PORT_C_HIGH:
		if (!(val & BIT_E_STOP)) {
			(*h).emergencyStop();
		} else {
			if (!(val & BIT_STOP)) {
				(*h).stopMachine();
			} else {
				if (val & BIT_START) {
					cnt = 0;
					h->shineLED(START_LED);
					(*h).restart();
				} else {
					h->removeLED(START_LED);

					if (val & BIT_RESET) {
						cnt = 0;
						h->shineLED(RESET_LED);
						(*h).resetAll();
					} else {
						h->removeLED(RESET_LED);
					}
				}
			}
		}
		break;
	}
}
