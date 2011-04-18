/**
 * Test_Sensor
 *
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the sensor system.
 *
 * Software-Tests:
 *
 * Tests the light sensor 		B(0)
 * Tests the light sensor 		B(1)
 * Tests the height-measure 	B(2)
 * Tests the light sensor 		B(3)
 * Tests the inductive sensor 	B(4)
 * Tests the magnetic sensor	B(5)
 * Tests the light sensor 		B(6)
 * Tests the light sensor		B(7)
 *
 *
 * Operator-Tests:
 *
 * Tests the height-measure		B(2)
 * Tests the inductive sensor	B(4)
 * Tests the magnetic sensor	B(5)
 *
 *
 * Inherits: Test_Sensor.h
 */

#include "Test_Sensor.h"

//TODO Write a enum for the various port states

enum PortState {
	RUN_IN_STATE = 1, IN_HEIGHT_STATE = 2, DEFAULT_HEIGHT = 0, IN_SWITCH_STATE = 0,
	IN_SLIDE_STATE = 0, OUTLET_STATE = 0,
};

Test_Sensor::Test_Sensor() {

	cc = CoreController::getInstance();
}

Test_Sensor::~Test_Sensor() {

}

void Test_Sensor::shutdown() {

}

void Test_Sensor::execute(void*) {

	//test_Software_Only();
	test_Operator_Included();

}

//TODO Tests some sensors without hardware
void Test_Sensor::test_Software_Only() {

	int res;
	cout << "\nSensor: testing started" << endl;

	while(1) {
		cout << "TEST B(0)" << endl;
		//(*cc).write(PORT_B, BIT_WP_RUN_IN);
		res = (*cc).read(PORT_B);
		cout << "TEST B(0) SUCCESSFUL" << (res & BIT_WP_RUN_IN) << endl;
		if((res & BIT_WP_RUN_IN) != RUN_IN_STATE ) {
			cout << "TEST B(0) FAILED" << (res & BIT_WP_RUN_IN) << endl;
		}
		sleep(3);

		cout << "TEST B(1)" << endl;
		//(*cc).write(PORT_B, BIT_WP_IN_HEIGHT);
		res = (*cc).read(PORT_B);
		cout << "TEST B(1) SUCCESSFUL" << (res & BIT_WP_IN_HEIGHT) << endl;
		if((res & BIT_WP_IN_HEIGHT) != IN_HEIGHT_STATE) {
			cout << "TEST B(1) FAILED" << (res & BIT_WP_IN_HEIGHT) << endl;
		}
		sleep(3);

		cout << "TEST B(2)" << endl;
		//(*cc).write(PORT_B, BIT_HEIGHT_1);
		res = (*cc).getHeight();
		cout << "TEST B(2) SUCCESSFUL" << res << endl;
		if(res != DEFAULT_HEIGHT) { //how exact is the measure?
			cout << "TEST B(2) FAILED" << res << endl;
		}
		sleep(3);
	}
	/*
	cout << "TEST B(3)" << endl;
	(*cc).write(PORT_B, BIT_WP_IN_SWITCH);
	(*cc).read(PORT_B);

	cout << "TEST B(4)" << endl;
	(*cc).write(PORT_B, BIT_WP_METAL);
	(*cc).read(PORT_B);

	cout << "TEST B(5)" << endl;
	(*cc).write(PORT_B, BIT_SWITCH_OPEN);
	(*cc).read(PORT_B);

	cout << "TEST B(6)" << endl;
	(*cc).write(PORT_B, BIT_WP_IN_SLIDE);
	(*cc).read(PORT_B);

	cout << "TEST B(7)" << endl;
	(*cc).write(PORT_B, BIT_WP_OUTLET);
	(*cc).read(PORT_B);
	*/
}

//TODO Test some sensors with actor action
void Test_Sensor::test_Operator_Included() {
	bool go_on = true;

	cout << "\nSensor with work piece: testing started" << endl;
	while(1) {

	go_on = print_Test("B(0)", (*cc).read(PORT_B));
	if (!(portB & BIT_WP_RUN_IN)) {
		(*cc).engineSlowRight();
	}else if(!(portB & BIT_WP_RUN_IN)) {
		go_on = print_Test("B(1)", (*cc).read(PORT_B));
		(*cc).engineSlowLeft();
	}
	sleep(1);
	//go_on = print_Test("B(2)", (*cc).read(PORT_B));
	}


}

bool Test_Sensor::print_Test(string sen, int res) {

	if((res & BIT_WP_RUN_IN) != RUN_IN_STATE ) {
		cout << "TEST " << " FAILED" << (res & BIT_WP_RUN_IN) << endl;
		return true;
	} else {
		cout << "TEST " << " SUCCESSFUL" << (res & BIT_WP_RUN_IN) << endl;
		return false;
	}
	return false;

}
