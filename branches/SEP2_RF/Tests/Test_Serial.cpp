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
	msg_test = 1;
	mine = TESTER;
	isStopped = false;
	testSuccessful = true;
	testCnt = 0;
}


Test_Serial::~Test_Serial() {
}

void Test_Serial::execute(void*) {
	std::cout << "settingUpCommunicatorDevice#############" << endl;
	if (settingUpCommunicatorDevice(NONE)) {
		std::cout << "settingUpCommunicatorDevice successful#############"
				<< endl;
		//wait that serial get initialized
		sleep(5);
		serial = Serial::getInstance();
		std::cout << "START TESTING SERIAL#############" << endl;
		if (serial->send(START_BUTTON, sizeof(START_BUTTON)) < 0) {
			std::cout << "SERIAL_TEST: ERROR send POCKET" << endl;
		}
		while (!isStopped) {
			cout << "wait for puls" << endl;
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handleMessage();
		}

		if (testSuccessful) {
			std::cout << "Test Succesful" << endl;
		} else {
			std::cout << "Test failed" << endl;
		}
		std::cout << "ending test serial..." << endl;
		endCommunication();

	} else {
		std::cout << "Test_Serial: prepareCommunication failed" << endl;
		return;
	}
	sleep(100);

}

void Test_Serial::shutdown() {
}

/*
 void Test_Serial::clean(){
 unregisterChannel(TESTER);
 cleanUp(0, m, r_msg);
 destroyChannel(chid);
 }*/

void Test_Serial::handleNormalMessage() {
	std::cout << "chid: " << r_msg->m.chid << " coid: " << r_msg->m.coid
			<< " Wert: " << r_msg->m.wert << std::endl;

	if (!handleConnectionMessage()) {
		switch (r_msg->pulse.value.sival_int) {
		case ACK:
			printf("Test_Serial:ACK ->Test Signal erfolgreich versendet\n");
			testCnt++;
			switch (testCnt) {
			case 1:
				if (serial->send(STOP_BUTTON, sizeof(STOP_BUTTON)) < 0) {
					std::cout << "SERIAL_TEST: ERROR send START_BUTTON" << endl;
					testSuccessful = false;
				}
				break;
			case 2:
				if (serial->send(START_BUTTON, sizeof(START_BUTTON)) < 0) {
					std::cout << "SERIAL_TEST: ERROR send START_BUTTON" << endl;
					testSuccessful = false;
				}
				break;
			case 3:
				isStopped = true;
				if (serial->send(STOP_BUTTON, sizeof(STOP_BUTTON)) < 0) {
					std::cout << "SERIAL_TEST: ERROR send START_BUTTON" << endl;
					testSuccessful = false;
				}
				break;
			default:
				std::cout << "SERIAL_TEST: ACK received. End of test" << endl;
				isStopped = true;

			}//switch
			break;
		default:
			std::cout << "TEST_SERIAL: unknown message" << endl;
		}
	}
}

void Test_Serial::handlePulsMessage() {
	std::cout << "TEST_SERIAL: unknown puls message" << endl;
}
