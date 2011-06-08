/**
 * Interrupt Controller
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsules many functions for Interrupts using Pulse Messages.
 *
 *
 * Inherits: HAWThread.h
 */

#include "InterruptController.h"

InterruptController::InterruptController() {
	msg =(Message*) malloc(sizeof(Message));
	if(msg == NULL){
		perror("IC: couldn't get space for ISR-Message!");
	}
	h = HALCore::getInstance();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	l = Lampen::getInstance();
	int i = h->getSetInterrupt();
	cout << "InterruptController: first_Interrupt 0x" << hex << i << endl;
	activateInterrupts();
	mine = INTERRUPTCONTROLLER;
}

InterruptController::~InterruptController() {

}

void InterruptController::activateInterrupts() {
	h->deactivateInterrupt(PORT_A);
	int i = h->getSetInterrupt();
	cout << "InterruptController: PortA_reset_Interrupt 0x" << hex << i << endl;
	h->deactivateInterrupt(PORT_B);
	i = h->getSetInterrupt();
	cout << "InterruptController: PortB_reset_Interrupt 0x" << hex << i << endl;
	h->deactivateInterrupt(PORT_C);
	i = h->getSetInterrupt();
	cout << "InterruptController: PortC_reset_Interrupt 0x" << hex << i << endl;
	h->activateInterrupt(PORT_B);
	h->activateInterrupt(PORT_C);
	i = h->getSetInterrupt();
	cout << "InterruptController: PortC_write_Interrupt 0x" << hex << i << endl;
	i = h->getInterrupt();
	cout << "IC: interrupts=" << i << endl;
}

void InterruptController::disconnectFromHAL(){
	if(InterruptDetach(interruptId) == -1){
		perror("InterruptController: failed to detach the Interrupts\n");
	}
	if (ConnectDetach(interruptCoid) == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
	}
	if (ChannelDestroy(interruptChannelId) == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
	}

}

void InterruptController::connectToHAL() {
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
		return;
	}
	cout << "InterruptController: COID for all is =" << coid << endl;
	SIGEV_PULSE_INIT(&(msg->event),coid,SIGEV_PULSE_PRIO_INHERIT,7,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, &(msg->event), sizeof((msg->event)), 0)) == -1) {
		perror("InterruptController: failed to create ISR coupling\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt Attached to event with InterruptCoid="<< interruptCoid << endl;
	int i = h->getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready."<< endl;
}

void InterruptController::execute(void*) {
	cout << "IC: now getting shit up!" << endl;
	if(settingUpCommunicatorDevice(NONE)){
		connectToHAL();
		if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("error for IO Control\n");
			return;
		}
		l->addLight(GREEN);
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}
		disconnectFromHAL();
		endCommunication();
	}
}

void InterruptController::handlePulsMessage() {
	id = getChannelIdForObject(SENSOR);
	coid = getConnectIdForObject(SENSOR);
	// some more Sensors can be added
	if (id != -1 && coid != -1) {
		if (r_msg->pulse.code == INTERRUPT_D_PORT_C_HIGH) {
			buildMessage(m, id, coid, reactC, INTERRUPTCONTROLLER,
					r_msg->pulse.value.sival_int);
		} else { //pulse.code == port B
			buildMessage(m, id, coid, react, INTERRUPTCONTROLLER,
					r_msg->pulse.value.sival_int);
		}
		if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
			perror(
					"InterruptController: failed to send Puls message to Sensor!");
		}
	} else {
		perror("InterruptController: no Sensor available!");
	}
}

void InterruptController::handleNormalMessage() {
	if(!handleConnectionMessage()){
		printf("InterruptController: unknown command in message encountered\n");
	}
}

void InterruptController::shutdown() {
}
