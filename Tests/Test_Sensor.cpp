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
 * Tests the sensor system. React to the messages
 * from the interrupt controller. Additional testing of
 * expected values and included reaction from the system.
 *
 * Tests:
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
 * Tests the start button 		C(4)
 * Tests the stop button		C(5)
 * Tests the reset button 		C(6)
 * Tests the emergency button	C(7)
 *
 * Inherits: Test_Sensor.h
 */

#include "Test_Sensor.h"

Test_Sensor::Test_Sensor()
:last_state_B(BIT_WP_OUT), last_state_C(BIT_START_PUSHED),
 success(true), section(0), height(0), res(0)
{
}

Test_Sensor::~Test_Sensor() {

}

void Test_Sensor::shutdown() {

}

void Test_Sensor::execute(void*) {

}

void Test_Sensor::test_sen_interrupt(int port, int value) {

	switch(port) {
	case INTERRUPT_D_PORT_B:
		if(section == 0) {

			if(!(value & BIT_WP_RUN_IN)) {
				if(last_state_B != 0) {
					success &= false;
					cout << "f0" << endl;
				}
				hc->shine(YELLOW);
				cout << "Section test1" <<  endl;
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(0)", (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*hc).engineRight();
				last_state_B = BIT_WP_RUN_IN;
			}
			if(!(value & BIT_WP_IN_HEIGHT)) {
				if(last_state_B != BIT_WP_RUN_IN) {
					success &= false;
					cout << "f12" << endl;
				}
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(1)", (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
				height = (*hc).identifyHeight();
				success &= assert_equals("B(2)", height, PLANE_WP_DEFAULT_HEIGHT);
				res = (*hc).read(PORT_B);
				last_state_B = BIT_WP_IN_HEIGHT;
			}

			if (!(value & BIT_WP_IN_SWITCH) && !(value & BIT_SWITCH_STATUS)) {
				if(last_state_B != BIT_WP_IN_HEIGHT) {
					success &= false;
					cout << "f34" << endl;
				}
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(3)", (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
				success &= assert_equals("B(4)", (res & BIT_WP_METAL), NO_METAL_STATE);
				(*hc).openSwitch();
				last_state_B = BIT_WP_IN_SWITCH;
			}

			if (!(value & BIT_WP_OUTLET)) {
				cout << "B(7)" << endl;
				if(last_state_B != BIT_WP_IN_SWITCH) {
					success &= false;
					cout << "f7" << endl;
				}
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(7)", (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
				(*hc).engineLeft();
				section++;
				last_state_B = BIT_WP_OUTLET;
			}
		}
		else if(section == 1) {

			if (!(value & BIT_WP_IN_SWITCH) && (value & BIT_SWITCH_STATUS)) {
				cout << "Section test2" <<  endl;
				if(last_state_B != BIT_WP_OUTLET) {
					success &= false;
					cout << "f43" << endl;
				}
				last_state_B = BIT_WP_IN_SWITCH;
				/*do nothing*/
			}
			if (!(value & BIT_WP_IN_HEIGHT)&& (value & BIT_SWITCH_STATUS)) {
				if(last_state_B != BIT_WP_IN_SWITCH) {
					success &= false;
					cout << "f5" << endl;
				}
				(*hc).closeSwitch();
				(*hc).engineRight();
				sleep(1);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(5)", (res & BIT_SWITCH_STATUS), SWITCH_CLOSED_STATE);
				last_state_B = BIT_WP_IN_HEIGHT;
			}
			if (!(value & BIT_WP_IN_SLIDE)) {
				if(last_state_B != BIT_WP_IN_HEIGHT) {
					success &= false;
					cout << "f6" << endl;
				}
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(6)", (res & BIT_WP_IN_SLIDE), IN_SLIDE_STATE_LOW);
				(*hc).engineReset();
				test_isSuccessful(success);
				last_state_B = BIT_WP_OUT;
				section--;
				success = true;
				cout << section << endl;
			}
		}
		break;
	case INTERRUPT_D_PORT_C_HIGH:

		if (!(value & BIT_E_STOP) && ((last_state_C == BIT_START_PUSHED) || (last_state_C == BIT_RESET_PUSHED) || (last_state_C == BIT_STOP_PUSHED))) {
			res = (*hc).read(PORT_C);
			success &= assert_equals("C(7)", (res & BIT_E_STOP)+1, BIT_E_STOP_PUSHED); //implement test for BIT_E_STOP_LOST
			(*hc).emergencyStop();
			last_state_C = BIT_E_STOP_PUSHED;
			test_isSuccessful(success);
			//success = true;
			//Final test isSuccessful()
		} else if (value & BIT_E_STOP && (last_state_C == BIT_E_STOP_PUSHED)) {
			res = (*hc).read(PORT_C);
			success &= assert_equals("C(7)", (res & BIT_E_STOP), BIT_E_STOP_LOST);
			last_state_C = BIT_E_STOP_LOST;
			test_isSuccessful(success);
			success = true;

		} else if (!(value & BIT_STOP) && ((last_state_C == BIT_START_PUSHED) || (last_state_C == BIT_RESET_PUSHED))) {
			res = (*hc).read(PORT_C);
			success &= assert_equals("C(5)", (res & BIT_STOP), BIT_STOP_PUSHED);
			(*hc).stopMachine();
			last_state_C = BIT_STOP_PUSHED;
		} else if (value & BIT_START) {
			cout << "Please, push the Emergency Stop as a last" << endl;
			res = (*hc).read(PORT_C);
			success &= assert_equals("C(4)", (res & BIT_START), BIT_START_PUSHED);
			(*hc).restart();
		} else if (value & BIT_RESET) {
			res = (*hc).read(PORT_C);
			success &= assert_equals("C(6)", (res & BIT_RESET), BIT_RESET_PUSHED);
			(*hc).resetAll();
		}
		break;
	}
}

void Test_Sensor::test_isSuccessful(bool success) {
	if(success) {
		cout << "Test successful." << endl;
		(*hc).shine(GREEN);
	} else {
		cout << "Test failure." << endl;
		(*hc).shine(RED);
	}
}

bool Test_Sensor::assert_equals(string sen_no, int actual, const int state) {
	if(actual != state ) {
		test_print(sen_no, actual, state);
		return false;
	} else {
		test_print(sen_no, actual, state);
		return true;
	}
	return false;
}

void Test_Sensor::test_print(string sen_no, int actual, const int state) {
	cout << "TEST " << sen_no << " RESULT: " << actual << "=?" << state << endl;
}

void Test_Sensor::test_sen_polling(int port, int value) {

	bool next_test = true;
	bool section1 = false;
	bool section2 = false;
	bool success = true;
	int height = 0;
	int res = 0;

	cout << "\nTest_Sensor: work piece included test started" << endl;
	(*hc).shine(YELLOW);
	while(1) {

		while(section1) {

			if (!(value & BIT_WP_RUN_IN) && next_test) {
				cout << "Section test1" <<  endl;
				next_test = !next_test;
				res = (*hc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*hc).engineSlowRight();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_HIGH);
				(*hc).engineSlowLeft();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals(0, (res & BIT_WP_RUN_IN), RUN_IN_STATE_LOW);
				(*hc).engineSlowRight();
			}

			if (!(value & BIT_WP_IN_HEIGHT) && !(next_test)) {
				next_test = !next_test;
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(1)", (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
				height = (*hc).identifyHeight();
				cout << "Height: " << height << endl;
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(2)", (res & BIT_HEIGHT_1), PLANE_WP_DEFAULT_HEIGHT);
				(*hc).engineSlowLeft();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(1)", (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_HIGH);
				(*hc).engineSlowRight();
				sleep(DURATION);
				(*hc).engineStop();
				sleep(5);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(1)", (res & BIT_WP_IN_HEIGHT), IN_HEIGHT_STATE_LOW);
				(*hc).engineContinue();
				(*hc).engineSlowRight();
			}

			if (!(value & BIT_WP_IN_SWITCH) && next_test) {
				next_test = !next_test;
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(3)", (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(4)", (res & BIT_WP_METAL), IS_METAL_STATE);
				(*hc).openSwitch();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success = assert_equals("B(5)", (res & BIT_SWITCH_STATUS), SWITCH_OPEN_STATE);
				(*hc).engineSlowRight();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(3)", (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_HIGH);
				(*hc).engineSlowLeft();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(3)", (res & BIT_WP_IN_SWITCH), IN_SWITCH_STATE_LOW);
				(*hc).engineSlowRight();
			}

			if (!(value & BIT_WP_OUTLET) && !(next_test)) {

				next_test = !next_test;
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(7)", (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
				(*hc).engineSlowLeft();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(7)", (res & BIT_WP_OUTLET), OUTLET_STATE_HIGH);
				(*hc).engineSlowRight();
				sleep(DURATION);
				(*hc).engineStop();
				sleep(5);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(7)", (res & BIT_WP_OUTLET), OUTLET_STATE_LOW);
				(*hc).engineContinue();
				(*hc).engineSlowLeft();
				section1 = false;
				cout << "out" << endl;
			}
		}

		while(section2) {
			if (!(value & BIT_WP_IN_HEIGHT) && next_test) {
				cout << "Section test2" <<  endl;
				next_test = !next_test;
				(*hc).closeSwitch();
				sleep(DURATION);
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(5)", (res & BIT_SWITCH_STATUS), SWITCH_CLOSED_STATE);
				(*hc).engineSlowRight();
			}

			if (!(value & BIT_WP_IN_SLIDE) && !(next_test)) {
				res = (*hc).read(PORT_B);
				success &= assert_equals("B(6)", (res & BIT_WP_IN_SLIDE), IN_SLIDE_STATE_LOW);
				(*hc).engineReset();
				section2 = false;
				test_isSuccessful(success);
			}
		}
	}
}
