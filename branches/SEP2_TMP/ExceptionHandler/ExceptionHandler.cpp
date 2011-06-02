/*
 * ExceptionHandler.cpp
 *
 *  Created on: 02.06.2011
 *      Author: Tell
 */

#include "ExceptionHandler.h"

ExceptionHandler::ExceptionHandler() {
	mine = EXCEPTIONHANDLER;
}

ExceptionHandler::~ExceptionHandler() {

}

void ExceptionHandler::execute(void*) {
	if (settingUpCommunicatorDevice(EXCEPTIONHANDLER)) {
		while (!isStopped()) {
			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
			handlePulsMessage();
		}
	} else {
		perror("ExceptionHandler: Setting Up failed!");
		endCommunication();
	}
}

void ExceptionHandler::shutdown() {

}

void ExceptionHandler::handlePulsMessage() {

}

void ExceptionHandler::handleNormalMessage() {

	coid = getConnectIdForObject(/*EXCEPTIONSOURCE*/SENSOR);
	buildMessage(m, r_msg->m.chid, coid, OK, EXCEPTIONHANDLER);
	if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
		perror(
				"ExceptionHandler: failed to send reply message to exception source!");
	}

	int exception = r_msg->pulse.value.sival_int;

	//TODO how to continue after a exception (see exercise page 4).
	//TODO implement different shining for specific acknowledge (see exercise page 5).
	switch (exception) {

	case WP_DISAPPEARED_B1:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	case WP_UNKOWN_B1:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	case WP_DISAPPEARED_B3:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	case WP_UNKOWN_B3:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	case WP_DISAPPEARED_B7:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	case WP_UNKOWN_B7:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;

	case SLIDE_FULL_B6:
		h->engineStop();
		l->shine(RED);
		//ErrorPrint
		break;
	default:
		cout << "ExceptionHandler: Unknown type to handle with." << endl;
	}
}

void ExceptionHandler::handleException(ExceptionType exception) {

	switch (exception) {

	default:
		cout << "ExceptionHandler: Unknown type to handle with." << endl;
	}
}
