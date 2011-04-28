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
	msg =(Message*) malloc(sizeof(Message));
	if(msg == NULL){
		perror("IC: couldn't get space for ISR-Message!");
	}
	h = HAL::getInstance();
	cc = CoreController::getInstance();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	int i = (*cc).getSetInterrupt();
	cout << "InterruptController: first_Interrupt 0x" << hex << i << endl;
	activateInterrupts();
}

InterruptController::~InterruptController() {

}


void InterruptController::activateInterrupts() {
	(*cc).deactivateInterrupt(PORT_A);
	int i = (*cc).getSetInterrupt();
	cout << "InterruptController: PortA_reset_Interrupt 0x" << hex << i << endl;
	(*cc).deactivateInterrupt(PORT_B);
	i = (*cc).getSetInterrupt();
	cout << "InterruptController: PortB_reset_Interrupt 0x" << hex << i << endl;
	(*cc).deactivateInterrupt(PORT_C);
	i = (*cc).getSetInterrupt();
	cout << "InterruptController: PortC_reset_Interrupt 0x" << hex << i << endl;
	(*cc).activateInterrupt(PORT_B);
	i = (*cc).getSetInterrupt();
	cout << "InterruptController: PortB_write_Interrupt 0x" << hex << i << endl;
	(*cc).activateInterrupt(PORT_C);
	 i = (*cc).getSetInterrupt();
	 cout << "InterruptController: PortC_write_Interrupt 0x" << hex << i << endl;
	 i = (*cc).getInterrupt();
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
	SIGEV_PULSE_INIT(&((*msg).event),coid,SIGEV_PULSE_PRIO_INHERIT,7,0);
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for IO Control\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt will be attached." << endl;
	if ((interruptId = InterruptAttach(INTERRUPT_VECTOR_NUMMER_D, ISR, &((*msg).event), sizeof(((*msg).event)), 0)) == -1) {
		perror("InterruptController: failed to create ISR coupling\n");
		cleanUp(coid);
		return;
	}
	cout << "InterruptController: Interrupt Attached to event with InterruptCoid="<< interruptCoid << endl;
	int i = (*cc).getSetInterrupt();
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
	//Communication::serverChannelId = chid;
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
	//Message r_msg;
	//struct _pulse r_msg;
	(*cc).addLight(GREEN);
	while (!isStopped()){
	//	cout << "InterruptController: waiting for Pulse on Channel " << chid <<endl;
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		//cout << "InterruptController: Message Received" << endl;
		switch (rcvid) {
		case 0:
			//pulse inc

			//cout << "P_0 COID: " << (*r_msg).pulse.scoid << endl;
			cout << "PC_O: Code: " << (*r_msg).pulse.code << " " << (*r_msg).pulse.value.sival_int << endl;

			/*cout << "P_0 COID: " << r_msg.sigev_coid << endl;
			cout << "P_1 NOTIFIY: " << r_msg.sigev_notify  << " "<< hex << r_msg.sigev_priority <<endl;
			cout << "PC_O: Code: " << r_msg.sigev_code<< " " << r_msg.sigev_value.sival_int << endl;
			 */
			//cout << "PC:" << (*r_msg).event.__sigev_un2.__st.__sigev_code << endl;
			//cout << "PulseCode: " << (*r_msg).event.__sigev_un1.__sigev_signo << endl;
			//cout << "PulseCode: " << (*r_msg).event.__sigev_un2.__st.__sigev_code<< endl;
			id = getChannelIdForObject(SENSOR);
			coid = getConnectIdForObject(SENSOR);
			// here can more Sensors be added
			if(id != -1 && coid != -1){
				if ((*r_msg).pulse.code == INTERRUPT_D_PORT_C_HIGH) {
					buildMessage(m, id, coid, reactC, INTERRUPTCONTROLLER,(*r_msg).pulse.value.sival_int);
					cout << "React C!"<<endl;
				} else { //pulse.code == port B
					buildMessage(m, id, coid, react , INTERRUPTCONTROLLER,(*r_msg).pulse.value.sival_int);
				}
				//cout << "InterruptController: Message to Sensor: CHID=" <<(*m).chid<<" COID="<< (*m).coid<<endl;
				if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
					perror("InterruptController: failed to send Puls message to Sensor!");
				}//*/
				//cout << "IC: send message to Sensor!" << endl;
			}else{
				perror("InterruptController: no Sensor available!");
			}
			break;
		case -1:
			perror("InterruptController: failed to get MsgPulse\n");
			break;
		default:
			//add new Communicator
			if ((*r_msg).m.ca == startConnection) {
				//cout << "IC: adding Sensor: CHID=" <<(*r_msg).chid<<" COID="<< (*r_msg).coid<<endl;
				if (addCommunicator((*r_msg).m.chid, (*r_msg).m.coid,(*r_msg).m.comtype)) {
					//cout << "IC: adding successful."<<endl;
					buildMessage(m, (*r_msg).m.chid, (*r_msg).m.coid, OK,INTERRUPTCONTROLLER);
					//cout << "IC: build message complete" << endl;
					if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
						perror("InterruptController: failed to send reply message to Communicator!");
					}//
					//cout << "IC: added Communicator" << endl;
				} else {
					perror("IC: failed to addCommunicator");
				}
				if ((coid = ConnectAttach(0, 0, (*r_msg).m.chid,_NTO_SIDE_CHANNEL, 0)) == -1) {
					perror("InterruptController: failed to attach Channel to other Instance\n");
				}
				(*getCommunicatorForObject((*r_msg).m.chid, (*r_msg).m.coid)).setConnectID(coid);
				//cout << "IC: connectAttached to other channel on coid: "<<coid <<endl;
			} else if ((*r_msg).m.ca == closeConnection) {
				if (removeCommunicator((*r_msg).m.chid, (*r_msg).m.coid,(*r_msg).m.comtype)) {
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
