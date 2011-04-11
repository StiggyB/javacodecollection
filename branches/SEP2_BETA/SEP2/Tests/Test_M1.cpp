/*
 * Test_M1.cpp
 *
 *  Created on: 10.04.2011
 *      Author: MQR
 */

#include "Test_M1.h"

extern CoreController* cc;

Test_M1::Test_M1() {
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	cc = CoreController::getInstance();
}

Test_M1::~Test_M1() {

}

void Test_M1::shutdown(){

}

void Test_M1::execute(void*){
	int time = 3;
	/*cout << "M1: starting test" << endl;
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		cout << "HAL_T:error for io cntl"<<endl;
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	//(*h).write(PORT_CNTRL,BIT_CNTRLS,false);
	out8(DIGITAL_CARD_CONTROL, 0x82);
	out8(PORT_A, 0);
	sleep(1);
	out8(PORT_A, 0x80);
	sleep(2);
	out8(PORT_A, 0);
	sleep(5);
	*/
	// Treibe die Ampel
	cout << "Farben starten: " << endl;
	for (int count = 0; count < 1; count++) {
		cout << "+rot" << endl;
		(*cc).shine(RED);
		sleep(time);

		cout << "+gelb" << endl;
		(*cc).shine(YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		(*cc).shine(GREEN);
		sleep(time);
		//aus
		cout << "off" << endl;
		(*cc).shine(OFF);
		sleep(time);
		// alle hinzuschalten
		cout << "+red" << endl;
		(*cc).addLight(RED);
		sleep(time);

		cout << "+gelb" << endl;
		(*cc).addLight(YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		(*cc).addLight(GREEN);
		sleep(time);

		//lampen ausschalten
		cout << "-red" << endl;
		(*cc).removeLight(RED);
		sleep(time);

		cout << "-gelb" << endl;
		(*cc).removeLight(YELLOW);
		sleep(time);

		cout << "-gruen" << endl;
		(*cc).removeLight(GREEN);
		sleep(time);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_RIGHT);
		sleep(time);

		cout << "ENGINE LEFT" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_LEFT);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*cc).reset(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "+ENGINE STOP" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "-ENGINE STOP" << endl;
		(*cc).reset(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "ENGINE S_L" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_S_L);
		sleep(time);

		cout << "ENGINE S_R" << endl;
		(*cc).write(PORT_A, BIT_ENGINE_S_R);
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*cc).write(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*cc).reset(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "RESET" << endl;
		(*cc).reset(PORT_A, 0xFF);
		sleep(time);
		(*cc).resetAllOutPut();
	}
	cout << "M1: closing..." << endl;
}
