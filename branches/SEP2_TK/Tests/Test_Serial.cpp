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
	s_0 = new Serial();
	s_1 = new Serial();
}

Test_Serial::~Test_Serial() {
	s_0->~Serial();
	s_1->~Serial();
}

void Test_Serial::execute(void*){

	// FALLS NICHT AUSREICHT zum starten... 1 Serial mal ausbauen!

	if (settingUpCommunicatorDevice(DUMMY,NONE)) {
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			cout << "T_S received something..."<<endl;
			handleMessage();
		}
		endCommunication(DUMMY);
/*
		int msg_test = 1;
		bool test_successful = true;
		s_0->init(1,true);
		s_1->init(2,true);

		printf("start s_1\n");
		s_1->start(NULL);

		printf("start s_0\n");
		s_0->start(NULL);

		//s_0->send(&msg_test, sizeof(msg_test));

		sleep(3);

		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();




		printf("\n\n\n start of TEST 1 #######################################\n");
		sleep(1);
		if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 1 gesendet \n") ;}else{printf("s_0 message 1 not cool \n");test_successful = false;}
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		sleep(5);
		if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 1 gesendet\n") ;}else{test_successful = false;}

		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		std::cout << "rcvid: " <<rcvid<< std::endl;
		handleMessage();
							sleep(2);


		printf("\n\n\n start of TEST 2 #######################################\n");
		msg_test = 2;
		if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 2 gesendet\n") ;}else{test_successful = false;}
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 2 gesendet\n");}else{test_successful = false;}
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();
		sleep(2);


		printf("\n\n\n start of TEST 3 #######################################\n");
		msg_test = 5;

		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 3 gesendet\n") ;}else{test_successful = false;}
		if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 3 gesendet\n");}else{test_successful = false;}
		rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
		handleMessage();

		sleep(5);
		printf("\n\n\n###########################################");
		printf("\nTest bestanden: %s\n\n\n",test_successful ? "true" : "false");

		sleep(5);
		s_0->stop();
		sleep(1);
		s_1->stop();
		sleep(1);
		delete s_0;
		delete s_1;
		sleep(10);
*/

	}else{
		cout << "Test_Serial: prepareCommunication failed" << endl;
		return;
	}

}

void Test_Serial::shutdown(){
	s_0->~Serial();
	s_1->~Serial();
}


/*
void Test_Serial::clean(){
	unregisterChannel(DUMMY);
	cleanUp(0, m, r_msg);
	destroyChannel(chid);
}*/

void Test_Serial::handleNormalMessage(){
	std::cout << "chid: " << r_msg->m.chid << " coid: " << r_msg->m.coid <<" Wert: " << r_msg->m.wert <<std::endl;
}

void Test_Serial::handlePulsMessage(){
	std::cout << "Test_Serial: received a Puls, but doesn't know what to do with it" << std::endl;
}

