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

//TODO 2prio -- implement a routine for a teaching piece

Test_Sensor::Test_Sensor()
:lastState(BIT_WP_OUT)
{
	cc = CoreController::getInstance();
}

Test_Sensor::~Test_Sensor() {

}

void Test_Sensor::shutdown() {

}

//could implement MsgReceive/Reply and communication stuff -- later!
void Test_Sensor::execute(void*) {

	//test_Software_Only();
	test_Operator_Included();

}

void Test_Sensor::test_sen(int port) {

	bool success = false;
	int res = 0;
	int height = 0;
	int section = 0;

	switch(port) {
	case INTERRUPT_D_PORT_B:
		if(section == 0) {
			if(!(portB & BIT_WP_RUN_IN)) {
				if(lastState != 0) {
					success &= false;
				}
				cout << "Section test1" <<  endl;
				res = (*cc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*cc).engineSlowRight();
				lastState = BIT_WP_RUN_IN;
			}
			if(!(portB & BIT_WP_IN_HEIGHT)) {
				if(lastState != BIT_WP_RUN_IN) {
					success &= false;
				}
				height = (*cc).identifyHeight();
				cout << "Height: " << height << endl;
				res = (*cc).read(PORT_B);
				success &= assert_equals(2, (res & BIT_HEIGHT_1), PLANE_WP_DEFAULT_HEIGHT);
				lastState = BIT_WP_IN_HEIGHT;
			}

			if (!(portB & BIT_WP_IN_SWITCH)) {
				if(lastState != BIT_WP_IN_HEIGHT) {
					success &= false;
				}
				res = (*cc).read(PORT_B);
				success &= assert_equals(4, (res & BIT_WP_METAL), IS_METAL_STATE);
				(*cc).openSwitch();
				lastState = BIT_WP_IN_SWITCH;
				section++;
			}

			if (!(portB & BIT_WP_OUTLET)) {
				if(lastState != BIT_WP_IN_SWITCH) {
					success &= false;
				}
				res = (*cc).read(PORT_B);
				success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
				(*cc).engineLeft();
				lastState = BIT_WP_OUTLET;
			}
		}
		else if(section == 1) {
			if (!(portB & BIT_WP_IN_HEIGHT)) {
				if(lastState != BIT_WP_IN_SWITCH) {
					success &= false;
				}
				(*cc).closeSwitch();
				res = (*cc).read(PORT_B);
				success &= assert_equals(5, (res & BIT_SWITCH_OPEN), SWITCH_CLOSED_STATE);
				(*cc).engineRight();
				lastState = BIT_WP_IN_HEIGHT;
			}
			if (!(portB & BIT_WP_IN_SWITCH)) {
				if(lastState != BIT_WP_IN_HEIGHT) {
					success &= false;
				}
				lastState = BIT_WP_IN_SWITCH;
				/*do nothing*/
			}

			if (!(portB & BIT_WP_IN_SLIDE)) {
				if(lastState != BIT_WP_IN_SWITCH) {
					success &= false;
				}
				res = (*cc).read(PORT_B);
				success &= assert_equals(6, (res & BIT_WP_IN_SLIDE), IN_SLIDE_STATE_LOW);
				(*cc).engineReset();
				test_isSuccessful(success);
				lastState = BIT_WP_IN_SLIDE;
				section--;
			}
		}
		break;
	case INTERRUPT_D_PORT_C:
		//TODO 0prio -- create a PORTC-Test with Operator
		cout << "Please, push the Emergency Stop as a last" << endl;

		if (!(portC & BIT_E_STOP)) {
			res = (*cc).read(PORT_C);
			success &= assert_equals(7, (res & BIT_E_STOP), BIT_E_STOP_PUSHED);
			(*cc).emergencyStop();
			//Final test isSuccessful()
			test_isSuccessful(success);
		} else if (!(portC & BIT_STOP)) {
			res = (*cc).read(PORT_C);
			success &= assert_equals(5, (res & BIT_STOP), BIT_STOP_PUSHED);
			(*cc).stopMachine();
		} else if (portC & BIT_START) {
			res = (*cc).read(PORT_C);
			success &= assert_equals(4, (res & BIT_START), BIT_START_PUSHED);
			(*cc).restart();
		} else if (portC & BIT_RESET) {
			res = (*cc).read(PORT_C);
			success &= assert_equals(6, (res & BIT_RESET), BIT_RESET_PUSHED);
			(*cc).resetAll();
		}
		break;
	}

}

void Test_Sensor::test_isSuccessful(bool success) {
	if(success) {
		cout << "Test successful." << endl;
		(*cc).shine(GREEN);
	} else {
		cout << "Test failure." << endl;
		(*cc).shine(RED);
	}
}

bool Test_Sensor::assert_equals(int sen_no, int actual, const int state) {
	if(actual != state ) {
		test_print(sen_no, actual, state);
		return false;
	} else {
		test_print(sen_no, actual, state);
		return true;
	}
	return false;
}

void Test_Sensor::test_print(int sen_no, int actual, const int state) {
	cout << "TEST B(" << sen_no << ")" << " RESULT: " << actual << "=?" << state << endl;
}

//Only with Height print
void Test_Sensor::test_Operator_Included() {

	bool next_test = true;
	bool section1 = false;
	bool section2 = false;
	bool success = false;
	int height = 0;
	int res = 0;

	cout << "\nTest_Sensor: work piece included test started" << endl;
	(*cc).shine(YELLOW);
	while(1) {
		cout << "measure" << endl;
		if (!(portB & BIT_WP_IN_HEIGHT) ) {
			height = (*cc).identifyHeight();
			cout << "Height: " << height << endl;
			printf("%d\n", height);
			sleep(TIME);
		}
	}
		while(section1) {

			if (!(portB & BIT_WP_RUN_IN) && next_test) {
				cout << "Section test1" <<  endl;
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*cc).engineSlowRight();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_HIGH);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_HEIGHT) && !(next_test)) {
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
				height = (*cc).identifyHeight();
				cout << "Height: " << height << endl;
				res = (*cc).read(PORT_B);
				success &= assert_equals(2, (res & BIT_HEIGHT_1), PLANE_WP_DEFAULT_HEIGHT);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_HIGH);
				(*cc).engineSlowRight();
				sleep(TIME);
				(*cc).engineStop();
				sleep(5);
				res = (*cc).read(PORT_B);
				success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
				(*cc).engineContinue();
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_SWITCH) && next_test) {
				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
				res = (*cc).read(PORT_B);
				success &= assert_equals(4, (res & BIT_WP_METAL), IS_METAL_STATE);
				(*cc).openSwitch();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success = assert_equals(5, (res & BIT_SWITCH_OPEN), SWITCH_OPEN_STATE);
				(*cc).engineSlowRight();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_HIGH);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_OUTLET) && !(next_test)) {

				next_test = !next_test;
				res = (*cc).read(PORT_B);
				success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
				(*cc).engineSlowLeft();
				sleep(TIME);
				res = (*cc).read(PORT_B);
				success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_HIGH);
				(*cc).engineSlowRight();
				sleep(TIME);
				(*cc).engineStop();
				sleep(5);
				res = (*cc).read(PORT_B);
				success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
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
				success &= assert_equals(5, (res & BIT_SWITCH_OPEN), SWITCH_CLOSED_STATE);
				(*cc).engineSlowRight();
			}

			if (!(portB & BIT_WP_IN_SLIDE) && !(next_test)) {
				res = (*cc).read(PORT_B);
				success &= assert_equals(6, (res & BIT_WP_IN_SLIDE), IN_SLIDE_STATE_LOW);
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

//TODO 2prio -- Tests some sensors without hardware
void Test_Sensor::test_Software_Only() {

	cout << "\nTest_Sensor: software only test started" << endl;

	//send some interrupts and test the reaction of Sensor.cpp
	//createChannel(0);
	//get connection...

	//MsgSend(/*work piece in B(0)*/);
	//
	//assert_equals(0, WP_RUN_IN_STATE, BIT_ENGINE_RIGHT);

	//MsgSend(/*work piece in B(1)*/);
	//
	//assert_equals(1, HEIGHT_MEASURE_STATE, (HEIGHT_MEASURE & (1<<7)/* == 1*/);

	//...
}


// Durch eine Vielzahl von Interrupts sollte jeder Sensor nur 1x geprueft werden
bool Test_Sensor::test_sen_b0() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
	(*cc).engineSlowRight();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_HIGH);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_sen_b1() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
	test_height_sen_b2();
	res = (*cc).read(PORT_B);
	success &= assert_equals(2, (res & BIT_HEIGHT_1), PLANE_WP_DEFAULT_HEIGHT);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_HIGH);
	(*cc).engineSlowRight();
	sleep(TIME);
	(*cc).engineStop();
	sleep(5);
	res = (*cc).read(PORT_B);
	success &= assert_equals(1, (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
	(*cc).engineContinue();
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_height_sen_b2() {
	bool success = false;
	int height = 0;
	height = (*cc).identifyHeight();
	cout << "Height: " << height << endl;
	//TODO 1prio -- test if it is the same in getHeight()!
	if((height <= PLANE_WP_DEFAULT_HEIGHT + tolerance_normal) && (height >= PLANE_WP_DEFAULT_HEIGHT - tolerance_normal)) {
		success = true;
	} else {
		success = false;
	}
	return success;
}

bool Test_Sensor::test_sen_b3() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
	test_induct_sen_b4();
	(*cc).openSwitch();
	sleep(TIME);
	test_mag_sen_b5();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_HIGH);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(3, (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
	(*cc).engineSlowRight();
	return success;
}

bool Test_Sensor::test_induct_sen_b4() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(4, (res & BIT_WP_METAL), IS_METAL_STATE);
	return success;
}

bool Test_Sensor::test_mag_sen_b5() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success = assert_equals(5, (res & BIT_SWITCH_OPEN), SWITCH_OPEN_STATE);
	(*cc).engineSlowRight();
	return success;
}
bool Test_Sensor::test_sen_b6() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(6, (res & BIT_WP_IN_SLIDE), IN_SLIDE_STATE_LOW);
	(*cc).engineReset();
	return success;
}
bool Test_Sensor::test_sen_b7() {
	bool success = false;
	int res = 0;
	res = (*cc).read(PORT_B);
	success &= assert_equals(7,(res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
	(*cc).engineSlowLeft();
	sleep(TIME);
	res = (*cc).read(PORT_B);
	success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_HIGH);
	(*cc).engineSlowRight();
	sleep(TIME);
	(*cc).engineStop();
	sleep(5);
	res = (*cc).read(PORT_B);
	success &= assert_equals(7, (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
	(*cc).engineContinue();
	(*cc).engineSlowLeft();
	return success;
}
