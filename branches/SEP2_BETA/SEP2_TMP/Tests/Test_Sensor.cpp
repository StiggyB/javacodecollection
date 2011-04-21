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
	RUN_IN_STATE_LOW = 0, RUN_IN_STATE_HIGH = (1<<0), IN_HEIGHT_STATE_LOW = 0, IN_HEIGHT_STATE_HIGH = (1<<1), PLANE_WP_DEFAULT_HEIGHT = 2715,
	IN_SWITCH_STATE_LOW = 0, IN_SWITCH_STATE_HIGH = (1<<3), IS_METAL_STATE = 0, NO_METAL_STATE = (1<<4), SWITCH_OPEN_STATE = (1<<5),
	SWITCH_CLOSED_STATE = 0, IN_SLIDE_STATE_LOW = 0, IN_SLIDE_STATE_HIGH = (1<<6), OUTLET_STATE_LOW = 0, OUTLET_STATE_HIGH = (1<<7)
};

//TODO Add some states
enum SensorState {
	RUN_IN_STATE = 1, HEIGHT_MEASURE_STATE = 1 /*,...*/
};

Test_Sensor::Test_Sensor() {

	cc = CoreController::getInstance();
}

Test_Sensor::~Test_Sensor() {

}

void Test_Sensor::shutdown() {

}

//TODO implement MsgReceive/Reply and communication stuff
void Test_Sensor::execute(void*) {

	int coid;
	int rcvid;
	int pulse;
	int id;


	/*
	// Do some communication stuff!!!
	//attachConnection(id, c);

	message * r_msg = (message*) malloc(512);//sizeof(message));
		if (r_msg == NULL) {
			perror("IC: failed to get space for receive message.");
	}

	while(1) {

		//rcvid = MsgReceive(chid, r_msg, sizeof(r_msg), NULL);
		//MsgReply(rcvid, EOK, r_msg, sozeof(r_msg);

		switch(pluse) {
		case BIT_WP_RUN_IN:
		test_sen_b0();
			break;
		}
		case ...



	}
	*/
	//test_Software_Only();
	test_Operator_Included();

}


//TODO Durch eine Vielzahl von Interrupts sollte jeder Sensor nur 1x geprueft werden
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
	height = (*cc).getHeight();
	cout << "Height: " << height << endl;
	//TODO test if it is the same in getHeight()!
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
		if (!(portB & BIT_WP_IN_HEIGHT) ) {
			height = (*cc).getHeight();
			cout << "Height: " << height << hex << endl;

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
				height = (*cc).getHeight();
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
}

//TODO Tests some sensors without hardware
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
