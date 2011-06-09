/*
 * ExampleClass.cpp
 *
 *  Created on: 09.06.2011
 *      Author: jan
 */

//#include "ExampleClass.h"
//
//ExampleClass::ExampleClass() {
//	// TODO Auto-generated constructor stub
//
//}
//
//ExampleClass::~ExampleClass() {
//	// TODO Auto-generated destructor stub
//}
//
//void execute(void *ptr){
//
//	if (settingUpCommunicatorDevice(NONE)) {
//		/* do your own setup... */
//
//		/* listen loop */
//		while (!isStopped()) {
//			rcvid = MsgReceive(chid, r_msg, sizeof(Message), NULL);
//			/* reaction on that message should be              */
//			/* done in handlePulsMessage or handleNormalMessage*/
//			handleMessage();
//			/* possibility to add more own code */
//		}
//		/* close all connections and stuff you opened*/
//
//		endCommunication();
//	}
//}
//
//void ExampleClass::handlePulsMessage() {
//	/* here comes the code that handles a received Pulse Message */
//	/* could be empty or give you an error message or what ever  */
//}
//
//void ExampleClass::handleNormalMessage() {
//	/* here will be the standard reactions done,        */
//	/* like building up a connection, usage recommended */
//	if(!handleConnectionMessage()){
//		/* here can you build your own code or example errors */
//		printf("InterruptController: unknown command in message encountered\n");
//		/* this can also be empty							  */
//	}
//	/* message got handled */
//}
