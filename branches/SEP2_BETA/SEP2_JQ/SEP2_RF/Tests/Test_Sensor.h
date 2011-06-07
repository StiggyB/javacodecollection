#ifndef _TEST_SENSOR_H_
#define _TEST_SENSOR_H_
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
 * Tests the sensor system. React to the pulse messages
 * from the interrupt controller. Additional testing of
 * expected values and included reaction from the light.
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
 * Inherits: string, CoreController.h, HAWThread.h
 */

#include <string>
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"

#define TIME 1

/*
 * Some expected values for the tests from port B.
 */
enum PortBState {
	RUN_IN_STATE_LOW = 0, RUN_IN_STATE_HIGH = (1<<0), IN_HEIGHT_STATE_LOW = 0, IN_HEIGHT_STATE_HIGH = (1<<1), PLANE_WP_DEFAULT_HEIGHT = PLANE_WP,
	IN_SWITCH_STATE_LOW = 0, IN_SWITCH_STATE_HIGH = (1<<3), NO_METAL_STATE = 0, IS_METAL_STATE = (1<<4), SWITCH_CLOSED_STATE = 0,
	SWITCH_OPEN_STATE = (1<<5), IN_SLIDE_STATE_LOW = 0, IN_SLIDE_STATE_HIGH = (1<<6), OUTLET_STATE_LOW = 0, OUTLET_STATE_HIGH = (1<<7)
};

/*
 * Some expected values for the tests from port C.
 */
enum PortCState {
	BIT_START_PUSHED = (1<<4), BIT_STOP_PUSHED = 0, BIT_RESET_PUSHED = (1<<6), BIT_E_STOP_PUSHED = 0x1, BIT_E_STOP_LOST = (1<<7)
};

class Test_Sensor : public thread::HAWThread {
public:
	Test_Sensor();
	virtual ~Test_Sensor();
	virtual void execute(void*);
	virtual void shutdown();
	void test_sen_interrupt(int port, int value);
	void test_sen_polling(int port, int value);

private:
	void test_isSuccessful(bool success);
	bool assert_equals(string sen_no, int actual, int state);
	void test_print(string sen_no, int actual, int state);
	bool test_sen_b0();
	bool test_sen_b1();
	bool test_height_sen_b2();
	bool test_sen_b3();
	bool test_induct_sen_b4();
	bool test_mag_sen_b5();
	bool test_sen_b6();
	bool test_sen_b7();

	HALCore *cc;
	PortB last_state_B;
	PortCState last_state_C;
	bool success;
	int section;
	int height;
	int res;
};


#endif /* _TEST_SENSOR_H_ */
