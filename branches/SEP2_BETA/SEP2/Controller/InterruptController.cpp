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
	(*h).activateInterrupt(PORT_C);
	i = (*h).getSetInterrupt();
	cout << "InterruptController: PortC_write_Interrupt 0x" << hex << i << endl;
}

void InterruptController::connectToHAL(int port) {

	if ((chid = ChannelCreate(0)) == -1) {
		perror("InterruptController: failed to create Channel for Interrupt\n");
		shutdown();
	}
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	SIGEV_PULSE_INIT(&event,coid,SIGEV_PULSE_PRIO_INHERIT,port,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, eventptr, sizeof(event), 0)) == -1) {
		perror("InterruptController: failed to create ISR coupling\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt Attached to event with coid=" << coid << endl;
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready." << endl;
}

void InterruptController::execute(void*) {
	connectToHAL(INTERRUPT_D_PORT_B);
	connectToHAL(INTERRUPT_D_PORT_C_HIGH);
	handlePulseMessages();
}

/*
 *   = (1<<1),BIT_HEIGHT_1 = (1<<2), = (1<<3),
	BIT_WP_METAL = (1<<4),BIT_SWITCH_OPEN = (1<<5),BIT_SLIDE_FULL = (1<<6),BIT_WP_OUTLET = (1<<7)
};
 */

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
		switch(pulse.code){
		case INTERRUPT_D_PORT_B:
			if (portB & BIT_WP_IN_HEIGHT) {
				(*cc).engineStop();
				(*cc).engineSlowSpeed();
				float f = (*h).getHeight();
				cout << "InterruptController: Hoehe: " << f << endl;
			}
			if (portB & BIT_WP_RUN_IN) {
				(*cc).engineStop();
				(*cc).engineSlowSpeed();
				float f = (*h).getHeight();
				cout << "InterruptController: Hoehe: " << f << endl;
			}

			if (portB & BIT_WP_IN_SWITCH) {
				if(portB & BIT_WP_METAL){
					cout << "IC: ist Metall :D" << endl;
				}
				if(!( portA & BIT_SWITCH_OPEN)){
					(*cc).openSwitch();
					cout << "InterruptController: opens switch " << endl;
				}
			}else {
				if( portA & BIT_SWITCH_OPEN){
					(*cc).closeSwitch();
					cout << "InterruptController: closes switch " << endl;
				}
			}
			if(portB & BIT_SLIDE_FULL){
				(*cc).stopMachine();
				(*cc).addLight(RED);
			}
			if(portB & BIT_WP_OUTLET){
				cout << "IC: somethings coming out ;)" << endl;
			}

			break;
		case INTERRUPT_D_PORT_C_HIGH:
			if(!(portC & BIT_E_STOP)){
				(*cc).emergencyStop();
			}else if(!(portC & BIT_STOP)){
				(*cc).stopMachine();
			}else if(portC & BIT_START){
				(*cc).restart();
			}else if(portC & BIT_RESET){
				(*cc).resetAll();
			}
			break;
		}
		cout << "InterruptController: pulse code: " << pulse.code << endl;
	}
}

void InterruptController::shutdown() {

}
