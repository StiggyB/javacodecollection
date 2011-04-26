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
Message msg;
Mutex InterruptController::singleton;

InterruptController* InterruptController::pInstance = NULL;

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
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
}


InterruptController::InterruptController() {
	h = HAL::getInstance();
	cc = CoreController::getInstance();
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
	/*if ((interruptChannelId = ChannelCreate(0)) == -1) {
		perror("InterruptController: failed to create Channel for Interrupt\n");
		shutdown();
	}*/
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
	}
	cout << "InterruptController: COID for all is =" << coid << endl;
	SIGEV_PULSE_INIT(&msg.Msg.event,coid,SIGEV_PULSE_PRIO_INHERIT,INTERRUPT_D_PORT_B,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, &(msg.Msg.event), sizeof((msg.Msg.event)), 0))
			== -1) {
		cout << "IC: error attaching!" << endl;
		perror("InterruptController: failed to create ISR coupling\n");
		shutdown();
	}
	cout << "InterruptController: Interrupt Attached to event with InterruptCoid="
			<< interruptCoid << endl;
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready."
			<< endl;
}

void InterruptController::execute(void*) {
	cout << "IC: now getting shit up!" << endl;

	//getSensor();
	if(!setUpChannel()){
		cout << "IC: channel setup failed" << endl;
	}else{
		cout << "IC: channel setup successful "<< chid << endl;
 	}
	if(!registerChannel(INTERRUPTCONTROLLER)){
		cout << "IC: register channel failed" << endl;
	}else{
		cout << "IC: register channel successful" << endl;
	}//*/


	//TEST Only
	/*if(!requestChannelIDForObject(INTERRUPTCONTROLLER)){
		cout << "IC: request failed" << endl;
	}else{
		cout << "IC: request successful" << endl;
	}//*/

	connectToHAL();
	handlePulseMessages();
	disconnectFromHAL();
	if (!deregisterChannel(INTERRUPTCONTROLLER)) {
		cout << "IC: register channel failed" << endl;
	} else {
		cout << "IC: register channel successful" << endl;
	}//*/
	destroyChannel(chid);
}

void InterruptController::handlePulseMessages() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		shutdown();
	}
	int rcvid, coid, id;

	//TODO -> attach Connection here

	Message * m = (Message *) malloc(sizeof(Message));
	if (m == NULL) {
		perror("IC: failed to get Space for Message.");
	}
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("IC: failed to get Space for Receive Message.");
	}
	(*cc).addLight(GREEN);
	while (1) {
		cout << "InterruptController: waiting for Pulse on Channel " << chid <<endl;
		rcvid = MsgReceive(chid,r_msg, sizeof(Message), NULL);
		cout << "InterruptController: Message Received" << endl;
		if (rcvid == 0) {
			//pulse inc
			cout << "PulseCode: " << (*r_msg).Msg.event.__sigev_un1.__sigev_signo << endl;
			id = getChannelIdForObject(SENSOR);
			coid = getConnectIdForObject(SENSOR);
			cout << "IC: sending to Sensor: ID=" << id<<" COID="<<coid<<endl;
			if ((*r_msg).Msg.event.__sigev_un1.__sigev_signo == INTERRUPT_D_PORT_C) {
				buildMessage(m, id, coid, reactC, INTERRUPTCONTROLLER);
			} else { //pulse.code == port B
				buildMessage(m, id, coid, react, INTERRUPTCONTROLLER);
			}
			cout << "InterruptController: Message to Sensor: CHID=" <<(*m).chid<<" COID="<< (*m).coid<<endl;
			if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
				perror("InterruptController: failed to send message to server!");
			}//*/
			cout << "IC: send message to Sensor!" << endl;
		}else if (rcvid == -1) {
			perror("InterruptController: failed to get MsgPulse\n");
			shutdown();
		}else{
			//add new Communicator
			if ((*r_msg).ca == startConnection) {
				cout << "IC: adding Sensor: CHID=" <<(*r_msg).chid<<" COID="<< (*r_msg).coid<<endl;
				if (addCommunicator((*r_msg).chid, (*r_msg).coid,(*r_msg).Msg.comtype)) {
					//cout << "IC: adding successful."<<endl;
					buildMessage(m, (*r_msg).chid, (*r_msg).coid, OK,INTERRUPTCONTROLLER);
					//cout << "IC: build message complete" << endl;
					if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
						perror("InterruptController: failed to send reply message to Communicator!");
					}//*/
					cout << "IC: added Communicator" << endl;
				} else {
					perror("IC: failed to addCommunicator");
				}
				if ((coid = ConnectAttach(0, 0, (*r_msg).chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
					perror("InterruptController: failed to attach Channel to other Instance\n");
				}
				(*getCommunicatorForObject((*r_msg).chid,(*r_msg).coid)).setConnectID(coid);
				cout << "IC: connectAttached to other channel on coid: "<<coid <<endl;
			}else if((*r_msg).ca ==  closeConnection){
				if(removeCommunicator((*r_msg).chid, (*r_msg).coid,(*r_msg).Msg.comtype)){
					perror("IC: remove Communicator.");
				}
			} else{
				cout << "message encountered, but not known..." <<endl;
			}

		}

		/*switch(pulse.code){
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
		 */
	}
}

void InterruptController::shutdown() {

}
