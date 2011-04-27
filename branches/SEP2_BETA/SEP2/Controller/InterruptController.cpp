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
	coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
		return;
	}
	cout << "InterruptController: COID for all is =" << coid << endl;
	SIGEV_PULSE_INIT(&msg.Msg.event,coid,SIGEV_PULSE_PRIO_INHERIT,INTERRUPT_D_PORT_B,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, &(msg.Msg.event), sizeof((msg.Msg.event)), 0)) == -1) {
		perror("InterruptController: failed to create ISR coupling\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt Attached to event with InterruptCoid="<< interruptCoid << endl;
	int i = (*h).getSetInterrupt();
	cout << "InterruptController: Interrupt 0x" << hex << i << " ready."<< endl;
}

void InterruptController::execute(void*) {
	cout << "IC: now getting shit up!" << endl;

	//getSensor();
	if(!setUpChannel()){
		perror("IC: channel setup failed");
		return;
	}else{
		cout << "IC: channel setup successful "<< chid << endl;
 	}
	if(!registerChannel(INTERRUPTCONTROLLER)){
		perror("IC: register channel failed");
		destroyChannel(chid);
		return;
	}else{
		cout << "IC: register channel successful" << endl;
	}

	connectToHAL();
	handlePulseMessages();
	disconnectFromHAL();

	if (!unregisterChannel(INTERRUPTCONTROLLER)) {
		perror("IC: unregister channel failed");
	}
	destroyChannel(chid);
}

void InterruptController::handlePulseMessages() {
	int rcvid, coid, id;
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		return;
	}
	Message * m = (Message *) malloc(sizeof(Message));
	if (m == NULL) {
		perror("IC: failed to get Space for Message.");
	}
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		cleanUp(0,m,NULL);
		perror("IC: failed to get Space for Receive Message.");
		return;
	}
	(*cc).addLight(GREEN);
	while (1) {
	//	cout << "InterruptController: waiting for Pulse on Channel " << chid <<endl;
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		//cout << "InterruptController: Message Received" << endl;
		switch (rcvid) {
		case 0:
			//pulse inc
			//cout << "PulseCode: " << (*r_msg).Msg.event.__sigev_un1.__sigev_signo << endl;
			id = getChannelIdForObject(SENSOR);
			coid = getConnectIdForObject(SENSOR);
			//cout << "IC: sending to Sensor: ID=" << id<<" COID="<<coid<<endl;

			// here can more Sensors be added
			if ((*r_msg).Msg.event.__sigev_un1.__sigev_signo == INTERRUPT_D_PORT_C) {
				buildMessage(m, id, coid, reactC, INTERRUPTCONTROLLER);
			} else { //pulse.code == port B
				buildMessage(m, id, coid, react, INTERRUPTCONTROLLER);
			}
			//cout << "InterruptController: Message to Sensor: CHID=" <<(*m).chid<<" COID="<< (*m).coid<<endl;
			if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
				perror("InterruptController: failed to send message to server!");
			}//*/
			//cout << "IC: send message to Sensor!" << endl;
			break;
		case -1:
			perror("InterruptController: failed to get MsgPulse\n");
			break;
		default:
			//add new Communicator
			if ((*r_msg).ca == startConnection) {
				//cout << "IC: adding Sensor: CHID=" <<(*r_msg).chid<<" COID="<< (*r_msg).coid<<endl;
				if (addCommunicator((*r_msg).chid, (*r_msg).coid,(*r_msg).Msg.comtype)) {
					//cout << "IC: adding successful."<<endl;
					buildMessage(m, (*r_msg).chid, (*r_msg).coid, OK,INTERRUPTCONTROLLER);
					//cout << "IC: build message complete" << endl;
					if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
						perror("InterruptController: failed to send reply message to Communicator!");
					}//*/
					//cout << "IC: added Communicator" << endl;
				} else {
					perror("IC: failed to addCommunicator");
				}
				if ((coid = ConnectAttach(0, 0, (*r_msg).chid,_NTO_SIDE_CHANNEL, 0)) == -1) {
					perror("InterruptController: failed to attach Channel to other Instance\n");
				}
				(*getCommunicatorForObject((*r_msg).chid, (*r_msg).coid)).setConnectID(coid);
				//cout << "IC: connectAttached to other channel on coid: "<<coid <<endl;
			} else if ((*r_msg).ca == closeConnection) {
				if (removeCommunicator((*r_msg).chid, (*r_msg).coid,(*r_msg).Msg.comtype)) {
					perror("IC: remove Communicator.");
				}
			} else {
				cout << "IC: message encountered, but not known..." << endl;
			}
			break;
		}
	}
}

void InterruptController::shutdown() {

}
