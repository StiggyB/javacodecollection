/**
 * Testing Class for Serial
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Prepares some Testing stuff for the Interrupts.
 *
 * Inherits: thread::HAWThread
 */
#include "Test_Serial.h"

Test_Serial::Test_Serial() {
	msg_test=1;
	mine = TESTER;
}

Test_Serial::~Test_Serial() {
}

void Test_Serial::execute(void*){
	int i = 0;

	if (settingUpCommunicatorDevice(NONE)) {
		printf("TS: chid: %d coid: %d\n",chid,coid);

		printf("start s_1\n");

		printf("start s_0\n");
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			i++;
			handleMessage();
			if (i == 4) {
				printf("s_0 send\n");
			}
		}
		cout << "ending test serial..." <<endl;
		endCommunication();


	}else{
		cout << "Test_Serial: prepareCommunication failed" << endl;
		return;
	}

}

void Test_Serial::shutdown(){
}


/*
void Test_Serial::clean(){
	unregisterChannel(TESTER);
	cleanUp(0, m, r_msg);
	destroyChannel(chid);
}*/

void Test_Serial::handleNormalMessage(){
	std::cout << "chid: " << r_msg->m.chid << " coid: " << r_msg->m.coid <<" Wert: " << r_msg->m.wert <<std::endl;
	if(!handleConnectionMessage()){
		cout << "Test_Serial: can't handle Message"<<endl;
	}
}

void Test_Serial::handlePulsMessage(){
	std::cout<<"Test_Serial: handlePulsMessage enter"<<endl;
	switch (r_msg->pulse.value.sival_int) {
	case SYNC_SIGNAL:
		printf("<<<<<----- Serial: SYNC_SIGNAL :\n");
		break;

		//message from Band 1 to Band 2
	case POCKET:
		printf("<<<<<----- Serial: POCKET an PORT\n");
		break;
	case NO_POCKET:
		printf("<<<<<----- Serial: NO_POCKET an PORT:\n");
		break;
	case REQUEST_FREE:
		printf("<<<<<----- Serial: REQUEST an PORT\n");
		break;

		//message from Band 2 to Band 1
	case MACHINE2_FREE:
		printf("<<<<<----- Serial: BAND2_FREE an PORT\n");
		break;
//	case BAND2_OCCUPIED:
//		printf("<<<<<----- Serial: BAND2_OCCUPIED an PORT: \n");
//		break;
	case PUCK_ARRIVED:
		printf("<<<<<----- Serial: PUK_ARRIVED an PORT: \n");
		break;

		//BUTTONS
	case E_STOP_PUSHED:
		printf("<<<<<----- Serial: E_STOP_PUSHED an PORT: \n");
		break;
	case E_STOP_PULLED:
		printf("<<<<<----- Serial: E_STOP_PULLED an PORT: \n");
		break;
	case STOP_BUTTON:
		printf("<<<<<----- Serial: STOP an PORT: \n");
		break;
	case START_BUTTON:
		printf("<<<<<----- Serial: START an PORT: \n");
		break;
	case RESET_BUTTON:
		printf("<<<<<----- Serial: RESET an PORT: \n");
		break;

		// init message
	case INIT_SERIAL:
		printf("<<<<<----- You want to be my DADDY??? -----> OK\n");
		break;
	case ACK_INIT_SERIAL:
		printf("<<<<<----- Serial: ACK_INIT_SERIAL an PORT: \n");
		break;
	default:
		std::cout << "ERROR: unknown info com" << endl;
		break;
	}//switch
}

