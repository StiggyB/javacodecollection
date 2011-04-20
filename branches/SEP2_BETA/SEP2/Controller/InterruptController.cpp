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

//TODO implement handlePulseMasseges

#include "InterruptController.h"

struct sigevent event;

/*InterruptController* InterruptController::pInstance = NULL;

InterruptController* InterruptController::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new InterruptController;
		}
		singleton.unlock();
	}
	return pInstance;
}

void InterruptController::deleteInstance(){
	if( pInstance != null ){
		singleton.lock();
		if( pInstance != null ){
			delete pInstance;
			pInstance = null;
		}
		singleton.unlock();
	}
}
*/

InterruptController::InterruptController() {//: sens() {
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
	 i = (*h).getInterrupt();
	 cout << "IC: interrupts=" << i << endl;
}

void InterruptController::connectToHAL(int port) {

	if ((chid = ChannelCreate(0)) == -1) {
		perror("InterruptController: failed to create Channel for Interrupt\n");
		shutdown();
	}
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
	}
	SIGEV_PULSE_INIT(&event,coid,SIGEV_PULSE_PRIO_INHERIT,port,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	cout << INTERRUPT_VECTOR_NUMMER_D << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, &event, sizeof(event), 0))
			== -1) {
		cout << "IC: error attaching!" << endl;
		perror("InterruptController: failed to create ISR coupling\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt Attached to event with coid="
			<< coid << endl;
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready."
			<< endl;
}

void InterruptController::execute(void*) {
	//getSensor();
	if(!setUpChannel()){
		cout << "IC: channel setup failed" << endl;
	}else{
		cout << "IC: channel setup successful" << endl;
 	}
	if(!registerChannel()){
		cout << "IC: register channel failed" << endl;
	}else{
		cout << "IC: register channel successful" << endl;
	}
	//attachConnection(int id, CommunicatorType c);
	//detachConnection(int id);

	connectToHAL(INTERRUPT_D_PORT_B);
	connectToHAL(INTERRUPT_D_PORT_C_HIGH);
	handlePulseMessages();
}

void InterruptController::getSensor() {

}

void InterruptController::handlePulseMessages() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	/*CoreController *cc = CoreController::getInstance();*/
	int rcvid;
	(*h).addLight(GREEN);
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
			cout << "IC: pB: " << portB << endl;
			if (!(portB & BIT_WP_IN_HEIGHT)) {
				// (*cc).getHeight();
				// test height for correctness
				cout << "InterruptController: WP_IN_H " << endl;
			}
			if (!(portB & BIT_WP_RUN_IN)) {
				(*h).removeLight(YELLOW);
				(*h).engineRight();
				cout << "InterruptController: BIT_WP_RUN_IN" << endl;
			}

			if (portB & BIT_WP_IN_SWITCH) {
				if (portB & BIT_SWITCH_OPEN) {
					(*h).closeSwitch();
					cout << "InterruptController: closes switch " << endl;
				}
			} else {
				if (portB & BIT_WP_METAL) {
					if (!(portB & BIT_SWITCH_OPEN)) {
						(*h).openSwitch();
						cout << "InterruptController: opens switch " << endl;
					}
					cout << "IC: ist Metall :D" << endl;
				}

			}
			if(! (portB & BIT_SLIDE_FULL)){
				//(*h).stopMachine();
				(*h).addLight(YELLOW);
				//Exception handling for isSlideFull() : bool
			}
			if(!(portB & BIT_WP_OUTLET)){
				(*h).engineReset();
				cout << "IC: somethings coming out ;)" << endl;
			}

			break;
		case INTERRUPT_D_PORT_C_HIGH:
			cout << "IC: pC: " << portC << endl;
			if(!(portC & BIT_E_STOP)){
				//(*cc).emergencyStop();
			}else if(!(portC & BIT_STOP)){
				//(*cc).stopMachine();
			}else if(portC & BIT_START){
				//(*cc).restart();
			}else if(portC & BIT_RESET){
				//(*cc).resetAll();
			}
			break;
		}

		// TODO send a message to Sensor
		// sendInterrupt();
		cout << "InterruptController: pulse code: " << hex <<pulse.code << endl;
	}
}

void InterruptController::shutdown() {

}
