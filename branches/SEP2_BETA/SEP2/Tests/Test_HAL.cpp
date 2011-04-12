/**
 * Testing Class for Milestone #2 - HAL
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the Lights and some other hardware stuff.
 * 1.  Testing the Direction of the Ports.
 * 2.  Turning on engine in right direction.
 * 3.  Ask engine direction.
 * 4.  Turning on engine in left direction.
 * 5.  Turning on engine in right direction.
 * 6.  Turning on engine in left direction.
 * 7.  Turn off lights one at a time.
 * 8.  Slowing the engine.
 * 9.  Getting back to Normal Speed.
 * 10.  Slowing the engine.
 * 11.  Getting back to Normal Speed.
 * 12.  Turning on engine in right direction.
 * 13.  Turning on engine in left direction.
 * 14.  Slowing the engine.
 * 15.  Getting back to Normal Speed.
 * 16.  Stopping the engine.
 * 17.  Starting the engine again.
 * 18.  Setting the engine to slow and left direction.
 * 19. Switching to slow in right direction.
 * 20. Resetting the engine.
 * 21. Opening the switch.
 * 22. Closing the switch.
 * 23. Opening the switch.
 * 24. Closing the switch.
 * 25. Resetting the hardware.
 *
 * Inherits: thread::HAWThread
 */

#include "Test_HAL.h"
/**
 * pointer to the CoreController
 */
extern CoreController* cc;

Test_HAL::Test_HAL() {
	/**
	 * gaining IO privileges
	 */
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	/**
	 * gets a pointer to an instance of the CoreController
	 */
	if (cc == NULL) {
		cc = CoreController::getInstance();
	}
}

Test_HAL::~Test_HAL() {

}

void Test_HAL::shutdown(){

}

void Test_HAL::execute(void*) {
	int time = 3;
	bool t = false;
	cout << "HAL: testing started" << endl;
	// do tests
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
