/**
 * Communication_DUMMY
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * DUMMY to test classes which implements Communication and sends pulses
 *
 *
 * Inherits: HAWThread.h
 */

#include "Communication_DUMMY.h"

Communication_DUMMY::Communication_DUMMY() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("error for DUMMY\n");
		return;
	}
}

Communication_DUMMY::~Communication_DUMMY() {

}


void Communication_DUMMY::execute(void*) {
	cout << "DUMMY: now getting shit up!" << endl;

	if(prepareCommunication(DUMMY)){

//		if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
//			perror("error for DUMMY\n");
//			return;
//		}
		if (!allocMessages()) {
			cleanUp(0, m, r_msg);
			perror("DUMMY: failed to get Space for Messages.");
			return;
		}

//		if(!connectWithCommunicator(0,SERIAL,DUMMY)){
//
//
//		}

		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}


		if (!unregisterChannel(DUMMY)) {
			perror("DUMMY: unregister channel failed");
		}
		destroyChannel(chid);
	}
}

void Communication_DUMMY::handlePulsMessage() {}

void Communication_DUMMY::handleNormalMessage() {
	if (r_msg->m.ca == startConnection) {
		if (addCommunicator(r_msg->m.chid, r_msg->m.coid, r_msg->m.comtype)) {
			buildMessage(m, r_msg->m.chid, r_msg->m.coid, OK,
					INTERRUPTCONTROLLER);
			if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
				perror("DUMMY: failed to send reply message to Communicator!");

			}
			if ((coid = ConnectAttach(0, 0, r_msg->m.chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
				perror("DUMMY: failed to attach Channel to other Instance\n");
			}
			getCommunicatorForObject(r_msg->m.chid, r_msg->m.coid)->setConnectID(coid);
		} else {
			perror("DUMMY: failed to addCommunicator");
		}
	} else if (r_msg->m.ca == closeConnection) {
		if (removeCommunicator(r_msg->m.chid, r_msg->m.coid, r_msg->m.comtype)) {
			perror("DUMMY: remove Communicator.");
		}
	} else {
		cout << "DUMMY: message encountered, but not known..." << endl;
	}

	printf("DUMMY: return handleNormalMessage\n");
}

void Communication_DUMMY::shutdown() {
}
