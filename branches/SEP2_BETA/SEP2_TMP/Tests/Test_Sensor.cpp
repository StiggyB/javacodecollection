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

enum PortState {
	RUN_IN_STATE_LOW = 0, RUN_IN_STATE_HIGH = (1<<0), IN_HEIGHT_STATE_LOW = 0, IN_HEIGHT_STATE_HIGH = (1<<1), DEFAULT_HEIGHT = 0,
	IN_SWITCH_STATE_LOW = 0, IN_SWITCH_STATE_HIGH = (1<<3), IS_METAL_STATE = 0, NO_METAL_STATE = (1<<4), SWITCH_OPEN_STATE = (1<<5),
	SWITCH_CLOSED_STATE = 0, IN_SLIDE_STATE_LOW = 0, IN_SLIDE_STATE_HIGH = (1<<6), OUTLET_STATE_LOW = 0, OUTLET_STATE_HIGH = (1<<7)
};

Test_Sensor::Test_Sensor() {

	cc = CoreController::getInstance();
}

Test_Sensor::~Test_Sensor() {

}

void Test_Sensor::shutdown() {

}

//TODO implement MsgReceive/Reply
void Test_Sensor::execute(void*) {
	while(1) {
		//MsgReceive();
		/*
		switch(pluse) {
		case BIT_WP_RUN_IN:
			break;
		}
		*/
	}
	//test_Software_Only();
	test_Operator_Included();

}

bool Test_Sensor::test_sen_b0() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_LOW);
	(*cc).engineSlowRight();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_HIGH);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_LOW);
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_sen_b1() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_LOW);
	test_height_sen_b2();
	res = (*cc).read(PORT_B);
	success &= is_correct_state(2, res, BIT_HEIGHT_1, DEFAULT_HEIGHT);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_HIGH);
	(*cc).engineSlowRight();
	sleep(TIME);
	(*cc).engineStop();
	sleep(5);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_LOW);
	(*cc).engineContinue();
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_height_sen_b2() {
	int height = 0;
	height = (*cc).getHeight();
	cout << "Height: " << height << endl;
	//if(correct height)
	return true;
}

bool Test_Sensor::test_sen_b3() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_LOW);
	test_induct_sen_b4();
	(*cc).openSwitch();
	sleep(TIME);
	test_mag_sen_b5();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_HIGH);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_LOW);
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_induct_sen_b4() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(4, res, BIT_WP_METAL, IS_METAL_STATE);
	return success;
}

bool Test_Sensor::test_mag_sen_b5() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success = is_correct_state(5, res, BIT_SWITCH_OPEN, SWITCH_OPEN_STATE);
	(*cc).engineSlowRight();
	return success;
}
bool Test_Sensor::test_sen_b6() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(6, res, BIT_WP_IN_SLIDE, IN_SLIDE_STATE_LOW);
	(*cc).engineReset();
	return success;
}
bool Test_Sensor::test_sen_b7() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_LOW);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_HIGH);
	(*cc).engineSlowRight();
	sleep(TIME);
	(*cc).engineStop();
	sleep(5);
	res = (*cc).read(PORT_B);
	success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_LOW);
	(*cc).engineContinue();
	(*cc).engineSlowLeft();
	return success;
}

//Only with Height print
void Test_Sensor::test_Operator_Included() {

	bool next_test = true;
	bool section1 = false;
	bool section2 = false;
	bool success = false;
	int height = 0;
	int res = 0;

	cout << "\nSensor with work piece: testing started" << endl;
	(*cc).shine(YELLOW);
	while(1) {
		if (!(portB & BIT_WP_IN_HEIGHT) ) {
			height = (*cc).getHeight();
			cout << "Height: " << height << hex << endl;

		}

		while(section1) {

			if (!(portB & BIT_WP_RUN_IN) && next_test) {
				cout << "Section test1" <<  endl;
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_LOW);
				(*cc).engineSlowRight();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_HIGH);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(0, res, BIT_WP_RUN_IN, RUN_IN_STATE_LOW);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_HEIGHT) && !(next_test)) {
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_LOW);
				height = (*cc).getHeight();
				cout << "Height: " << height << endl;
				res = (*cc).read(PORT_B);
				success &= is_correct_state(2, res, BIT_HEIGHT_1, DEFAULT_HEIGHT);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_HIGH);
				(*cc).engineSlowRight();
				sleep(TIME);
				(*cc).engineStop();
				sleep(5);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(1, res, BIT_WP_IN_HEIGHT, IN_HEIGHT_STATE_LOW);
				(*cc).engineContinue();
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_SWITCH) && next_test) {
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_LOW);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(4, res, BIT_WP_METAL, IS_METAL_STATE);
				(*cc).openSwitch();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success = is_correct_state(5, res, BIT_SWITCH_OPEN, SWITCH_OPEN_STATE);
				(*cc).engineSlowRight();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_HIGH);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(3, res, BIT_WP_IN_SWITCH, IN_SWITCH_STATE_LOW);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_OUTLET) && !(next_test)) {

				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_LOW);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_HIGH);
				(*cc).engineSlowRight();
				sleep(TIME);
				(*cc).engineStop();
				sleep(5);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(7, res, BIT_WP_OUTLET, OUTLET_STATE_LOW);
				(*cc).engineContinue();
				(*cc).engineSlowLeft();
				section1 = false;
				cout << "out" << endl;
			}
		}

		while(section2) {
			//cout << "section2" << endl;
			if (!(portB & BIT_WP_IN_HEIGHT) && next_test) {
				cout << "Section test2" <<  endl;
				next_test = !next_test;
				(*cc).closeSwitch();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= is_correct_state(5, res, BIT_SWITCH_OPEN, SWITCH_CLOSED_STATE);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_SLIDE) && !(next_test)) {
				res = (*cc).read(PORT_B);
				success &= is_correct_state(6, res, BIT_WP_IN_SLIDE, IN_SLIDE_STATE_LOW);
				(*cc).engineReset();
				section2 = false;
				if(success) {
					cout << "Test successful." << endl;
					(*cc).shine(GREEN);
				} else {
					cout << "Test failure." << endl;
					(*cc).shine(RED);
				}
			}
		}
	}
}

//TODO Tests some sensors without hardware
void Test_Sensor::test_Software_Only() {

	int res;
	cout << "\nSensor: testing started" << endl;

	while(1) {
		cout << "TEST B(0)" << endl;
		res = (*cc).read(PORT_B);
		cout << "TEST B(0) SUCCESSFUL" << (res & BIT_WP_RUN_IN) << endl;
		if((res & BIT_WP_RUN_IN) != RUN_IN_STATE_LOW ) {
			cout << "TEST B(0) FAILED" << (res & BIT_WP_RUN_IN) << endl;
		}
		sleep(3);

		cout << "TEST B(1)" << endl;
		res = (*cc).read(PORT_B);
		cout << "TEST B(1) SUCCESSFUL" << (res & BIT_WP_IN_HEIGHT) << endl;
		if((res & BIT_WP_IN_HEIGHT) != IN_HEIGHT_STATE_LOW) {
			cout << "TEST B(1) FAILED" << (res & BIT_WP_IN_HEIGHT) << endl;
		}
		sleep(3);

		cout << "TEST B(2)" << endl;
		res = (*cc).getHeight();
		cout << "TEST B(2) SUCCESSFUL" << res << endl;
		if(res != DEFAULT_HEIGHT) { //how exact is the measure?
			cout << "TEST B(2) FAILED" << res << endl;
		}
		sleep(3);
	}
}

bool Test_Sensor::is_correct_state(int sen_no, int res, const int bit, const int state) {
	if((res & bit) != state ) {
		test_print(sen_no, res, bit, state);
		return false;
	} else {
		test_print(sen_no, res, bit, state);
		return true;
	}
	return false;
}

void Test_Sensor::test_print(int sen_no, int res, const int bit, const int state) {
	cout << "TEST B(" << sen_no << ")" << " RESULT: " << (res & bit) << "=?" << state << endl;
}
