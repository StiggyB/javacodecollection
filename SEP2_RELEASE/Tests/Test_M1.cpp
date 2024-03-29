/**
 * Testing Class for Milestone #1
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the Lights and some other hardware stuff.
 * 1.  Add lights after another.
 * 2.  Turn lights off instantly.
 * 3.  Add lights after another.
 * 4.  Turn off lights one at a time.
 * 5.  Turning on engine in right direction.
 * 6.  Turning on engine in left direction.
 * 7.  Slowing the engine.
 * 8.  Getting back to Normal Speed.
 * 8.  Stopping the engine.
 * 9.  Setting the engine to slow and left direction.
 * 10. Switching to slow in right direction.
 * 11. Opening the switch.
 * 12. Closing the switch.
 * 13. Resetting the hardware.
 *
 * Inherits: thread::HAWThread
 */

#include "Test_M1.h"

Test_M1::Test_M1() {
	/**
	 * gaining IO privileges
	 */
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	/**
	 * gets a pointer to an instance of the CoreController
	 */
	h = HALCore::getInstance();
}

Test_M1::~Test_M1() {

}

void Test_M1::shutdown(){

}

/**
 * do the Tests
 */
void Test_M1::execute(void*){
	int time = 3;
	cout << "M1: testing started" << endl;
	// let it start
	cout << "Farben starten: " << endl;
	for (int count = 0; count < 1; count++) {
		// add all lights
		cout << "+rot" << endl;
		(*h).shine(RED);
		sleep(time);

		cout << "+gelb" << endl;
		(*h).shine(YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		(*h).shine(GREEN);
		sleep(time);
		//switches all lights off instantly
		cout << "off" << endl;
		(*h).shine(OFF);
		sleep(time);
		//add all lights
		cout << "+red" << endl;
		(*h).addLight(RED);
		sleep(time);

		cout << "+gelb" << endl;
		(*h).addLight(YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		(*h).addLight(GREEN);
		sleep(time);

		//switch lights off
		cout << "-red" << endl;
		(*h).removeLight(RED);
		sleep(time);

		cout << "-gelb" << endl;
		(*h).removeLight(YELLOW);
		sleep(time);

		cout << "-gruen" << endl;
		(*h).removeLight(GREEN);
		sleep(time);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_RIGHT);
		sleep(time);

		cout << "ENGINE LEFT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_LEFT);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*h).write(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*h).reset(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "+ENGINE STOP" << endl;
		(*h).write(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "-ENGINE STOP" << endl;
		(*h).reset(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "ENGINE S_L" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_L);
		sleep(time);

		cout << "ENGINE S_R" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_R);
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*h).write(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*h).reset(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "RESET" << endl;
		(*h).reset(PORT_A, 0xFF);
		sleep(time);
		(*h).resetAllOutPut();
	}
	cout << "M1: closing..." << endl;
}
