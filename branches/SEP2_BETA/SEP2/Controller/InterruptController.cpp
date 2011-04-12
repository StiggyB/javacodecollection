/*
 * Sensor.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "InterruptController.h"

volatile struct sigevent event;
const struct sigevent *eventptr = (const struct sigevent*) &event;
extern CoreController* cc;

InterruptController::InterruptController() {
	h = HAL::getInstance();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: first_Interrupt 0x" << hex << i << endl;
	activateInterrupts();
}

InterruptController::~InterruptController() {

}

void InterruptController::activateInterrupts() {
	(*h).deactivateInterrupt(PORT_A);
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: PortA_reset_Interrupt 0x" << hex << i << endl;
	(*h).deactivateInterrupt(PORT_B);
	i = (*h).getSetInterrupt();
	cout << "InterruptController: PortB_reset_Interrupt 0x" << hex << i << endl;
	(*h).deactivateInterrupt(PORT_C);
	i = (*h).getSetInterrupt();
	cout << "InterruptController: PortC_reset_Interrupt 0x" << hex << i << endl;
	(*h).activateInterrupt(PORT_B);
	i = (*h).getSetInterrupt();
	cout << "InterruptController: PortB_write_Interrupt 0x" << hex << i << endl;
}

void InterruptController::connectToHAL() {

	if ((chid = ChannelCreate(0)) == -1) {
		perror("InterruptController: failed to create Channel for Interrupt\n");
		shutdown();
	}
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	SIGEV_PULSE_INIT(&event,coid,SIGEV_PULSE_PRIO_INHERIT,SENSOR_PULSE_CODE,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER, ISR, eventptr, sizeof(event), 0)) == -1) {
		perror("InterruptController: failed to create ISR coupling\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt Attached to event with coid=" << coid << endl;
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready." << endl;
}

void InterruptController::execute(void*) {
	connectToHAL();
	handlePulseMessages();
}

void InterruptController::handlePulseMessages() {
	int rcvid;
	while (1) {
		cout << "InterruptController: waiting for Pulse" << endl;
		rcvid = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
		cout << "InterruptController: Pulse received" << endl;
		if (rcvid == -1) {
			perror("InterruptController: failed to get MsgPulse\n");
			shutdown();
		}
		if(pulse.code == SENSOR_PULSE_CODE){
			if(portB & (1<<1)){
				(*cc).engineStop();
				(*cc).engineSlow();
				float f = (*h).getHeight();
				cout << "InterruptController: Hoehe: " << f << endl;
			}

		}
		cout << "InterruptController: pulse code: " << pulse.code << endl;
	}
}

void InterruptController::shutdown() {

}
