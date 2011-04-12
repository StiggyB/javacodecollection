/*
 * Test_HAL.cpp
 *
 *  Created on: 10.04.2011
 *      Author: MQR
 */

#include "Test_HAL.h"

extern CoreController* cc;

Test_HAL::Test_HAL() {
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if(cc == NULL) cc = CoreController::getInstance();
}

Test_HAL::~Test_HAL() {

}

void Test_HAL::shutdown(){

}

void Test_HAL::execute(void*) {
	int time = 3;
	bool t = false;
	cout << "HAL: testing started" << endl;
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		cout << "HAL_T:error for io cntl"<<endl;
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	//(*cc).write(PORT_CNTRL,BIT_CNTRLS,false);
	// Treibe die Ampel
	for (int count = 0; count < 1; count++) {

		cout << "PORTs testen" << endl;
		t = (*cc).isInput(PORT_A);
		cout << "PORT_A is Input? " << t << endl;
		t = (*cc).isInput(PORT_B);
		cout << "PORT_B is Input? " << t << endl;
		t = (*cc).isInput(PORT_C);
		cout << "PORT_C is Intput? " << t << endl;
		t = (*cc).isOutput(PORT_A);
		cout << "PORT_A is Output? " << t << endl;
		t = (*cc).isOutput(PORT_B);
		cout << "PORT_B is Output? " << t << endl;
		t = (*cc).isOutput(PORT_C);
		cout << "PORT_C is Output? " << t << endl;
		sleep(time);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*cc).engineRight();
		sleep(time);

		t = (*cc).engineStopped();
		cout << "Engine Stopped?" << t << endl;

		cout << "ENGINE LEFT" << endl;
		(*cc).engineLeft();
		sleep(time);

		cout << "Engine RIGHT" << endl;
		(*cc).engineStart(BIT_ENGINE_RIGHT);
		sleep(time);

		cout << "ENGINE LEFT" << endl;
		(*cc).engineStart(BIT_ENGINE_LEFT);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*cc).engineSlowSpeed();
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*cc).engineNormalSpeed();
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*cc).engineSpeed(true);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*cc).engineSpeed(false);
		sleep(time);
		cout << "ENGINE SLOW RIGHT" << endl;
		(*cc).engineSlowSpeed(BIT_ENGINE_S_R);
		sleep(time);

		cout << "ENGINE SLOW LEFT" << endl;
		(*cc).engineSlowSpeed(BIT_ENGINE_S_L);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*cc).engineSlowSpeed(BIT_ENGINE_SLOW);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*cc).engineSpeed(false);
		sleep(time);

		cout << "+ENGINE STOP" << endl;
		(*cc).engineStop();
		sleep(time);

		cout << "-ENGINE STOP" << endl;
		(*cc).engineContinue();
		sleep(time);

		cout << "ENGINE S_L" << endl;
		(*cc).engineSlowLeft();
		sleep(time);

		cout << "ENGINE S_R" << endl;
		(*cc).engineSlowRight();
		sleep(time);

		cout << "ENGINE RESET" << endl;
		(*cc).engineReset();
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*cc).openSwitch();
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*cc).closeSwitch();
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*cc).setSwitchDirection(true);
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*cc).setSwitchDirection(false);
		sleep(time);

		cout << "RESET" << endl;
		(*cc).resetAllOutPut();
		sleep(time);
	}
	cout << "HAL: closing..." << endl;
}
