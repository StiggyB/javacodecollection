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
	//cout << "Sensor: attached Connection" << endl;
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, chid, coid, startConnection, SENSOR);
	//cout << "Sensor: message Build" << endl;
	if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Sensor: failed to send message to IC!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}//*/
	//cout << "Sensor: message Send successful!" << endl;
	if (-1 == (id = getChannelIdForObject(INTERRUPTCONTROLLER))) {
		perror("Sensor: failed to get ChannelId!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}
	//cout << "Sensor: Channel id of IC: " << id << endl;#
	while (!isStopped()) {
		//cout << "Sensor: waiting for Interrupt...on chid: "<< chid << " coid: " << coid << endl;
		rcvid = MsgReceive(chid,r_msg, sizeof(Message), NULL);
		//cout << "Sensor: received Message " << endl;
		//cout << "Sensor: Message from IC: CHID=" <<(*r_msg).chid<<" COID="<< (*r_msg).coid<<endl;
		coid = getConnectIdForObject(INTERRUPTCONTROLLER);
		buildMessage(m, (*r_msg).m.chid, coid, OK, SENSOR);
		//cout << "IC: build message complete" << endl;
		if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
			perror("Sensor: failed to send reply message to IC!");
		}//*/
		//cout << "Sensor: react="<<(*r_msg).ca << endl;
		if ((*r_msg).m.ca == react) {
			p = INTERRUPT_D_PORT_B;
		} else {
			//cout << "Sensor: do something else..." << endl;
			p = INTERRUPT_D_PORT_C_HIGH;
		}
		interrupt(p);
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

void Sensor::interrupt(int port) {
	switch (port) {
	case INTERRUPT_D_PORT_B:
		// CA = 1100 1010 ->
		//cout << "Sensor: pB: " << portB << endl;
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
				//cout << " ist metall " << endl;
				if (!(portB & BIT_SWITCH_OPEN)) {
					(*cc).openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(portB & BIT_SLIDE_FULL)) {
			(*cc).stopMachine();
			(*cc).shine(RED);
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
